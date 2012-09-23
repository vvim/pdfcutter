#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pagestocutdialog.h"
#include "ui_pagestocutdialog.h"
#include <QFileDialog>
#include <QLabel>
#include <QMessageBox>
#include <QListWidgetItem>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->removePageRangeButton->setDisabled(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_choosePDFFile_clicked()
{
    /*
    QStringList filters;
    filters << "PDF files (*.pdf)"
            << "Any files (*)";

    QFileDialog dialog(this);
    dialog.setNameFilters(filters);
    dialog.exec();
    */

    // open Dialog Box
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open PDF om te knippen"), "./", tr("PDF bestanden (*.pdf);;Alle bestanden (*.* *)"));

    // change label if PDF file was chosen
    if(fileName != NULL)
    {
        ui->PDFFileNameLabel->setText(fileName);
    }
    else
    {
        ui->PDFFileNameLabel->setText(tr("...geen PDF gekozen"));
    }
}

void MainWindow::on_addPageRangeButton_clicked()
{
    PagesToCutDialog *pagestocut = new PagesToCutDialog();
    if (pagestocut->exec())
    {
        // exec() is accepted, no click on the CANCEL button
        // if exec() is accepted, than the "CutFrom" and "CutTo" will also be > -1, so we do not have to check for that
        // if exec() is accepted, than the "CutFrom" and "CutTo" will also be within the acceptable page range, so we do not have to check for that
        QString van;
        van = van.setNum(pagestocut->getCutFrom());
        QString tot;
        tot = tot.setNum(pagestocut->getCutTo());

        /*
        // <vvim> controleren of getallen niet >> aantal pagina's van PDF ! </vvim>
        if ((cutTo > MaximumPaginas) || (cutFrom > MaximumPaginas))
        {
        }
        */


        //List items can be inserted automatically into a list, when they are constructed, by specifying the list widget: http://qt-project.org/doc/qt-4.8/qlistwidgetitem.html
        new QListWidgetItem("bereik "+van+" - "+tot, ui->cuttingListWidget);
    }

}

void MainWindow::on_cuttingListWidget_itemClicked(QListWidgetItem *item)
{
    // item selected
    ui->removePageRangeButton->setEnabled(true);
    QMessageBox msgBox;
    msgBox.setText(item->text()+" clicked!");
    msgBox.exec();
}

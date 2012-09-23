#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pagestocutdialog.h"
#include "ui_pagestocutdialog.h"
#include <QFileDialog>
#include <QProcess>
#include <QLabel>
#include <QMessageBox>
#include <QListWidgetItem>
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->addPageRangeButton->setDisabled(true);
    ui->startCuttingProcessButton->setDisabled(true);
    ui->deleteAllPageRangeButton->setDisabled(true);
    ui->cuttingListLabel->setDisabled(true);
    ui->cuttingListWidget->setDisabled(true);

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
        // now we can also enable the functionality of the addPageRangeButton and the startCuttingProcessButton (without a PDF file, they are useless)
        ui->addPageRangeButton->setEnabled(true);
        ui->startCuttingProcessButton->setEnabled(true);
        ui->deleteAllPageRangeButton->setEnabled(true);
        ui->cuttingListLabel->setEnabled(true);
        ui->cuttingListWidget->setEnabled(true);
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

       // ui->cuttingListWidget->addItem( new QListWidgetItem("hazel"));

    }

}

void MainWindow::on_cuttingListWidget_itemClicked(QListWidgetItem *item)
{
    // item selected,removal has to be possible
    ui->removePageRangeButton->setEnabled(true);
}

void MainWindow::on_startCuttingProcessButton_clicked()
{
    if(ui->cuttingListWidget->count() == 0)
    {
        // geen bereik ingegeven, dus waarom in hoofdstukken verknippen?
        QMessageBox msgbox;
        msgbox.setText(tr("Er zijn geen bereiken ingegeven, dus hoe kan ik het PDF bestand dan in hoofdstukken verknippen?"));
        msgbox.setInformativeText(tr("Klik op de knop \"Bereik toevoegen\" om hoofdstukken te definiëren."));
        msgbox.exec();
    }
    else
    {
        /*
                //if (ui->cuttingListWidget->size().height())
        QProcess *proc = new QProcess();
        QString program = "/usr/bin/evince";
        QStringList arguments;
        arguments << ui->PDFFileNameLabel->text();
        proc->execute(program, arguments);
        */
    }
}

void MainWindow::on_removePageRangeButton_clicked()
{
    qDeleteAll(ui->cuttingListWidget->selectedItems()); // see http://lists.trolltech.com/qt-interest/2007-09/thread00253-0.html
    ui->cuttingListWidget->clearSelection(); // don't show any selection (normally the selection shifts, I want it gone
    ui->removePageRangeButton->setDisabled(true);
}

void MainWindow::on_deleteAllPageRangeButton_clicked()
{
    QMessageBox msgBox;

    msgBox.setText(tr("Verwijder alle bereiken."));
    msgBox.setInformativeText(tr("Ben je zeker dat je de hele lijst wilt wissen?"));
    msgBox.setStandardButtons(QMessageBox::Cancel | QMessageBox::YesAll);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    int ret = msgBox.exec();

    if (ret == QMessageBox::YesAll)
    {
        ui->cuttingListWidget->clear();
        ui->removePageRangeButton->setDisabled(true);
    }
}

void MainWindow::keyPressEvent( QKeyEvent *k )
{
    if(k->matches(QKeySequence::Delete))
        on_removePageRangeButton_clicked();
    else if(k->matches(QKeySequence::Open))
        on_choosePDFFile_clicked();
}

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "pagestocutdialog.h"
#include "ui_pagestocutdialog.h"
#include <QFileDialog>
#include <QLabel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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

void MainWindow::on_addCutButton_clicked()
{
    PagesToCutDialog *pagestocut = new PagesToCutDialog();
    pagestocut->show();
}

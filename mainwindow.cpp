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

#define LIST_ITEM_DATA_FROM 1000
#define LIST_ITEM_DATA_TO 1001

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

    ui->statusBar->showMessage(tr("Open een PDF-bestand om te knippen"));
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

        ui->statusBar->showMessage(tr("Nieuw PDF-bestand geopend"));
    }
/*
    DO NOT put an "else". Imagine the scenario that the user has selected a PDF file to cut, than accidentally presses "Open File" again and presses "CANCEL" to correct his error.

    else
    {
        ui->PDFFileNameLabel->setText(tr("...geen PDF gekozen"));
    }
*/
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
//        new QListWidgetItem("A"+van+"-"+tot, ui->cuttingListWidget); // <vvim> quick&dirty PDFTK-hack, maak onderscheid tussen ->text() en ->data()
        //new QListWidgetItem("bereik "+van+" - "+tot, ui->cuttingListWidget);

        QListWidgetItem *newrange = new QListWidgetItem();
        newrange->setData( LIST_ITEM_DATA_FROM ,van);
        newrange->setData( LIST_ITEM_DATA_TO   ,tot);
        newrange->setText(tr("van pagina ")+van+tr(" tot en met ")+tot);
//        newrange->setText("A"+van+"-"+tot);
        ui->cuttingListWidget->addItem(newrange);
        ui->cuttingListWidget->sortItems(); // sorteren? Kan misschien problemen geven met 1, 10, 100...
        ui->statusBar->showMessage(tr("Nieuw paginabereik toegevoegd."));
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
        // disable all buttons to make clear cutting has started. (add status bar?)
        ui->addPageRangeButton->setDisabled(true);
        ui->startCuttingProcessButton->setDisabled(true);
        ui->deleteAllPageRangeButton->setDisabled(true);
        ui->cuttingListLabel->setDisabled(true);
        ui->cuttingListWidget->setDisabled(true);
        ui->statusBar->showMessage(tr("Bezig met knippen van ")+ui->PDFFileNameLabel->text());

        ui->removePageRangeButton->setDisabled(true);

        int teller = 1000; // <vvim> quick & dirty to avoid trouble with 1, 10, 100, ...

        while(ui->cuttingListWidget->count()>0)
        {
            // voor elk item in de lijst, doe: pdftk A=LABEL cat ITEM output hoofdstuk-TELLER.pdf

            QListWidgetItem *temporary_item = ui->cuttingListWidget->takeItem(0);  // takeItem REMOVES and RETURNS, so no extra DELETE needed: http://www.riverbankcomputing.co.uk/static/Docs/PyQt4/html/qlistwidget.html#takeItem
            QString pageranges = "A" + temporary_item->data( LIST_ITEM_DATA_FROM ).toString() + "-" + temporary_item->data( LIST_ITEM_DATA_TO ).toString();

            ///////
            QString t; t = t.setNum(teller);

            QProcess *proc = new QProcess();
            QString program = "echo"; //"pdftk";

            QStringList arguments;
            arguments << "A="+ui->PDFFileNameLabel->text(); // escaping not necessary, QProcess does that
            arguments << "cat" << pageranges << "output" << ui->PDFFileNameLabel->text()+tr("hoofdstuk-")+t+".pdf";

            proc->execute(program, arguments);

            teller++;
        }

        QString t; t = t.setNum(teller-1000);

        ui->statusBar->showMessage(tr("Klaar, ")+t+tr(" hoofdstukken aangemaakt."));

        QMessageBox msgbox;
        msgbox.setText(tr("Klaar, ")+t+tr(" hoofdstukken aangemaakt."));
        msgbox.exec();

    }
}

void MainWindow::on_removePageRangeButton_clicked()
{
    qDeleteAll(ui->cuttingListWidget->selectedItems()); // see http://lists.trolltech.com/qt-interest/2007-09/thread00253-0.html
    ui->cuttingListWidget->clearSelection(); // don't show any selection (normally the selection shifts, I want it gone
    ui->removePageRangeButton->setDisabled(true);
    ui->statusBar->showMessage(tr("Paginabereik verwijderd."));
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
        ui->statusBar->showMessage(tr("Alle paginabereiken verwijderd."));
    }
}

void MainWindow::keyPressEvent( QKeyEvent *k )
{
    if(k->key() == Qt::Key_Delete)
        on_removePageRangeButton_clicked();
    else if(k->matches(QKeySequence::Open))
        on_choosePDFFile_clicked();
    else if (k->key() == Qt::Key_Insert)
        on_addPageRangeButton_clicked();
}

#include "mainwindow.h"
#include "pagerangelistwidgetitem.h"
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
        path_to_PDF = QFileInfo(fileName).absoluteDir();
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

    // enter naming suggestions for the chapters
    namingsuggestions.booktitle = "Joris";
    namingsuggestions.studentlevel = "1";
    namingsuggestions.chapter = "index";
    namingsuggestions.manualtype = "LWB";
    namingsuggestions.pagerange = "p1-2";
    namingsuggestions.pagerange_start = 0;
    namingsuggestions.pagerange_end = 0;
}

void MainWindow::on_addPageRangeButton_clicked()
{
    PagesToCutDialog *pagestocut = new PagesToCutDialog();

    // fill in the naming suggestions:
    pagestocut->setNameBookTitle(namingsuggestions.booktitle);
    pagestocut->setNameStudentLevel(namingsuggestions.studentlevel);
    pagestocut->setNameChapter(namingsuggestions.chapter);
    pagestocut->setNameManualType(namingsuggestions.manualtype);
    //pagestocut->setNamePagerange(namingsuggestions.pagerange_start, namingsuggestions.pagerange_end);
    pagestocut->setNamePagerange(namingsuggestions.pagerange);

    // execute dialog
    if (pagestocut->exec())
    {
        // exec() is accepted, no click on the CANCEL button
        // if exec() is accepted, than the "CutFrom" and "CutTo" will also be > -1, so we do not have to check for that
        // if exec() is accepted, than the "CutFrom" and "CutTo" will also be within the acceptable page range, so we do not have to check for that
        QString page_range_start;
        page_range_start = page_range_start.setNum(pagestocut->getCutFrom());
        QString page_range_end;
        page_range_end = page_range_end.setNum(pagestocut->getCutTo());

        /*
        // <vvim> controleren of getallen niet >> aantal pagina's van PDF ! </vvim>
        if ((cutTo > MaximumPaginas) || (cutFrom > MaximumPaginas))
        {
        }
        */

        //Copy the chapternaming info from the dialogbox to the variable 'namingsuggestions' so that similar suggestions will be given the next time that the dialog box is called
        namingsuggestions.booktitle = pagestocut->getNameBookTitle();
        namingsuggestions.studentlevel = pagestocut->getNameStudentLevel();
        namingsuggestions.chapter = pagestocut->getNameChapter();
        namingsuggestions.manualtype = pagestocut->getNameManualType();
        namingsuggestions.pagerange = pagestocut->getNamePagerange();
        namingsuggestions.pagerange_start = pagestocut->getNamePagerangeStart();
        namingsuggestions.pagerange_end = pagestocut->getNamePagerangeEnd();

        //List items can be inserted automatically into a list, when they are constructed, by specifying the list widget: http://qt-project.org/doc/qt-4.8/qlistwidgetitem.html
        PageRangeListWidgetItem *newrange = new PageRangeListWidgetItem();
        newrange->setPageRangeStart(pagestocut->getCutFrom());
        newrange->setPageRangeEnd(pagestocut->getCutTo());
        newrange->setChapterNaming(namingsuggestions);
        newrange->setText("["+page_range_start+"-"+page_range_end+"] "+newrange->getChaptertoString());
        ui->cuttingListWidget->addItem(newrange);
        ui->cuttingListWidget->sortItems(); // sorteren? Kan misschien problemen geven met 1, 10, 100...
        ui->statusBar->showMessage(tr("Nieuw paginabereik toegevoegd."));

        // <vvim> IF getnamechapter().IsInt() => suggestion == chapter++

        // <vvim> namingsuggestions.pagerange_start = pagerange_end + 1!! (misschien ook de CutFrom aanpassen???)
        namingsuggestions.pagerange_start = namingsuggestions.pagerange_end + 1;

        int average_chapter_length = 10;
        namingsuggestions.pagerange_end = namingsuggestions.pagerange_start + average_chapter_length;
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

        int teller = 1001; // <vvim> quick & dirty to avoid trouble with 1, 10, 100, ...

        while(ui->cuttingListWidget->count()>0)
        {
            // voor elk item in de lijst, doe: pdftk A=LABEL cat ITEM output hoofdstuk-TELLER.pdf

            PageRangeListWidgetItem *temporary_item = (PageRangeListWidgetItem*) ui->cuttingListWidget->takeItem(0);  // takeItem REMOVES and RETURNS, so no extra DELETE needed: http://www.riverbankcomputing.co.uk/static/Docs/PyQt4/html/qlistwidget.html#takeItem
            QString pageranges = temporary_item->getPDFtkPageRange(); // = "A" + temporary_item->data( LIST_ITEM_DATA_FROM ).toString() + "-" + temporary_item->data( LIST_ITEM_DATA_TO ).toString();

            ///////
            QString t; t = t.setNum(teller);

            QProcess *proc = new QProcess();
            QString program = "pdftk";

            QStringList arguments;
            arguments << "A="+ui->PDFFileNameLabel->text(); // escaping not necessary, QProcess does that
            arguments << "cat" << pageranges << "output" << path_to_PDF.absolutePath() + "/" + temporary_item->getChaptertoString()+".pdf";

            proc->execute(program, arguments);

            teller++;
        }

        QString t; t = t.setNum(teller-1001);

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

#include <QMessageBox>
#include "pagestocutdialog.h"
#include "ui_pagestocutdialog.h"

PagesToCutDialog::PagesToCutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PagesToCutDialog)
{
    ui->setupUi(this);
    inputValidated = false;
}

PagesToCutDialog::~PagesToCutDialog()
{
    delete ui;
}

int PagesToCutDialog::getCutFrom()
{
    if (inputValidated)
            return ui->CutFromSpinBox->value();
    else
        return -1;
}

int PagesToCutDialog::getCutTo()
{
    if (inputValidated)
        return ui->CutToSpinBox->value();
    else
        return -1;
}

void PagesToCutDialog::on_buttonBox_accepted()
{
    int cutFrom = ui->CutFromSpinBox->value();
    int cutTo = ui->CutToSpinBox->value();

    if (cutTo < cutFrom)
    {
        // impossible range: error!
        QMessageBox msgBox;
        msgBox.setText(tr("Het paginabereik is incorrect:\n\nde 'van'-pagina kan niet hoger zijn dan de 'tot en met'-pagina."));
        msgBox.exec();
    }
    /*
    // <vvim> controleren of getallen niet >> aantal pagina's van PDF ! </vvim>
    else if ((cutTo > MaximumPaginas) || (cutFrom > MaximumPaginas))
    {
    }
    */
    else
    {
        // all fine! set "inputValidated" so that the functions "getCut*" can pass the value to the mainwindow
        inputValidated = true;
        this->accept();
    }
}

void PagesToCutDialog::on_buttonBox_rejected()
{
    this->reject();
}


void PagesToCutDialog::SetNameBookTitle(QString booktitle)
{
    ui->NameBookTitle->setText(booktitle);
}

QString PagesToCutDialog::GetNameBookTitle()
{
    return ui->NameBookTitle->text();
}

void PagesToCutDialog::SetNameStudentLevel(QString studentlevel)
{
    ui->NameStudentLevel->setText(studentlevel);
}

QString PagesToCutDialog::GetNameStudentLevel()
{
    return ui->NameStudentLevel->text();
}

void PagesToCutDialog::SetNameChapter(QString chapter)
{
    ui->NameChapter->setText(chapter);
}

QString PagesToCutDialog::GetNameChapter()
{
    return ui->NameChapter->text();
}

void PagesToCutDialog::SetNameManualType(QString manualtype)
{
    ui->NameManualType->setText(manualtype);
}

QString PagesToCutDialog::GetNameManualType()
{
    return ui->NameChapter->text();
}

void PagesToCutDialog::SetNamePagerange(int pagerange_start, int pagerange_end)
{
    ui->NamePageRange->setText("p0-0"); // ("p"+pagerange_start+"-"+pagerange_end);
}

int PagesToCutDialog::GetNamePagerangeStart()
{
    /*
    if ui->NamePageRange->text() is of the type p<int>-<int>
            return <int>
    else
    */
            return 0;
}

int PagesToCutDialog::GetNamePagerangeEnd()
{
    /*
    if ui->NamePageRange->text() is of the type p<int>-<int>
            return <int>
    else
    */
            return 0;
}

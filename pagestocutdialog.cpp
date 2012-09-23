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

#include <QMessageBox>
#include "pagestocutdialog.h"
#include "ui_pagestocutdialog.h"

PagesToCutDialog::PagesToCutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PagesToCutDialog)
{
    ui->setupUi(this);
}

PagesToCutDialog::~PagesToCutDialog()
{
    delete ui;
}


void PagesToCutDialog::on_buttonBox_clicked(QAbstractButton *button)
{
    int cutFrom = ui->CutFromSpinBox->value();
    int cutTo = ui->CutToSpinBox->value();

    if (cutTo < cutFrom)
    {
        QMessageBox msgBox;
        msgBox.setText(tr("Het paginabereik is incorrect:\n\nde 'van'-pagina kan niet hoger zijn dan de 'tot en met'-pagina."));
        msgBox.exec();
    }

    /*
    // <vvim> controleren of getallen niet >> aantal pagina's van PDF ! </vvim>
    if ((cutTo > MaximumPaginas) || (cutFrom > MaximumPaginas))
    {
    }
    */

}

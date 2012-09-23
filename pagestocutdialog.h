#ifndef PAGESTOCUTDIALOG_H
#define PAGESTOCUTDIALOG_H

#include <QDialog>
#include <QAbstractButton>

namespace Ui {
    class PagesToCutDialog;
}

class PagesToCutDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PagesToCutDialog(QWidget *parent = 0);
    ~PagesToCutDialog();
    int getCutFrom();
    int getCutTo();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::PagesToCutDialog *ui;
    bool inputValidated;
};

#endif // PAGESTOCUTDIALOG_H

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

private slots:
    void on_buttonBox_clicked(QAbstractButton *button);

private:
    Ui::PagesToCutDialog *ui;
};

#endif // PAGESTOCUTDIALOG_H

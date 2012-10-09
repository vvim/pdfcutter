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

    void SetNameBookTitle(QString booktitle);
    QString GetNameBookTitle();

    void SetNameStudentLevel(QString studentlevel);
    QString GetNameStudentLevel();

    void SetNameChapter(QString chapter);
    QString GetNameChapter();

    void SetNameManualType(QString manualtype);
    QString GetNameManualType();

    void SetNamePagerange(int pagerange_start, int pagerange_end);
    int GetNamePagerangeStart();
    int GetNamePagerangeEnd();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::PagesToCutDialog *ui;
    bool inputValidated;
};

#endif // PAGESTOCUTDIALOG_H

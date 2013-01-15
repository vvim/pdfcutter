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

    void setNameBookTitle(QString booktitle);
    QString getNameBookTitle();

    void setNameStudentLevel(QString studentlevel);
    QString getNameStudentLevel();

    void setNameChapter(QString chapter);
    QString getNameChapter();

    void setNameManualType(QString manualtype);
    QString getNameManualType();

    void setNamePagerange(int pagerange_start, int pagerange_end);
    void setNamePagerange(QString pagerange);
    QString getNamePagerange();

    void setPagerange(int pagerangestart, int pagerangeend);
    int getNamePagerangeStart();
    int getNamePagerangeEnd();
    int getPagerangeStart();
    int getPagerangeEnd();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::PagesToCutDialog *ui;
    bool inputValidated;
};

#endif // PAGESTOCUTDIALOG_H

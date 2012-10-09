#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>

namespace Ui {
    class MainWindow;
    class PagesToCutDialog;
}

struct chapternaming {
    QString booktitle;
    QString studentlevel;
    QString manualtype;
    QString chapter;
    int pagerange_start, pagerange_end;
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_choosePDFFile_clicked();

    void on_addPageRangeButton_clicked();

    void on_cuttingListWidget_itemClicked(QListWidgetItem *item);

    void on_startCuttingProcessButton_clicked();

    void on_removePageRangeButton_clicked();

    void on_deleteAllPageRangeButton_clicked();

    void keyPressEvent( QKeyEvent *k );

private:
    Ui::MainWindow *ui;
    chapternaming namingsuggestions;
};

#endif // MAINWINDOW_H


// <vvim>: internationalizeren:     tr( "Cannot open %1" ).arg( fileName ) , http://doc.qt.digia.com/qq/qq03-swedish-chef.html
// <vvim>: en wat met Designer???

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>

namespace Ui {
    class MainWindow;
    class PagesToCutDialog;
}

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

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

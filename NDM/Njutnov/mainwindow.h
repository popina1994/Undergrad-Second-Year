#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "Njutnov.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_spinBoxRow_valueChanged(int arg1);
    void IncreaseSize(int n);
    void UpdateTable();
    void UpdateFx();

    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    Newton* ptNj = nullptr;
};

#endif // MAINWINDOW_H

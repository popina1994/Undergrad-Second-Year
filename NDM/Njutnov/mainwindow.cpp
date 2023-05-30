#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QTableWidget>
#include <QStringList>
#include <QTableWidgetItem>
#include <QMessageBox>
#include "Njutnov.h"
#include "Greska.h"

using namespace std;
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    IncreaseSize(0);
    ui->radioButton1->setChecked(true);
    ui->spinBoxX->setMaximum(10000);
    ui->spinBoxX->setMinimum(-9999);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::IncreaseSize(int n) {
    int col = 2;

    if (n > 0)
        col += n - 1    ;
    ui->tbNjutn->setColumnCount(col);
    ui->tbNjutn->setRowCount(n);

    QStringList headerRow;
    QStringList headerCol;

    headerRow << "x" << "y";
    for (int i = 1; i <= col; i++) {
        QString curString = "\u2207^"; // ako te ne bude mrzelo skucaj to superscript
        curString += QString::number(i);
        curString += "y";
        headerRow += curString;
    }
    ui->tbNjutn->setHorizontalHeaderLabels(headerRow);

    qApp->processEvents();

}

void MainWindow::UpdateTable() {
    delete ptNj;
    int n = ui->spinBoxRow->value();
    double* x = new double [n];
    double* y = new double[n];


    for (int row = 0; row < n; row ++) {
       QTableWidgetItem* cell = ui->tbNjutn->item(row, 0);

       if ((cell == nullptr) || (cell->text().length() == 0)) {
           delete x; delete y;
           throw NoData(row, 0);
       }
       x[row] = cell->text().toDouble();


       cell = ui->tbNjutn->item(row, 1);
       if ((cell == nullptr) || (cell->text().length() == 0)) {
           delete x; delete y;
           throw NoData(row, 1);
       }
       y[row] = cell->text().toDouble();
    }
    ptNj = new Newton(n, x, y);
    ptNj->Evaluate();

    for (int row = 0; row < n; row++) {
       for (int col = 1; col < n; col++) {
            QTableWidgetItem* cell = new QTableWidgetItem;
           cell->setText(QString::number((*ptNj)(row, col)));
           ui->lbY->setText(cell->text());
           ui->tbNjutn->setItem(row, col +1, cell);
        }
    }

    delete x;
    delete y;
}

void MainWindow::UpdateFx() {

    bool first;
    if (ui->radioButton1->isChecked())
        first = true;
    else
        first = false;
    QString sol = "f(x) = ";
    int deg = ui->spinBoxDeg->value();
    sol += QString::number((*ptNj)(ui->spinBoxX->value(), deg, first));
    ui->lbY->setText(sol);
}

void MainWindow::on_spinBoxRow_valueChanged(int arg1) {
    IncreaseSize(arg1);
}

void MainWindow::on_pushButton_clicked()
{
    try {
        UpdateTable();
        UpdateFx();
    }
    catch (const NoData& e){
        QString errorText;
        errorText += QString("Ред: ");
        errorText += QString::number(e.row + 1);
        errorText += QString(" колона: ");
        errorText += QString::number(e.col + 1);
        QMessageBox::critical(this, QString("Критична грешка"), errorText);

    }
}

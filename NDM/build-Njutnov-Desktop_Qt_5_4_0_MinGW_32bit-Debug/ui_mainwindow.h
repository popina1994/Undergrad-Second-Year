/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QTableWidget *tbNjutn;
    QLabel *lbX;
    QLabel *label_2;
    QSpinBox *spinBoxRow;
    QDoubleSpinBox *spinBoxX;
    QLabel *lbY;
    QPushButton *pushButton;
    QLabel *label;
    QSpinBox *spinBoxDeg;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QRadioButton *radioButton1;
    QRadioButton *radioButton2;
    QMenuBar *menuBar;
    QMenu *menu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(701, 494);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        tbNjutn = new QTableWidget(centralWidget);
        if (tbNjutn->columnCount() < 2)
            tbNjutn->setColumnCount(2);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        tbNjutn->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        tbNjutn->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        tbNjutn->setObjectName(QStringLiteral("tbNjutn"));
        tbNjutn->setGeometry(QRect(60, 10, 451, 241));
        lbX = new QLabel(centralWidget);
        lbX->setObjectName(QStringLiteral("lbX"));
        lbX->setGeometry(QRect(110, 310, 16, 17));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(50, 260, 81, 31));
        spinBoxRow = new QSpinBox(centralWidget);
        spinBoxRow->setObjectName(QStringLiteral("spinBoxRow"));
        spinBoxRow->setGeometry(QRect(150, 270, 81, 21));
        spinBoxX = new QDoubleSpinBox(centralWidget);
        spinBoxX->setObjectName(QStringLiteral("spinBoxX"));
        spinBoxX->setGeometry(QRect(160, 310, 111, 31));
        lbY = new QLabel(centralWidget);
        lbY->setObjectName(QStringLiteral("lbY"));
        lbY->setGeometry(QRect(520, 360, 131, 31));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(520, 290, 99, 27));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(20, 380, 131, 21));
        spinBoxDeg = new QSpinBox(centralWidget);
        spinBoxDeg->setObjectName(QStringLiteral("spinBoxDeg"));
        spinBoxDeg->setGeometry(QRect(200, 380, 61, 31));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(320, 310, 134, 52));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        radioButton1 = new QRadioButton(widget);
        radioButton1->setObjectName(QStringLiteral("radioButton1"));

        verticalLayout->addWidget(radioButton1);

        radioButton2 = new QRadioButton(widget);
        radioButton2->setObjectName(QStringLiteral("radioButton2"));

        verticalLayout->addWidget(radioButton2);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 701, 25));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\320\212\321\203\321\202\320\275\320\276\320\262 \320\270\320\275\321\202\320\265\321\200\320\277\320\276\320\273\320\260\321\206\320\270\320\276\320\275\320\270 \320\277\320\276\320\273\320\270\320\275\320\276\320\274", 0));
        QTableWidgetItem *___qtablewidgetitem = tbNjutn->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("MainWindow", "x", 0));
        QTableWidgetItem *___qtablewidgetitem1 = tbNjutn->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("MainWindow", "f(x)", 0));
        lbX->setText(QApplication::translate("MainWindow", "x", 0));
        label_2->setText(QApplication::translate("MainWindow", "\320\221\321\200\320\276\321\230 \320\262\321\200\321\201\321\202\320\260", 0));
        lbY->setText(QApplication::translate("MainWindow", "f(x) = ", 0));
        pushButton->setText(QApplication::translate("MainWindow", "\320\230\320\267\321\200\320\260\321\207\321\203\320\275\320\260\321\230", 0));
        label->setText(QApplication::translate("MainWindow", "\320\241\321\202\320\265\320\277\320\265\320\275 \320\277\320\276\320\273\320\270\320\275\320\276\320\274\320\260", 0));
        radioButton1->setText(QApplication::translate("MainWindow", "\320\237\321\200\320\262\320\270 \320\212\321\203\321\202\320\275\320\276\320\262", 0));
        radioButton2->setText(QApplication::translate("MainWindow", "\320\224\321\200\321\203\320\263\320\270 \320\212\321\203\321\202\320\275\320\276\320\262", 0));
        menu->setTitle(QApplication::translate("MainWindow", "\320\212\321\203\321\202\320\275\320\276\320\262 \320\270\320\275\321\202\320\265\321\200\320\277\320\276\320\273\320\260\321\206\320\270\320\276\320\275\320\270 \320\277\320\276\320\273\320\270\320\275\320\276\320\274", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

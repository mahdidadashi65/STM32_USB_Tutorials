/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *pbOpenHID;
    QTextEdit *txtResp;
    QPushButton *btnClearResp;
    QCheckBox *ckLED1;
    QCheckBox *ckLED2;
    QCheckBox *ckLED3;
    QCheckBox *ckReceiveData;
    QCheckBox *ckSW1;
    QCheckBox *ckSW2;
    QCheckBox *ckSW3;
    QCheckBox *ckSW4;
    QLCDNumber *lcdNumber;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(581, 409);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        pbOpenHID = new QPushButton(centralWidget);
        pbOpenHID->setObjectName(QStringLiteral("pbOpenHID"));
        pbOpenHID->setGeometry(QRect(10, 10, 121, 23));
        txtResp = new QTextEdit(centralWidget);
        txtResp->setObjectName(QStringLiteral("txtResp"));
        txtResp->setGeometry(QRect(10, 190, 271, 161));
        btnClearResp = new QPushButton(centralWidget);
        btnClearResp->setObjectName(QStringLiteral("btnClearResp"));
        btnClearResp->setGeometry(QRect(10, 170, 75, 23));
        ckLED1 = new QCheckBox(centralWidget);
        ckLED1->setObjectName(QStringLiteral("ckLED1"));
        ckLED1->setGeometry(QRect(170, 20, 51, 17));
        ckLED2 = new QCheckBox(centralWidget);
        ckLED2->setObjectName(QStringLiteral("ckLED2"));
        ckLED2->setGeometry(QRect(220, 20, 51, 17));
        ckLED3 = new QCheckBox(centralWidget);
        ckLED3->setObjectName(QStringLiteral("ckLED3"));
        ckLED3->setGeometry(QRect(280, 20, 51, 17));
        ckReceiveData = new QCheckBox(centralWidget);
        ckReceiveData->setObjectName(QStringLiteral("ckReceiveData"));
        ckReceiveData->setGeometry(QRect(10, 150, 70, 17));
        ckSW1 = new QCheckBox(centralWidget);
        ckSW1->setObjectName(QStringLiteral("ckSW1"));
        ckSW1->setGeometry(QRect(360, 20, 51, 17));
        ckSW2 = new QCheckBox(centralWidget);
        ckSW2->setObjectName(QStringLiteral("ckSW2"));
        ckSW2->setGeometry(QRect(410, 20, 51, 17));
        ckSW3 = new QCheckBox(centralWidget);
        ckSW3->setObjectName(QStringLiteral("ckSW3"));
        ckSW3->setGeometry(QRect(460, 20, 51, 17));
        ckSW4 = new QCheckBox(centralWidget);
        ckSW4->setObjectName(QStringLiteral("ckSW4"));
        ckSW4->setGeometry(QRect(510, 20, 51, 17));
        lcdNumber = new QLCDNumber(centralWidget);
        lcdNumber->setObjectName(QStringLiteral("lcdNumber"));
        lcdNumber->setEnabled(true);
        lcdNumber->setGeometry(QRect(360, 60, 191, 61));
        lcdNumber->setSmallDecimalPoint(false);
        lcdNumber->setSegmentStyle(QLCDNumber::Flat);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 581, 21));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0));
        pbOpenHID->setText(QApplication::translate("MainWindow", "Open HID Device", 0));
        btnClearResp->setText(QApplication::translate("MainWindow", "Clear", 0));
        ckLED1->setText(QApplication::translate("MainWindow", "LED1", 0));
        ckLED2->setText(QApplication::translate("MainWindow", "LED2", 0));
        ckLED3->setText(QApplication::translate("MainWindow", "LED3", 0));
        ckReceiveData->setText(QApplication::translate("MainWindow", "ReceiveData", 0));
        ckSW1->setText(QApplication::translate("MainWindow", "SW1", 0));
        ckSW2->setText(QApplication::translate("MainWindow", "SW2", 0));
        ckSW3->setText(QApplication::translate("MainWindow", "SW3", 0));
        ckSW4->setText(QApplication::translate("MainWindow", "SW4", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

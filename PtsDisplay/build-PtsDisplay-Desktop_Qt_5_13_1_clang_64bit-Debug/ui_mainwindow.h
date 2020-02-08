/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGroupBox *groupBox;
    QPushButton *pushButton;
    QPushButton *BtnViewing;
    QSpinBox *spinPointSize;
    QLabel *label_3;
    QCheckBox *ckbColored;
    QLabel *label_4;
    QLabel *label_5;
    QDoubleSpinBox *spinDist;
    QDoubleSpinBox *spinHor;
    QDoubleSpinBox *spinVer;
    QCheckBox *ckbShowLine;
    QComboBox *cbxHistories;
    QLabel *label_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1093, 749);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(0, 0, 1091, 171));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        groupBox->setFont(font);
        pushButton = new QPushButton(groupBox);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(510, 30, 101, 81));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font1.setPointSize(12);
        pushButton->setFont(font1);
        pushButton->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: 1px solid #8f8f91;\n"
"    border-radius: 2px;\n"
"    background-color: rgb(66,133,244);\n"
"    min-width: 80px;\n"
"    color:#FFFFFF;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"    border: 1px solid #8f8f91;\n"
"    border-radius: 3px;\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #5295F4, stop: 1 #4285F4);\n"
"    min-width: 80px;\n"
"}\n"
"\n"
"QPushButton :pressed{\n"
"    border: 1px solid #8f8f91;\n"
"    border-radius: 2px;\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #5295F4, stop: 1 #4285F4);\n"
"    min-width: 80px;\n"
"    color:#FFFFFF;\n"
"}\n"
"\n"
"\n"
""));
        BtnViewing = new QPushButton(groupBox);
        BtnViewing->setObjectName(QString::fromUtf8("BtnViewing"));
        BtnViewing->setGeometry(QRect(510, 120, 101, 41));
        BtnViewing->setFont(font);
        BtnViewing->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    border: 1px solid #8f8f91;\n"
"    border-radius: 2px;\n"
"    background-color: rgb(234,67,53);\n"
"    min-width: 80px;\n"
"    color:#FFFFFF;\n"
"}\n"
"\n"
"QPushButton:hover{\n"
"    border: 1px solid #8f8f91;\n"
"    border-radius: 3px;\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 rgb(180,110,110), stop: 1 rgb(110,10,10));\n"
"    min-width: 80px;\n"
"}\n"
"\n"
"QPushButton :pressed{\n"
"    border: 1px solid #8f8f91;\n"
"    border-radius: 2px;\n"
"    background-color: qlineargradient(x1: 0, y1: 0, x2: 0, y2: 1,stop: 0 #4E6060, stop: 1 #1B1B1B);\n"
"    min-width: 80px;\n"
"    color:#FFFFFF;\n"
"}\n"
"\n"
"\n"
""));
        BtnViewing->setCheckable(true);
        spinPointSize = new QSpinBox(groupBox);
        spinPointSize->setObjectName(QString::fromUtf8("spinPointSize"));
        spinPointSize->setGeometry(QRect(80, 40, 61, 31));
        spinPointSize->setMinimum(1);
        spinPointSize->setMaximum(20);
        spinPointSize->setValue(9);
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 40, 61, 31));
        label_3->setAlignment(Qt::AlignCenter);
        ckbColored = new QCheckBox(groupBox);
        ckbColored->setObjectName(QString::fromUtf8("ckbColored"));
        ckbColored->setGeometry(QRect(20, 100, 101, 31));
        ckbColored->setChecked(true);
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(180, 90, 71, 31));
        label_4->setAlignment(Qt::AlignCenter);
        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(180, 40, 71, 31));
        label_5->setAlignment(Qt::AlignCenter);
        spinDist = new QDoubleSpinBox(groupBox);
        spinDist->setObjectName(QString::fromUtf8("spinDist"));
        spinDist->setGeometry(QRect(260, 40, 70, 31));
        spinDist->setMinimum(0.010000000000000);
        spinDist->setMaximum(500.000000000000000);
        spinDist->setSingleStep(0.030000000000000);
        spinDist->setValue(1.000000000000000);
        spinHor = new QDoubleSpinBox(groupBox);
        spinHor->setObjectName(QString::fromUtf8("spinHor"));
        spinHor->setGeometry(QRect(260, 90, 70, 31));
        spinHor->setMinimum(-360.000000000000000);
        spinHor->setMaximum(360.000000000000000);
        spinHor->setValue(45.000000000000000);
        spinVer = new QDoubleSpinBox(groupBox);
        spinVer->setObjectName(QString::fromUtf8("spinVer"));
        spinVer->setGeometry(QRect(350, 90, 70, 31));
        spinVer->setMinimum(-89.000000000000000);
        spinVer->setMaximum(89.000000000000000);
        ckbShowLine = new QCheckBox(groupBox);
        ckbShowLine->setObjectName(QString::fromUtf8("ckbShowLine"));
        ckbShowLine->setGeometry(QRect(20, 130, 101, 31));
        ckbShowLine->setChecked(true);
        cbxHistories = new QComboBox(groupBox);
        cbxHistories->setObjectName(QString::fromUtf8("cbxHistories"));
        cbxHistories->setGeometry(QRect(710, 90, 151, 22));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(-10, 0, 1101, 751));
        label_2->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        MainWindow->setCentralWidget(centralWidget);
        label_2->raise();
        groupBox->raise();

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox->setTitle(QString());
        pushButton->setText(QCoreApplication::translate("MainWindow", "\345\212\240\350\275\275\346\225\260\346\215\256", nullptr));
        BtnViewing->setText(QCoreApplication::translate("MainWindow", "\346\227\213\350\275\254", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\347\202\271\345\244\247\345\260\217", nullptr));
        ckbColored->setText(QCoreApplication::translate("MainWindow", "\351\242\234\350\211\262", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\350\247\202\345\257\237\350\247\222\345\272\246", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\347\233\270\346\234\272\350\267\235\347\246\273", nullptr));
        ckbShowLine->setText(QCoreApplication::translate("MainWindow", "\346\230\276\347\244\272KNN", nullptr));
        label_2->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

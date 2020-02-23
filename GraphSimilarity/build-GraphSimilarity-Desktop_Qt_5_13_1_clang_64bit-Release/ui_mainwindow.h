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
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include <widget.h>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *btnLoadFmData;
    QPushButton *btnSim;
    QPushButton *btnGFD;
    QPushButton *btnClear;
    QPushButton *btnGen;
    QPushButton *btnCalculate;
    QPushButton *btnNext;
    QComboBox *comboBox;
    QPushButton *btnSave;
    QPushButton *btnOpen;
    QLabel *graphletId;
    QComboBox *cbxKernel;
    QComboBox *comboSearchRange;
    QWidget *container;
    QHBoxLayout *horizontalLayout;
    Widget *m_widget_0;
    Widget *m_widget_1;
    QComboBox *fileListBox;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        horizontalLayout_2 = new QHBoxLayout(groupBox);
        horizontalLayout_2->setSpacing(0);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        btnLoadFmData = new QPushButton(groupBox);
        btnLoadFmData->setObjectName(QString::fromUtf8("btnLoadFmData"));

        horizontalLayout_2->addWidget(btnLoadFmData);

        btnSim = new QPushButton(groupBox);
        btnSim->setObjectName(QString::fromUtf8("btnSim"));

        horizontalLayout_2->addWidget(btnSim);

        btnGFD = new QPushButton(groupBox);
        btnGFD->setObjectName(QString::fromUtf8("btnGFD"));

        horizontalLayout_2->addWidget(btnGFD);

        btnClear = new QPushButton(groupBox);
        btnClear->setObjectName(QString::fromUtf8("btnClear"));

        horizontalLayout_2->addWidget(btnClear);

        btnGen = new QPushButton(groupBox);
        btnGen->setObjectName(QString::fromUtf8("btnGen"));

        horizontalLayout_2->addWidget(btnGen);

        btnCalculate = new QPushButton(groupBox);
        btnCalculate->setObjectName(QString::fromUtf8("btnCalculate"));

        horizontalLayout_2->addWidget(btnCalculate);

        btnNext = new QPushButton(groupBox);
        btnNext->setObjectName(QString::fromUtf8("btnNext"));

        horizontalLayout_2->addWidget(btnNext);

        comboBox = new QComboBox(groupBox);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        horizontalLayout_2->addWidget(comboBox);

        btnSave = new QPushButton(groupBox);
        btnSave->setObjectName(QString::fromUtf8("btnSave"));

        horizontalLayout_2->addWidget(btnSave);

        btnOpen = new QPushButton(groupBox);
        btnOpen->setObjectName(QString::fromUtf8("btnOpen"));

        horizontalLayout_2->addWidget(btnOpen);

        graphletId = new QLabel(groupBox);
        graphletId->setObjectName(QString::fromUtf8("graphletId"));

        horizontalLayout_2->addWidget(graphletId);


        verticalLayout->addWidget(groupBox);

        cbxKernel = new QComboBox(centralwidget);
        cbxKernel->addItem(QString());
        cbxKernel->addItem(QString());
        cbxKernel->addItem(QString());
        cbxKernel->setObjectName(QString::fromUtf8("cbxKernel"));

        verticalLayout->addWidget(cbxKernel);

        comboSearchRange = new QComboBox(centralwidget);
        comboSearchRange->setObjectName(QString::fromUtf8("comboSearchRange"));

        verticalLayout->addWidget(comboSearchRange);

        container = new QWidget(centralwidget);
        container->setObjectName(QString::fromUtf8("container"));
        horizontalLayout = new QHBoxLayout(container);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        m_widget_0 = new Widget(container);
        m_widget_0->setObjectName(QString::fromUtf8("m_widget_0"));

        horizontalLayout->addWidget(m_widget_0);

        m_widget_1 = new Widget(container);
        m_widget_1->setObjectName(QString::fromUtf8("m_widget_1"));

        horizontalLayout->addWidget(m_widget_1);


        verticalLayout->addWidget(container);

        fileListBox = new QComboBox(centralwidget);
        fileListBox->setObjectName(QString::fromUtf8("fileListBox"));

        verticalLayout->addWidget(fileListBox);

        verticalLayout->setStretch(3, 20);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 22));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "GroupBox", nullptr));
        btnLoadFmData->setText(QCoreApplication::translate("MainWindow", "load fm data", nullptr));
        btnSim->setText(QCoreApplication::translate("MainWindow", "Similarity", nullptr));
        btnGFD->setText(QCoreApplication::translate("MainWindow", "GFD", nullptr));
        btnClear->setText(QCoreApplication::translate("MainWindow", "Clear", nullptr));
        btnGen->setText(QCoreApplication::translate("MainWindow", "Generate", nullptr));
        btnCalculate->setText(QCoreApplication::translate("MainWindow", "Search", nullptr));
        btnNext->setText(QCoreApplication::translate("MainWindow", "Next", nullptr));
        btnSave->setText(QCoreApplication::translate("MainWindow", "Save", nullptr));
        btnOpen->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
        graphletId->setText(QCoreApplication::translate("MainWindow", "graphlet:", nullptr));
        cbxKernel->setItemText(0, QCoreApplication::translate("MainWindow", "Cosine Similarity", nullptr));
        cbxKernel->setItemText(1, QCoreApplication::translate("MainWindow", "RBF", nullptr));
        cbxKernel->setItemText(2, QCoreApplication::translate("MainWindow", "Laplacian", nullptr));

    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_widget = new Widget(ui->centralwidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}


#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    for(int i=0; i<10; ++i)
    {
        ui->comboBox->addItem(QString("Graph:%1").arg(i));
    }
    emit sig_aaa();

    connect(ui->btnOpen, SIGNAL(clicked(bool)), this, SLOT(slot_openGraph()));
    connect(ui->btnCalculate,SIGNAL(clicked(bool)),this,SLOT(slot_calculateGraphLet()));
    connect(ui->btnNext,SIGNAL(clicked(bool)),this,SLOT(slot_btnNext()));
    m_widget = new Widget(ui->centralwidget);
}

void MainWindow::slot_openGraph()
{
    QString filename = QFileDialog::getOpenFileName(this,"Open Graph",".", "Graph {*.graph}");

    if(filename == "")
        return;
}

void MainWindow::slot_saveGraph()
{

}

void MainWindow::slot_calculateGraphLet()  // 点击计算按钮
{
    m_widget->m_graph.GetGraphlets();
}

void MainWindow::slot_btnNext()
{
    m_widget->m_graph.ShowNextGraphlet();
    m_widget->update();
}

MainWindow::~MainWindow()
{
    delete ui;
}


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
        ui->comboBox->addItem(QString("Graph:%1").arg(i+1));
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
    m_widget->m_graph.GetGraphlets(m_graphlet_id);
}

void MainWindow::slot_btnNext()
{
    m_widget->m_graph.ShowNextGraphlet();
    m_widget->update();

    ui->graphletId->setText("graphlet:" + QString::number(m_widget->m_graph.cur_ID));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnGen_clicked()
{
    m_widget->m_graph = genGraph(500, 499);//(200, 1000) cost 0-100ms
    m_widget->update();
}

Graph MainWindow::genGraph(int nodeNum, int edgeNum)
{
    Graph g;
    int maxWidth = m_widget->width();
    int maxHeight = m_widget->height();

    srand(time(0));
    // Random nodes
    for (int i = 0; i < nodeNum; i++) {
        int nx = rand() % (maxWidth+1);
        int ny = rand() % (maxHeight+1);
        g.addNode(Node(nx, ny));
    }

    // Random edges
    for (int i = 0; i < edgeNum; i++) {
        int sid = rand() % nodeNum;
        int tid = rand() % nodeNum;
        g.addEdge(sid, tid);
    }

    return g;
}

void MainWindow::on_comboBox_activated(int index)
{
    m_graphlet_id = index;
}

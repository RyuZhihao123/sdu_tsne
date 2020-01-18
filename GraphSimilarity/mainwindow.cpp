#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    for(int i=0; i<21; ++i)
    {
        ui->comboBox->addItem(QString("Graph:%1").arg(i+1));
    }

    connect(ui->btnOpen, SIGNAL(clicked(bool)), this, SLOT(slot_openGraph()));
    connect(ui->btnSave,SIGNAL(clicked(bool)),this,SLOT(slot_saveGraph()));

    connect(ui->btnCalculate,SIGNAL(clicked(bool)),this,SLOT(slot_calculateGraphLet()));
    connect(ui->btnNext,SIGNAL(clicked(bool)),this,SLOT(slot_btnNext()));

    m_widget = new Widget(ui->centralwidget);
}

void MainWindow::slot_openGraph()
{
    QString filename = QFileDialog::getOpenFileName(this,"Open Graph",".", "Graph (*.graph)");

    if(filename == "")
    {
        return;
    }

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QMessageBox::warning(this,tr("错误"),tr("打开文件失败"));
        return;
    }

    QTextStream in(&file);

    Graph g;

    bool flag = false;
    QString line = in.readLine();
    while (!line.isNull())
    {
        qDebug() << line;

        if (line == "#")
        {
            qDebug() << g.nodeNum();
            flag = true;
            line = in.readLine();
            continue;
        }
        QStringList list = line.split(QRegExp("\\s+"));
        if (!flag)
        {
            // We assume that nodes are stored in file sequentially
            g.addNode(Node(list[1].toFloat(), list[2].toFloat()));
        }
        else
        {
            for (int i = 1; i < list.size(); i++)
            {
                g.addEdge(list[0].toInt(), list[i].toInt());
            }
        }
        line = in.readLine();
    }

    m_widget->m_graph = g;
    m_widget->update();
}

void MainWindow::slot_saveGraph()
{
    QFileDialog fileDialog;
    QString fileName = fileDialog.getSaveFileName(this,tr("Save Graph"),"/home",tr("Graph (*.graph)"));
    if(fileName == "")
    {
        return;
    }

    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(this,tr("错误"),tr("打开文件失败"));
        return;
    }
    else
    {
        QTextStream textStream(&file);

        QString str;
        // positions of nodes
        for (int i = 0; i < m_widget->m_graph.nodeNum(); i++)
        {
            str += QString::number(i);
            str += " ";

            Node* s = m_widget->m_graph.GetNode(i);
            str += QString("%1").arg(s->x);
            str += " ";

            str += QString("%1").arg(s->y);
            str += "\n";
        }

        str += "#\n";

        // edges of the graph
        for (int i = 0; i < m_widget->m_graph.nodeNum(); i++)
        {
            str += QString::number(i);
            str += " ";

            Node* s = m_widget->m_graph.GetNode(i);
            for (int j = 0; j < s->childs.size(); j++)
            {
                str += QString::number(s->childs[j]);
                str += " ";
            }
            str += "\n";
        }

        textStream<<str;
        QMessageBox::warning(this,tr("提示"),tr("保存文件成功"));
        file.close();
    }
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

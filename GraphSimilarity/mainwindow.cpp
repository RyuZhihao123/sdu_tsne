#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    for(int i=0; i<ALL_GRAPHLET; ++i)
    {
        ui->comboBox->addItem(QString("Graph:%1").arg(i+1));
    }
//    ui->comboBox->setCurrentIndex(19);

    connect(ui->btnOpen, SIGNAL(clicked(bool)), this, SLOT(slot_openGraph()));
    connect(ui->btnSave,SIGNAL(clicked(bool)),this,SLOT(slot_saveGraph()));

    connect(ui->btnCalculate,SIGNAL(clicked(bool)),this,SLOT(slot_calculateGraphLet()));
    connect(ui->btnNext,SIGNAL(clicked(bool)),this,SLOT(slot_btnNext()));

    m_widget = new Widget(ui->centralwidget);
}

void MainWindow::slot_openGraph()
{
    QString filename = QFileDialog::getOpenFileName(this,"Open Graph","/Users/joe/Codes/QtProjects/t-sne for comparison/GraphSimilarity/data/", "Graph (*.graph)");
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
            for (int i = 1; i < list.size()-1; i++)
            {
                g.addEdge(list[0].toInt(), list[i].toInt());
                qDebug() << QString("Add edge(%1,%2)").arg(list[0], list[i]);
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
    QString fileName = fileDialog.getSaveFileName(this,tr("Save Graph"),".",tr("Graph (*.graph)"));
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
        // Store positions of nodes
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

        // Delimeter
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
    m_widget->m_graph.GetGraphletFromGraph(m_graphlet_id);
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
    for (int i = 0; i < nodeNum; i++)
    {
        int nx = rand() % (maxWidth+1);
        int ny = rand() % (maxHeight+1);
        g.addNode(Node(nx, ny));
    }

    // Random edges
    for (int i = 0; i < edgeNum; i++)
    {
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

void MainWindow::on_btnClear_clicked()
{
    m_widget->m_graph.clear();
    m_widget->update();
}

void MainWindow::on_btnGFD_clicked()
{
    // For test
    int sid = 0;

    QVector<float> v =m_widget->m_graph.GetfeatureVector(sid);
    qDebug() << "Feature vector:";
    for (int i = 0; i < v.size(); i++)
    {
        qDebug() << v[i] << " ";
    }
}

Graph MainWindow::read_fm_data(const QString& fileName)
{
    Graph g;

    QFile file(fileName);
//    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
//    {
//        QMessageBox::warning(this,tr("错误"),tr("打开文件失败"));
//        return;
//    }
    file.open(QIODevice::ReadOnly);

    QTextStream ts(&file);
    // process TRUNCK
    while(!ts.atEnd())
    {
        QStringList line= ts.readLine().split(QRegExp("\\s+"));
        line.removeAll("");

        if( line.size() == 0)
            continue;

        if(line[0][0] == "G")  // 接下来要读取Graph Adjacency List;
            break;

        g.addNode(Node());
    }

    qDebug()<<"加载完毕, 顶点数"<<g.nodeNum();

    // add edges
    while(!ts.atEnd())
    {
        QStringList line= ts.readLine().split(QRegExp("\\s+"));
        line.removeAll("");

        if( line.size() == 0)
            continue;

        int id = line[0].toInt();
        for(int i=1; i<line.size(); i+=2)
        {
            g.addEdge(id, line[i].toInt());
        }
    }

    return g;
}

void MainWindow::saveSims(const MatchList &matchList, const QString &fileName)
{
    QFile file(fileName);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(this,tr("错误"),tr("打开文件失败"));
        return;
    }
    else
    {
        QTextStream textStream(&file);
        for (auto iter = matchList.begin(); iter != matchList.end(); iter++)
        {
            qDebug() << "save: " << iter.key().first << ", " << iter.key().second << ", " << iter.value();
            textStream << QString::number(iter.key().first);
            textStream << "\t";
            textStream << QString::number(iter.key().second);
            textStream << "\t";
            textStream << iter.value();
            textStream << "\n";
        }
        file.close();
    }
}

void MainWindow::on_btnSim_clicked()
{
    QStringList filenames = QFileDialog::getOpenFileNames(this,"Open two graphs","/Users/joe/Codes/QtProjects/t-sne for comparison/data/highdims/", "text file(*.txt)");
    assert(filenames.size() == 2);

    Graph g0 = read_fm_data(filenames[0]);
    Graph g1 = read_fm_data(filenames[1]);

    MatchList matchList = calcSims(g0, g1);

    saveSims(matchList,
             QString("/Users/joe/Codes/QtProjects/t-sne for comparison/data/qt_sim/similar_points_%1_%2.txt").arg(QFileInfo(filenames[0]).baseName(), QFileInfo(filenames[1]).baseName()));
}

MatchList MainWindow::calcSims(Graph &g1, Graph &g2)
{
    MatchList matchList;

    for (int i = 0; i < g1.nodeNum(); i++)
    {
        QVector<float> vi = g1.GetfeatureVector(i);

        QPair<int, int> maxP;
        float maxS = -INFINITY;

        for (int j = 0; j < g2.nodeNum(); j++)
        {
            QVector<float> vj = g2.GetfeatureVector(j);


            float sum = 0.f;
            float len1 = 0.f, len2 = 0.f;
            for(int k = 0; k < vi.size(); k++)
            {
                // dot product bewteen v1 and v2
                sum += vi[k]*vj[k];
                // dot product bewteen v1 and v1
                len1 += vi[k]*vi[k];
                // dot product bewteen v2 and v2
                len2 += vj[k]*vj[k];
            }
            len1 = sqrtf(len1);
            len2 = sqrtf(len2);

            float s = sum / (len1 * len2);
            if (s > maxS)
            {
                maxS = s;
                maxP.first = i;
                maxP.second = j;
            }
        }

        matchList[maxP] = maxS;
    }

    return matchList;
}

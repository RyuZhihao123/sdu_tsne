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
        ui->comboBox->addItem(QString("Graphlet:%1").arg(i+1));
    }
    for (int i = 0; i < MAX_SEARCH_RANGE; i++) {
        ui->cbxRange->addItem(QString("neighborhood:%1").arg(i+1));
    }

    ui->cbxRange->setCurrentIndex(glet_search_range-1);
    ui->cbxGFDCalc->setCurrentIndex(m_gfd_cal);

    //    ui->comboBox->setCurrentIndex(19);

    connect(ui->btnOpen, SIGNAL(clicked(bool)), this, SLOT(slot_openGraph()));
    connect(ui->btnSave,SIGNAL(clicked(bool)),this,SLOT(slot_saveGraph()));

    connect(ui->btnCalculate,SIGNAL(clicked(bool)),this,SLOT(slot_calculateGraphLet()));
    connect(ui->btnNext,SIGNAL(clicked(bool)),this,SLOT(slot_btnNext()));

    m_filenames.clear();
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

    ui->m_widget_0->m_graph = g;
    ui->m_widget_0->update();
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
        for (int i = 0; i < ui->m_widget_0->m_graph.nodeNum(); i++)
        {
            str += QString::number(i);
            str += " ";

            Node* s = ui->m_widget_0->m_graph.GetNode(i);
            str += QString("%1").arg(s->x);
            str += " ";

            str += QString("%1").arg(s->y);
            str += "\n";
        }

        // Delimeter
        str += "#\n";

        // edges of the graph
        for (int i = 0; i < ui->m_widget_0->m_graph.nodeNum(); i++)
        {
            str += QString::number(i);
            str += " ";

            Node* s = ui->m_widget_0->m_graph.GetNode(i);
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
    ui->m_widget_0->m_graph.GetGraphletFromGraph(m_graphlet_id);
}

void MainWindow::slot_btnNext()
{
    ui->m_widget_0->m_graph.ShowNextGraphlet();
    ui->m_widget_0->update();

    ui->graphletId->setText("graphlet:" + QString::number(ui->m_widget_0->m_graph.cur_ID));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnGen_clicked()
{
    ui->m_widget_0->m_graph = genGraph(500, 499);//(200, 1000) cost 0-100ms
    ui->m_widget_0->update();
}

Graph MainWindow::genGraph(int nodeNum, int edgeNum)
{
    Graph g;
    int maxWidth = ui->m_widget_0->width();
    int maxHeight = ui->m_widget_0->height();

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
    ui->m_widget_0->m_graph.clear();
    ui->m_widget_0->update();
}

void MainWindow::on_btnGFD_clicked()
{
    // For test
    int sid = 0;

    QVector<float> gfd =ui->m_widget_0->m_graph.GetfeatureVectorAll(sid);

    QString str;
    for (int i = 0; i < gfd.size(); i++)
    {
        str += QString::number(gfd[i]) + ", ";
    }
    qDebug()<< str;
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

void MainWindow::savePointSims(const QVector<float> &matchScores, const QString &fileName)
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
        for (int i = 0; i < matchScores.size(); i++)
        {
            //            qDebug() << "save: " << i << ", " << i << ", " << matchScores[i];
            textStream << QString::number(i);
            textStream << "\t";
            textStream << QString::number(i);
            textStream << "\t";
            textStream << matchScores[i];
            textStream << "\n";
        }
        file.close();
    }

    qDebug() << "save file: " << fileName << " successful.";
}

void MainWindow::saveEdgeSims(const MatchEdgeList &matchEdges, const QString &fileName)
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
        for (auto iter = matchEdges.begin(); iter != matchEdges.end(); iter++)
        {
            qDebug() << "save: " << iter.key().first << ", " << iter.key().second << ", " << iter.value();
            textStream << QString::number(iter.key().first);
            textStream << "\t";
            textStream << QString::number(iter.key().second);
            textStream << "\t";
            textStream << QString::number(iter.key().first);
            textStream << "\t";
            textStream << QString::number(iter.key().second);
            textStream << "\t";
            textStream << iter.value();
            textStream << "\n";
        }
        file.close();
    }
    qDebug() << "save file: " << fileName << " successful.";
}

void MainWindow::on_btnSim_clicked()
{
    //    QStringList filenames = QFileDialog::getOpenFileNames(this,"Open two graphs","/Users/joe/Codes/QtProjects/t-sne for comparison/data/highdims/", "text file(*.txt)");
    //    assert(filenames.size() == 2);
    QString fileName0, fileName1;
    fileName0 = m_filenames[m_filenames.size()-2];
    fileName1 = m_filenames[m_filenames.size()-1];

    // Pick the last two files
    Graph g0 = read_fm_data(fileName0);
    Graph g1 = read_fm_data(fileName1);

    //
    //    QVector<QVector<GraphLet>> vi_1 = g0.GetGraphLets(4);
    //    QVector<QVector<GraphLet>> vi_2 = g1.GetGraphLets(4);

    QVector<float> pointSims = calcPointSims(g0, g1);
    // we leave it to python to compute edge similarity
    //    MatchEdgeList matchEdges = calcEdgeSims(g0, g1,pointSims);

    QFileInfo finfo0(fileName0);
    QFileInfo finfo1(fileName1);

    QStringList dirList0 = finfo0.dir().path().split("/");
    QStringList dirList1 = finfo1.dir().path().split("/");

    // /Users/joe/Codes/QtProjects/t-sne for comparison/data/data1/highdims/dim3/size100/2nn
    QString knn = dirList0[dirList0.size()-1];
    QString sizem = dirList0[dirList0.size()-2];
    QString dimn = dirList0[dirList0.size()-3];
    QString data_type = dirList0[dirList0.size()-5];

    int d0 = (finfo0.baseName().split("_")[1]).toInt();
    int d1 = (finfo1.baseName().split("_")[1]).toInt();

    // we also consider searching range into similarities
    QString dir = QString("/Users/joe/Codes/QtProjects/t-sne for comparison/data/%1/qt_sim/%2/%3/%4/level%5/%6").arg(data_type).arg(dimn).arg(sizem).arg(knn).arg(glet_search_range).arg(ui->cbxGFDCalc->itemText(m_gfd_cal));
    QDir fileDir(dir);
    if (!fileDir.exists())
    {
        fileDir.mkpath(dir);
    }

    qDebug() << fileDir.path();
    savePointSims(pointSims,
                  (fileDir.path() + "/similar_points_%1_%2.txt").arg(d0).arg(d1));

    //    saveEdgeSims(matchEdges,
    //             QString("/Users/joe/Codes/QtProjects/t-sne for comparison/data/qt_sim/similar_edges_%1_%2.txt").arg(d0).arg(d1));
}

QVector<float> MainWindow::calcPointSims(Graph &g1, Graph &g2)
{
    QVector<float> matchScores;

    for (int i = 0; i < g1.nodeNum(); i++)
    {
        QVector<float> vi_1;
        QVector<float> vi_2;

//#ifdef STACK_GFD
        if (m_gfd_cal == CONCAT)
        {
            vi_1 = g1.GetfeatureVector(i);
            vi_2 = g2.GetfeatureVector(i);
        }
//#else
        else
        {
            vi_1 = g1.GetfeatureVectorAll(i);
            vi_2 = g2.GetfeatureVectorAll(i);
        }
//#endif

        float s = applyKernel(vi_1, vi_2, m_kernel);

//        qDebug() <<  i << ": " << s;
        qDebug() <<  i << "," << s;
        matchScores.push_back(s);
    }

    return matchScores;
}

MatchEdgeList MainWindow::calcEdgeSims(Graph &g1, Graph &g2, const QVector<float> &pointSims)
{
    MatchEdgeList matchEdges;
    for (int i = 0; i < g1.nodeNum(); i++)
    {
        Node* ni = g1.GetNode(i);
        for (int j = 0; j < ni->childs.size(); j++)
        {
            if (g2.hasEdge(i, ni->childs[j]))
            {
                matchEdges[QPair<int, int>(i, ni->childs[j])] = (pointSims[i] + pointSims[ni->childs[j]])/2.f;
            }
        }
    }

    return matchEdges;
}

void MainWindow::on_btnLoadFmData_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this,"Open two graphs","/Users/joe/Codes/QtProjects/t-sne for comparison/data/highdims/", "text file(*.txt)");
    m_filenames.push_back(fileName);

    ui->fileListBox->addItem(fileName);
}

void MainWindow::on_cbxRange_activated(int index)
{
    glet_search_range = index + 1;
    qDebug() << "set searching range: " << glet_search_range;
}

void MainWindow::on_cbxKernel_activated(int index)
{
    m_kernel = KernelFunc(index);
    qDebug() << "set kernel function: " << m_kernel << " " << ui->cbxKernel->itemText(index);
}

float MainWindow::applyKernel(const QVector<float> &vec1, const QVector<float> &vec2, KernelFunc func)
{
    assert(vec1.size() == vec2.size());
    switch (func) {
    case COS:
        return cosine(vec1, vec2);
    case RBF:
        return rbf(vec1, vec2);
    case LAPLACIAN:
        return laplacian(vec1, vec2);
//    default:
//        return cosine(vec1, vec2);
    }
}

float MainWindow::cosine(const QVector<float> &vec1, const QVector<float> &vec2)
{
    float sum = 0.f;
    float len1 = 0.f, len2 = 0.f;
    for(int k = 0; k < vec1.size(); k++)
    {
        // dot product bewteen v1 and v2
        sum += vec1[k]*vec2[k];
        // dot product bewteen v1 and v1
        len1 += vec1[k]*vec1[k];
        // dot product bewteen v2 and v2
        len2 += vec2[k]*vec2[k];
    }
    len1 = sqrtf(len1);
    len2 = sqrtf(len2);

    float s = 0;
    if (len1 != 0 && len2 != 0)
    {
        s = sum / (len1 * len2);
    }

    return s;
}

float MainWindow::rbf(const QVector<float> &vec1, const QVector<float> &vec2, float delta)
{
    //
    return exp(-L2Distance(vec1, vec2)/(2*delta*delta));

}

float MainWindow::laplacian(const QVector<float> &vec1, const QVector<float> &vec2, float delta)
{
    return exp(-L1Distance(vec1, vec2)/delta);
}

float MainWindow::L1Distance(const QVector<float> &vec1, const QVector<float> &vec2)
{
    int size = vec1.size();

    float sum = 0.f;
    for (int i = 0; i < size; i++)
    {
        sum += fabs(vec1[i]-vec2[i]);
    }
    return sum;
}

float MainWindow::L2Distance(const QVector<float> &vec1, const QVector<float> &vec2)
{
    int size = vec1.size();

    float sum = 0.f;
    for (int i = 0; i < size; i++)
    {
        sum += (vec1[i]-vec2[i])*(vec1[i]-vec2[i]);
    }
    return sum;
}

void MainWindow::on_cbxGFDCalc_activated(int index)
{
    m_gfd_cal = GFDCalc(index);
}

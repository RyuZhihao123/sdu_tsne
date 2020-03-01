#include "mainwindow.h"
#include "ui_mainwindow.h"

#define MSG_BLACK QString("<font color=\"#000000\">%1</font>")
#define MSG_RED   QString("<font color=\"#FF0000\">%1</font>")
#define MSG_BLUE  QString("<font color=\"#0000FF\">%1</font>")

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->m_glwiget = new GLWidget(ui->centralWidget);
//    m_glwiget->setAutoFillBackground(true);

    // Note that: Change here to set up your own window title
    this->setWindowTitle("RyuZhihao123");

    this->UpdateParameters();

    connect(ui->spinPointSize,SIGNAL(valueChanged(int)),this,SLOT(UpdateParameters()));
    connect(ui->ckbShowLine,SIGNAL(clicked(bool)),this, SLOT(UpdateParameters()));
    connect(ui->ckbColored,SIGNAL(clicked(bool)),this,SLOT(UpdateParameters()));

    connect(ui->pushButton,SIGNAL(clicked(bool)),this,SLOT(loadNewFile()));
    connect(ui->BtnViewing,SIGNAL(clicked(bool)),this,SLOT(StartViewingTimer()));

    connect(m_glwiget,SIGNAL(sig_cameraPose(float,float,float)),this,SLOT(UpdateCameraPose(float,float,float)));

#ifdef DRAW_LABEL
    connect(m_glwiget, SIGNAL(drawLabel(const QVector<QPair<int, QVector2D>>&)),this, SLOT(UpdateLabels(const QVector<QPair<int, QVector2D>>&)));
#endif

    connect(ui->spinDist,SIGNAL(valueChanged(double)),this,SLOT(UpdateParameters()));
    connect(ui->spinHor,SIGNAL(valueChanged(double)),this,SLOT(UpdateParameters()));
    connect(ui->spinVer,SIGNAL(valueChanged(double)),this,SLOT(UpdateParameters()));

    connect(ui->cbxHistories,SIGNAL(currentIndexChanged(int)),this,SLOT(slot_cbxhistories()));

    QVector<bool> matrix;
    matrix.resize(50176);
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    m_glwiget->setGeometry(0,ui->groupBox->y()+ui->groupBox->height(),
                           width(),height()-ui->groupBox->y()-ui->groupBox->height());

}

void MainWindow::loadNewFile()
{
    QString filename = QFileDialog::getOpenFileName(this,"选择点云",
                                                    "/Users/joe/Codes/QtProjects/t-sne for comparison/data/highdims/featuremaps","PLY Files (*.txt)");

    if(filename == "")
        return;
//    qDebug()<<"111111";
    m_glwiget->distance = 1.5* m_glwiget->m_objloader->loadPtsFromPly(filename);
//    qDebug()<<"222222";
    m_glwiget->m_objloader->BuildPtsVBO();
    m_glwiget->m_objloader->BuildLineVBO();
//    qDebug()<<"333333";


    m_glwiget->update();

    ui->cbxHistories->addItem(filename);
}

void MainWindow::UpdateCameraPose(float scale, float hor, float ver)
{
    ui->spinDist->setValue(scale);
    ui->spinHor->setValue(hor);
    ui->spinVer->setValue(ver);
}

void MainWindow::UpdateParameters()
{
    m_glwiget->m_pointSize = ui->spinPointSize->value();
    m_glwiget->m_isColored = ui->ckbColored->isChecked();
    m_glwiget->scale = ui->spinDist->value();
    m_glwiget->m_horAngle = ui->spinHor->value();
    m_glwiget->m_verAngle = ui->spinVer->value();
    m_glwiget->m_isShowLine = ui->ckbShowLine->isChecked();
    m_glwiget->update();
}

void MainWindow::StartViewingTimer()
{
    if(m_glwiget->m_viewingTimer.isActive())
    {
        m_glwiget->m_viewingTimer.stop();
    }
    else
    {
        m_glwiget->m_viewingTimer.setInterval(10);
        m_glwiget->m_viewingTimer.start();
    }
}

void MainWindow::slot_cbxhistories()
{
    m_glwiget->distance = 1.5* m_glwiget->m_objloader->loadPtsFromPly(ui->cbxHistories->currentText());
    m_glwiget->m_objloader->BuildPtsVBO();
    m_glwiget->m_objloader->BuildLineVBO();
    m_glwiget->update();
}

void MainWindow::UpdateLabels(const QVector<QPair<int, QVector2D> > &labelPos)
{
//    qDebug() << "update labels";
    for(int i=0; i<m_labels.size(); ++i)
    {
        m_labels[i]->close();
        delete m_labels[i];
    }
    m_labels.clear();
    for (int i = 0; i < labelPos.size(); i++)
    {
        int label = labelPos[i].first;
        QVector2D pos = labelPos[i].second;

        QLabel *pointLabel = new QLabel(m_glwiget);
        pointLabel->setFont(QFont("New Times Roman", 15));
        pointLabel->setStyleSheet("QLabel{color:#FF0000;}");
        pointLabel->setText(QString::number(label));
        pointLabel->move(pos.x(), pos.y());
        pointLabel->show();
        m_labels.push_back(pointLabel);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

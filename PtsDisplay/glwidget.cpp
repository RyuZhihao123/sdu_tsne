#include "glwidget.h"

#define VERTEX_ATTRIBUTE  0
#define COLOUR_ATTRIBUTE  1
#define NORMAL_ATTRIBUTE  2
#define TEXTURE_ATTRIBUTE 3

GLWidget::GLWidget(QWidget *parent) :
    QOpenGLWidget(parent),
    distance(10.0),scale(1.0),m_horAngle(45.0),m_verAngle(0.0),
    m_eyeDist(QVector3D(0,0,0))
{
    this->setFocusPolicy(Qt::StrongFocus);
    m_lineProgram = NULL;
    m_pointProgram = NULL;

    connect(&m_viewingTimer,SIGNAL(timeout()),this,SLOT(OnViewingTimer()));
}

// 初始化shader program
void GLWidget::initShaders(QOpenGLShaderProgram*& m_program,const QString& shaderName,
                           bool v = false,bool c = false, bool n = false, bool t=false)
{

    m_program = new QOpenGLShaderProgram(this);

    m_program->addShaderFromSourceFile(QOpenGLShader::Vertex,  QString(":/shader/res/%1VShader.glsl").arg(shaderName));
    m_program->addShaderFromSourceFile(QOpenGLShader::Fragment,QString(":/shader/res/%1FShader.glsl").arg(shaderName));

    if(v)
        m_program->bindAttributeLocation("a_position",VERTEX_ATTRIBUTE);
    if(c)
        m_program->bindAttributeLocation("a_color"   ,COLOUR_ATTRIBUTE);
    if(n)
        m_program->bindAttributeLocation("a_normal"  ,NORMAL_ATTRIBUTE);
    if(t)
        m_program->bindAttributeLocation("a_texcoord",TEXTURE_ATTRIBUTE);

    m_program->link();
    m_program->bind();
}

// 设置当前shader program
void GLWidget::setupShaders(QOpenGLShaderProgram *&m_program)
{
    m_program->bind();

    m_program->setUniformValue("mat_projection",m_projectMatrix);
    m_program->setUniformValue("mat_view",m_viewMatrix);
}

void GLWidget::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(1.0,1.0,1.00,1.0);

    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    //glEnable(GL_MULTISAMPLE); // 抗锯齿

    glShadeModel(GL_SMOOTH);
    glEnable(GL_POINT_SMOOTH);
    glEnable(GL_BLEND);

    initShaders(m_pointProgram,"Points",true,true,false,false);
    initShaders(m_lineProgram,"Graph",true,false,false,false);

    m_objloader = new ObjLoader();
}

void GLWidget::resizeGL(int w, int h)
{
    glViewport(0,0,width(),height());

    m_projectMatrix.setToIdentity();
    m_projectMatrix.perspective(45.0f,(float)w/(float)h,0.001f,1000.0f);
}

void GLWidget::paintGL()
{
    // 设置Mesh的显示模式
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_eyePos = m_eyeDist+QVector3D(scale*distance*cos(PI*m_verAngle/180.0)*cos(PI*m_horAngle/180.0),
                                   scale*distance*sin(PI*m_verAngle/180.0),
                                   scale*distance*cos(PI*m_verAngle/180.0)*sin(PI*m_horAngle/180.0));

    m_viewMatrix.setToIdentity();
    m_viewMatrix.lookAt(m_eyePos,m_eyeDist,QVector3D(0,1,0));

    m_modelMat.setToIdentity();

    // 如果是显示3D模型
    if(m_isShowLine)
    {
        //qDebug()<<"Render Mesh";
        setupShaders(m_lineProgram);
        m_lineProgram->setUniformValue("viewPos",m_eyePos*QVector3D(-1.0,1.0,-1.0f));
        m_objloader->renderLines(m_lineProgram,m_modelMat);
    }
    // 如果是显示点云信息
    //if(m_displayMode == DISPLAY_MODE::_POINT_CLOUD)
    {

        glPointSize(m_pointSize);
        setupShaders(m_pointProgram);
        m_pointProgram->setUniformValue("isColor",m_isColored);
        m_objloader->renderPts(m_pointProgram,m_modelMat);
    }


    QMatrix4x4 M, V, P;
    M = m_modelMat;
    V = m_viewMatrix;
    P = m_projectMatrix;

    QMatrix4x4 PVM = P*V*M;

    QVector<QPair<int, QVector2D>> labelPos;
    // compute x,y for each label
    for (int i = 0; i < m_objloader->m_vertices.size(); i++)
    {
        QVector4D tmp = PVM*QVector4D(m_objloader->m_vertices[i], 1.f);
        QVector4D tmp2 = tmp/tmp.w();
//        QVector4D tmp2 = tmp;
//        qDebug() << tmp2;

        float x = tmp2.x()*width()/2 + width()/2;
        float y = height() - (tmp2.y()*height()/2 +height()/2);

//        qDebug() << x << " " << y;
        labelPos.append(QPair<int, QVector2D>(i, QVector2D(x, y)));
    }

    // emit the signal to MainWindow
    emit drawLabel(labelPos);
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    m_clickpos = event->pos();
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::LeftButton)
    {
        QPoint cur = event->pos();

        double dx = (cur.x() - m_clickpos.x())/5.0;
        double dy = (cur.y() - m_clickpos.y())/5.0;

        m_horAngle +=dx;
        if(m_verAngle+dy <89.0 && m_verAngle+dy>-89.0)
            m_verAngle +=dy;

        if(m_horAngle<=-360.0f)
            m_horAngle += 360.0f;
        if(m_horAngle>=360.0f)
            m_horAngle -= 360.0f;



        m_clickpos = cur;

        emit sig_cameraPose(scale,m_horAngle,m_verAngle);
        update();
    }
}

void GLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    event->pos();   // nothing to do........
}

void GLWidget::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_W || e->key() == Qt::Key_Up)
    {
        m_eyeDist.setY( m_eyeDist.y() + 0.1f);
    }
    if(e->key() == Qt::Key_S || e->key() == Qt::Key_Down)
    {
        m_eyeDist.setY( m_eyeDist.y() - 0.1f);
    }

    update();
}

void GLWidget::wheelEvent(QWheelEvent *event)
{
    double ds = 0.03;
    if(event->delta()>0 && scale-ds>0)
        scale-=ds;
    else if(event->delta()<0)
        scale+=ds;

    emit sig_cameraPose(scale,m_horAngle,m_verAngle);
    update();
}

void GLWidget::OnViewingTimer()
{
    m_horAngle +=1;
    update();
}

GLWidget::~GLWidget(){}

#include "objloader.h"
#define VERTEX_ATTRIBUTE  0
#define COLOUR_ATTRIBUTE  1
#define NORMAL_ATTRIBUTE  2
#define TEXTURE_ATTRIBUTE 3

QString g_backupColor_filepath = ":/shader/res/tsne_backupcolors";

ObjLoader::ObjLoader()
{
    this->initializeOpenGLFunctions();
    this->LoadBackupColors();
}

void ObjLoader::BuildPtsVBO()
{
    if(m_pointVBO.vbo.isCreated())
        m_pointVBO.vbo.release();

    // Create Points VBO
    m_pointVBO.count = data.size()/6;

    m_pointVBO.vbo.create();
    m_pointVBO.vbo.bind();
    m_pointVBO.vbo.allocate(data.constData(),data.count()*sizeof(GLfloat));

    data.clear();
}

float _max(float a,float b) { return (a>b)?a:b; }

void ObjLoader::BuildLineVBO()
{
    if(m_lineVBO.vbo.isCreated())
        m_lineVBO.vbo.release();

    // Create Mesh VBO
    m_lineVBO.count = data_1.size()/3;

    m_lineVBO.vbo.create();
    m_lineVBO.vbo.bind();
    m_lineVBO.vbo.allocate(data_1.constData(),data_1.count()*sizeof(GLfloat));

    data_1.clear();
}

float ObjLoader::loadPtsFromPly(const QString &pathObj)
{
    QFile file(pathObj);

    file.open(QIODevice::ReadOnly);
    QTextStream ts(&file);
    float minx = 1000000.0f;
    float maxx = -100000.0f;
    float miny = 1000000.0f;
    float maxy = -100000.0f;
    float minz = 1000000.0f;
    float maxz = -100000.0f;

    m_nodes.clear();
    m_vertices.clear();
    m_colors.clear();
    data.clear();
    data_1.clear();

    // process TRUNCK
    while(!ts.atEnd())
    {
        QStringList line= ts.readLine().split(QRegExp("\\s+"));
        line.removeAll("");

        if( line.size() == 0)
            continue;

        if(line[0][0] == "G")  // 接下来要读取Graph Adjacency List;
            break;
        Node node;
        for(int i=0; i<line.size()-1; ++i)   //  [0,1,2,...,size-2]  size-1位置是label
            node.push_back(line[i].toDouble());
        node.label = line.back().toInt();
        m_nodes.push_back(node);

        if(line.size() >= 3)  // 只可视化前3维
        {
            float x  = node[0];
            float y  = node[1];
            float z  = node[2];
            float r  = m_backupColors[node.label%m_backupColors.size()].red()/255.0f;
            float g  = m_backupColors[node.label%m_backupColors.size()].green()/255.0f;
            float b  = m_backupColors[node.label%m_backupColors.size()].blue()/255.0f;
            // push back into the container of algo data;
            m_vertices.push_back(QVector3D(x,y,z));
            m_colors.push_back(QVector3D(r,g,b));

            // Update min & max
            minx = (minx<x)?minx:x;
            maxx = (maxx>x)?maxx:x;
            miny = (miny<y)?miny:y;
            maxy = (maxy>y)?maxy:y;
            minz = (minz<z)?minz:z;
            maxz = (maxz>z)?maxz:z;
        }
    }
    qDebug()<<"加载完毕, 顶点数"<<m_vertices.size();

    while(!ts.atEnd())
    {
        QStringList line= ts.readLine().split(QRegExp("\\s+"));
        line.removeAll("");

        if( line.size() == 0)
            continue;

        int id = line[0].toInt();

        for(int i=1; i<line.size(); i+=2)
        {
            m_nodes[id].indices.push_back(line[i].toInt());
            m_nodes[id].dists.push_back(line[i+1].toDouble());
        }
    }

    // Move to center (构建data和data_1)
    QVector3D centerPos((maxx+minx)/2.0f, (maxy+miny)/2.0f, (maxz+minz)/2.0f);

    for(int i=0; i<m_vertices.size(); ++i)
    {
        m_vertices[i] -= centerPos;

        // push back into the DATA Vector for OpenGL Buffer
        data.push_back(m_vertices[i].x());data.push_back(m_vertices[i].y());data.push_back(m_vertices[i].z());
        data.push_back(m_colors[i].x());data.push_back(m_colors[i].y());data.push_back(m_colors[i].z());
    }
    // 构建 data_1
    for(int i=0; i<m_vertices.size(); ++i)
    {
        for(int t=0; t<m_nodes[i].indices.size(); ++t)
        {
            data_1.push_back(m_vertices[i].x());
            data_1.push_back(m_vertices[i].y());
            data_1.push_back(m_vertices[i].z());
            data_1.push_back(m_vertices[m_nodes[i].indices[t]].x());
            data_1.push_back(m_vertices[m_nodes[i].indices[t]].y());
            data_1.push_back(m_vertices[m_nodes[i].indices[t]].z());
        }
    }

    return _max(_max((maxy-miny),(maxz-minz)),(maxx-minx));
}

using namespace std;

void ObjLoader::renderPts(QOpenGLShaderProgram *&program, const QMatrix4x4 &modelMat)
{
    if(!m_pointVBO.vbo.isCreated() || m_pointVBO.count <0)
        return;

    program->setUniformValue("mat_model",modelMat);

    m_pointVBO.vbo.bind();

    program->enableAttributeArray(VERTEX_ATTRIBUTE);
    program->enableAttributeArray(COLOUR_ATTRIBUTE);

    program->setAttributeBuffer(VERTEX_ATTRIBUTE ,GL_FLOAT, 0,                3,6*sizeof(GLfloat));
    program->setAttributeBuffer(COLOUR_ATTRIBUTE ,GL_FLOAT, 3*sizeof(GLfloat),3,6*sizeof(GLfloat));

    glDrawArrays(GL_POINTS,0,this->m_pointVBO.count);
}

void ObjLoader::renderLines(QOpenGLShaderProgram *&program, const QMatrix4x4 &modelMat)
{
    if(!m_lineVBO.vbo.isCreated() || m_lineVBO.count <0)
        return;

    program->setUniformValue("mat_model",modelMat);

    m_lineVBO.vbo.bind();

    program->enableAttributeArray(VERTEX_ATTRIBUTE);
    program->setAttributeBuffer(VERTEX_ATTRIBUTE ,GL_FLOAT, 0,                3,3*sizeof(GLfloat));

    glDrawArrays(GL_LINES,0,this->m_lineVBO.count);
}


void ObjLoader::LoadBackupColors()
{
    QFile file(g_backupColor_filepath);
    file.open(QIODevice::ReadOnly);
    QDataStream ds(&file);

    while(!ds.atEnd())
    {
        int r,g,b;
        ds>>r>>g>>b;

        m_backupColors.push_back(QColor(r,g,b));
    }
    qDebug()<<"颜色加载完毕:"<<m_backupColors.size();
    file.close();
}

void ObjLoader::clearAll()
{

}


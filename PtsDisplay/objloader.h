#ifndef OBJLOADER_H
#define OBJLOADER_H
#include <QOpenGLBuffer>
#include <QOpenGLTexture>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions>
#include <QFile>
#include <QTextStream>
#include <QFileInfo>
#include <QDebug>
#include <QTime>
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <QVector>


struct Node
{
    // feature vector (d-dimension)
    QVector<double> data;
    int label = 0;

    // knn graph information
    QVector<int>  indices;
    QVector<double> dists;

    void push_back(const double& t) {data.push_back(t);}
    double operator[](long long id) {return data[id];}
};

class Buffer
{
public:
    QOpenGLBuffer vbo;
    int count;
};

struct Face
{
    int id[3];
};

class ObjLoader : public QOpenGLFunctions
{
public:
    QVector<QVector3D> m_vertices;
    QVector<QVector3D> m_normals;
    QVector<QVector3D> m_colors;
    QVector<GLfloat> data;
    QVector<GLfloat> data_1;

    QVector<Node> m_nodes;

    Buffer m_pointVBO;
    Buffer m_lineVBO;

    ObjLoader();

    float loadPtsFromPly(const QString& pathObj);

    QVector<QColor> m_backupColors;
    void LoadBackupColors();

    void BuildPtsVBO();
    void BuildLineVBO();

    void renderPts(QOpenGLShaderProgram*& program, const QMatrix4x4& modelMat);
    void renderLines(QOpenGLShaderProgram*& program, const QMatrix4x4& modelMat);

    void clearAll();

private:
    // KNN Graph - related

};

#endif // OBJLOADER_H

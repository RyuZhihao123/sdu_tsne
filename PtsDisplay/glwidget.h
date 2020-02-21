#ifndef GLWIDGET_H
#define GLWIDGET_H
#include <QMouseEvent>
#include <QKeyEvent>
#include <QWheelEvent>
#include <QTimer>
#include <QOpenGLWidget>
#include "objloader.h"
#include <cmath>
#define PI 3.1415926

class GLWidget  : public QOpenGLWidget , public QOpenGLFunctions
{
    Q_OBJECT

public:
    explicit GLWidget(QWidget *parent = 0);
    ~GLWidget();

    ObjLoader* m_objloader;
    QTimer m_viewingTimer;

    // DISPLAY PROPERTIES
    bool m_isShowLine = true;

    bool m_isColored = true;   // 是否显示顶点的颜色
    int m_pointSize = 3.0f;
    double distance;

    double scale;
    double m_horAngle,m_verAngle;  // theta alpha

signals:
    void drawLabel(const QVector<QPair<int, QVector2D>>& labelPos);

protected:
    void initializeGL();
    void resizeGL(int w, int h);

    void paintGL();

    // shader programs: OpenGL渲染控制
    QOpenGLShaderProgram* m_pointProgram;
    QOpenGLShaderProgram* m_lineProgram;

    void initShaders(QOpenGLShaderProgram *&m_program, const QString &shaderName, bool v, bool c, bool n, bool t);
    void setupShaders(QOpenGLShaderProgram*& m_program);

    // OpenGL Matrix相关
    QMatrix4x4 m_projectMatrix;
    QMatrix4x4 m_viewMatrix;
    QMatrix4x4 m_modelMat;
    QVector3D m_eyePos,m_eyeDist;

    // View control
    QPoint m_clickpos;

    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

    void wheelEvent(QWheelEvent* event);
    void keyPressEvent(QKeyEvent* e);

signals:
    void sig_cameraPose(float scale, float hor, float ver);

private slots:
    void OnViewingTimer();
};

#endif // GLWIDGET_H

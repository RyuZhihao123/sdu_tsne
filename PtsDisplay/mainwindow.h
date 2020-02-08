#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QScrollBar>
#include "glwidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    GLWidget* m_glwiget;

protected:
    void resizeEvent(QResizeEvent *event);

private slots:
    void UpdateCameraPose(float scale, float hor, float ver);
    void UpdateParameters();
    void StartViewingTimer();

    void loadNewFile();
    void slot_cbxhistories();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "widget.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    Widget* m_widget;

signals:
    void sig_aaa();

private slots:
    void slot_openGraph();
    void slot_saveGraph();
    void slot_calculateGraphLet();
    void slot_btnNext();

    void on_btnGen_clicked();

    Graph genGraph(int nodeNum = 500, int edgeNum = 499);

    void on_comboBox_activated(int index);

private:
    Ui::MainWindow *ui;
    int m_graphlet_id = 0;
};
#endif // MAINWINDOW_H

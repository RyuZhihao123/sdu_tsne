#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QTextStream>
#include <qdebug.h>
#include "widget.h"
#include <math.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


extern int glet_search_range;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

//    Widget* m_widget_0;
//    Widget* m_widget_1;


private slots:
    void slot_openGraph();
    void slot_saveGraph();
    void slot_calculateGraphLet();
    void slot_btnNext();

    void on_btnGen_clicked();

    Graph genGraph(int nodeNum = 500, int edgeNum = 499);

    void on_comboBox_activated(int index);

    void on_btnClear_clicked();

    void on_btnGFD_clicked();


    void on_btnSim_clicked();

    // read graph structure from fm_data generated from pytho
    Graph read_fm_data(const QString& fileName);

    // save similarities to file
    void savePointSims(const QVector<float>& matchScores, const QString& fileName);
    void saveEdgeSims(const MatchEdgeList& matchEdges, const QString& fileName);

    // compute the similarities between two graphs
    QVector<float> calcPointSims(Graph& g1, Graph& g2);
    MatchEdgeList calcEdgeSims(Graph& g1, Graph& g2, const QVector<float>& pointSims);

    void on_btnLoadFmData_clicked();

    void on_cbxRange_activated(int index);

    void on_cbxKernel_activated(int index);

    void on_cbxGFDCalc_activated(int index);

private:
    Ui::MainWindow *ui;
    int m_graphlet_id = 0;

    enum KernelFunc{
        COS,
        RBF,
        LAPLACIAN
    } m_kernel = COS;

    enum GFDCalc{
        ACCUM,
        CONCAT
    } m_gfd_cal = CONCAT;

    float applyKernel(const QVector<float>& vec1, const QVector<float>& vec2, KernelFunc func);

    float cosine(const QVector<float>& vec1, const QVector<float>& vec2);
    float rbf(const QVector<float>& vec1, const QVector<float>& vec2, float delta = 1.0);
    float laplacian(const QVector<float>& vec1, const QVector<float>& vec2, float delta = 1.0);

    float L1Distance(const QVector<float>& vec1, const QVector<float>& vec2);
    float L2Distance(const QVector<float>& vec1, const QVector<float>& vec2);

    QStringList m_filenames;
};
#endif // MAINWINDOW_H

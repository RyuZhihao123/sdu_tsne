#ifndef GRAPH_H
#define GRAPH_H
#define MAX_SEARCH_RANGE 3
#define ALL_GRAPHLET    21

#include <QVector>
#include <QPainter>
#include <cassert>
#include <QQueue>
#include <QTime>
#include <cmath>

struct Node    // 图
{
    float x,y;
    QVector<int> childs;

    Node():x(0),y(0){}
    Node(float x, float y): x(x),y(y) {}

    void addEdge(int id)  //
    {
        if(!childs.contains(id))
            childs.push_back(id);
    }
};

typedef QPair<int,QVector<int>> GraphLetNode;   // node and its adjacient edges
typedef QVector<GraphLetNode> GraphLet;         // graphlet representation

class Graph
{
public:
    Graph();
    QVector<Node> m_nodes;                   // 结点
    int cur_ID = 0;                          // 当前显示的graphlet编号
    QVector<GraphLet> m_cur_graphlets;       //  当前找到的

    int nodeNum() const;

    void addNode(const Node& n);
    void addEdge(int a, int b);

    void renderGraph(QPainter* painter);
    void renderCurGraphLets(QPainter* painter);

    // to do:
    Node *GetNode(int id);
    int HasNodeAt(QPoint p, float radius = 100);

    void GetGraphlets(int gid);   // 计算graphlets
    void ShowNextGraphlet();

    void clear();


    QVector<GraphLet> SearchGraphLet(int gid, int sid);
    QVector<float> calGFD(int sid);
    QVector<float> localGFD(int sid);  // return the feature vector of given node
private:
    // A family of functions for searching graphlets
    // Search graphlet from sid
    QVector<GraphLet> SearchGraphLet1(int sid);
    QVector<GraphLet> SearchGraphLet2(int sid);
    QVector<GraphLet> SearchGraphLet3(int sid);
    QVector<GraphLet> SearchGraphLet4(int sid);
    QVector<GraphLet> SearchGraphLet5(int sid);
    QVector<GraphLet> SearchGraphLet6(int sid);
    QVector<GraphLet> SearchGraphLet7(int sid);
    QVector<GraphLet> SearchGraphLet8(int sid);
    QVector<GraphLet> SearchGraphLet9(int sid);
    QVector<GraphLet> SearchGraphLet10(int sid);
    QVector<GraphLet> SearchGraphLet11(int sid);
    QVector<GraphLet> SearchGraphLet13(int sid);
    QVector<GraphLet> SearchGraphLet14(int sid);/// Bug...
    QVector<GraphLet> SearchGraphLet15(int sid);
    QVector<GraphLet> SearchGraphLet16(int sid);/// 1Bug...

};

#endif // GRAPH_H

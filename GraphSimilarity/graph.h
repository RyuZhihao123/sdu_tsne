#ifndef GRAPH_H
#define GRAPH_H
#include <QVector>
#include <QPainter>
#include <cassert>
#include <QQueue>
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

typedef QPair<int,QVector<int>> GraphLetNode;
typedef QVector<GraphLetNode> GraphLet;

class Graph
{
public:
    Graph();
    QVector<Node> m_nodes;                   // 结点
    int cur_ID = 0;                          // 当前显示的graphlet编号
    QVector<GraphLet> m_cur_graphlets;       //  当前找到的

    void addNode(const Node& n);
    void addEdge(int a, int b);

    void renderGraph(QPainter* painter);
    void renderCurGraphLets(QPainter* painter);

    // to do:
    Node *GetNode(int id);
    int HasNodeAt(QPoint p, float radius = 100);

    void GetGraphlets();   // 计算graphlets
    void ShowNextGraphlet();
    QVector<GraphLet> SearchGraphLet1(int sid);  // 以起始点sid，为起点搜索graphlet.
};

#endif // GRAPH_H

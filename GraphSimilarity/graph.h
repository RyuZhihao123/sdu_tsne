#ifndef GRAPH_H
#define GRAPH_H
#include <QVector>
#include <QPainter>
#include <cassert>
#include <QQueue>
struct Node
{
    float x,y;
    QVector<int> childs;

    Node():x(0),y(0){}
    Node(float x, float y): x(x),y(y) {}

    void addEdge(int id)
    {
        if(!childs.contains(id))
            childs.push_back(id);
    }
};

typedef QVector<Node> GraphLet;

class Graph
{
public:
    Graph();
    QVector<Node> m_nodes;            // 结点

    QVector<GraphLet> m_gl1;         //  - =

    void addNode(const Node& n);
    void addEdge(int a, int b);

    void renderGraph(QPainter* painter);

    // to do:
    Node GetNode(int id);
    int HasNodeAt(QPoint p, float radius = 100);

    QVector<GraphLet> SearchGraphLet1(int sid);  // 以起始点sid，为起点搜索graphlet.


};

#endif // GRAPH_H

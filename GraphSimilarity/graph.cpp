#include "graph.h"

Graph::Graph()
{

}

Node Graph::GetNode(int id)
{
    assert(id >= 0 && id < m_nodes.size());

    return this->m_nodes[id];
}

void Graph::addNode(const Node &n)
{
    this->m_nodes.push_back(n);
}

void Graph::addEdge(int a, int b)
{
    assert(a >= 0 && a<m_nodes.size());
    assert(b >= 0 && b<m_nodes.size());

    m_nodes[a].addEdge(b);
    m_nodes[b].addEdge(a);
}

void Graph::renderGraph(QPainter *painter)
{
    painter->setPen(QColor(60,60,60));
    painter->setBrush(QBrush(QColor(90,60,220)));

    for(int i=0; i<m_nodes.size(); ++i)
    {
        painter->drawEllipse(QPoint(m_nodes[i].x,m_nodes[i].y),6,6);
        painter->drawText(m_nodes[i].x - 5, m_nodes[i].y-8,QString::number(i));

        for(int t=0; t<m_nodes[i].childs.size(); ++t)
        {
            int cid = m_nodes[i].childs[t];
            painter->drawLine(m_nodes[i].x,m_nodes[i].y, m_nodes[cid].x, m_nodes[cid].y);
        }
    }
}

int Graph::HasNodeAt(QPoint p, float radius)
{
    int id = -1;
    float dist = INT_MAX;
    for(int i=0; i<m_nodes.size(); ++i)
    {
        float _dist = pow(m_nodes[i].x - p.x(),2) + pow(m_nodes[i].y-p.y(),2);

        if(_dist < dist && _dist< radius)
        {
            id = i;
            dist = _dist;
        }
    }
    return id;
}

QVector<GraphLet> Graph::SearchGraphLet1(int sid)
{
    // g4: n0->n1, n1->n2, n1->n3
    QVector<bool> visited(m_nodes.size(),false);
    visited[sid] = true;

    QVector<GraphLet> glets;

    return glets;
}




#include "graph.h"
#include <QDebug>
Graph::Graph()
{

}

Node* Graph::GetNode(int id)
{
    assert(id >= 0 && id < m_nodes.size());

    return &this->m_nodes[id];
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

void Graph:: renderGraph(QPainter *painter)
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

void Graph::renderCurGraphLets(QPainter *painter)
{
    if(m_cur_graphlets.isEmpty())
        return;
    painter->setPen(QPen(QColor(255,0,0),3));

    painter->setBrush(QBrush(QColor(255,0,0)));
    qDebug()<<"更新";
    for(int i=0; i<m_cur_graphlets[cur_ID].size(); ++i)
    {
        int n0 = m_cur_graphlets[cur_ID][i].first;
        qDebug()<<m_cur_graphlets[cur_ID][i].first;

        painter->drawEllipse(QPoint(m_nodes[n0].x,m_nodes[n0].y),6,6);

        for(int t=0; t<m_cur_graphlets[cur_ID][i].second.size(); ++t)
        {
            int n2 = m_cur_graphlets[cur_ID][i].second[t];
            qDebug()<<" "<<m_cur_graphlets[cur_ID][i].second[t];
            painter->drawLine(m_nodes[n0].x,m_nodes[n0].y, m_nodes[n2].x, m_nodes[n2].y);
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

void Graph::ShowNextGraphlet()
{
    cur_ID = (cur_ID+1) % m_cur_graphlets.size();
}

void Graph::GetGraphlets()
{
    m_cur_graphlets.clear();
    cur_ID = 0;

    for(int i=0; i<m_nodes.size(); ++i)
    {
        m_cur_graphlets.append(SearchGraphLet1(i));
        // to do......
    }
}

QVector<GraphLet> Graph::SearchGraphLet1(int sid)   // 输入的当前以那个点为起点找graphlet
{
    // g4: n0->n1, n1->n2, n1->n3
    QVector<bool> visited(m_nodes.size(),false);
    visited[sid] = true;

    QVector<GraphLet> glets;

    int n0 = sid;   //

    for(int i = 0; i<m_nodes[sid].childs.size(); ++i)
    {
        int n1 = m_nodes[sid].childs[i];
        Node* t1 = GetNode(n1);

        for(int k=0; k<t1->childs.size(); ++k)
        {
            int n2 = t1->childs[k];
            if(n2 == n0)
                continue;
            for(int m=k+1; m<t1->childs.size(); ++m)
            {
                int n3 = t1->childs[m];
                if(n3 == n0)
                    continue;
                GraphLet tmp;
                GraphLetNode m0,m1,m2,m3;
                m0.first = n0;
                m1.first = n1;
                m2.first = n2;
                m3.first = n3;
                m0.second.append(n1);
                m1.second.append(n2);
                m1.second.append(n3);
                tmp.append(m0);
                tmp.append(m1);
                tmp.append(m2);
                tmp.append(m3);

                glets.append(tmp);
            }
        }
    }

    return glets;
}




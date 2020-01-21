#include "graph.h"
#include <QDebug>
Graph::Graph()
{

}

int Graph::nodeNum() const
{
    return m_nodes.size();
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
            qDebug() << " " << n2;
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

void Graph::clear()
{
    m_nodes.clear();
}


void Graph::GetGraphlets(int gid)
{
    assert(gid >= 0 && gid < ALL_GRAPHLET);

    QTime time;
    time.start();

    m_cur_graphlets.clear();
    cur_ID = 0;
    for(int i=0; i<m_nodes.size(); ++i)
    {
        m_cur_graphlets.append(SearchGraphLet(gid, i));
    }
    qDebug() << "Compute graphlets: " << gid << " cost " << time.elapsed() << "ms";
}


QVector<GraphLet> Graph::SearchGraphLet(int gid, int sid)
{
    switch (gid) {
    case 0:
        return SearchGraphLet1(sid);
    case 1:
        return SearchGraphLet2(sid);
    case 2:
        return SearchGraphLet3(sid);
    case 3:
        return SearchGraphLet4(sid);
    case 4:
        return SearchGraphLet5(sid);
    case 5:
        return SearchGraphLet6(sid);
    case 6:
        return SearchGraphLet7(sid);
    case 7:
        return SearchGraphLet8(sid);
    case 8:
        return SearchGraphLet9(sid);
    case 9:
        return SearchGraphLet10(sid);
    case 10:
        return SearchGraphLet11(sid);
    case 12:
        qDebug() << "SearchGraphLet13";
        return SearchGraphLet13(sid);
    case 13:
        return SearchGraphLet14(sid);
    case 14:
        return SearchGraphLet15(sid);
    case 15:
        return SearchGraphLet16(sid);
    default:
        return SearchGraphLet1(sid);
    }
}

QVector<float> Graph::calGFD(int sid)
{
    QVector<float> GFD;

    int sum = 0;
    for (int i = 0; i < ALL_GRAPHLET; i++)
    {
        int f = SearchGraphLet(i, sid).size();
        GFD.push_back((float)f);
        sum += f;
    }

    for (int i = 0; i < GFD.size(); i++)
    {
        GFD[i] /= sum;
    }

    return GFD;
}

QVector<float> Graph::localGFD(int sid)
{
    QVector<QVector<float>> allGFDs;

    typedef QPair<int, int> tuple;  // first is level, second is node

    QVector<bool> visited(m_nodes.size(), false);// ensure each node is visited once

    visited[sid] = true;

    QQueue<tuple> q;
    q.enqueue(tuple(0, sid));

    int llevel = 0;
    // BFS for MAX_SEARCH_RANGE times
    while(!q.isEmpty())
    {
        // top
        tuple t = q.head();
        int clevel = t.first;
        int cnode = t.second;


        qDebug() << "visit:" << cnode;

        if (clevel != llevel)
        {
            llevel = clevel;
            if (clevel >= MAX_SEARCH_RANGE)
            {
                qDebug() << "max level reached.";
                break;
            }
        }


        QVector<float> GFD = calGFD(cnode);
        allGFDs.push_back(GFD);


        // pop
        q.dequeue();

        // push
        Node* n = GetNode(cnode);
        for (int i = 0; i< n->childs.size(); i++)
        {
            if (!visited[n->childs[i]])
            {
                visited[n->childs[i]] = true;
                q.enqueue(tuple(clevel+1, n->childs[i]));
            }
        }
    }

    // average feature vector over all nodes within the range
    QVector<float> v(ALL_GRAPHLET);
    for (int i = 0; i < v.size(); i++)
    {
        for (int j = 0; j < allGFDs.size(); j++) {
            v[i] += allGFDs[j][i];
        }
        v[i] /= allGFDs.size();
    }
    return v;
}

QVector<GraphLet> Graph::SearchGraphLet1(int sid)   // 输入的当前以那个点为起点找graphlet
{
    // g1: n0->n1, n1->n2
    QVector<bool> visited(m_nodes.size(),false);
    QVector<GraphLet> glets;

    int n0 = sid;
    visited[n0] = true;

    for(int i = 0; i<m_nodes[n0].childs.size(); ++i)
    {
        int n1 = m_nodes[n0].childs[i];
        visited[n1] = true;

        Node* t1 = GetNode(n1);
        for(int k=0; k<t1->childs.size(); ++k)
        {
            int n2 = t1->childs[k];
            if(visited[n2])
                continue;

            GraphLet tmp;
            GraphLetNode m0,m1,m2;
            m0.first = n0;
            m1.first = n1;
            m2.first = n2;
            m0.second.append(n1);
            m1.second.append(n2);

            tmp.append(m0);
            tmp.append(m1);
            tmp.append(m2);

            glets.append(tmp);
        }
    }
    return glets;
}



QVector<GraphLet> Graph::SearchGraphLet2(int sid)   // 输入的当前以那个点为起点找graphlet
{
    // g1: n0->n1, n1->n2, n2->n0
    QVector<GraphLet> glets;

    int n0 = sid;
    Node* t0 = GetNode(n0);

    for(int i = 0; i<t0->childs.size(); ++i)
    {
        int n1 = t0->childs[i];
        Node* t1 = GetNode(n1);

        for(int k=0; k<t1->childs.size(); ++k)
        {
            int n2 = t1->childs[k];
            if (n2 == n0)
                continue;

            Node* t2 = GetNode(n2);
            for (int m=0; m < t2->childs.size(); ++m) {
                int n3 = t2->childs[m];

                if(n3 == n0) {
                    GraphLet tmp;
                    GraphLetNode m0,m1,m2;
                    m0.first = n0;
                    m1.first = n1;
                    m2.first = n2;
                    m0.second.append(n1);
                    m1.second.append(n2);
                    m2.second.append(n0);

                    tmp.append(m0);
                    tmp.append(m1);
                    tmp.append(m2);

                    glets.append(tmp);
                }
            }
        }
    }
    return glets;
}

QVector<GraphLet> Graph::SearchGraphLet3(int sid)
{
    // g1: n0->n1, n1->n2, n2->n3
    QVector<GraphLet> glets;

    int n0 = sid;
    Node* t0 = GetNode(n0);

    for(int i = 0; i<t0->childs.size(); ++i)
    {
        int n1 = t0->childs[i];
        Node* t1 = GetNode(n1);

        for(int k=0; k<t1->childs.size(); ++k)
        {
            int n2 = t1->childs[k];
            if(n2 == n0)
                continue;

            Node* t2 = GetNode(n2);
            for(int m=0; m<t2->childs.size(); ++m)
            {
                int n3 = t2->childs[m];
                if (n3 == n1 || n3 == n0)
                    continue;

                GraphLet tmp;
                GraphLetNode m0, m1, m2, m3;
                m0.first = n0;
                m1.first = n1;
                m2.first = n2;
                m3.first = n3;

                m0.second.append(n1);
                m1.second.append(n2);
                m2.second.append(n3);

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

QVector<GraphLet> Graph::SearchGraphLet4(int sid)
{
    // g4: n0->n1, n1->n2, n1->n3
    QVector<GraphLet> glets;

    int n0 = sid;   //
    Node* t0 = GetNode(n0);

    for(int i = 0; i<t0->childs.size(); ++i)
    {
        int n1 = t0->childs[i];
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


QVector<GraphLet> Graph::SearchGraphLet5(int sid)
{
    // g1: n0->n1, n1->n2, n2->n3, n3->n0
    QVector<GraphLet> glets;

    int n0 = sid;
    Node* t0 = GetNode(n0);

    for(int i = 0; i<t0->childs.size(); ++i)
    {
        int n1 = t0->childs[i];
        Node* t1 = GetNode(n1);

        for(int k=0; k<t1->childs.size(); ++k)
        {
            int n2 = t1->childs[k];
            if(n2 == n0)
                continue;

            Node* t2 = GetNode(n2);
            for(int m=0; m<t2->childs.size(); ++m)
            {
                int n3 = t2->childs[m];
                if (n3 == n1 || n3 == n0)
                    continue;

                Node* t3 = GetNode(n3);
                for(int n=0; n<t3->childs.size(); ++n)
                {
                    int n4 = t3->childs[n];
                    if (n4 == n0)
                    {
                        GraphLet tmp;
                        GraphLetNode m0, m1, m2, m3;
                        m0.first = n0;
                        m1.first = n1;
                        m2.first = n2;
                        m3.first = n3;

                        m0.second.append(n1);
                        m1.second.append(n2);
                        m2.second.append(n3);
                        m3.second.append(n0);

                        tmp.append(m0);
                        tmp.append(m1);
                        tmp.append(m2);
                        tmp.append(m3);

                        glets.append(tmp);
                    }
                }
            }
        }

    }
    return glets;
}

QVector<GraphLet> Graph::SearchGraphLet6(int sid)
{
    // g4: n0->n1, n1->n2, n1->n3, n2->n3
    QVector<GraphLet> glets;

    int n0 = sid;   //
    Node* t0 = GetNode(n0);

    for(int i = 0; i<t0->childs.size(); ++i)
    {
        int n1 = t0->childs[i];
        Node* t1 = GetNode(n1);

        for(int k=0; k<t1->childs.size(); ++k)
        {
            int n2 = t1->childs[k];
            if(n2 == n0)
                continue;
            Node* t2 = GetNode(n2);
            for(int m=0; m<t2->childs.size(); ++m)
            {
                int n3 = t2->childs[m];
                if(n3 == n0 || n3 == n1)
                    continue;

                Node* t3 = GetNode(n3);
                for (int n = 0; n < t3->childs.size(); ++n) {
                    int n4 = t3->childs[n];
                    if (n4 == n1) {
                        GraphLet tmp;
                        GraphLetNode m0,m1,m2,m3;
                        m0.first = n0;
                        m1.first = n1;
                        m2.first = n2;
                        m3.first = n3;
                        m0.second.append(n1);
                        m1.second.append(n2);
                        m2.second.append(n3);
                        m3.second.append(n1);
                        tmp.append(m0);
                        tmp.append(m1);
                        tmp.append(m2);
                        tmp.append(m3);

                        glets.append(tmp);
                    }
                }
            }
        }
    }

    return glets;
}

QVector<GraphLet> Graph::SearchGraphLet7(int sid)
{
    // g1: n0->n1, n1->n2, n2->n3, n3->n0, n3->n1
    QVector<GraphLet> glets;

    int n0 = sid;
    Node* t0 = GetNode(n0);

    for(int i = 0; i<t0->childs.size(); ++i)
    {
        int n1 = t0->childs[i];
        Node* t1 = GetNode(n1);

        for(int k=0; k<t1->childs.size(); ++k)
        {
            int n2 = t1->childs[k];
            if(n2 == n0)
                continue;

            Node* t2 = GetNode(n2);
            for(int m=0; m<t2->childs.size(); ++m)
            {
                int n3 = t2->childs[m];
                if (n3 == n1 || n3 == n0)
                    continue;

                Node* t3 = GetNode(n3);
                for(int n=0; n<t3->childs.size(); ++n)
                {
                    int n4 = t3->childs[n];
                    for (int j = n+1; j<t3->childs.size(); ++j) {
                        int n5 = t3->childs[j];
                        if (n4 == n0 && n5 == n1)
                        {

                            GraphLet tmp;
                            GraphLetNode m0, m1, m2, m3;
                            m0.first = n0;
                            m1.first = n1;
                            m2.first = n2;
                            m3.first = n3;

                            m0.second.append(n1);
                            m1.second.append(n2);
                            m2.second.append(n3);
                            m3.second.append(n0);
                            m3.second.append(n1);

                            tmp.append(m0);
                            tmp.append(m1);
                            tmp.append(m2);
                            tmp.append(m3);

                            glets.append(tmp);
                        }
                    }


                }
            }
        }

    }
    return glets;
}

QVector<GraphLet> Graph::SearchGraphLet8(int sid)
{
    // g1: n0->n1, n1->n2, n2->n0, n2->n3, n3->n0, n3->n1
    QVector<GraphLet> glets;

    int n0 = sid;
    Node* t0 = GetNode(n0);

    for(int i = 0; i<t0->childs.size(); ++i)
    {
        int n1 = t0->childs[i];
        Node* t1 = GetNode(n1);

        for(int k=0; k<t1->childs.size(); ++k)
        {
            int n2 = t1->childs[k];
            if (n2 == n0)
                continue;

            Node* t2 = GetNode(n2);
            for (int m=0; m < t2->childs.size(); ++m) {
                int n3 = t2->childs[m];

                if(n3 == n0) {
                    for (int n = m+1; n < t2->childs.size(); ++n) {
                        n3 = t2->childs[n];

                        Node* t3 = GetNode(n3);
                        for (int j = 0; j < t3->childs.size(); ++j) {
                            for (int jj=j+1; jj < t3->childs.size(); ++jj) {
                                int n4 = t3->childs[j];
                                int n5 = t3->childs[jj];
                                if (n4 == n0 && n5 == n1) {
                                    GraphLet tmp;
                                    GraphLetNode m0,m1,m2, m3;
                                    m0.first = n0;
                                    m1.first = n1;
                                    m2.first = n2;
                                    m3.first = n3;
                                    m0.second.append(n1);
                                    m1.second.append(n2);
                                    m2.second.append(n0);
                                    m2.second.append(n3);
                                    m3.second.append(n0);
                                    m3.second.append(n1);

                                    tmp.append(m0);
                                    tmp.append(m1);
                                    tmp.append(m2);
                                    tmp.append(m3);

                                    glets.append(tmp);
                                }
                            }
                        }

                    }
                }
            }
        }
    }
    return glets;
}

QVector<GraphLet> Graph::SearchGraphLet9(int sid)
{
    // g1: n0->n1, n1->n2, n2->n3, n3->n4
    QVector<GraphLet> glets;

    int n0 = sid;
    Node* t0 = GetNode(n0);

    for(int i = 0; i<t0->childs.size(); ++i)
    {
        int n1 = t0->childs[i];
        Node* t1 = GetNode(n1);

        for(int k=0; k<t1->childs.size(); ++k)
        {
            int n2 = t1->childs[k];
            if(n2 == n0)
                continue;

            Node* t2 = GetNode(n2);
            for(int m=0; m<t2->childs.size(); ++m)
            {
                int n3 = t2->childs[m];
                if (n3 == n1 || n3 == n0)
                    continue;

                Node* t3 = GetNode(n3);
                for (int n = 0; n<t3->childs.size(); ++n)
                {
                    int n4 = t3->childs[n];
                    if (n4 == n2 || n4 == n1 || n4 == n0)
                        continue;

                    GraphLet tmp;
                    GraphLetNode m0, m1, m2, m3, m4;
                    m0.first = n0;
                    m1.first = n1;
                    m2.first = n2;
                    m3.first = n3;
                    m4.first = n4;

                    m0.second.append(n1);
                    m1.second.append(n2);
                    m2.second.append(n3);
                    m3.second.append(n4);

                    tmp.append(m0);
                    tmp.append(m1);
                    tmp.append(m2);
                    tmp.append(m3);
                    tmp.append(m4);

                    glets.append(tmp);
                }
            }
        }

    }
    return glets;
}

QVector<GraphLet> Graph::SearchGraphLet10(int sid)
{
    // g10: n0->n1, n1->n2, n2->n3, n2->n4
    QVector<GraphLet> glets;

    int n0 = sid;
    Node* t0 = GetNode(n0);

    for(int i = 0; i<t0->childs.size(); ++i)
    {
        int n1 = t0->childs[i];
        Node* t1 = GetNode(n1);

        for (int j = 0; j<t1->childs.size(); j++) {
            int n2 = t1->childs[j];
            if (n2 == n0)
                continue;

            Node* t2 = GetNode(n2);
            for(int k=0; k<t2->childs.size(); ++k)
            {
                int n3 = t2->childs[k];
                if(n3 == n0 || n3 == n1)
                    continue;

                for(int m=k+1; m<t2->childs.size(); ++m)
                {
                    int n4 = t2->childs[m];
                    if(n4 == n0 || n4 == n1)
                        continue;

                    GraphLet tmp;
                    GraphLetNode m0,m1,m2,m3,m4;
                    m0.first = n0;
                    m1.first = n1;
                    m2.first = n2;
                    m3.first = n3;
                    m4.first = n4;

                    m0.second.append(n1);
                    m1.second.append(n2);
                    m2.second.append(n3);
                    m2.second.append(n4);

                    tmp.append(m0);
                    tmp.append(m1);
                    tmp.append(m2);
                    tmp.append(m3);
                    tmp.append(m4);

                    glets.append(tmp);
                }
            }
        }
    }

    return glets;
}

QVector<GraphLet> Graph::SearchGraphLet11(int sid)
{
    // g11
    QVector<GraphLet> glets;

    int n0 = sid;
    Node* t0 = GetNode(n0);

    for(int i = 0; i<t0->childs.size(); ++i)
    {
        int n1 = t0->childs[i];

        for (int j = i+1; j<t0->childs.size(); ++j) {
            int n2 = t0->childs[j];
            if (n2 == n0)
                continue;

            for (int k = j+1; k < t0->childs.size(); ++k) {
                int n3 = t0->childs[k];
                if (n3 == n0 || n3 == n1)
                    continue;

                for (int m = k+1; m < t0->childs.size(); ++m) {
                    int n4 = t0->childs[m];
                    if (n4 == n0 || n4 == n1 || n4 == n2)
                        continue;

                    GraphLet tmp;
                    GraphLetNode m0,m1,m2,m3,m4;
                    m0.first = n0;
                    m1.first = n1;
                    m2.first = n2;
                    m3.first = n3;
                    m4.first = n4;

                    m0.second.append(n1);
                    m0.second.append(n2);
                    m0.second.append(n3);
                    m0.second.append(n4);

                    tmp.append(m0);
                    tmp.append(m1);
                    tmp.append(m2);
                    tmp.append(m3);
                    tmp.append(m4);

                    glets.append(tmp);
                }
            }
        }
    }

    return glets;
}

QVector<GraphLet> Graph::SearchGraphLet13(int sid)
{
    // g10: n0->n1, n1->n2, n2->n3, n3->n4, n4->n2
    QVector<GraphLet> glets;

    int n0 = sid;
    Node* t0 = GetNode(n0);

    for(int i = 0; i<t0->childs.size(); ++i)
    {
        int n1 = t0->childs[i];
        Node* t1 = GetNode(n1);

        for (int j = 0; j<t1->childs.size(); j++) {
            int n2 = t1->childs[j];
            if (n2 == n0)
                continue;

            Node* t2 = GetNode(n2);
            for(int k=0; k<t2->childs.size(); ++k)
            {
                int n3 = t2->childs[k];
                if(n3 == n0 || n3 == n1)
                    continue;

                Node* t3 = GetNode(n3);
                for(int m=0; m<t3->childs.size(); ++m)
                {
                    int n4 = t3->childs[m];
                    if(n4 == n0 || n4 == n1 || n4 == n2)
                        continue;

                    Node* t4 = GetNode(n4);
                    for (int n=0; n < t4->childs.size(); ++n)
                    {
                        int n5 = t4->childs[n];
                        if(n5 == n2)
                        {
                            GraphLet tmp;
                            GraphLetNode m0,m1,m2,m3,m4;
                            m0.first = n0;
                            m1.first = n1;
                            m2.first = n2;
                            m3.first = n3;
                            m4.first = n4;

                            m0.second.append(n1);
                            m1.second.append(n2);
                            m2.second.append(n3);
                            m3.second.append(n4);
                            m4.second.append(n2);

                            tmp.append(m0);
                            tmp.append(m1);
                            tmp.append(m2);
                            tmp.append(m3);
                            tmp.append(m4);

                            glets.append(tmp);
                        }
                    }
                }
            }
        }
    }

    return glets;
}

QVector<GraphLet> Graph::SearchGraphLet14(int sid)
{
    // g4: n0->n1, n1->n2, n1->n3, n2->n3
    QVector<GraphLet> glets;

    int n0 = sid;   //
    Node* t0 = GetNode(n0);

    for(int i = 0; i<t0->childs.size(); ++i)
    {
        int n1 = t0->childs[i];
        Node* t1 = GetNode(n1);

        for(int j=0; j<t1->childs.size(); ++j)
        {
            int n2 = t1->childs[j];
            if(n2 == n0)
                continue;

            Node* t2 = GetNode(n2);
            for(int k=0; k<t2->childs.size(); ++k)
            {
                int n3 = t2->childs[k];
                if(n3 == n0 || n3 == n1)
                    continue;

                Node* t3 = GetNode(n3);
                for (int m = 0; m < t3->childs.size(); ++m)
                {
                    int n4 = t3->childs[m];
                    if (n4 == n1)
                    {
                        for (int n = j+1; n<t1->childs.size(); ++n)
                        {
                            // n1's next child
                            n4 = t1->childs[n];
                            if (n4 == n0 || n4 == n3)
                                continue;

                            GraphLet tmp;
                            GraphLetNode m0,m1,m2,m3,m4;
                            m0.first = n0;
                            m1.first = n1;
                            m2.first = n2;
                            m3.first = n3;
                            m4.first = n4;

                            m0.second.append(n1);
                            m1.second.append(n2);
                            m1.second.append(n4);
                            m2.second.append(n3);
                            m3.second.append(n1);


                            tmp.append(m0);
                            tmp.append(m1);
                            tmp.append(m2);
                            tmp.append(m3);
                            tmp.append(m4);

                            glets.append(tmp);
                        }
                    }
                }
            }
        }
    }

    return glets;
}


QVector<GraphLet> Graph::SearchGraphLet15(int sid)
{
    // g1: n0->n1, n1->n2, n2->n3, n3->n4, n4->n0
    QVector<GraphLet> glets;

    int n0 = sid;
    Node* t0 = GetNode(n0);

    for(int i = 0; i<t0->childs.size(); ++i)
    {
        int n1 = t0->childs[i];
        Node* t1 = GetNode(n1);

        for(int j=0; j<t1->childs.size(); ++j)
        {
            int n2 = t1->childs[j];
            if(n2 == n0)
                continue;

            Node* t2 = GetNode(n2);
            for(int k=0; k<t2->childs.size(); ++k)
            {
                int n3 = t2->childs[k];
                if (n3 == n1 || n3 == n0)
                    continue;

                Node* t3 = GetNode(n3);
                for (int m = 0; m<t3->childs.size(); ++m)
                {
                    int n4 = t3->childs[m];
                    if (n4 == n2 || n4 == n1 || n4 == n0)
                        continue;

                    Node* t4 = GetNode(n4);
                    for (int n = 0; n<t4->childs.size(); ++n) {
                        int n5 = t4->childs[n];
                        if (n5 == n0) {
                            GraphLet tmp;
                            GraphLetNode m0, m1, m2, m3, m4;
                            m0.first = n0;
                            m1.first = n1;
                            m2.first = n2;
                            m3.first = n3;
                            m4.first = n4;

                            m0.second.append(n1);
                            m1.second.append(n2);
                            m2.second.append(n3);
                            m3.second.append(n4);
                            m4.second.append(n0);

                            tmp.append(m0);
                            tmp.append(m1);
                            tmp.append(m2);
                            tmp.append(m3);
                            tmp.append(m4);

                            glets.append(tmp);
                        }
                    }
                }
            }
        }

    }
    return glets;
}

QVector<GraphLet> Graph::SearchGraphLet16(int sid)
{
    // g16: n0->n1, n1->n2, n1->n3, n2->n4, n3->n4
    QVector<GraphLet> glets;

    int n0 = sid;
    Node* t0 = GetNode(n0);

    for(int i = 0; i<t0->childs.size(); ++i)
    {
        int n1 = t0->childs[i];
        Node* t1 = GetNode(n1);

        for(int j=0; j<t1->childs.size(); ++j)
        {
            int n2 = t1->childs[j];
            if(n2 == n0)
                continue;

            Node* t2 = GetNode(n2);
            for(int k=0; k<t2->childs.size(); ++k)
            {
                int n3 = t2->childs[k];
                if (n3 == n1 || n3 == n0)
                    continue;

                Node* t3 = GetNode(n3);
                for (int m = 0; m<t3->childs.size(); ++m)
                {
                    int n4 = t3->childs[m];
                    if (n4 == n2 || n4 == n1 || n4 == n0)
                        continue;

                    Node* t4 = GetNode(n4);
                    for (int n = 0; n<t4->childs.size(); ++n)
                    {
                        int n5 = t4->childs[n];
                        if (n5 == n1)
                        {
                            GraphLet tmp;
                            GraphLetNode m0, m1, m2, m3, m4;
                            m0.first = n0;
                            m1.first = n1;
                            m2.first = n2;
                            m3.first = n3;
                            m4.first = n4;

                            m0.second.append(n1);
                            m1.second.append(n2);
                            m2.second.append(n3);
                            m3.second.append(n4);
                            m4.second.append(n1);

                            tmp.append(m0);
                            tmp.append(m1);
                            tmp.append(m2);
                            tmp.append(m3);
                            tmp.append(m4);

                            glets.append(tmp);
                        }
                    }
                }
            }
        }

    }
    return glets;
}


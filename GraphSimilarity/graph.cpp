#include "graph.h"
#include <QDebug>

int glet_search_range = 6;                // user setting searching range

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

#ifdef UNDIRECT_GRAPH
    m_nodes[b].addEdge(a);
#endif
}


bool Graph::hasEdge(int a, int b)
{
    if (a < 0 || a >= m_nodes.size() || b < 0 || b>= m_nodes.size())
    {
        return false;
    }
#ifdef UNDIRECT_GRAPH
    return m_nodes[a].hasEdge(b) && m_nodes[b].hasEdge(a);
#else
    return m_nodes[a].hasEdge(b);
#endif
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
//    qDebug()<<"更新";
    for(int i=0; i<m_cur_graphlets[cur_ID].size(); ++i)
    {
        int n0 = m_cur_graphlets[cur_ID][i].first;
//        qDebug()<<m_cur_graphlets[cur_ID][i].first;

        painter->drawEllipse(QPoint(m_nodes[n0].x,m_nodes[n0].y),6,6);

        for(int t=0; t<m_cur_graphlets[cur_ID][i].second.size(); ++t)
        {
            int n2 = m_cur_graphlets[cur_ID][i].second[t];
//            qDebug() << " " << n2;
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
    if (!m_cur_graphlets.empty())
        cur_ID = (cur_ID+1) % m_cur_graphlets.size();
}

void Graph::clear()
{
    m_nodes.clear();
    m_cur_graphlets.clear();
}


void Graph::GetGraphletFromGraph(int gid)
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
    // de-duplicate graphlets
    DedupGraphLets(m_cur_graphlets);

    qDebug() << "Compute graphlets: " << gid << " cost " << time.elapsed() << "ms";
}


QVector<GraphLet> Graph::SearchGraphLet(int gid, int sid)
{
    QVector<GraphLet> glets;
    switch (gid) {
    case 0:
        glets = SearchGraphLet1(sid);
        break;
    case 1:
        glets = SearchGraphLet2(sid);
        break;
    case 2:
        glets = SearchGraphLet3(sid);
        break;
    case 3:
        glets = SearchGraphLet4(sid);
        break;
    case 4:
        glets = SearchGraphLet5(sid);
        break;
    case 5:
        glets = SearchGraphLet6(sid);
        break;
    case 6:
        glets = SearchGraphLet7(sid);
        break;
    case 7:
        glets = SearchGraphLet8(sid);
        break;
    case 8:
        glets = SearchGraphLet9(sid);
        break;
    case 9:
        glets = SearchGraphLet10(sid);
        break;
    case 10:
        glets = SearchGraphLet11(sid);
        break;
    case 11:
        glets = SearchGraphLet12(sid);
        break;
    case 12:
        //        qDebug() << "SearchGraphLet13";
        glets = SearchGraphLet13(sid);
        break;
    case 13:
        glets = SearchGraphLet14(sid);
        break;
    case 14:
        glets = SearchGraphLet15(sid);
        break;
    case 15:
        glets = SearchGraphLet16(sid);
        break;
    case 16:
        glets = SearchGraphLet17(sid);
        break;
    case 17:
        glets = SearchGraphLet18(sid);
        break;
    case 18:
        glets = SearchGraphLet19(sid);
        break;
    case 19:
        glets = SearchGraphLet20(sid);
        break;
    case 20:
        glets = SearchGraphLet21(sid);
        break;
    case 21:
        glets = SearchGraphLet22(sid);
        break;
    case 22:
        glets = SearchGraphLet23(sid);
        break;
    case 23:
        glets = SearchGraphLet24(sid);
        break;
    case 24:
        glets = SearchGraphLet25(sid);
        break;
    case 25:
        glets = SearchGraphLet26(sid);
        break;
    case 26:
        glets = SearchGraphLet27(sid);
        break;
    case 27:
        glets = SearchGraphLet28(sid);
        break;
    case 28:
        glets = SearchGraphLet29(sid);
        break;
    default:
        glets = SearchGraphLet1(sid);
        break;
    }
    return glets;
}

QVector<QVector<GraphLet> > Graph::GetGraphLets(int sid)
{
    QVector<QVector<GraphLet>> allGlets(ALL_GRAPHLET);

    for (int i = 0; i < allGlets.size(); i++)
    {
        allGlets[i] = SearchGraphLet(i, sid);
    }

    return allGlets;
}

QVector<QVector<GraphLet> > Graph::GetNeighborGraphlets(int sid)
{
    typedef QPair<int, int> tuple;  // first is level, second is node


    QVector<bool> visited(m_nodes.size(), false);// ensure each node is visited once
    visited[sid] = true;

    QQueue<tuple> q;
    q.enqueue(tuple(0, sid));

    int llevel = 0;
    QVector<QVector<GraphLet>> neighborGlets(ALL_GRAPHLET * glet_search_range);
//    for (int i = 0; i < neighborGlets.size(); i++)
//    {
//        neighborGlets[i] = QVector<GraphLet>(); // create empty QVector
//    }

    QVector<QVector<GraphLet>> cLevelGlets(ALL_GRAPHLET);
    // BFS, limited in neighbor size of MAX_SEARCH_RANGE
    while(!q.isEmpty())
    {
        // top
        tuple t = q.head();
        int clevel = t.first;
        int cnode = t.second;

//        qDebug() << "visit:" << cnode;

        if (clevel != llevel)
        {
            // store graphlets found on last level
            std::copy(cLevelGlets.begin(), cLevelGlets.end(), neighborGlets.begin() + llevel*ALL_GRAPHLET);
            for (int i = 0; i < cLevelGlets.size(); i++)
            {
                cLevelGlets[i].clear();
            }

            llevel = clevel;
            if (clevel >= glet_search_range)
            {
//                qDebug() << "max level reached.";
                break;
            }
        }


        // accumulate graphlets found in this level
        QVector<QVector<GraphLet>> glets = GetGraphLets(cnode);
        for (int i = 0; i < glets.size(); i++)
        {
            for (int j = 0; j < glets[i].size(); j++)
            {
                cLevelGlets[i].push_back(glets[i][j]);
            }
        }

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

    return neighborGlets;
}

QVector<QVector<GraphLet> > Graph::GetNeighborGraphletsAll(int sid)
{
    typedef QPair<int, int> tuple;  // first is level, second is node


    QVector<bool> visited(m_nodes.size(), false);// ensure each node is visited once
    visited[sid] = true;

    QQueue<tuple> q;
    q.enqueue(tuple(0, sid));

    int llevel = 0;
    QVector<QVector<GraphLet>> allGlets(ALL_GRAPHLET);
    // BFS, limited in neighbor size of MAX_SEARCH_RANGE
    while(!q.isEmpty())
    {
        // top
        tuple t = q.head();
        int clevel = t.first;
        int cnode = t.second;


        if (clevel != llevel)
        {
            llevel = clevel;
            if (clevel >= glet_search_range)
            {
//                qDebug() << "max level reached.";
                break;
            }
        }


        // accumulate graphlets found in this node
        QVector<QVector<GraphLet>> glets = GetGraphLets(cnode);
        for (int i = 0; i < glets.size(); i++)
        {
            for (int j = 0; j < glets[i].size(); j++)
            {
                allGlets[i].push_back(glets[i][j]);
            }
        }

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

    return allGlets;
}

QVector<float> Graph::GetfeatureVector(int sid)
{
    QVector<QVector<GraphLet> > neighborGlets = GetNeighborGraphlets(sid);
    assert(neighborGlets.size() == ALL_GRAPHLET * glet_search_range);

    // De-duplicate each graphlet type
    for (int i = 0; i < neighborGlets.size(); i++)
    {
//        qDebug() << "removing neighborhood:" << i/ALL_GRAPHLET << " graphlet type:" << i%ALL_GRAPHLET;
        DedupGraphLets(neighborGlets[i]);
    }
    //

    // compute GFD for each level
    QVector<float> featureVector(ALL_GRAPHLET * glet_search_range);
    for (int i = 0; i < glet_search_range; i++)
    {

        GFD gfd(ALL_GRAPHLET);
        int count = 0;
        for (int j = 0; j < gfd.size(); j++)
        {
            gfd[j] = neighborGlets[i*ALL_GRAPHLET + j].size();
            count += neighborGlets[i*ALL_GRAPHLET + j].size();
        }

        if (count != 0)
        {
            for (int j = 0; j < gfd.size(); j++)
            {
                gfd[j] /= (float)count;
            }
        }

        // concat
        std::copy(gfd.begin(), gfd.end(), featureVector.begin() + i*ALL_GRAPHLET);
    }
    return featureVector;
}

QVector<float> Graph::GetfeatureVectorAll(int sid)
{
    QVector<QVector<GraphLet> > neighborGlets = GetNeighborGraphletsAll(sid);
    assert(neighborGlets.size() == ALL_GRAPHLET);

    // De-duplicate each graphlet type
    for (int i = 0; i < neighborGlets.size(); i++)
    {
//        qDebug() << "removing graphlet type:" << i;
        DedupGraphLets(neighborGlets[i]);
    }
    //

    QString str;
    GFD gfd(ALL_GRAPHLET);
    int count = 0;
    for (int i = 0; i < gfd.size(); i++)
    {
        gfd[i] = neighborGlets[i].size();
        str += QString::number(gfd[i]) + ", ";
        count += neighborGlets[i].size();
    }


//    qDebug() << "featurevector of " << sid << ": " << str;

    if (count != 0)
    {
        for (int i = 0; i < gfd.size(); i++)
        {
            gfd[i] /= (float)count;
        }
    }
    return gfd;
}

QVector<GraphLet> Graph::SearchGraphLet1(int sid)   // 输入的当前以那个点为起点找graphlet
{
    // g1: n0->n1, n1->n2
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

            GraphLet tmp;
            GraphLetNode m0,m1,m2;
            m0.first = n0;
            m1.first = n1;
            m2.first = n2;

            m0.second.append(n1);
            m1.second.append(n2);

            // for undirected graph
#ifdef UNDIRECT_GRAPH
            m1.second.append(n0);
            m2.second.append(n1);
#endif

            tmp.append(m0);
            tmp.append(m1);
            tmp.append(m2);

            glets.append(tmp);
        }
    }
    return glets;
}


QVector<GraphLet> Graph::SearchGraphLet2(int sid)
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

#ifdef UNDIRECT_GRAPH
                    m1.second.append(n0);
                    m2.second.append(n1);
                    m0.second.append(n2);
#endif
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

#ifdef UNDIRECT_GRAPH
                m1.second.append(n0);
                m2.second.append(n1);
                m3.second.append(n2);
#endif
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
            for(int m=0; m<t1->childs.size(); ++m)
            {
                int n3 = t1->childs[m];
                if(n3 == n0 || n3 == n2)
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

#ifdef UNDIRECT_GRAPH
                m1.second.append(n0);
                m2.second.append(n1);
                m3.second.append(n1);
#endif
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

#ifdef UNDIRECT_GRAPH
                        m1.second.append(n0);
                        m2.second.append(n1);
                        m3.second.append(n2);
                        m0.second.append(n3);
#endif
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

#ifdef UNDIRECT_GRAPH
                        m1.second.append(n0);
                        m2.second.append(n1);
                        m3.second.append(n2);
                        m1.second.append(n3);
#endif
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
                    for (int j = 0; j<t3->childs.size(); ++j) {
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
#ifdef UNDIRECT_GRAPH
                            m1.second.append(n0);
                            m2.second.append(n1);
                            m3.second.append(n2);
                            m0.second.append(n3);
                            m1.second.append(n3);
#endif
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
    // g8: n0->n1, n1->n2, n2->n0,
    // n2->n3,
    // n3->n0, n3->n1
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
            if (n2 == n0)
                continue;

            Node* t2 = GetNode(n2);
            for (int k=0; k < t2->childs.size(); ++k) {
                int n3 = t2->childs[k];
                if(n3 == n0) {  // A loop
                    for (int m = 0; m < t2->childs.size(); ++m) {
                        n3 = t2->childs[m];
                        if (n3 == n0 || n3 == n1)
                            continue;

                        Node* t3 = GetNode(n3);
                        for (int n = 0; n < t3->childs.size(); ++n) {
                            for (int o = 0; o < t3->childs.size(); ++o) {
                                int n4 = t3->childs[n];
                                int n5 = t3->childs[o];
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
#ifdef UNDIRECT_GRAPH
                                    m1.second.append(n0);
                                    m2.second.append(n1);
                                    m0.second.append(n2);
                                    m3.second.append(n2);
                                    m0.second.append(n3);
                                    m1.second.append(n3);
#endif
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
#ifdef UNDIRECT_GRAPH
                    m1.second.append(n0);
                    m2.second.append(n1);
                    m3.second.append(n2);
                    m4.second.append(n3);
#endif
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

                for(int m=0; m<t2->childs.size(); ++m)
                {
                    int n4 = t2->childs[m];
                    if(n4 == n0 || n4 == n1 || n4 == n3)
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
#ifdef UNDIRECT_GRAPH
                    m1.second.append(n0);
                    m2.second.append(n1);
                    m3.second.append(n2);
                    m4.second.append(n2);
#endif
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

        for (int j = 0; j<t0->childs.size(); ++j) {
            int n2 = t0->childs[j];
            if (n2 == n0 || n2 == n1)
                continue;

            for (int k = 0; k < t0->childs.size(); ++k) {
                int n3 = t0->childs[k];
                if (n3 == n0 || n3 == n1 || n3 == n2)
                    continue;

                for (int m = 0; m < t0->childs.size(); ++m) {
                    int n4 = t0->childs[m];
                    if (n4 == n0 || n4 == n1 || n4 == n2 || n4 == n3)
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
#ifdef UNDIRECT_GRAPH
                    m1.second.append(n0);
                    m2.second.append(n0);
                    m3.second.append(n0);
                    m4.second.append(n0);
#endif
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

QVector<GraphLet> Graph::SearchGraphLet12(int sid)
{
    // g12: n0->n1, n1->n2, n2->n3, n3->n4
    // n1->n3
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
                for (int l = 0; l<t3->childs.size(); ++l)
                {
                    int n4 = t3->childs[l];
                    if (n4 == n2 || n4 == n1 || n4 == n0)
                        continue;

                    for (int m = 0; m < t1->childs.size(); m++)
                    {
                        int n5 = t1->childs[m];
                        if (n5 == n3)
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
                            m1.second.append(n3);
                            m2.second.append(n3);
                            m3.second.append(n4);
#ifdef UNDIRECT_GRAPH
                            m1.second.append(n0);
                            m2.second.append(n1);
                            m3.second.append(n1);
                            m3.second.append(n2);
                            m4.second.append(n3);
#endif
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

        for (int j = 0; j<t1->childs.size(); j++)
        {
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
#ifdef UNDIRECT_GRAPH
                            m1.second.append(n0);
                            m2.second.append(n1);
                            m3.second.append(n2);
                            m4.second.append(n3);
                            m2.second.append(n4);
#endif
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
    // g4: n0->n1, n1->n2, n2->n3, n3->n1
    // n1 -> n4
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
                        for (int n = 0; n<t1->childs.size(); ++n)
                        {
                            // n1's next child
                            n4 = t1->childs[n];
                            if (n4 == n0 || n4 == n2 || n4 == n3)
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
#ifdef UNDIRECT_GRAPH
                            m1.second.append(n0);
                            m2.second.append(n1);
                            m4.second.append(n1);
                            m3.second.append(n2);
                            m1.second.append(n3);
#endif
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
    // g15: n0->n1, n1->n2, n2->n3, n3->n4, n4->n0
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
#ifdef UNDIRECT_GRAPH
                            m1.second.append(n0);
                            m2.second.append(n1);
                            m3.second.append(n2);
                            m4.second.append(n3);
                            m0.second.append(n4);
#endif
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
    // g16: n0->n1, n1->n2, n2->n3, n3->n4, n4->n1
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
#ifdef UNDIRECT_GRAPH
                            m1.second.append(n0);
                            m2.second.append(n1);
                            m3.second.append(n2);
                            m4.second.append(n3);
                            m1.second.append(n4);
#endif
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

QVector<GraphLet> Graph::SearchGraphLet17(int sid)
{
    // g17: n0->n1, n1->n2, n2->n3, n3->n4, n4->n1, n1->n3
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
                            // Find n3
                            for (int o = 0; o < t1->childs.size(); ++o)
                            {
                                n5 = t1->childs[o];
                                if (n5 == n3)
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
                                    m1.second.append(n3);
                                    m2.second.append(n3);
                                    m3.second.append(n4);
                                    m4.second.append(n1);
#ifdef UNDIRECT_GRAPH
                                    m1.second.append(n0);
                                    m2.second.append(n1);
                                    m3.second.append(n1);
                                    m3.second.append(n2);
                                    m4.second.append(n3);
                                    m1.second.append(n4);
#endif
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
        }

    }
    return glets;
}

QVector<GraphLet> Graph::SearchGraphLet18(int sid)
{
    // g18: n0->
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
                        for (int n = 0; n<t1->childs.size(); ++n)
                        {
                            // n1's next child
                            n4 = t1->childs[n];
                            if (n4 == n0 || n4 == n3 || n4 == n2)
                                continue;

                            Node* t4 = GetNode(n4);
                            for (int o = 0; o < t4->childs.size(); ++o)
                            {
                                int n5 = t4->childs[o];
                                if (n5 == n0)
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
                                    m1.second.append(n4);
                                    m2.second.append(n3);
                                    m3.second.append(n1);
                                    m4.second.append(n0);
#ifdef UNDIRECT_GRAPH
                                    m1.second.append(n0);
                                    m2.second.append(n1);
                                    m4.second.append(n1);
                                    m3.second.append(n2);
                                    m1.second.append(n3);
                                    m0.second.append(n4);
#endif
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
        }
    }

    return glets;
}

QVector<GraphLet> Graph::SearchGraphLet19(int sid)
{
    // g16: n0->n1, n1->n2, n2->n3, n3->n4, n4->n1
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
                            for (int o = 0; o < t2->childs.size(); ++o)
                            {
                                n5 = t2->childs[o];
                                if (n5 == n4)
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
                                    m2.second.append(n4);
                                    m3.second.append(n4);
                                    m4.second.append(n1);
#ifdef UNDIRECT_GRAPH
                                    m1.second.append(n0);
                                    m2.second.append(n1);
                                    m3.second.append(n2);
                                    m4.second.append(n2);
                                    m4.second.append(n3);
                                    m1.second.append(n4);
#endif
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
        }

    }
    return glets;
}

QVector<GraphLet> Graph::SearchGraphLet20(int sid)
{
    // g20: n0->n1, n1->n2, n2->n3, n3->n0, n0->n4, n4->n2
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
                for(int m=0; m<t3->childs.size(); ++m)
                {
                    int n4 = t3->childs[m];
                    if (n4 == n0)
                    {
                        for (int n = 0; n < t0->childs.size(); ++n)
                        {
                            n4 = t0->childs[n];
                            if (n4 == n1 || n4 == n2 || n4 == n3)
                                continue;

                            Node* t4 = GetNode(n4);
                            for (int o = 0; o < t4->childs.size(); ++o)
                            {
                                int n5 = t4->childs[o];
                                if (n5 == n2)
                                {
                                    GraphLet tmp;
                                    GraphLetNode m0, m1, m2, m3, m4;
                                    m0.first = n0;
                                    m1.first = n1;
                                    m2.first = n2;
                                    m3.first = n3;
                                    m4.first = n4;

                                    m0.second.append(n1);
                                    m0.second.append(n4);
                                    m1.second.append(n2);
                                    m2.second.append(n3);
                                    m3.second.append(n0);
                                    m4.second.append(n2);
#ifdef UNDIRECT_GRAPH
                                    m1.second.append(n0);
                                    m4.second.append(n0);
                                    m2.second.append(n1);
                                    m3.second.append(n2);
                                    m0.second.append(n3);
                                    m2.second.append(n4);
#endif
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
        }

    }
    return glets;
}

QVector<GraphLet> Graph::SearchGraphLet21(int sid)
{
    // g21: n0->n1, n1->n2, n2->n3, n3->n4, n4->n0,
    // n0->n2
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
                        if (n5 == n0)
                        {
                            //                            qDebug() << "loop 5";
                            for (int o = 0; o<t0->childs.size(); ++o)
                            {
                                n5 = t0->childs[o];
                                if (n5 == n2)
                                {
                                    GraphLet tmp;
                                    GraphLetNode m0, m1, m2, m3, m4;
                                    m0.first = n0;
                                    m1.first = n1;
                                    m2.first = n2;
                                    m3.first = n3;
                                    m4.first = n4;

                                    m0.second.append(n1);
                                    m0.second.append(n2);
                                    m1.second.append(n2);
                                    m2.second.append(n3);
                                    m3.second.append(n4);
                                    m4.second.append(n0);
#ifdef UNDIRECT_GRAPH
                                    m1.second.append(n0);
                                    m2.second.append(n0);
                                    m2.second.append(n1);
                                    m3.second.append(n2);
                                    m4.second.append(n3);
                                    m0.second.append(n4);
#endif
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
        }

    }
    return glets;
}


QVector<GraphLet> Graph::SearchGraphLet22(int sid)
{
    // g22: n0->n1, n1->n2, n2->n3, n3->n0,
    // n0->n4, n4->n2,
    // n0->n2
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
                for(int m=0; m<t3->childs.size(); ++m)
                {
                    int n4 = t3->childs[m];
                    if (n4 == n0)
                    {
                        for (int n = 0; n < t0->childs.size(); ++n)
                        {
                            n4 = t0->childs[n];
                            if (n4 == n2 || n4 == n3 || n4 == n1)
                                continue;
                            Node* t4 = GetNode(n4);
                            for (int o = 0; o < t4->childs.size(); ++o)
                            {
                                int n5 = t4->childs[o];
                                if (n5 == n2)
                                {
                                    for (int p = 0; p < t0->childs.size(); ++p)
                                    {
                                        n5 = t0->childs[p];
                                        if (n5 == n2)
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
                                            m3.second.append(n0);
                                            m0.second.append(n4);
                                            m4.second.append(n2);
                                            m0.second.append(n2);
#ifdef UNDIRECT_GRAPH
                                            m1.second.append(n0);
                                            m2.second.append(n1);
                                            m3.second.append(n2);
                                            m0.second.append(n3);
                                            m4.second.append(n0);
                                            m2.second.append(n4);
                                            m2.second.append(n0);
#endif
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
                }
            }
        }

    }
    return glets;
}

QVector<GraphLet> Graph::SearchGraphLet23(int sid)
{
    // g23: n0->n1, n1->n2, n2->n3, n3->n1
    // n1->n4
    // n4->n2, n4->n3
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
                        for (int n = 0; n < t1->childs.size(); ++n)
                        {
                            n4 = t1->childs[n];
                            if (n4 == n2 || n4 == n0 || n4 == n3)
                                continue;

                            Node* t4 = GetNode(n4);
                            for (int o = 0; o < t4->childs.size(); ++o)
                            {
                                int n5 = t4->childs[o];
                                for (int p = 0; p < t4->childs.size(); ++p)
                                {
                                    int n6 = t4->childs[p];
                                    if (n5 == n2 && n6 == n3) {
                                        GraphLet tmp;
                                        GraphLetNode m0,m1,m2,m3, m4;
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
                                        m4.second.append(n2);
                                        m4.second.append(n3);
#ifdef UNDIRECT_GRAPH
                                        m1.second.append(n0);
                                        m2.second.append(n1);
                                        m4.second.append(n1);
                                        m3.second.append(n2);
                                        m1.second.append(n3);
                                        m2.second.append(n4);
                                        m3.second.append(n4);
#endif
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
            }
        }
    }

    return glets;
}

QVector<GraphLet> Graph::SearchGraphLet24(int sid)
{
    // g24: n0->n1, n1->n2, n2->n3, n3->n4, n4->n0
    // n0->n2, n0->n3
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
                            for (int o = 0; o < t0->childs.size(); ++o)
                            {
                                int n6 = t0->childs[o];
                                for (int p = 0; p < t0->childs.size(); ++p)
                                {
                                    int n7= t0->childs[p];
                                    if (n6 == n2 && n7==n3)
                                    {
                                        GraphLet tmp;
                                        GraphLetNode m0, m1, m2, m3, m4;
                                        m0.first = n0;
                                        m1.first = n1;
                                        m2.first = n2;
                                        m3.first = n3;
                                        m4.first = n4;

                                        m0.second.append(n1);
                                        m0.second.append(n2);
                                        m0.second.append(n3);
                                        m1.second.append(n2);
                                        m2.second.append(n3);
                                        m3.second.append(n4);
                                        m4.second.append(n0);
#ifdef UNDIRECT_GRAPH
                                        m1.second.append(n0);
                                        m2.second.append(n0);
                                        m3.second.append(n0);
                                        m2.second.append(n1);
                                        m3.second.append(n2);
                                        m4.second.append(n3);
                                        m0.second.append(n4);
#endif
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
            }
        }

    }
    return glets;
}

QVector<GraphLet> Graph::SearchGraphLet25(int sid)
{
    // g27: n0->n1, n1->n2, n2->n3, n3->n0, n0->n4,
    // n4->n1
    // n4->n3
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
                for(int m=0; m<t3->childs.size(); ++m)
                {
                    int n4 = t3->childs[m];
                    if (n4 == n0)
                    {// A loop
                        for (int n = 0; n < t0->childs.size(); ++n)
                        {
                            n4 = t0->childs[n];
                            if (n4 == n1 || n4 == n2 || n4 == n3)
                                continue;

                            Node* t4 = GetNode(n4);
                            for (int o = 0; o < t4->childs.size(); ++o)
                            {
                                int n5 = t4->childs[o];
                                for (int p = 0; p < t4->childs.size(); ++p)
                                {
                                    int n6 = t4->childs[p];
                                    if (n5==n1 && n6==n3)
                                    {
                                        GraphLet tmp;
                                        GraphLetNode m0, m1, m2, m3, m4;
                                        m0.first = n0;
                                        m1.first = n1;
                                        m2.first = n2;
                                        m3.first = n3;
                                        m4.first = n4;

                                        m0.second.append(n1);
                                        m0.second.append(n4);
                                        m1.second.append(n2);
                                        m2.second.append(n3);
                                        m3.second.append(n0);
                                        m4.second.append(n1);
                                        m4.second.append(n3);
#ifdef UNDIRECT_GRAPH
                                        m1.second.append(n0);
                                        m4.second.append(n0);
                                        m2.second.append(n1);
                                        m3.second.append(n2);
                                        m0.second.append(n3);
                                        m1.second.append(n4);
                                        m3.second.append(n4);
#endif
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
            }
        }

    }
    return glets;
}

QVector<GraphLet> Graph::SearchGraphLet26(int sid)
{
    // g26: n0->n1, n1->n2, n2->n3, n3->n0,
    // n0->n4,n4->n2
    // n0->n2,
    // n4->n3
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
                for(int m=0; m<t3->childs.size(); ++m)
                {
                    int n4 = t3->childs[m];
                    if (n4 == n0)
                    {
                        for (int n = 0; n < t0->childs.size(); ++n)
                        {
                            n4 = t0->childs[n];
                            if (n4 == n2 || n4 == n3 || n4 == n1)
                                continue;
                            Node* t4 = GetNode(n4);
                            for (int o = 0; o < t4->childs.size(); ++o)
                            {
                                int n5 = t4->childs[o];
                                if (n5 == n2)
                                {
                                    for (int p = 0; p < t0->childs.size(); ++p)
                                    {
                                        n5 = t0->childs[p];
                                        if (n5 == n2)
                                        {
                                            for (int q = 0; q < t4->childs.size(); ++q)
                                            {
                                                n5 = t4->childs[q];
                                                if (n5 == n3)
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
                                                    m3.second.append(n0);
                                                    m0.second.append(n4);
                                                    m4.second.append(n2);
                                                    m4.second.append(n3);
                                                    m0.second.append(n2);
#ifdef UNDIRECT_GRAPH
                                                    m1.second.append(n0);
                                                    m2.second.append(n1);
                                                    m3.second.append(n2);
                                                    m0.second.append(n3);
                                                    m4.second.append(n0);
                                                    m2.second.append(n4);
                                                    m3.second.append(n4);
                                                    m2.second.append(n0);
#endif
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
                        }

                    }
                }
            }
        }

    }
    return glets;
}

QVector<GraphLet> Graph::SearchGraphLet27(int sid)
{
    // g27: n0->n1, n1->n2, n2->n3, n3->n0, n0->n4,
    // n4->n1
    // n4->n2
    // n4->n3
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
                for(int m=0; m<t3->childs.size(); ++m)
                {
                    int n4 = t3->childs[m];
                    if (n4 == n0)
                    {// A loop
                        for (int n = 0; n < t0->childs.size(); ++n)
                        {
                            n4 = t0->childs[n];
                            if (n4 == n1 || n4 == n2 || n4 == n3)
                                continue;

                            Node* t4 = GetNode(n4);
                            for (int o = 0; o < t4->childs.size(); ++o)
                            {
                                int n5 = t4->childs[o];
                                for (int p = 0; p < t4->childs.size(); ++p)
                                {
                                    int n6 = t4->childs[p];
                                    for (int q = 0; q < t4->childs.size(); ++q)
                                    {
                                        int n7 = t4->childs[q];
                                        if (n5==n1 && n6==n2 && n7==n3)
                                        {
                                            GraphLet tmp;
                                            GraphLetNode m0, m1, m2, m3, m4;
                                            m0.first = n0;
                                            m1.first = n1;
                                            m2.first = n2;
                                            m3.first = n3;
                                            m4.first = n4;

                                            m0.second.append(n1);
                                            m0.second.append(n4);
                                            m1.second.append(n2);
                                            m2.second.append(n3);
                                            m3.second.append(n0);
                                            m4.second.append(n1);
                                            m4.second.append(n2);
                                            m4.second.append(n3);
#ifdef UNDIRECT_GRAPH
                                            m1.second.append(n0);
                                            m4.second.append(n0);
                                            m2.second.append(n1);
                                            m3.second.append(n2);
                                            m0.second.append(n3);
                                            m1.second.append(n4);
                                            m2.second.append(n4);
                                            m3.second.append(n4);
#endif
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
                }
            }
        }

    }
    return glets;
}

QVector<GraphLet> Graph::SearchGraphLet28(int sid)
{
    // g28: n0->n1, n1->n2, n2->n3, n3->n0,
    // n0->n4,n4->n2
    // n0->n2,
    // n4->n3, n4->n1
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
                for(int m=0; m<t3->childs.size(); ++m)
                {
                    int n4 = t3->childs[m];
                    if (n4 == n0)
                    {
                        for (int n = 0; n < t0->childs.size(); ++n)
                        {
                            n4 = t0->childs[n];
                            if (n4 == n2 || n4 == n3 || n4 == n1)
                                continue;
                            Node* t4 = GetNode(n4);
                            for (int o = 0; o < t4->childs.size(); ++o)
                            {
                                int n5 = t4->childs[o];
                                if (n5 == n2)
                                {
                                    for (int p = 0; p < t0->childs.size(); ++p)
                                    {
                                        n5 = t0->childs[p];
                                        if (n5 == n2)
                                        {
                                            for (int q = 0; q < t4->childs.size(); ++q)
                                            {
                                                n5 = t4->childs[q];
                                                if (n5 == n3)
                                                {
                                                    for (int r = 0; r < t4->childs.size(); ++r)
                                                    {
                                                        n5 = t4->childs[r];
                                                        if (n5 == n1) {
                                                            GraphLet tmp;
                                                            GraphLetNode m0, m1, m2, m3, m4;
                                                            m0.first = n0;
                                                            m1.first = n1;
                                                            m2.first = n2;
                                                            m3.first = n3;
                                                            m4.first = n4;

                                                            m0.second.append(n1);
                                                            m0.second.append(n4);
                                                            m0.second.append(n2);
                                                            m1.second.append(n2);
                                                            m2.second.append(n3);
                                                            m3.second.append(n0);
                                                            m4.second.append(n1);
                                                            m4.second.append(n2);
                                                            m4.second.append(n3);
#ifdef UNDIRECT_GRAPH
                                                            m1.second.append(n0);
                                                            m4.second.append(n0);
                                                            m2.second.append(n0);
                                                            m2.second.append(n1);
                                                            m3.second.append(n2);
                                                            m0.second.append(n3);
                                                            m1.second.append(n4);
                                                            m2.second.append(n4);
                                                            m3.second.append(n4);
#endif

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

QVector<GraphLet> Graph::SearchGraphLet29(int sid)
{
    // g21: n0->n1, n1->n2, n2->n3, n3->n4, n4->n0
    // n0->n2, n0->n3
    // n1->n3, n1->n4
    // n2->n4
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
                        if (n5 == n0) { // A loop
                            for (int o = 0; o < t0->childs.size(); ++o)
                            {
                                for (int p = 0; p < t0->childs.size(); ++p)
                                {
                                    for (int q = 0; q < t1->childs.size(); ++q)
                                    {
                                        for (int r = 0; r < t1->childs.size(); ++r)
                                        {
                                            for (int s = 0; s < t2->childs.size(); ++s)
                                            {
                                                if (t0->childs[o] == n2 &&
                                                        t0->childs[p] == n3&&
                                                        t1->childs[q] == n3 &&
                                                        t1->childs[r] == n4 &&
                                                        t2->childs[s] == n4)
                                                {
                                                    GraphLet tmp;
                                                    GraphLetNode m0, m1, m2, m3, m4;
                                                    m0.first = n0;
                                                    m1.first = n1;
                                                    m2.first = n2;
                                                    m3.first = n3;
                                                    m4.first = n4;

                                                    m0.second.append(n1);
                                                    m0.second.append(n2);
                                                    m0.second.append(n3);
                                                    m0.second.append(n4);
                                                    m1.second.append(n2);
                                                    m1.second.append(n3);
                                                    m1.second.append(n4);
                                                    m2.second.append(n3);
                                                    m2.second.append(n4);
                                                    m3.second.append(n4);
#ifdef UNDIRECT_GRAPH
                                                    m1.second.append(n0);
                                                    m2.second.append(n0);
                                                    m3.second.append(n0);
                                                    m4.second.append(n0);
                                                    m2.second.append(n1);
                                                    m3.second.append(n1);
                                                    m4.second.append(n1);
                                                    m3.second.append(n2);
                                                    m4.second.append(n2);
                                                    m4.second.append(n3);
#endif
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
                        }
                    }
                }
            }
        }

    }
    return glets;
}

void Graph::DedupGraphLets(QVector<GraphLet> &allGraphlets)
{
    std::sort(allGraphlets.begin(), allGraphlets.end(),
              [this](GraphLet& glet1, GraphLet& glet2)
    {
        SortGraphLet(glet1);
        SortGraphLet(glet2);

        int nodeNum1 = glet1.size();
        int nodeNum2 = glet2.size();
        if (nodeNum1 != nodeNum2)
        {
            return nodeNum1 < nodeNum2;
        }
        // compare node id
        for (int i = 0; i < nodeNum1; i++)
        {
            if (glet1[i].first != glet2[i].first)
            {
                return glet1[i].first < glet2[i].first;
            }
        }
        // compare edge
        for (int i = 0; i < nodeNum1; i++)
        {
            int edgeNum1 = glet1[i].second.size();
            int edgeNum2 = glet2[i].second.size();
            if (edgeNum1 != edgeNum2)
            {
                return edgeNum1 < edgeNum2;
            }

            for (int j = 0; j < edgeNum1; j++)
            {
                if (glet1[i].second[j] != glet2[i].second[j])
                {
                    return glet1[i].second[j] < glet2[i].second[j];
                }
            }
        }

        // two graphlets are the same, no matter what
        return false;
    });

    // find consecutive duplicated elements
    int n = std::unique(allGraphlets.begin(), allGraphlets.end()) - allGraphlets.begin();
//    int n = std::unique(allGraphlets.begin(), allGraphlets.end(), [](){

//    }) - allGraphlets.begin();
    // remove last
    int total = allGraphlets.size();

//    if (total - n != 0)
//    {
//        qDebug() << "remove duplicate: " << total - n;
//    }

    for (int i = n; i < total; i++)
    {
        allGraphlets.pop_back();
    }
}


void Graph::SortGraphLet(GraphLet& glet) {

#ifndef UNDIRECT_GRAPH
    // if the graph is directed, we synmetric the graphlet for de-duplication
    for (int i = 0; i < glet.size(); i++)
    {
        int ni = glet[i].first;
        for (int j = 0; j < glet[i].second.size(); j++)
        {
            int  nj = glet[i].second[j];
            // if (ni, nj) exists
            for (int k = 0; k < glet.size(); k++)
            {
                // insert (nj, ni)
                if (glet[k].first == nj)
                {
                    if(!glet[nj].second.contains(ni))
                    {
                        glet[nj].second.append(ni);
                    }
                }
            }
        }
    }
#endif

    // sort nodes within the graphlet
    std::sort(glet.begin(), glet.end(),
              [](GraphLetNode& gnode1, GraphLetNode&gnode2)
    {
        // sort
        return gnode1.first < gnode2.first;
    }
    );

    // sort the out edges of each node
    for (int i = 0; i < glet.size(); i++)
    {
        std::sort(glet[i].second.begin(), glet[i].second.end(), [](int a, int b)
        {
            return a < b;
        });
    }

}

bool Graph::GraphletEqual(const GraphLet &glet1, const GraphLet &glet2)
{

    if (glet1.size() != glet2.size())
    {
        return false;
    }
    for (int i = 0; i < glet1.size(); i++)
    {
        if (glet1[i].first != glet2[i].first)
        {
            return false;
        }
        for (int j = 0; j < glet1[i].second.size(); j++)
        {
            if (glet1[i].second[j] != glet2[i].second[j])
            {
                return false;
            }
        }
    }

    return true;
}


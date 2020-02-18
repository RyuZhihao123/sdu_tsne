#ifndef GRAPH_H
#define GRAPH_H
#define MAX_SEARCH_RANGE 1  //1 is the best?
#define ALL_GRAPHLET    29

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

typedef QPair<int,QVector<int>> GraphLetNode;   // node and its adjacient edges, which is an undirected graph
typedef QVector<GraphLetNode> GraphLet;         // graphlet representation
typedef QVector<float> GFD;                     // graphlet frequency distribution

typedef QMap<QPair<int, int>, float> MatchList;// matching point and their similarities
//typedef QVector<MatchPoint> MatchList;

// Undirected graph
class Graph
{
public:
    Graph();
    QVector<Node> m_nodes;                   // 结点
    int cur_ID = 0;                          // 当前显示的graphlet编号
    QVector<GraphLet> m_cur_graphlets;       // 当前找到的

    int nodeNum() const;

    void addNode(const Node& n);
    void addEdge(int a, int b);             // now directed graph

    void renderGraph(QPainter* painter);
    void renderCurGraphLets(QPainter* painter);

    // to do:
    Node *GetNode(int id);
    int HasNodeAt(QPoint p, float radius = 100);

    // get all graphlets from current graph. 是为了演示效果
    void GetGraphletFromGraph(int gid);
    void ShowNextGraphlet();

    void clear();


    // Search graphlet type gid starting from node sid
    QVector<GraphLet> SearchGraphLet(int gid, int sid);

    //  return all graphlets found on given node
    QVector<QVector<GraphLet>> GetGraphLets(int sid);

    QVector<QVector<GraphLet>> GetNeighborGraphlets(int sid);
    QVector<QVector<GraphLet>> GetNeighborGraphletsAll(int sid);

     // return the feature vector of given node
    QVector<float> GetfeatureVector(int sid);
    QVector<float> GetfeatureVectorAll(int sid);
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
    QVector<GraphLet> SearchGraphLet12(int sid);
    QVector<GraphLet> SearchGraphLet13(int sid);
    QVector<GraphLet> SearchGraphLet14(int sid);
    QVector<GraphLet> SearchGraphLet15(int sid);
    QVector<GraphLet> SearchGraphLet16(int sid);
    QVector<GraphLet> SearchGraphLet17(int sid);
    QVector<GraphLet> SearchGraphLet18(int sid);
    QVector<GraphLet> SearchGraphLet19(int sid);
    QVector<GraphLet> SearchGraphLet20(int sid);
    QVector<GraphLet> SearchGraphLet21(int sid);
    QVector<GraphLet> SearchGraphLet22(int sid);
    QVector<GraphLet> SearchGraphLet23(int sid);
    QVector<GraphLet> SearchGraphLet24(int sid);
    QVector<GraphLet> SearchGraphLet25(int sid);
    QVector<GraphLet> SearchGraphLet26(int sid);
    QVector<GraphLet> SearchGraphLet27(int sid);
    QVector<GraphLet> SearchGraphLet28(int sid);
    QVector<GraphLet> SearchGraphLet29(int sid);

    // de-duplicate graphlets of certain type
    void DedupGraphLets(QVector<GraphLet>& allGraphlets);
    // sort graphlet node in a graphlet
    void SortGraphLet(GraphLet& glet);
    // determine whether two graphlets are the same.
    // Before calling this function, glet1 and glet2 must be sorted.
    bool GraphletEqual(const GraphLet& glet1, const GraphLet& glet2);

};

#endif // GRAPH_H

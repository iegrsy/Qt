#ifndef MYGRAPH_H
#define MYGRAPH_H

#include <mynode.h>

class MyGraph
{
public:
    QList<MyNode> nodes;
    MyGraph();
    void addNode(QString name,QList<MyNode> parents,QList<MyNode> childs);
};

#endif // MYGRAPH_H

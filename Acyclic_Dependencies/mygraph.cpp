#include "mygraph.h"

MyGraph::MyGraph()
{

}

void MyGraph::addNode(QString name,QList<MyNode> parents,QList<MyNode> childs){
    MyNode node(name, parents, childs);
    nodes.append(node);
}

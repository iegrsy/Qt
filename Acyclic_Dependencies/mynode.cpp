#include "mynode.h"

MyNode::MyNode()
{

}

MyNode::MyNode(QString name,QList<MyNode> parents,QList<MyNode> childs)
{
    nodeName=name;
    parentList=parents;
    childList=childs;
}

QString MyNode::getNodeName(){
    return nodeName;
}

void MyNode::toString(){
    foreach (MyNode s, parentList) {
        qDebug()<<nodeName<<"-->"<<s.getNodeName();
    }
    foreach (MyNode s, childList) {
        qDebug()<<nodeName<<"<--"<<s.getNodeName();
    }
}

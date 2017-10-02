#ifndef MYNODE_H
#define MYNODE_H

#include <QString>
#include <QList>
#include <QDebug>

class MyNode
{
    QString nodeName;
    QList<MyNode> parentList;
    QList<MyNode> childList;
public:
    explicit MyNode();
    MyNode(QString name,QList<MyNode> parents,QList<MyNode> childs);
    QString getNodeName();
    void toString();
};

#endif // MYNODE_H

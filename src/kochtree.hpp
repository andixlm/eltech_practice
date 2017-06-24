#ifndef KOCHTREE_HPP
#define KOCHTREE_HPP

#include <QLineF>
#include <QList>

class KochNode
{
public:
    explicit KochNode(QLineF line = QLineF());

    bool setLine(QLineF line);
    QLineF getLine();

    bool addChild(KochNode* node);
    QList<KochNode*> getChildren();

private:
    QLineF mLine;

    QList<KochNode*> mChilder;
};

class KochTree
{
public:
    explicit KochTree();
};

#endif // KOCHTREE_HPP

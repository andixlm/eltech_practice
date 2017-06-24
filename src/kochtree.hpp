#ifndef KOCHTREE_HPP
#define KOCHTREE_HPP

#include <QLineF>
#include <QList>

class KochNode
{
public:
    explicit KochNode(QLineF line = QLineF());

    void setLine(QLineF line);
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
    explicit KochTree(int iterations);

    int getCount();

private:
    int mIterations;

    KochNode* mRoot;
};

#endif // KOCHTREE_HPP

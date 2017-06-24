#ifndef KOCHNODE_HPP
#define KOCHNODE_HPP

#include <QLineF>
#include <QList>

class KochNode
{
public:
    explicit KochNode(QLineF line);

    void setLine(QLineF line);
    QLineF getLine() const;

    bool addChild(KochNode* node);
    bool removeChild(KochNode* node);

    bool isFull() const;
    bool hasChildren() const;

    QList<KochNode*> getChildren();

private:
    const int MAXIMUM_CHILDREN_COUNT = 4;

    QLineF mLine;

    QList<KochNode*> mChildren;
};

#endif // KOCHNODE_HPP

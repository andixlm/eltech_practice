#ifndef KOCHNODE_HPP
#define KOCHNODE_HPP

#include <QList>

#include "kochline.hpp"

class KochNode
{
public:
    explicit KochNode(KochLine line);

    void setLine(KochLine line);
    KochLine getLine() const;

    bool addChild(KochNode* node);
    bool removeChild(KochNode* node);

    bool isFull() const;
    bool hasChildren() const;

    QList<KochNode*> getChildren();

private:
    static const int MAXIMUM_CHILDREN_COUNT = 4;

    KochLine mLine;

    QList<KochNode*> mChildren;
};

#endif // KOCHNODE_HPP

#include <QLineF>

#include "kochnode.hpp"

KochNode::KochNode(QLineF line)
    : mLine(line)
{

}

void KochNode::setLine(QLineF line)
{
    mLine = line;
}

QLineF KochNode::getLine() const
{
    return mLine;
}

bool KochNode::addChild(KochNode* node)
{
    if (mChildren.count() >= MAXIMUM_CHILDREN_COUNT || node == Q_NULLPTR)
    {
        return false;
    }

    mChildren.append(node);

    return true;
}

bool KochNode::removeChild(KochNode* node)
{
    if (node == Q_NULLPTR)
    {
        return false;
    }

    return mChildren.removeOne(node);
}

bool KochNode::isFull() const
{
    return mChildren.count() == MAXIMUM_CHILDREN_COUNT;
}

bool KochNode::hasChildren() const
{
    return !mChildren.isEmpty();
}

QList<KochNode*> KochNode::getChildren()
{
    return mChildren;
}

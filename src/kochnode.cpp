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
    if (mChilder.count() >= MAXIMUM_CHILDER_COUNT || node == Q_NULLPTR)
    {
        return false;
    }

    mChilder.append(node);

    return true;
}

bool KochNode::removeChild(KochNode* node)
{
    if (node == Q_NULLPTR)
    {
        return false;
    }

    return mChilder.removeOne(node);
}

bool KochNode::isFull() const
{
    return mChilder.count() == MAXIMUM_CHILDER_COUNT;
}

bool KochNode::hasChildren() const
{
    return !mChilder.isEmpty();
}

QList<KochNode*> KochNode::getChildren()
{
    return mChilder;
}

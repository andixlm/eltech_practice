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

QLineF KochNode::getLine()
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

QList<KochNode*> KochNode::getChildren()
{
    return mChilder;
}

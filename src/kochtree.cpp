#include <QLineF>

#include "kochtree.hpp"

KochNode::KochNode(QLineF line)
    : mLine(line)
{

}

bool KochNode::setLine(QLineF line)
{
    mLine = line;
}

QLineF KochNode::getLine()
{
    return mLine;
}

bool KochNode::addChild(KochNode* node)
{
    if (mChilder.count() > 3 || node == Q_NULLPTR)
    {
        return false;
    }

    mChilder.append(node);

    return true;
}



KochTree::KochTree()
{

}

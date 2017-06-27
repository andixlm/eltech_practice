#include "kochline.hpp"
#include "kochnode.hpp"

KochNode::KochNode(KochLine line)
    : mLine(line)
{

}

void KochNode::setLine(KochLine line)
{
    mLine = line;
}

KochLine KochNode::getLine() const
{
    return mLine;
}

bool KochNode::addChild(KochNode* node)
{
    if (isFull() || node == Q_NULLPTR)
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

int KochNode::getChildrenCount()
{
    return mChildren.count();
}

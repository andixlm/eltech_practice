#include <QLineF>
#include <QtMath>

#include "kochtree.hpp"

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
    if (mChilder.count() > 3 || node == Q_NULLPTR)
    {
        return false;
    }

    mChilder.append(node);

    return true;
}

KochTree::KochTree(QLineF fLine, QLineF sLine, QLineF tLine)
    : mIterations(DEFAULT_ITERATIONS),
      mRoot(new KochNode())
{
    mRoot->addChild(new KochNode(fLine));
    mRoot->addChild(new KochNode(sLine));
    mRoot->addChild(new KochNode(tLine));
}

int KochTree::getCount()
{
    int count = 3;

    for (int iteration = 2; iteration <= mIterations; ++iteration)
    {
        count += 3 * static_cast<int>(qPow(4.0, static_cast<qreal>(iteration - 1)));
    }

    return count;
}

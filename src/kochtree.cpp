#include <QLineF>
#include <QtMath>

#include "kochnode.hpp"
#include "kochtree.hpp"

KochTree::KochTree(QLineF fLine, QLineF sLine, QLineF tLine)
    : mHeight(DEFAULT_HEIGHT),
      mRoot(new KochNode())
{
    mRoot->addChild(new KochNode(fLine));
    mRoot->addChild(new KochNode(sLine));
    mRoot->addChild(new KochNode(tLine));
}

bool KochTree::insert(QLineF line)
{
    QList<KochNode*> nodes = QList<KochNode*>(mRoot->getChildren());

    while (!nodes.isEmpty())
    {
        KochNode* crntNode = nodes.takeFirst();

        if (crntNode->isFull())
        {
            nodes.append(crntNode->getChildren());
        }
        else
        {
            return crntNode->addChild(new KochNode(line));
        }
    }
}

int KochTree::getCount()
{
    int count = 3;

    for (int height = 2; height <= mHeight; ++height)
    {
        count += 3 * static_cast<int>(qPow(4.0, static_cast<qreal>(height - 1)));
    }

    return count;
}

#include <QtMath>

#include "kochnode.hpp"
#include "kochtree.hpp"

KochTree::KochTree(QList<KochLine> lines)
    : mCount(3),
      mRoot(new KochNode(KochLine()))
{
    for (auto line = lines.cbegin(), listEnd = lines.cend();
         line != listEnd; ++line)
    {
        mRoot->addChild(new KochNode(*line));
    }
}

KochTree::KochTree(KochLine fLine, KochLine sLine, KochLine tLine)
    : mCount(3),
      mRoot(new KochNode(KochLine()))
{
    mRoot->addChild(new KochNode(fLine));
    mRoot->addChild(new KochNode(sLine));
    mRoot->addChild(new KochNode(tLine));
}

KochTree::~KochTree()
{
    this->clear();
}

bool KochTree::insert(KochLine line)
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
            ++mCount;
            return crntNode->addChild(new KochNode(line));
        }
    }

    return false;
}

void KochTree::clear()
{
    _clear(mRoot);
    mRoot = Q_NULLPTR;
}

void KochTree::_clear(KochNode* node)
{
    if (node->hasChildren())
    {
        QList<KochNode*> childNodes = node->getChildren();

        for (auto crntChildNode = childNodes.cbegin(), listEnd = childNodes.cend();
             crntChildNode != listEnd; ++crntChildNode)
        {
            if ((*crntChildNode)->hasChildren())
            {
                _clear(*crntChildNode);
            }
        }
    }
    else
    {
        delete node;
    }
}

int KochTree::getCount() const
{
    return mCount;
}

KochNode* KochTree::getRoot() const
{
    return mRoot;
}

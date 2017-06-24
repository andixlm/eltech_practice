#ifndef KOCHTREE_HPP
#define KOCHTREE_HPP

#include <QLineF>
#include <QList>

#include "kochnode.hpp"

class KochTree
{
public:
    explicit KochTree(QLineF fLine, QLineF sLine, QLineF tLine);

    int getCount();

private:
    const int DEFAULT_HEIGHT = 1;

    int mHeight;

    KochNode* mRoot;
};

#endif // KOCHTREE_HPP

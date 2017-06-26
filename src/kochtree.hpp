#ifndef KOCHTREE_HPP
#define KOCHTREE_HPP

#include <QLineF>
#include <QList>

#include "kochnode.hpp"

class KochTree
{
public:
    explicit KochTree(QList<QLineF> lines);
    explicit KochTree(QLineF fLine, QLineF sLine, QLineF tLine);
    ~KochTree();

    bool insert(QLineF line);
    void clear();

    int getCount() const;
    KochNode* getRoot() const;

private:
    static const int DEFAULT_HEIGHT = 1;

    int mHeight;

    KochNode* mRoot;

    void _clear(KochNode* node);
};

#endif // KOCHTREE_HPP

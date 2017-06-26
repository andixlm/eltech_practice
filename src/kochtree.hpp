#ifndef KOCHTREE_HPP
#define KOCHTREE_HPP

#include <QList>

#include "kochline.hpp"
#include "kochnode.hpp"

class KochTree
{
public:
    explicit KochTree(QList<KochLine> lines);
    explicit KochTree(KochLine fLine, KochLine sLine, KochLine tLine);
    ~KochTree();

    bool insert(KochLine line);
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

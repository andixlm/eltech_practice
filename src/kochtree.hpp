#ifndef KOCHTREE_HPP
#define KOCHTREE_HPP

#include <QList>

#include "kochline.hpp"
#include "kochnode.hpp"

class KochTree
{
public:
    explicit KochTree(const QList<KochLine>&& lines);
    explicit KochTree(const KochLine& fLine,
                      const KochLine& sLine,
                      const KochLine& tLine);
    ~KochTree();

    bool insert(const KochLine& line);
    void clear();

    int getCount() const;
    KochNode* getRoot() const;

private:
    int mCount;

    KochNode* mRoot;

    void _clear(KochNode* node);
};

#endif // KOCHTREE_HPP

#ifndef KOCHNODE_HPP
#define KOCHNODE_HPP

#include <QLineF>
#include <QList>

class KochNode
{
public:
    explicit KochNode(QLineF line = QLineF());

    void setLine(QLineF line);
    QLineF getLine();

    bool addChild(KochNode* node);
    bool removeChild(KochNode* node);

    QList<KochNode*> getChildren();

private:
    const int MAXIMUM_CHILDER_COUNT = 4;

    QLineF mLine;

    QList<KochNode*> mChilder;
};

#endif // KOCHNODE_HPP

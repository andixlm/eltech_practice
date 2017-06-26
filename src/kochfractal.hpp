#ifndef KOCHFRACTAL_HPP
#define KOCHFRACTAL_HPP

#include <QLineF>
#include <QList>

#include "kochtree.hpp"

class KochFractal
{
public:
    explicit KochFractal(QList<QLineF> lines);
    explicit KochFractal(QLineF fLine, QLineF sLine, QLineF tLine);

    bool setIterations(int iterations);
    int getIterations() const;

    KochTree* getTree();

    QImage getKochSnowflake(int width, int height);
    QImage getKochSnowflake(QSize size);

    void process();

private:
    const int MINIMUM_ITERATIONS = 1;
    const int DEFAULT_ITERATIONS = 1;
    const int MAXIMUM_ITERATIONS = 7;

    int mIterations;

    KochTree mKochTree;

    void _getKochSnowflake(KochNode* node, QImage* image);
};

#endif // KOCHFRACTAL_HPP

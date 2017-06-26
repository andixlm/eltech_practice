#ifndef KOCHFRACTAL_HPP
#define KOCHFRACTAL_HPP

#include <QSize>

#include "kochtree.hpp"

class KochFractal
{
public:
    explicit KochFractal(int width, int height);
    explicit KochFractal(QSize size);

    bool setIterations(int iterations);
    int getIterations() const;

    KochTree* getTree();

    QImage getKochSnowflake(int width, int height);
    QImage getKochSnowflake(QSize size);

    void process();

private:
    static const int MINIMUM_ITERATIONS = 1;
    static const int DEFAULT_ITERATIONS = 1;
    static const int MAXIMUM_ITERATIONS = 7;

    int mIterations;

    KochTree mKochTree;

    void _getKochSnowflake(KochNode* node, QImage* image);
};

#endif // KOCHFRACTAL_HPP

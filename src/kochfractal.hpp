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

    QImage getTreeImage();
    QImage getKochSnowflake();

    void process();

private:
    static const int MINIMUM_ITERATIONS = 1;
    static const int DEFAULT_ITERATIONS = 1;
    static const int MAXIMUM_ITERATIONS = 7;

    static const int NODE_CIRCLE_RADIUS = 5;
    static const int HORIZONTAL_GAP = 3 * NODE_CIRCLE_RADIUS;
    static const int VERTICAL_GAP = 4 * NODE_CIRCLE_RADIUS;

    int mIterations;

    KochTree mKochTree;

    void _getTreeImage(KochNode* node, QImage* image, QPointF parent,
                       double minX, double maxX, int y, int height);
    void _getKochSnowflake(KochNode* node, QImage* image);

    QSize getTreeImageSize();
};

#endif // KOCHFRACTAL_HPP

#ifndef TOOLS_HPP
#define TOOLS_HPP

#include <QImage>
#include <QLineF>
#include <QList>
#include <QSize>

class Tools
{
public:
    static QImage getPlaneImage(int width, int height);
    static QImage getPlaneImage(QSize size);

    static QImage getEquilateralTriangle(int width, int height);
    static QImage getEquilateralTriangle(QSize size);
    static QList<QLineF> getEquilateralTriangleLines(int width, int height);
    static QList<QLineF> getEquilateralTriangleLines(QSize size);

    static int gcd(int alpha, int beta);
};

#endif // TOOLS_HPP

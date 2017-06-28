#ifndef TOOLS_HPP
#define TOOLS_HPP

#include <QImage>
#include <QList>
#include <QSize>

#include "kochline.hpp"

class Tools
{
public:
    static QImage getImage(int width, int height);
    static QImage getImage(QSize size);

    static QImage getPlaneImage(int width, int height);
    static QImage getPlaneImage(QSize size);

    static QImage getEquilateralTriangle(int width, int height);
    static QImage getEquilateralTriangle(QSize size);
    static QList<KochLine> getEquilateralTriangleLines(int width, int height);
    static QList<KochLine> getEquilateralTriangleLines(QSize size);

    static QColor getColorByHeight(int height);

    static int gcd(int alpha, int beta);
};

#endif // TOOLS_HPP

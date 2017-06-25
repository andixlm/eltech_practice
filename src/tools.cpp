#include <QImage>
#include <QList>
#include <QPainter>
#include <QPointF>
#include <QtMath>

#include "tools.hpp"

QImage Tools::getImage(int width, int height)
{
    QImage image = QImage(width, height, QImage::Format_RGB32);
    image.fill(Qt::white);

    return image;
}

QImage Tools::getImage(QSize size)
{
    return getImage(size.width(), size.height());
}

QImage Tools::getPlaneImage(int width, int height)
{
    QImage image = getImage(width, height);

    QPainter painter;

    painter.begin(&image);
    painter.drawLine(0, height / 2, width, height / 2);
    painter.drawLine(width / 2, 0, width / 2, height);
    painter.end();

    return image;
}

QImage Tools::getPlaneImage(QSize size)
{
    return getPlaneImage(size.width(), size.height());
}

QImage Tools::getEquilateralTriangle(int width, int height)
{
    QImage image = getImage(width, height);

    QList<QLineF> lines = getEquilateralTriangleLines(width, height);

    QPainter painter;
    painter.begin(&image);
    for (auto line = lines.cbegin(), listEnd = lines.cend();
         line != listEnd; ++line)
    {
        painter.drawLine(*line);
    }
    painter.end();

    return image;
}

QImage Tools::getEquilateralTriangle(QSize size)
{
    return getEquilateralTriangle(size.width(), size.height());
}

QList<QLineF> Tools::getEquilateralTriangleLines(int width, int height)
{
    QList<QLineF> lines;
    QLineF lineOne, lineTwo, lineThree;
    double lineLength = static_cast<double>(width) - 200.0;
    double triangleHeight = lineLength * qCos(qDegreesToRadians(30.0));

    lineOne.setP1(QPointF(static_cast<double>(width) - 100.0,
                          static_cast<double>(height) / 2.0 +
                          triangleHeight / 2.0));
    lineOne.setLength(lineLength);
    lineOne.setAngle(180.0);

    lineTwo.setP1(QPointF(100.0,
                          static_cast<double>(height) / 2.0 +
                          triangleHeight / 2.0));
    lineTwo.setLength(lineLength);
    lineTwo.setAngle(60.0);

    lineThree.setP1(QPointF(static_cast<double>(width) - 100.0,
                            static_cast<double>(height) / 2.0 +
                            triangleHeight / 2.0));
    lineThree.setLength(lineLength);
    lineThree.setAngle(120.0);

    lines.append(lineOne);
    lines.append(lineTwo);
    lines.append(lineThree);

    return lines;
}

QList<QLineF> Tools::getEquilateralTriangleLines(QSize size)
{
    return getEquilateralTriangleLines(size.width(), size.height());
}

int Tools::gcd(int alpha, int beta)
{
    while (alpha != 0 && beta != 0)
    {
        if (alpha >= beta)
        {
            alpha %= beta;
        }
        else
        {
            beta %= alpha;
        }
    }

    return alpha + beta;
}

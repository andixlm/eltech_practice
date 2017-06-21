#include <QImage>
#include <QPainter>

#include "tools.hpp"

QImage Tools::getPlaneImage(int width, int height)
{
    QImage image = QImage(width, height, QImage::Format_RGB32);
    image.fill(Qt::white);

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

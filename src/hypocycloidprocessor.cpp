#include <QPainter>
#include <QPointF>
#include <QSize>
#include <QThread>
#include <QtMath>

#include "hypocycloidprocessor.hpp"
#include "tools.hpp"

HypocycloidProcessor::HypocycloidProcessor(QSize imageSize,
                                           int outerRadius, int innerRadius)
    : mImageSize(imageSize),
      mAbscissaOrigin(imageSize.width() / 2),
      mOrdinateOrigin(imageSize.height() / 2),
      mOuterRadius(outerRadius),
      mInnerRadius(innerRadius),
      mRadiusRelation(static_cast<float>(mOuterRadius) /
                      static_cast<float>(mInnerRadius))
{

}

void HypocycloidProcessor::process()
{
    mImage = Tools::getPlaneImage(mImageSize);

    QPainter painter;
    painter.begin(&mImage);
    painter.drawEllipse(QPoint(mAbscissaOrigin, mOrdinateOrigin),
                        mOuterRadius, mOuterRadius);
    painter.end();

    emit imageReady(mImage);

    int angle = 0;
    int lapsAngle = 360 * mInnerRadius / Tools::gcd(mOuterRadius, mInnerRadius);
    float lastX, lastY, crntX, crntY;

    lastX = computeX(angle);
    lastY = computeY(angle);
    ++angle;

    while (angle != lapsAngle)
    {
        crntX = computeX(angle);
        crntY = computeY(angle);

        painter.begin(&mImage);
        painter.drawLine(QPointF(static_cast<float>(mAbscissaOrigin) + lastX,
                                 static_cast<float>(mOrdinateOrigin) + lastY),
                         QPointF(static_cast<float>(mAbscissaOrigin) + crntX,
                                 static_cast<float>(mOrdinateOrigin) + crntY));
        painter.end();

        emit imageReady(mImage);

        lastX = crntX;
        lastY = crntY;
        ++angle;

        QThread::msleep(1000 / FPS);
    }

    emit finished();
}


float HypocycloidProcessor::computeX(int angle)
{
    float angleRadians = qDegreesToRadians(static_cast<float>(angle));

    return static_cast<float>(mInnerRadius) * (mRadiusRelation - 1.0f) *
            (qCos(angleRadians) + qCos((mRadiusRelation - 1.0f) * angleRadians) /
             (mRadiusRelation - 1.0f));
}

float HypocycloidProcessor::computeY(int angle)
{
    float angleRadians = qDegreesToRadians(static_cast<float>(angle));

    return static_cast<float>(mInnerRadius) * (mRadiusRelation - 1.0f) *
            (qSin(angleRadians) - qSin((mRadiusRelation - 1.0f) * angleRadians) /
             (mRadiusRelation - 1.0f));
}

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

    drawOuterCicrle();
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

        drawHypocycloidPart(lastX, lastY, crntX, crntY);

        emit imageReady(drawInnerCircle(angle, crntX, crntY));

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

QImage HypocycloidProcessor::drawInnerCircle(int angle,
                                             float crntX, float crntY)
{
    int centerOfInnerCircle = qAbs(mOuterRadius - mInnerRadius);
    float angleRadians = qDegreesToRadians(static_cast<float>(angle));

    float innerCircleX = static_cast<float>(mAbscissaOrigin) +
            static_cast<float>(centerOfInnerCircle) * qCos(angleRadians);
    float innerCircleY = static_cast<float>(mOrdinateOrigin) +
            static_cast<float>(centerOfInnerCircle) * qSin(angleRadians);

    QImage image = mImage;

    QPainter painter;
    painter.begin(&image);
    painter.setPen(Qt::DashLine);
    painter.drawEllipse(QPointF(innerCircleX, innerCircleY),
                        static_cast<float>(mInnerRadius),
                        static_cast<float>(mInnerRadius));
    painter.drawLine(QPointF(innerCircleX, innerCircleY),
                     QPointF(static_cast<float>(mAbscissaOrigin) + crntX,
                             static_cast<float>(mOrdinateOrigin) + crntY));
    painter.end();

    return image;
}

void HypocycloidProcessor::drawOuterCicrle()
{
    QPainter painter;

    painter.begin(&mImage);
    painter.drawEllipse(QPoint(mAbscissaOrigin, mOrdinateOrigin),
                        mOuterRadius, mOuterRadius);
    painter.end();
}

void HypocycloidProcessor::drawHypocycloidPart(float& lastX, float& lastY,
                                               float& crntX, float& crntY)
{
    QPainter painter;

    painter.begin(&mImage);
    painter.drawLine(QPointF(static_cast<float>(mAbscissaOrigin) + lastX,
                             static_cast<float>(mOrdinateOrigin) + lastY),
                     QPointF(static_cast<float>(mAbscissaOrigin) + crntX,
                             static_cast<float>(mOrdinateOrigin) + crntY));
    painter.end();
}

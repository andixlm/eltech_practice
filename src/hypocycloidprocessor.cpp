#include <QPainter>
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
      mInnerRadius(innerRadius)
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
    mLastX = computeX(angle);
    mLastY = computeY(angle);
    ++angle;

    while (angle % 360 != 0)
    {
        int crntX = computeX(angle);
        int crntY = computeY(angle);

        painter.begin(&mImage);
        painter.drawLine(mAbscissaOrigin + mLastX, mOrdinateOrigin + mLastY,
                         mAbscissaOrigin + crntX, mOrdinateOrigin + crntY);
        painter.end();

        emit imageReady(mImage);

        mLastX = crntX;
        mLastY = crntY;
        ++angle;

        QThread::msleep(1000 / FPS);
    }

    emit finished();
}


int HypocycloidProcessor::computeX(int angle)
{
    float angleRadians = qDegreesToRadians(static_cast<float>(angle));

    return (mOuterRadius - mInnerRadius) * qCos(angleRadians) + mInnerRadius *
            qCos((mOuterRadius - mInnerRadius) / mInnerRadius * angleRadians);
}

int HypocycloidProcessor::computeY(int angle)
{
    float angleRadians = qDegreesToRadians(static_cast<float>(angle));

    return (mOuterRadius - mInnerRadius) * qSin(angleRadians) - mInnerRadius *
            qSin((mOuterRadius - mInnerRadius) / mInnerRadius * angleRadians);
}

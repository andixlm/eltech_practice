#include <QPainter>
#include <QPen>
#include <QPointF>
#include <QSize>
#include <QThread>
#include <QtMath>

#include "hypocycloidprocessor.hpp"
#include "tools.hpp"

HypocycloidProcessor::HypocycloidProcessor(int outerRadius, int innerRadius,
                                           int fps, QSize imageSize,
                                           QColor fillColor,
                                           QColor outlineColor)
    : mFps(fps),
      mImageSize(imageSize),
      mFillColor(fillColor),
      mOutlineColor(outlineColor),
      mAbscissaOrigin(imageSize.width() / 2),
      mOrdinateOrigin(imageSize.height() / 2),
      mOuterRadius(outerRadius),
      mInnerRadius(innerRadius),
      mInnerCircleCenter(qAbs(mOuterRadius - mInnerRadius)),
      mRadiusRelation(static_cast<float>(mOuterRadius) /
                      static_cast<float>(mInnerRadius)),
      mAngle(0),
      mAngleRadians(mAngle),
      mCurrentX(0),
      mCurrentY(0),
      mLastX(mCurrentX),
      mLastY(mCurrentY)
{

}

void HypocycloidProcessor::setImageSize(QSize imageSize)
{
    mImageSize = imageSize;
}

QSize HypocycloidProcessor::getImageSize()
{
    return mImageSize;
}

void HypocycloidProcessor::setFps(int fps)
{
    mFps = fps;
}

int HypocycloidProcessor::getFps()
{
    return mFps;
}

void HypocycloidProcessor::process()
{
    mImage = Tools::getPlaneImage(mImageSize);
    drawOuterCicrle();
    emit imageReady(mImage);

    int lapsAngle = 360 * mInnerRadius / Tools::gcd(mOuterRadius, mInnerRadius);

    mLastX = computeX();
    mLastY = computeY();
    ++mAngle;

    while (mAngle <= lapsAngle)
    {
        mAngleRadians = qDegreesToRadians(static_cast<float>(mAngle));

        mCurrentX = computeX();
        mCurrentY = computeY();

        drawHypocycloidPart();

        emit imageReady(drawInnerCircle());

        mLastX = mCurrentX;
        mLastY = mCurrentY;
        ++mAngle;

        QThread::msleep(1000 / mFps);
    }

    emit finished();
}


float HypocycloidProcessor::computeX()
{
    return static_cast<float>(mInnerRadius) * (mRadiusRelation - 1.0f) *
            (qCos(mAngleRadians) + qCos((mRadiusRelation - 1.0f) * mAngleRadians) /
             (mRadiusRelation - 1.0f));
}

float HypocycloidProcessor::computeY()
{
    return static_cast<float>(mInnerRadius) * (mRadiusRelation - 1.0f) *
            (qSin(mAngleRadians) - qSin((mRadiusRelation - 1.0f) * mAngleRadians) /
             (mRadiusRelation - 1.0f));
}

QImage HypocycloidProcessor::drawInnerCircle()
{
    float innerCircleX = static_cast<float>(mAbscissaOrigin) +
            static_cast<float>(mInnerCircleCenter) * qCos(mAngleRadians);
    float innerCircleY = static_cast<float>(mOrdinateOrigin) +
            static_cast<float>(mInnerCircleCenter) * qSin(mAngleRadians);

    QPainter painter;
    QImage image = mImage;
    painter.begin(&image);
    painter.setPen(Qt::DashLine);
    painter.drawEllipse(QPointF(innerCircleX, innerCircleY),
                        static_cast<float>(mInnerRadius),
                        static_cast<float>(mInnerRadius));
    painter.fillRect(QRectF(QPointF(innerCircleX - (mInnerRadius * 1.25f) / 2.0f,
                                    innerCircleY - (mInnerRadius * 1.25f) / 2.0f),
                            QSizeF(static_cast<float>(mInnerRadius * 1.25f),
                                   static_cast<float>(mInnerRadius * 1.25f))),
                     mFillColor);
    painter.drawLine(QPointF(innerCircleX, innerCircleY),
                     QPointF(static_cast<float>(mAbscissaOrigin) + mCurrentX,
                             static_cast<float>(mOrdinateOrigin) + mCurrentY));
    painter.end();

    return image;
}

void HypocycloidProcessor::drawOuterCicrle()
{
    QPainter painter;
    painter.begin(&mImage);
    painter.setPen(Qt::DashLine);
    painter.drawEllipse(QPoint(mAbscissaOrigin, mOrdinateOrigin),
                        mOuterRadius, mOuterRadius);
    painter.end();
}

void HypocycloidProcessor::drawHypocycloidPart()
{
    QPainter painter;
    painter.begin(&mImage);
    painter.setPen(mOutlineColor);
    painter.drawLine(QPointF(static_cast<float>(mAbscissaOrigin) + mLastX,
                             static_cast<float>(mOrdinateOrigin) + mLastY),
                     QPointF(static_cast<float>(mAbscissaOrigin) + mCurrentX,
                             static_cast<float>(mOrdinateOrigin) + mCurrentY));
    painter.end();
}

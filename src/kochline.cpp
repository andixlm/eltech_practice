#include <QLineF>
#include <QPointF>
#include <QtMath>

#include "kochline.hpp"

KochLine::KochLine(double x, double y, double length, double angle)
    : mP1(QPointF(x, y)),
      mLength(length),
      mAngle(angle)
{

}

QPointF KochLine::getP1()
{
    return mP1;
}

void KochLine::setP1(QPointF point)
{
    mP1 = point;
}

QPointF KochLine::getP2()
{
    return QPointF(mP1.x() + mLength * qCos(qDegreesToRadians(mAngle)),
                   mP1.y() + mLength * qSin(qDegreesToRadians(mAngle)));
}

double KochLine::getLength()
{
    return mLength;
}

void KochLine::setLength(double length)
{
    mLength = length;
}

double KochLine::getAngle()
{
    return mAngle;
}

void KochLine::setAngle(double angle)
{
    mAngle = angle;
}

QLineF KochLine::getLine()
{
    return QLineF(this->getP1(), this->getP2());
}
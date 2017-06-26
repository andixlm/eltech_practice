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

double KochLine::getX1()
{
    return this->getP1().x();
}

void KochLine::setX1(double x)
{
    this->getP1().setX(x);
}

double KochLine::getY1()
{
    return this->getP1().y();
}

void KochLine::setY1(double y)
{
    this->getP1().setY(y);
}

QPointF KochLine::getP2()
{
    return QPointF(mP1.x() + mLength * qCos(qDegreesToRadians(mAngle)),
                   mP1.y() + mLength * qSin(qDegreesToRadians(mAngle)));
}

double KochLine::getX2()
{
    return this->getP2().x();
}

double KochLine::getY2()
{
    return this->getP2().y();
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

#ifndef KOCHLINE_HPP
#define KOCHLINE_HPP

#include <QLineF>
#include <QPointF>

class KochLine
{
public:
    KochLine(double x = 0.0, double y = 0.0,
             double length = 0.0, double angle = 0.0);

    QPointF getP1();
    void setP1(QPointF point);

    double getX1();
    void setX1(double x);
    double getY1();
    void setY1(double y);

    QPointF getP2();

    double getX2();
    double getY2();

    double getLength();
    void setLength(double length);

    double getAngle();
    void setAngle(double angle);

    QLineF getLine();

private:
    QPointF mP1;

    double mLength;
    double mAngle;
};

#endif // KOCHLINE_HPP

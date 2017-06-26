#ifndef KOCHLINE_HPP
#define KOCHLINE_HPP

#include <QLineF>
#include <QPointF>

class KochLine
{
public:
    KochLine(double x = 0.0, double y = 0.0,
             double length = 0.0, double angle = 0.0);

    inline QPointF getP1();
    inline void setP1(QPointF point);

    inline QPointF getP2();

    inline double getLength();
    inline void setLength(double length);

    inline QLineF getLine();

private:
    QPointF mP1;

    double mLength;
    double mAngle;
};

#endif // KOCHLINE_HPP

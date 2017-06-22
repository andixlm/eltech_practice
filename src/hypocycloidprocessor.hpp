#ifndef HYPOCYCLOIDPROCESSOR_HPP
#define HYPOCYCLOIDPROCESSOR_HPP

#include <QImage>
#include <QSize>

class HypocycloidProcessor : public QObject
{
    Q_OBJECT

public:
    HypocycloidProcessor(QSize mImageSize, int outerRadius, int innerRadius);

    void setImageSize(QSize imageSize);
    QSize getImageSize();

public slots:
    void process();

private:
    const int FPS = 120;

    QImage mImage;
    QSize mImageSize;

    int mAbscissaOrigin;
    int mOrdinateOrigin;

    int mOuterRadius;
    int mInnerRadius;
    int mInnerCircleCenter;
    float mRadiusRelation;

    int mAngle;
    float mAngleRadians;

    float mCurrentX;
    float mCurrentY;
    float mLastX;
    float mLastY;

    float computeX();
    float computeY();

    QImage drawInnerCircle();
    void drawOuterCicrle();
    void drawHypocycloidPart();

signals:
    void imageReady(const QImage& image);
    void finished();
};

#endif // HYPOCYCLOIDPROCESSOR_HPP

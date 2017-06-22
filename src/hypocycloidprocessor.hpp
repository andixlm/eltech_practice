#ifndef HYPOCYCLOIDPROCESSOR_HPP
#define HYPOCYCLOIDPROCESSOR_HPP

#include <QImage>
#include <QSize>

class HypocycloidProcessor : public QObject
{
    Q_OBJECT

public:
    HypocycloidProcessor(QSize mImageSize, int outerRadius, int innerRadius);

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
    float mRadiusRelation;

    float computeX(int angle);
    float computeY(int angle);

    QImage drawInnerCircle(int angle, float crntX, float crntY);
    void drawOuterCicrle();
    void drawHypocycloidPart(float& lastX, float& lastY,
                             float& crntX, float& crntY);

signals:
    void imageReady(const QImage& image);
    void finished();
};

#endif // HYPOCYCLOIDPROCESSOR_HPP

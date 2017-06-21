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
    const int FPS = 60;

    QImage mImage;
    QSize mImageSize;

    int mAbscissaOrigin;
    int mOrdinateOrigin;

    int mOuterRadius;
    int mInnerRadius;

    int mLastX;
    int mLastY;

    int computeX(int angle);
    int computeY(int angle);

signals:
    void imageReady(const QImage& image);
    void finished();
};

#endif // HYPOCYCLOIDPROCESSOR_HPP

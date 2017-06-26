#ifndef IH1WIDGET_HPP
#define IH1WIDGET_HPP

#include <QColor>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QImage>
#include <QLabel>
#include <QPushButton>
#include <QSize>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QWidget>

#include "clickablelabel.hpp"
#include "hypocycloidprocessor.hpp"
#include "ihwidget.hpp"

class IH1Widget : public IHWidget
{
    Q_OBJECT

public:
    explicit IH1Widget(QWidget* parent = Q_NULLPTR);

private:
    static const int DEFAULT_FPS = 60;
    static const int MINIMUM_FPS = 24;
    static const int MAXIMUM_FPS = 1000;

    static const int DEFAULT_RADIUS = 200;
    static const int MINIMUM_RADIUS = 1;
    static const int MAXIMUM_RADIUS = 512;

    static const Qt::GlobalColor DEFAULT_FILL_COLOR = Qt::white;
    static const Qt::GlobalColor DEFAULT_OUTLINE_COLOR = Qt::black;

    static const int IMAGE_WIDTH = 512;
    static const int IMAGE_HEIGHT = 512;

    int mFps;

    int mOuterCircleRadius;
    int mInnerCircleRadius;

    HypocycloidProcessor* mProcessor;
    QThread* mProcessorThread;

    QGridLayout mParametersLayout;

    QLabel mTaskDescription;
    QLabel mTaskImage;
    QLabel mOuterCircleRadiusLabel;
    QSpinBox mOuterCircleRadiusSpinBox;
    QLabel mInnerCircleRadiusLabel;
    QSpinBox mInnerCircleRadiusSpinBox;

    QLabel mFpsLabel;
    QSpinBox mFpsSpinBox;

    QColor mFillColor;
    QLabel mFillColorLabel;
    ClickableLabel mFillColorFrame;
    QColor mOutlineColor;
    QLabel mOutlineColorLabel;
    ClickableLabel mOutlineColorFrame;

    QLabel mStartButtonLabel;
    QPushButton mStartButton;

    QLabel mImageFrame;

private slots:
    void startButtonPressed();
    void updateImage(QImage image);
};

#endif // IH1WIDGET_HPP

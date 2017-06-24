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
    ~IH1Widget();

private:
    const int DEFAULT_FPS = 60;
    const int MINIMUM_FPS = 24;
    const int MAXIMUM_FPS = 1000;

    const int DEFAULT_RADIUS = 200;
    const int MINIMUM_RADIUS = 1;
    const int MAXIMUM_RADIUS = 512;

    const Qt::GlobalColor DEFAULT_FILL_COLOR = Qt::white;
    const Qt::GlobalColor DEFAULT_OUTLINE_COLOR = Qt::black;

    const int IMAGE_WIDTH = 512;
    const int IMAGE_HEIGHT = 512;

    int mFps;

    int mOuterCircleRadius;
    int mInnerCircleRadius;

    HypocycloidProcessor* mProcessor;
    QThread* mProcessorThread;

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

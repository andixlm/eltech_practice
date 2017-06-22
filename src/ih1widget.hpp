#ifndef IH1WIDGET_HPP
#define IH1WIDGET_HPP

#include <QGridLayout>
#include <QHBoxLayout>
#include <QImage>
#include <QLabel>
#include <QPushButton>
#include <QSize>
#include <QSpinBox>
#include <QVBoxLayout>
#include <QWidget>

#include "hypocycloidprocessor.hpp"

class IH1Widget : public QWidget
{
    Q_OBJECT

public:
    IH1Widget(QWidget* parent = Q_NULLPTR);
    ~IH1Widget();

private:
    const int DEFAULT_FPS = 60;
    const int MINIMUM_FPS = 24;
    const int MAXIMUM_FPS = 1000;

    const int DEFAULT_RADIUS = 200;
    const int MINIMUM_RADIUS = 1;
    const int MAXIMUM_RADIUS = 200;

    const int IMAGE_WIDTH = 512;
    const int IMAGE_HEIGHT = 512;
    const QSize IMAGE_SIZE = QSize(IMAGE_WIDTH, IMAGE_HEIGHT);

    int mFps;

    int mOuterCircleRadius;
    int mInnerCircleRadius;

    HypocycloidProcessor* mProcessor;
    QThread* mProcessorThread;

    QHBoxLayout mMainLayout;

    QWidget mControlWidget;
    QVBoxLayout mInfoLayout;
    QGridLayout mParametersLayout;
    QLabel mTaskDescription;
    QLabel mTaskImage;
    QLabel mOuterCircleRadiusLabel;
    QSpinBox mOuterCircleRadiusSpinBox;
    QLabel mInnerCircleRadiusLabel;
    QSpinBox mInnerCircleRadiusSpinBox;

    QLabel mFpsLabel;
    QSpinBox mFpsSpinBox;

    QLabel mStartButtonLabel;
    QPushButton mStartButton;

    QLabel mImageFrame;

private slots:
    void startButtonPressed();
    void updateImage(QImage image);
};

#endif // IH1WIDGET_HPP

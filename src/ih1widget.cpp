#include <QColorDialog>
#include <QThread>
#include <QWidget>

#include "hypocycloidprocessor.hpp"
#include "ihwidget.hpp"
#include "ih1widget.hpp"
#include "tools.hpp"

IH1Widget::IH1Widget(QWidget* parent)
    : IHWidget(parent),
      mFps(DEFAULT_FPS),
      mOuterCircleRadius(DEFAULT_RADIUS),
      mInnerCircleRadius(DEFAULT_RADIUS * 3 / 5),
      mProcessor(Q_NULLPTR),
      mProcessorThread(Q_NULLPTR),
      mFillColor(DEFAULT_FILL_COLOR),
      mOutlineColor(DEFAULT_OUTLINE_COLOR)
{
    mTaskDescription.setText("Shape:\thypocycloid;\n"
                             "Object:\tcircle;\n"
                             "Fill:\t~50%;\n"
                             "Outine:\tset color;");
    mInfoLayout.addWidget(&mTaskDescription);

    mTaskImage.setPixmap(QPixmap::fromImage(QImage("res/ih1.jpg")));
    mInfoLayout.addWidget(&mTaskImage);

    mOuterCircleRadiusLabel.setText("Outer cicrle radius: ");
    mOuterCircleRadiusSpinBox.setMinimum(MINIMUM_RADIUS);
    mOuterCircleRadiusSpinBox.setMaximum(MAXIMUM_RADIUS);
    mOuterCircleRadiusSpinBox.setValue(mOuterCircleRadius);
    connect(&mOuterCircleRadiusSpinBox,
            static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this,[this](int value) {
        mOuterCircleRadius = value;

        if (mOuterCircleRadius <= mInnerCircleRadius)
        {
            mStartButton.setEnabled(false);
        }
        else
        {
            mStartButton.setEnabled(true);
        }
    });
    mParametersLayout.addWidget(&mOuterCircleRadiusLabel, 0, 0);
    mParametersLayout.addWidget(&mOuterCircleRadiusSpinBox, 0, 1);

    mInnerCircleRadiusLabel.setText("Inner circle radius: ");
    mInnerCircleRadiusSpinBox.setMinimum(MINIMUM_RADIUS);
    mInnerCircleRadiusSpinBox.setMaximum(MAXIMUM_RADIUS);
    mInnerCircleRadiusSpinBox.setValue(mInnerCircleRadius);
    connect(&mInnerCircleRadiusSpinBox,
            static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this, [this](int value) {
        mInnerCircleRadius = value;

        if (mInnerCircleRadius < mOuterCircleRadius)
        {
            mStartButton.setEnabled(true);
        }
        else
        {
            mStartButton.setEnabled(false);
        }
    });
    mParametersLayout.addWidget(&mInnerCircleRadiusLabel, 1, 0);
    mParametersLayout.addWidget(&mInnerCircleRadiusSpinBox, 1, 1);

    mFpsLabel.setText("Frames per second: ");
    mFpsSpinBox.setMinimum(MINIMUM_FPS);
    mFpsSpinBox.setMaximum(MAXIMUM_FPS);
    mFpsSpinBox.setValue(DEFAULT_FPS);
    connect(&mFpsSpinBox,
            static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this, [this](int fps) {
        mFps = fps;

        if (mProcessor != Q_NULLPTR)
        {
            mProcessor->setFps(fps);
        }
    });
    mParametersLayout.addWidget(&mFpsLabel, 2, 0);
    mParametersLayout.addWidget(&mFpsSpinBox, 2, 1);

    mFillColorLabel.setText("Fill color: ");
    mFillColorFrame.setFrameStyle(QFrame::Box);
    connect(&mFillColorFrame, &ClickableLabel::clicked,
            this, [this]() {
        mFillColor = QColorDialog::getColor();
        mFillColorFrame.setStyleSheet(
                    "background-color: rgb(" +
                    QString::number(mFillColor.red()) + ", " +
                    QString::number(mFillColor.green()) + ", " +
                    QString::number(mFillColor.blue()) + ");");
    });
    mParametersLayout.addWidget(&mFillColorLabel, 3, 0);
    mParametersLayout.addWidget(&mFillColorFrame, 3, 1);

    mOutlineColorLabel.setText("Outline color: ");
    mOutlineColorFrame.setFrameStyle(QFrame::Box);
    connect(&mOutlineColorFrame, &ClickableLabel::clicked,
            this, [this]() {
        mOutlineColor = QColorDialog::getColor();
        mOutlineColorFrame.setStyleSheet(
                    "background-color: rgb(" +
                    QString::number(mOutlineColor.red()) + ", " +
                    QString::number(mOutlineColor.green()) + ", " +
                    QString::number(mOutlineColor.blue()) + ");");
    });
    mParametersLayout.addWidget(&mOutlineColorLabel, 4, 0);
    mParametersLayout.addWidget(&mOutlineColorFrame, 4, 1);

    mStartButtonLabel.setText("Click to animate:");
    mParametersLayout.addWidget(&mStartButtonLabel, 5, 0);
    mStartButton.setText("Start");
    connect(&mStartButton, &QPushButton::clicked,
            this, &IH1Widget::startButtonPressed);
    mParametersLayout.addWidget(&mStartButton, 5, 1);

    mInfoLayout.addLayout(&mParametersLayout);

    mMainLayout.addWidget(&mControlWidget);

    mImageFrame.setFixedSize(IMAGE_WIDTH, IMAGE_HEIGHT);
    mImageFrame.setFrameStyle(QFrame::Box);
    mImageFrame.setPixmap(QPixmap::fromImage(Tools::getPlaneImage(IMAGE_WIDTH,
                                                                  IMAGE_HEIGHT)));
    mMainLayout.addWidget(&mImageFrame);
}

IH1Widget::~IH1Widget()
{

}

void IH1Widget::startButtonPressed()
{
    if (mFillColor.name() == "#ffffff")
    {
        mFillColor.setAlpha(0);
    }

    mProcessorThread = new QThread();
    mProcessor = new HypocycloidProcessor(mOuterCircleRadius,
                                          mInnerCircleRadius,
                                          mFps, QSize(IMAGE_WIDTH, IMAGE_HEIGHT),
                                          mFillColor,
                                          mOutlineColor);
    mProcessor->moveToThread(mProcessorThread);

    connect(mProcessor, &HypocycloidProcessor::imageReady,
            this, &IH1Widget::updateImage);
    connect(mProcessorThread, &QThread::started,
            this, [this]() { mStartButton.setEnabled(false); });
    connect(mProcessor, &HypocycloidProcessor::finished,
            this, [this]() {
        delete mProcessor;
        mProcessor = Q_NULLPTR;

        mProcessorThread->exit();
        mProcessorThread = Q_NULLPTR;

        mStartButton.setEnabled(true);
    });
    connect(mProcessorThread, &QThread::started,
            mProcessor, &HypocycloidProcessor::process);

    mProcessorThread->start();
}

void IH1Widget::updateImage(QImage image)
{
    mImageFrame.setPixmap(QPixmap::fromImage(image));
}

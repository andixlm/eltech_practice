#include <QColorDialog>
#include <QThread>
#include <QWidget>

#include "hypocycloidprocessor.hpp"
#include "ih1widget.hpp"
#include "tools.hpp"

IH1Widget::IH1Widget(QWidget* parent)
    : QWidget(parent),
      mFps(DEFAULT_FPS),
      mOuterCircleRadius(DEFAULT_RADIUS),
      mInnerCircleRadius(DEFAULT_RADIUS * 3 / 5),
      mProcessor(Q_NULLPTR),
      mProcessorThread(Q_NULLPTR),
      mMainLayout(this),
      mControlWidget(this),
      mInfoLayout(&mControlWidget)
{
    mTaskDescription.setText("Task:\n"
                             "\tShape:\thypocycloid;\n"
                             "\tObject:\tcircle;\n"
                             "\tFill:\t~50%;\n"
                             "\tOutine:\tset color;");
    mInfoLayout.addWidget(&mTaskDescription);

    mTaskImage.setPixmap(QPixmap::fromImage(QImage("res/ih1.jpg")));
    mInfoLayout.addWidget(&mTaskImage);

    mOuterCircleRadiusLabel.setText("Outer cicrle radius: ");
    mOuterCircleRadiusSpinBox.setMinimum(MINIMUM_RADIUS);
    mOuterCircleRadiusSpinBox.setMaximum(MAXIMUM_RADIUS);
    mOuterCircleRadiusSpinBox.setValue(mOuterCircleRadius);
    connect(&mOuterCircleRadiusSpinBox,
            static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this,[this](int value) { mOuterCircleRadius = value; });
    mParametersLayout.addWidget(&mOuterCircleRadiusLabel, 0, 0);
    mParametersLayout.addWidget(&mOuterCircleRadiusSpinBox, 0, 1);

    mInnerCircleRadiusLabel.setText("Inner circle radius: ");
    mInnerCircleRadiusSpinBox.setMinimum(MINIMUM_RADIUS);
    mInnerCircleRadiusSpinBox.setMaximum(MAXIMUM_RADIUS);
    mInnerCircleRadiusSpinBox.setValue(mInnerCircleRadius);
    connect(&mInnerCircleRadiusSpinBox,
            static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this, [this](int value) { mInnerCircleRadius = value; });
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
    mInfoLayout.setAlignment(Qt::AlignTop | Qt::AlignHCenter);

    mMainLayout.addWidget(&mControlWidget);

    mImageFrame.setFixedSize(IMAGE_SIZE);
    mImageFrame.setFrameStyle(QFrame::Box);
    mImageFrame.setPixmap(QPixmap::fromImage(Tools::getPlaneImage(IMAGE_SIZE)));
    mMainLayout.addWidget(&mImageFrame);

    mMainLayout.setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
}

IH1Widget::~IH1Widget()
{

}

void IH1Widget::startButtonPressed()
{
    if (mProcessorThread != Q_NULLPTR)
    {
        mProcessorThread->exit();
        mProcessorThread = Q_NULLPTR;
    }

    mProcessorThread = new QThread();

    if (mProcessor != Q_NULLPTR)
    {
        delete mProcessor;
        mProcessor = Q_NULLPTR;
    }

    mProcessor = new HypocycloidProcessor(mOuterCircleRadius,
                                          mInnerCircleRadius,
                                          mFps, IMAGE_SIZE);
    mProcessor->moveToThread(mProcessorThread);

    connect(mProcessor, &HypocycloidProcessor::imageReady,
            this, &IH1Widget::updateImage);
    connect(mProcessorThread, &QThread::started,
            this, [this]() { mStartButton.setEnabled(false); });
    connect(mProcessor, &HypocycloidProcessor::finished,
            this, [this]() { mStartButton.setEnabled(true); });
    connect(mProcessorThread, &QThread::started,
            mProcessor, &HypocycloidProcessor::process);

    mProcessorThread->start();
}

void IH1Widget::updateImage(QImage image)
{
    mImageFrame.setPixmap(QPixmap::fromImage(image));
}

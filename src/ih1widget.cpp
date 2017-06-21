#include <QThread>
#include <QWidget>

#include "hypocycloidprocessor.hpp"
#include "ih1widget.hpp"
#include "tools.hpp"

IH1Widget::IH1Widget(QWidget* parent)
    : QWidget(parent),
      mOuterCircleRadius(DEFAULT_RADIUS),
      mInnerCircleRadius(DEFAULT_RADIUS / 4),
      mProcessor(Q_NULLPTR),
      mProcessorThread(Q_NULLPTR),
      mMainLayout(this),
      mControlWidget(this),
      mInfoLayout(&mControlWidget)
{
    mTaskDescription.setText("Task:\n"
                             "  Shape:\thypocycloid;\n"
                             "  Object:\tcircle;\n"
                             "  Fill:\t~50%;\n"
                             "  Outine:\tset color;");
    mInfoLayout.addWidget(&mTaskDescription);

    mTaskImage.setPixmap(QPixmap::fromImage(QImage("res/ih1.jpg")));
    mInfoLayout.addWidget(&mTaskImage);

    mOuterCircleRadiusLabel.setText("Outer cicrle radius: ");
    mOuterCircleRadiusSpinBox.setMinimum(MINIMUM_RADIUS);
    mOuterCircleRadiusSpinBox.setMaximum(MAXIMUM_RADIUS);
    mOuterCircleRadiusSpinBox.setValue(DEFAULT_RADIUS);
    connect(&mOuterCircleRadiusSpinBox,
            static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this,[this](int value) { mOuterCircleRadius = value; });
    mParametersLayout.addWidget(&mOuterCircleRadiusLabel, 0, 0);
    mParametersLayout.addWidget(&mOuterCircleRadiusSpinBox, 0, 1);

    mInnerCircleRadiusLabel.setText("Inner circle radius: ");
    mInnerCircleRadiusSpinBox.setMinimum(MINIMUM_RADIUS);
    mInnerCircleRadiusSpinBox.setMaximum(MAXIMUM_RADIUS);
    mInnerCircleRadiusSpinBox.setValue(DEFAULT_RADIUS / 4);
    connect(&mInnerCircleRadiusSpinBox,
            static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this, [this](int value) { mInnerCircleRadius = value; });
    mParametersLayout.addWidget(&mInnerCircleRadiusLabel, 1, 0);
    mParametersLayout.addWidget(&mInnerCircleRadiusSpinBox, 1, 1);

    mStartButtonLabel.setText("Click to animate:");
    mParametersLayout.addWidget(&mStartButtonLabel, 2, 0);
    mStartButton.setText("Start");
    connect(&mStartButton, &QPushButton::clicked,
            this, &IH1Widget::startButtonPressed);
    mParametersLayout.addWidget(&mStartButton, 2, 1);

    mInfoLayout.addLayout(&mParametersLayout);
    mInfoLayout.setAlignment(Qt::AlignTop | Qt::AlignHCenter);

    mMainLayout.addWidget(&mControlWidget);

    mImageFrame.setFixedSize(IMAGE_SIZE);
    mImageFrame.setFrameStyle(QFrame::Box);
    mImageFrame.setPixmap(QPixmap::fromImage(Tools::getPlaneImage(IMAGE_SIZE)));
    mMainLayout.addWidget(&mImageFrame);
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

    mProcessor = new HypocycloidProcessor(IMAGE_SIZE, mOuterCircleRadius,
                                          mInnerCircleRadius);
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

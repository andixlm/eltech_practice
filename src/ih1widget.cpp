#include <QThread>
#include <QWidget>

#include "hypocycloidprocessor.hpp"
#include "ih1widget.hpp"
#include "tools.hpp"

IH1Widget::IH1Widget(QWidget* parent)
    : QWidget(parent),
      mOuterCircleRadius(DEFAULT_RADIUS),
      mInnerCircleRadius(DEFAULT_RADIUS / 4),
      mMainLayout(this),
      mParametersWidget(this),
      mParametersLayout(&mParametersWidget)
{
    mTaskDescription.setText("Task:\n"
                             "  Shape:\thypocycloid;\n"
                             "  Object:\tcircle;\n"
                             "  Fill:\t~50%;\n"
                             "  Outine:\tset color;");
    mParametersLayout.addWidget(&mTaskDescription, 0, 0);

    mOuterCircleRadiusLabel.setText("Outer cicrle radius: ");
    mOuterCircleRadiusSpinBox.setMinimum(MINIMUM_RADIUS);
    mOuterCircleRadiusSpinBox.setMaximum(MAXIMUM_RADIUS);
    mOuterCircleRadiusSpinBox.setValue(DEFAULT_RADIUS);
    connect(&mOuterCircleRadiusSpinBox,
            static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this,[this](int value) { mOuterCircleRadius = value; });
    mParametersLayout.addWidget(&mOuterCircleRadiusLabel, 1, 0);
    mParametersLayout.addWidget(&mOuterCircleRadiusSpinBox, 1, 1);

    mInnerCircleRadiusLabel.setText("Inner circle radius: ");
    mInnerCircleRadiusSpinBox.setMinimum(MINIMUM_RADIUS);
    mInnerCircleRadiusSpinBox.setMaximum(MAXIMUM_RADIUS);
    mInnerCircleRadiusSpinBox.setValue(DEFAULT_RADIUS / 4);
    connect(&mInnerCircleRadiusSpinBox,
            static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this, [this](int value) { mInnerCircleRadius = value; });
    mParametersLayout.addWidget(&mInnerCircleRadiusLabel, 2, 0);
    mParametersLayout.addWidget(&mInnerCircleRadiusSpinBox, 2, 1);

    mStartButtonLabel.setText("Click to animate:");
    mParametersLayout.addWidget(&mStartButtonLabel, 3, 0);
    mStartButton.setText("Start");
    connect(&mStartButton, &QPushButton::clicked,
            this, &IH1Widget::startButtonPressed);
    mParametersLayout.addWidget(&mStartButton, 3, 1);

    mParametersLayout.setAlignment(Qt::AlignTop | Qt::AlignHCenter);
    mMainLayout.addWidget(&mParametersWidget);

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

}

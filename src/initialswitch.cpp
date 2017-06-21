#include <QVBoxLayout>

#include "initialswitch.hpp"

InitialSwitch::InitialSwitch(QWidget* parent)
    : QWidget(parent),
      switchLayout(this),
      mRadioBox(this),
      mRadioBoxLayout(&mRadioBox)
{
    for (int cnt = 1; cnt <= individualHomeworkCount; ++cnt)
    {
        QRadioButton* rb = new QRadioButton("Individual Homework " +
                                            QString::number(cnt), &mRadioBox);

        mRadioButtons.append(rb);
        mRadioBoxLayout.addWidget(rb);
    }

    mRadioBox.setLayout(&mRadioBoxLayout);

    mStartButton.setText("Start");
    connect(&mStartButton, &QPushButton::clicked,
            this, &InitialSwitch::startButtonPressed);

    switchLayout.addWidget(&mRadioBox);
    switchLayout.addWidget(&mStartButton);

    switchLayout.setAlignment(&mRadioBox, Qt::AlignCenter);
    switchLayout.setAlignment(&mStartButton, Qt::AlignCenter);
}

InitialSwitch::~InitialSwitch()
{
    for (QList<QRadioButton*>::const_iterator
            iRadioButton = mRadioButtons.cbegin(), end = mRadioButtons.cend();
         iRadioButton != end; ++iRadioButton)
    {
        delete *iRadioButton;
    }
}

void InitialSwitch::startButtonPressed()
{

}

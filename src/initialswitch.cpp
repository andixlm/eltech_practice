#include <QVBoxLayout>

#include "initialswitch.hpp"

InitialSwitch::InitialSwitch(QWidget* parent)
    : QWidget(parent),
      switchLayout(this)
{
    for (int cnt = 1; cnt <= individualHomeworkCount; ++cnt)
    {
        QRadioButton* rb = new QRadioButton("Individual Homework " +
                                            QString::number(cnt));

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
    for (QVector<QRadioButton*>::const_iterator
            iRadioButton = mRadioButtons.cbegin(), end = mRadioButtons.cend();
         iRadioButton != end; ++iRadioButton)
    {
        delete *iRadioButton;
    }
}

void InitialSwitch::startButtonPressed()
{

}

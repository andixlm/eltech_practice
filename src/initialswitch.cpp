#include <QVBoxLayout>

#include "initialswitch.hpp"

InitialSwitch::InitialSwitch(QWidget* parent)
    : QWidget(parent),
      mainLayout(this),
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

    mainLayout.addWidget(&mRadioBox);
    mainLayout.addWidget(&mStartButton);

    mainLayout.setAlignment(&mRadioBox, Qt::AlignCenter);
    mainLayout.setAlignment(&mStartButton, Qt::AlignCenter);
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

int InitialSwitch::getCheckedRadioButtonId()
{
    int id = 1;

    QList<QRadioButton*> rbs = mRadioBox.findChildren<QRadioButton*>();

    for (QList<QRadioButton*>::const_iterator
            iRadioButton = rbs.cbegin(), end = rbs.cend();
         iRadioButton != end; ++iRadioButton)
    {
        if ((*iRadioButton)->isChecked())
        {
            return id;
        }

        ++id;
    }

    return -1;
}

void InitialSwitch::startButtonPressed()
{

}

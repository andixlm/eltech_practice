#include <QList>
#include <QRadioButton>
#include <QString>
#include <QWidget>

#include "initialswitch.hpp"
#include "ih1widget.hpp"

InitialSwitch::InitialSwitch(QWidget* parent)
    : QWidget(parent),
      mainLayout(this),
      mRadioBox(this),
      mRadioBoxLayout(&mRadioBox),
      mWorkWidget(Q_NULLPTR)
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
    int workId = getCheckedRadioButtonId();

    if (workId < 1)
    {
        return;
    }

    if (mWorkWidget != Q_NULLPTR)
    {
        delete mWorkWidget;
        mWorkWidget = Q_NULLPTR;
    }

    switch (workId)
    {
        case 1:
            mWorkWidget = new IH1Widget();
            break;

        default:
            return;
    }

    mWorkWidget->setWindowTitle("Individual Homework " +
                                QString::number(workId));
    mWorkWidget->show();
}

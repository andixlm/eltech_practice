#ifndef INITIALSWITCH_H
#define INITIALSWITCH_H

#include <QGroupBox>
#include <QList>
#include <QPushButton>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QWidget>

class InitialSwitch : public QWidget
{
    Q_OBJECT

public:
    InitialSwitch(QWidget* parent = Q_NULLPTR);
    ~InitialSwitch();

private:
    int individualHomeworkCount = 1;

    QVBoxLayout switchLayout;

    QGroupBox mRadioBox;
    QVBoxLayout mRadioBoxLayout;
    QList<QRadioButton*> mRadioButtons;

    QPushButton mStartButton;

private slots:
    void startButtonPressed();
};

#endif // INITIALSWITCH_HPP

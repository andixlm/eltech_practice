#ifndef INITIALSWITCH_H
#define INITIALSWITCH_H

#include <QGroupBox>
#include <QPushButton>
#include <QRadioButton>
#include <QVBoxLayout>
#include <QVector>
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
    QVector<QRadioButton*> mRadioButtons;

    QPushButton mStartButton;

private slots:
    void startButtonPressed();
};

#endif // INITIALSWITCH_HPP

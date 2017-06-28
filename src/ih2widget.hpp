#ifndef IH2WIDGET_HPP
#define IH2WIDGET_HPP

#include <QGridLayout>
#include <QLabel>
#include <QList>
#include <QPushButton>
#include <QScrollArea>
#include <QSpinBox>
#include <QWidget>

#include "ihwidget.hpp"
#include "kochfractal.hpp"
#include "kochfractalprocessor.hpp"

class IH2Widget : public IHWidget
{
public:
    explicit IH2Widget(QWidget* parent = Q_NULLPTR);

private:
    static const int IMAGE_WIDTH = 256;
    static const int IMAGE_HEIGHT = 256;

    static const int IMAGE_MARGIN = 10;
    static const int SCROLL_BAR_MARGIN = 20;

    static const int MINIMUM_ITERATIONS = 1;
    static const int DEFAULT_ITERATIONS = MINIMUM_ITERATIONS;
    static const int MAXIMUM_ITERATIONS = 6;

    QGridLayout mParametersLayout;

    QLabel mTaskDescription;
    QLabel mTaskImage;

    KochFractal* mKochFractal;
    KochFractalProcessor* mProcessor;
    QThread* mProcessorThread;

    int mIterations;
    QLabel mIterationsLabel;
    QSpinBox mIterationsSpinBox;

    QLabel mBuildButtonLabel;
    QPushButton mBuildButton;

    QVBoxLayout mImagesLayout;

    QScrollArea mTreeImageArea;
    QLabel mTreeImage;

    QScrollArea mSnowflakeImagesArea;
    QWidget mSnowflakeImagesWidget;
    QHBoxLayout mSnowFlakeImagesLayout;
    QList<QLabel*> mSnowflakeImages;
};

#endif // IH2WIDGET_HPP

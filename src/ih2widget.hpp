#ifndef IH2WIDGET_HPP
#define IH2WIDGET_HPP

#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
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
    static const int IMAGE_WIDTH = 512;
    static const int IMAGE_HEIGHT = 512;

    static const int MINIMUM_ITERATIONS = 1;
    static const int DEFAULT_ITERATIONS = MINIMUM_ITERATIONS;
    static const int MAXIMUM_ITERATIONS = 7;

    static const int MINIMUM_FRACTALS = 1;
    static const int DEFAULT_FRACTALS = 2;
    static const int MAXIMUM_FRACTALS = 6;

    static const int MINIMUM_TREE_NODE = 0;
    static const int DEFAULT_TREE_NODE = MINIMUM_TREE_NODE;
    static const int MAXIMUM_TREE_NODE = MINIMUM_TREE_NODE;

    QGridLayout mParametersLayout;

    QLabel mTaskDescription;
    QLabel mTaskImage;

    KochFractal mKochFractal;
    KochFractalProcessor* mProcessor;
    QThread* mProcessorThread;

    int mIterations;
    QLabel mIterationsLabel;
    QSpinBox mIterationsSpinBox;

    int mFractals;
    QLabel mFractalsLabel;
    QSpinBox mFractalsSpinBox;

    int mTreeNode;
    QLabel mTreeNodeLabel;
    QSpinBox mTreeNodeSpinBox;

    QLabel mBuildButtonLabel;
    QPushButton mBuildButton;
};

#endif // IH2WIDGET_HPP

#ifndef IH2WIDGET_HPP
#define IH2WIDGET_HPP

#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>
#include <QWidget>

#include "ihwidget.hpp"

class IH2Widget : public IHWidget
{
public:
    explicit IH2Widget(QWidget* parent = Q_NULLPTR);

private:
    const int MINIMUM_ITERATIONS = 1;
    const int DEFAULT_ITERATIONS = 3;
    const int MAXIMUM_ITERATIONS = 7;

    const int MINIMUM_FRACTALS = 1;
    const int DEFAULT_FRACTALS = 2;
    const int MAXIMUM_FRACTALS = 6;

    const int MINIMUM_TREE_NODE = 0;
    const int DEFAULT_TREE_NODE = MINIMUM_TREE_NODE;
    const int MAXIMUM_TREE_NODE = MINIMUM_TREE_NODE;

    QGridLayout mParametersLayout;

    QLabel mTaskDescription;
    QLabel mTaskImage;

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

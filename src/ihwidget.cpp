#include <QWidget>

#include "ihwidget.hpp"

IHWidget::IHWidget(QWidget* parent)
    : QWidget(parent),
      mMainLayout(this),
      mInfoLayout(&mControlWidget)
{
    mMainLayout.setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);
    mInfoLayout.setAlignment(Qt::AlignTop | Qt::AlignHCenter);
}

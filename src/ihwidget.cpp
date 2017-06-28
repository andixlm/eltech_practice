#include <QWidget>

#include "ihwidget.hpp"

IHWidget::IHWidget(QWidget* parent)
    : QWidget(parent),
      mMainLayout(this),
      mInfoLayout(&mInfoWidget)
{
    mInfoLayout.setAlignment(Qt::AlignTop | Qt::AlignHCenter);

    mMainLayout.addWidget(&mInfoWidget);
    mMainLayout.setAlignment(Qt::AlignTop | Qt::AlignHCenter);
}

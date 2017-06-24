#ifndef IHWIDGET_HPP
#define IHWIDGET_HPP

#include <QGridLayout>
#include <QHBoxLayout>
#include <QSize>
#include <QVBoxLayout>
#include <QWidget>

class IHWidget : public QWidget
{
public:
    explicit IHWidget(QWidget* parent = Q_NULLPTR);

protected:
    QHBoxLayout mMainLayout;

    QWidget mInfoWidget;
    QVBoxLayout mInfoLayout;
};

#endif // IHWIDGET_HPP

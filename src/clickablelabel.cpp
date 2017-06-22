#include <QLabel>
#include <QMouseEvent>
#include <QWidget>

#include "clickablelabel.hpp"

ClickableLabel::ClickableLabel(QWidget* parent)
    : QLabel(parent)
{

}

void ClickableLabel::mousePressEvent(QMouseEvent* event)
{
    emit clicked(event);
}

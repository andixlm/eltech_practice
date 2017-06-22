#ifndef CLICKABLELABEL_HPP
#define CLICKABLELABEL_HPP

#include <QLabel>
#include <QMouseEvent>
#include <QWidget>

class ClickableLabel : public QLabel
{
    Q_OBJECT

public:
    ClickableLabel(QWidget* parent = Q_NULLPTR);

protected:
    void mousePressEvent(QMouseEvent* event);

signals:
    void clicked(QMouseEvent* event);
};

#endif // CLICKABLELABEL_HPP

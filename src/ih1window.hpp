#ifndef IH1WINDOW_HPP
#define IH1WINDOW_HPP

#include <QWindow>

class IH1Window : public QWindow
{
    Q_OBJECT

public:
    IH1Window(QWindow* parent = Q_NULLPTR);
    ~IH1Window();
};

#endif // IH1WINDOW_HPP

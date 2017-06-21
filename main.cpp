#include <QApplication>

#include "src/initialswitch.hpp"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    InitialSwitch initialSwitch;
    initialSwitch.show();

    return app.exec();
}

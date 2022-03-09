#include "SunnyTcsGraphicTest.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SunnyTcsGraphicTest w;
    w.show();
    return a.exec();
}

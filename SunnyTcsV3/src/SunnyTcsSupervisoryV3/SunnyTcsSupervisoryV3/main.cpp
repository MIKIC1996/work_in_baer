#include "SunnyTcsSupervisoryV3.h"
#include <QtWidgets/QApplication>

#include "SunnyTcsMapEditor.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   // SunnyTcsSupervisoryV3 w;
   // w.show();

	SunnyTcsMapEditor e;
	e.show();
    return a.exec();
}
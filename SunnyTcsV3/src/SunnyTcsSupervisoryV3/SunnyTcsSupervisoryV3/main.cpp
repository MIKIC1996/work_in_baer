#include "SunnyTcsSupervisoryV3.h"
#include <QtWidgets/QApplication>

#include "SunnyTcsMapEditor.h"
#include "SunnyTcsLocationEditWidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
   // SunnyTcsSupervisoryV3 w;
   // w.show();

	SunnyTcsLocationEditWidget act;
	act.show();

	SunnyTcsMapEditor e;
	e.show();
    return a.exec();
}

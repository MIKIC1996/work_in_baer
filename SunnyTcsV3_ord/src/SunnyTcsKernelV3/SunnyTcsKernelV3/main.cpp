#include <QtCore/QCoreApplication>

#include "SunnyTcsKernelGeneral.h"


class AA {
public:
	int add(int a) {
		return a * 10;
	}

	int add2(int a) {
		return a + 1;
	}

};



int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);

	SunnyTcsThreadSeed_basic<int(int)> seed;
	AA as;
	seed.submit(&AA::add,&as, 10);
	seed.submit(&AA::add2,&as, 10);
	seed.work();
	int* val = (int*)(seed.getResultPtr());
	qDebug() << *val;
	seed.work();
	qDebug() << *val;

    return a.exec();
}

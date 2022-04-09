#include <QtCore/QCoreApplication>
#include "generalArg.h"
#include "threadSeed.h"
#include "uidWorkerTest.h"
#include "craftTest.h"
#include <set>



using namespace basic;


int main(int argc, char *argv[])
{
   /* QCoreApplication a(argc, argv);*/
	/*return a.exec();*/
	{
	
		SunnyTcsAction ac(1, "GP");
		ac.setParams_meta<0>(QString("param0"));
		ac.setParams_meta<1>((qint64)200);
		ac.setParams_meta<2>(QString("param3"));
		ac.setParams_meta<3>(quint8(9));

		ac.setParams_meta<6>(quint8(9));
		qDebug() << ac.toString();
		SunnyTcsAction ac2;
		if (!ac2.fromJson(ac.toJson(), QString())) {
			qDebug() << "err";
		}
		qDebug() << ac2.toString();
	}
	

	getchar();
	return 0;
}

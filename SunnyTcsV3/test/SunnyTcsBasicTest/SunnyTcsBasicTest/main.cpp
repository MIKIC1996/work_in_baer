#include <QtCore/QCoreApplication>
#include "generalArg.h"
#include "threadSeed.h"
#include "uidWorkerTest.h"
#include "craftTest.h"
#include <set>


void add(qreal val) {
	//val += 3.0;
}

int main(int argc, char *argv[])
{
   /* QCoreApplication a(argc, argv);*/
	/*return a.exec();*/
	


	QVector<int> vec1{ 1,2,3 };
	QVector<int> vec2{ 2};
	QVector<int> ret;



	set_intersection(vec1.begin(), vec1.end(), vec2.begin(), vec2.end(), std::insert_iterator<QVector<int>>(ret, ret.begin()));

	for (auto iter : ret) {
		qDebug() << iter;
	}

	getchar();
	return 0;
}

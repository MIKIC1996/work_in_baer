#include <QtCore/QCoreApplication>

#include <SunnyTcsOrderCenter.h>
#include <SunnyTcsThreadCenter.h>
#include <SunnyTcsCoreLogicParser.h>

using namespace core::threadseed;
using namespace core::logic;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

	QString str = "{[<agv>(warn|100,error&5)(abspos>=100,error&5)]&&[<agv>(warn|100,error&5)(abspos>=100,error&5)]}";
	QString err;
	SunnyTcsCoreLogicParser parser;
	std::shared_ptr<I_SunnyTcsCondition> ptr = parser.parseLogicStr(str, err);
	if (!ptr) {
		qDebug() << "error";
	}
	else {
		qDebug() << ptr->toString();
	}
	
	getchar();
    return a.exec();
}

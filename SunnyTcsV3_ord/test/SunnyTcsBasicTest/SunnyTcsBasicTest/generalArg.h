#pragma once

#include <SunnyTcsGeneralArg.hpp>
#include <iostream>
#include <QDebug>
#include <SunnyTcsMessage.h>

using namespace std;
using namespace basic;

void generalArgTest() {
	SunnyTcsMessage msg1;
	msg1.setMsgCounter(1100);
	msg1.setMsgId(1001);
	msg1.setSeedTime(QDateTime::currentMSecsSinceEpoch());
	msg1.setIsBroadcast(true);
	msg1.setIsNeedReply(false);
	msg1.setTargetId(3);
	msg1.setSourceId(2);

	msg1.appendArg(32);
	msg1.appendArg((qint64)32);
	msg1.appendArg(QString("hello"));


	SunnyTcsMessage msg2;
	bool ok = true;
	qDebug() << msg1.toBytes();
	qint32 ct = msg2.parseFromBytes(msg1.toBytes(),ok);
	if (ok) {
		cout << msg2.toString().toStdString() << endl;
	}
	else {
		qDebug() << "error";
		cout << ct << endl;
	}
	
	
	

}
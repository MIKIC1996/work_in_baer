#pragma once


#include <SunnyTcsUIDWorker.h>
#include <QDebug>

using namespace basic;

void UidTest() {
	SunnyTcsUIDWorker::getUIDWorker();
	QList<quint64> ids;
	for (int i = 0; i < 10000; ++i) {
		quint64 id =SunnyTcsUIDWorker::m_instance->nextId();
		if (ids.contains(id)) {
			qDebug() << "error";
			return;
		}
		qDebug() << id;
	}

}
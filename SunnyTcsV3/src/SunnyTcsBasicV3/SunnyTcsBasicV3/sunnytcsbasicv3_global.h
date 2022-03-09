#pragma once

#include <QtCore/qglobal.h>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QVector>
#include <QMap>
#include <QHash>
#include <QList>
#include <memory>
#include <QMutex>
#include <QThread>
#include <QQueue>
#include <QByteArray>
#include <QDateTime>
#include <QDebug>
#include <qmath.h>
#include <functional>
#include <iostream>
#include <string>
#include <mutex>
#include <utility>
#include <QTextCodec>
#include <tuple>
#include <QFile>
#include <queue>
#include <shared_mutex>
#include <set>
#include <QRegExp>

#include "SunnyTcsPromise.hpp"

#ifndef BUILD_STATIC
# if defined(SUNNYTCSBASICV3_LIB)
#  define SUNNYTCSBASICV3_EXPORT Q_DECL_EXPORT
# else
#  define SUNNYTCSBASICV3_EXPORT Q_DECL_IMPORT
# endif
#else
# define SUNNYTCSBASICV3_EXPORT
#endif


//中文支持c风格字符串
static QTextCodec* pcode = QTextCodec::codecForName("GBK");
#define QSTRING_GBK(str) \
		pcode->toUnicode(str)
#define STD_STRING_GBK(str)\
		pcode->toUnicode(str).toStdString()
#define DB_STR_LIST_TMP QList<QString>()



//map





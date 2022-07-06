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
#include <SunnyTcsPromise.hpp>
#include <shared_mutex>


#ifndef BUILD_STATIC
# if defined(SUNNYTCSBASICV3_LIB)
#  define SUNNYTCSBASICV3_EXPORT Q_DECL_EXPORT
# else
#  define SUNNYTCSBASICV3_EXPORT Q_DECL_IMPORT
# endif
#else
# define SUNNYTCSBASICV3_EXPORT
#endif





//map
#define VEHICLE_NAGA_RUBBON 0X01
#define VEHICLE_NAGA_INERTIA 0X02
#define VEHICLE_NAGA_LASER 0X03



//logic
//1.���������Str
#define CONDITION_TAR_AGV "agv"
#define CONDITION_TAR_LINE "line"
#define CONDITION_TAR_POINT "point"
#define CONDITION_TAR_PATH "path"
#define CONDITION_TAR_DEVICE "device"
#define CONDITION_TAR_LOCATION "location"


//2.���������str
#define CONDITION_COMPARE_EQUAL_STR "=="
#define CONDITION_COMPARE_UNEQUAL_STR "!="
#define CONDITION_COMPARE_BIGGER_STR ">"
#define CONDITION_COMPARE_SMALLER_STR "<"
#define CONDITION_COMPARE_BIGGER_OR_EQUAL_STR ">="
#define CONDITION_COMPARE_SMALLER_OR_EQUAL_STR "<="
#define CONDITION_COMPARE_AND_OPERATION_STR "&"
#define CONDITION_COMPARE_OR_OPERATION_STR "|"


//3. �߼���������str
#define CONDITION_LOGICOPE_AND_STR "&"
#define CONDITION_LOGICOPE_OR_STR "|"


//3.ÿ������ռ�ݵ�λ �����64�֣���0��63 �ֲ���
//general
#define	CONDITION_ID 0 //id ȫ������ 
#define CONDITION_ID_STR "id"

#define CONDITION_HAS_AGV 1 //�Ƿ��г�������  path point
#define CONDITION_HAS_AGV_STR "hasagv"

//agv
#define CONDITION_ABSPOS 11
#define CONDITION_ABSPOS_STR "abspos"

#define CONDITION_RX 12
#define CONDITION_RX_STR "rx"

#define CONDITION_RY 13
#define CONDITION_RY_STR "ry"

#define CONDITION_LIFT 14
#define CONDITION_LIFT_STR "lift"

#define CONDITION_ERROR 15
#define CONDITION_ERROR_STR "error"

#define CONDITION_WARNING 16
#define CONDITION_WARNING_STR "warn"

#define CONDITION_IN_PATH 17
#define CONDITION_IN_PATH_STR "inpath"

#define CONDITION_IN_POINT 18
#define CONDITION_IN_POINT_STR "inpoint"

#define CONDITION_AGV_NAMAMODE 19
#define CONDITION_AGV_NAMAMODE_STR "agvnagamode"

//path
#define CONDITION_LIMIT_SPEED 21//·������
#define CONDITION_LIMIT_SPEED_STR "speedlimit"

#define CONDITION_AGV_COUNT 22 //�м�������path����
#define CONDITION_AGV_COUNT_STR "agvcount"

//point
#define CONDITION_POINT_NAGAMODE 31
#define CONDITION_POINT_NAGAMODE_STR "pointnagamode"

//�߱�
#define CONDITION_LINE_VAL 42 //��ʱ
#define CONDITION_LINE_VAL_STR "lineval"

//��Χ�豸




//craft ��ָ����agv
#define CRAFT_NO_DECIDE_AGV 0


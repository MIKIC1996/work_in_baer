#pragma once


#include "sunnytcsgraphicv3_global.h"

#include <QPolygon>
#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMouseEvent>
#include <QDebug>
#include <QHash>
#include <QTextCodec>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QImage>


#include <SunnyTcsBasicV3.h>
#include <SunnyTcsFuncGeneral.hpp>
#include <SunnyTcsVehicleLib.h>

#include <SunnyTcsPromise.hpp>





#ifndef BUILD_STATIC
# if defined(SUNNYTCSGRAPHICV3_LIB)
#  define SUNNYTCSGRAPHICV3_EXPORT Q_DECL_EXPORT
# else
#  define SUNNYTCSGRAPHICV3_EXPORT Q_DECL_IMPORT
# endif
#else
# define SUNNYTCSGRAPHICV3_EXPORT
#endif

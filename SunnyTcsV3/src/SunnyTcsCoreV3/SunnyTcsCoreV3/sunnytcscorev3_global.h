#pragma once

#include <QtCore/qglobal.h>

#include <SunnyTcsBasicV3/SunnyTcsGeneralAlgorithm.hpp>
#include <SunnyTcsBasicV3/SunnyTcsLibGeneral.hpp>
#include <iostream>
#include <SunnyTcsBasicV3/SunnyTcsAction.h>
#include <SunnyTcsBasicV3/SunnyTcsCraft.h>
#include <SunnyTcsBasicV3/SunnyTcsLogicParser.h>
#include <SunnyTcsBasicV3/SunnyTcsVagueCondition.h>
#include <SunnyTcsBasicV3/SunnyTcsMapActualData.hpp>
#include <SunnyTcsBasicV3/SunnyTcsFuncGeneral.hpp>
#include <SunnyTcsAlgorithmV3/SunnyTcsDispatchAlgorithm_basic.h>
#include <SunnyTcsAlgorithmV3/SunnyTcsRouteAlgorithm_basic.h>
#include <SunnyTcsBasicV3/SunnyTcsMessage.h>
#include <mutex>
#include <SunnyTcsPromiseV3/SunnyTcsPromise.hpp>

#ifndef BUILD_STATIC
# if defined(SUNNYTCSCOREV3_LIB)
#  define SUNNYTCSCOREV3_EXPORT Q_DECL_EXPORT
# else
#  define SUNNYTCSCOREV3_EXPORT Q_DECL_IMPORT
# endif
#else
# define SUNNYTCSCOREV3_EXPORT
#endif


//各个主要部分的识别节点号，作为内外消息通讯的节点号

#define NODE_ID_DEFAULT 0x00 //默认id
#define NODE_ID_ORDERCENTER 0x01
#define NODE_ID_DISPATCHER 0x02
#define NODE_ID_ROUTER 0x03
#define NODE_ID_MODEL 0x04



/*
订单中心
*/

//RECV
#define MSG_RECV_ID_CREATE_ORDER 11001
#define MSG_RECV_ID_CANCEL_ORDER 11002


/*
添加一个工艺，消息格式
1.新工艺ID
2.各个子工艺数组

*/
#define MSG_RECV_ID_ADD_CRAFT    11003

/*
删除一个工艺，消息格式
1.工艺ID.
*/
#define MSG_RECV_ID_DELETE_CRAFT 11004


//SEND
#define MSG_SEND_ID_ORDER_CHANGE 12001


#define MSG_SEND_ID_ORDER_FAIL   12002



/*
分配器
*/








/*
模型执行器
*/







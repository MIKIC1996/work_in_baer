#pragma once

#include <exception>

//本文件是对服务之间通讯格式的约定文件


//地图数据采用 json格式 进行服务间传输，其json字段定义如下
// MODEL
#define JSON_MAP_MODEL_ID				"JSON_MAP_MODEL_ID"
#define JSON_MAP_MODEL_NAME				"JSON_MAP_MODEL_NAME"
#define JSON_MAP_MODEL_WIDTH			"JSON_MAP_MODEL_WIDTH"
#define JSON_MAP_MODEL_HEIGHT			"JSON_MAP_MODEL_HEIGHT"
#define JSON_MAP_MODEL_RESOLUTION		"JSON_MAP_MODEL_RESOLUTION"
#define JSON_MAP_MODEL_TIME				"JSON_MAP_MODEL_TIME"
#define JSON_MAP_MODEL_COORSYS			"JSON_MAP_MODEL_COORSYS"
#define JSON_MAP_MODEL_POINTS			"JSON_MAP_MODEL_POINTS"
#define JSON_MAP_MODEL_PATHS			"JSON_MAP_MODEL_PATHS"
#define JSON_MAP_MODEL_LOCATIONS		"JSON_MAP_MODEL_LOCATIONS"
#define JSON_MAP_MODEL_VEHICLES			"JSON_MAP_MODEL_VEHICLES"
#define JSON_MAP_MODEL_AUTO_TRAFFIC		"JSON_MAP_MODEL_AUTO_TRAFFIC"

//VECODE
#define JSON_MAP_MODEL_VECODES					"JSON_MAP_MODEL_VECODES"
#define JSON_MAP_MODEL_VECODES_PARAMS_COUNT		"JSON_MAP_MODEL_VECODES_PARAMS_COUNT"
#define JSON_MAP_MODEL_VECODES_PARAMS_TYPE		"JSON_MAP_MODEL_VECODES_PARAMS_TYPE"
#define JSON_MAP_MODEL_VECODES_SPT_NAGA			"JSON_MAP_MODEL_VECODES_SPT_NAGA"
#define JSON_MAP_MODEL_VECODES_VALUE			"JSON_MAP_MODEL_VECODES_VALUE"

// CS
#define JSON_MAP_CS_ID			"JSON_MAP_CS_ID"
#define JSON_MAP_CS_NAME		"JSON_MAP_CS_NAME"
#define JSON_MAP_CS_SCENE_X		"JSON_MAP_CS_SCENE_X"
#define JSON_MAP_CS_SCENE_Y		"JSON_MAP_CS_SCENE_Y"
#define JSON_MAP_CS_AXIS_X		"JSON_MAP_CS_AXIS_X"
#define JSON_MAP_CS_AXIS_Y		"JSON_MAP_CS_AXIS_Y"

//POINT
#define JSON_MAP_PT_ID			"JSON_MAP_PT_ID"
#define JSON_MAP_PT_NAME		"JSON_MAP_PT_NAME"
#define JSON_MAP_PT_ABS_POS		"JSON_MAP_PT_ABS_POS"
#define JSON_MAP_PT_REALITY_X	"JSON_MAP_PT_REALITY_X"
#define JSON_MAP_PT_REALITY_Y	"JSON_MAP_PT_REALITY_Y"
#define JSON_MAP_PT_SPT_NAGAMODE	"JSON_MAP_PT_SPT_NAGAMODE"


//PATHS
#define JSON_MAP_PATH_ID						"JSON_MAP_PATH_ID"
#define JSON_MAP_PATH_NAME						"JSON_MAP_PATH_NAME"
#define JSON_MAP_PATH_ST_ID						"JSON_MAP_PATH_ST_ID"
#define JSON_MAP_PATH_ED_ID						"JSON_MAP_PATH_ED_ID"
#define JSON_MAP_PATH_CT_ID						"JSON_MAP_PATH_CT_ID"
#define JSON_MAP_PATH_SPT_POSI_DIRECTION		"JSON_MAP_PATH_SPT_POSI_DIRECTION"//支持前向
#define JSON_MAP_PATH_SPT_NEGA_DIRECTION		"JSON_MAP_PATH_SPT_NEGA_DIRECTION" //支持后向
#define JSON_MAP_PATH_POSI_SPD					"JSON_MAP_PATH_POSI_SPD"
#define JSON_MAP_PATH_NEGA_SPD					"JSON_MAP_PATH_NEGA_SPD"
#define JSON_MAP_PATH_IS_SCAN_ACTIVED			"JSON_MAP_IS_SCAN_ACTIVED"
#define JSON_MAP_PATH_POSI_SCAN					"JSON_MAP_POSI_SCAN"
#define JSON_MAP_PATH_NEGA_SCAN					"JSON_MAP_NEGA_SCAN"


//vehicle
#define JSON_MAP_VE_ID				"JSON_MAP_VE_ID"
#define JSON_MAP_VE_NAME			"JSON_MAP_VE_NAME"
#define JSON_MAP_VE_CODE			"JSON_MAP_VE_CODE"
#define JSON_MAP_VE_RADAR_RADIUS	"JSON_MAP_VE_RADAR_RADIUS"
#define JSON_MAP_VE_IP				"JSON_MAP_VE_IP"
#define JSON_MAP_VE_PORT			"JSON_MAP_VE_PORT"
#define JSON_MAP_VE_GROUP_ID		"JSON_MAP_VE_GROUP_ID"
#define JSON_MAP_VE_SCENE_X			"JSON_MAP_VE_SCENE_X"
#define JSON_MAP_VE_SCENE_Y			"JSON_MAP_VE_SCENE_Y"


//location
#define JSON_MAP_LOC_ID				"JSON_MAP_LOC_ID"
#define JSON_MAP_LOC_NAME			"JSON_MAP_LOC_NAME"
#define JSON_MAP_LOC_LINK_PT		"JSON_MAP_LOC_LINK_PT"
#define JSON_MAP_LOC_PARAM_TYPES	"JSON_MAP_LOC_PARAM_TYPES"
#define JSON_MAP_LOC_ACTIONS		"JSON_MAP_LOC_ACTIONS"//action
#define JSON_MAP_LOC_SCENE_X		"JSON_MAP_LOC_SCENE_X"
#define JSON_MAP_LOC_SCENE_Y		"JSON_MAP_LOC_SCENE_Y"


//sunnytcsarg
#define JSON_ARG_TYPE				"JSON_ARG_TYPE"
#define JSON_ARG_SIZE				"JSON_ARG_SIZE"
#define JSON_ARG_PARAM				"JSON_ARG_PARAM"

//action 指令
#define JSON_ACTION_COMMAND_CODE	"JSON_ACTION_COMMAND_CODE"
#define JSON_ACTION_PARAMS			"JSON_ACTION_PARAMS"








//tag
#define JSON_OBJECT_TAG_TYPE "mapObjectTag"
#define JSON_OBJECT_TAG_ID "mapObjectTag"

//coordinate<int32>
#define JSON_COOR_INT32_X "coorX_int32"
#define JSON_COOR_INT32_Y "coorY_int32"
#define JSON_COOR_INT32_Z "coorZ_int32"
#define JSON_COOR_INT32_DIM "coorDim_int32"

//range<coordinate_int32>
#define JSON_RANGE_COOR_INT32_START	"rangeStart"
#define JSON_RANGE_COOR_INT32_END	"rangeEnd"
#define JSON_RANGE_COOR_INT32_CTRL "rangeCtrl"
#define JSON_RANGE_COOR_INT32_TAG	 "rangeTag"
#define JSON_RANGE_COOR_INT32_ISARCH "rangeIsArch"
#define JSON_RANGE_COOR_INT32_START_CONTAINED "rangeStartContained"
#define JSON_RANGE_COOR_INT32_END_CONTAINED "rangeEndContained"





//数据中心配置文件Json格式定义
#define JSON_DB_TYPE		"JSON_DB_TYPE"
#define JSON_DB_IP			"JSON_DB_IP"
#define JSON_DB_PORT		"JSON_DB_PORT"
#define JSON_DB_USERNAME	"JSON_DB_USERNAME"
#define JSON_DB_PSW			"JSON_DB_PSW"
#define JSON_DB_NAME		"JSON_DB_NAME"




//使用中文错误信息宏
#define USE_CHINESE_ERR_INFO 

#ifdef USE_CHINESE_ERR_INFO
static constexpr bool useChinese = true;
#else
static constexpr bool useChinese = false;
#endif // USE_CHINESE_ERR_INFO


//关于系统错误的相关定义，错误码 统一使用范围 10000 到 20000 范围内数字，要求所有错误码都由 相关元函数 提供详细的信息,默认值0表示没有错误
//错误元函数 规范如下


//错误元函数标准模板
template<unsigned int>
struct SunnyTcsErrorInfo {
	typedef unsigned int value_type;
	static constexpr value_type value = 0;
	static constexpr char* err_info = "unknown error";
	static constexpr char* err_info_cn = "未知错误";
};



//正确无误
#define ERROR_NO_ERROR 0 
template<>
struct SunnyTcsErrorInfo<ERROR_NO_ERROR>
{
	typedef unsigned int value_type;
	static constexpr value_type value = ERROR_NO_ERROR;
	static constexpr char* err_info = "no error";
	static constexpr char* err_info_cn = "无错误";
};


//基础库相关错误信息，范围 12000 到 14000
#define ERROR_BASIC_ARG_FROMBYTE_ERROR 13000
template<>
struct SunnyTcsErrorInfo<ERROR_BASIC_ARG_FROMBYTE_ERROR>
{
	typedef unsigned int value_type;
	static constexpr value_type value = ERROR_BASIC_ARG_FROMBYTE_ERROR;
	static constexpr char* err_info = "general arg fromBytes error";
	static constexpr char* err_info_cn = "通用参数从字节数组中分析错误";
};


#define ERROR_BASIC_ARG_TOBYTE_ERROR 13001
template<>
struct SunnyTcsErrorInfo<ERROR_BASIC_ARG_TOBYTE_ERROR>
{
	typedef unsigned int value_type;
	static constexpr value_type value = ERROR_BASIC_ARG_TOBYTE_ERROR;
	static constexpr char* err_info = "general arg toBytes error";
	static constexpr char* err_info_cn = "通用参数转字节数组错误";
};


#define ERROR_BASIC_REPEAT_INDEX_IN_CRAFT 13002
template<>
struct SunnyTcsErrorInfo<ERROR_BASIC_REPEAT_INDEX_IN_CRAFT>
{
	typedef unsigned int value_type;
	static constexpr value_type value = ERROR_BASIC_REPEAT_INDEX_IN_CRAFT;
	static constexpr char* err_info = "repeat error when creating craft";
	static constexpr char* err_info_cn = "在创建工艺的时候使用了重复索引";
};



#define ERROR_BASIC_CONFUSED_RELATIONSHIP 13003
template<>
struct SunnyTcsErrorInfo<ERROR_BASIC_CONFUSED_RELATIONSHIP>
{
	typedef unsigned int value_type;
	static constexpr value_type value = ERROR_BASIC_CONFUSED_RELATIONSHIP;
	static constexpr char* err_info = "confused relationship between son crafts";
	static constexpr char* err_info_cn = "子工艺中产生了混乱的关系";
};



#define ERROR_BASIC_UNEXISTED_CRAFT_INDEX 13004
template<>
struct SunnyTcsErrorInfo<ERROR_BASIC_UNEXISTED_CRAFT_INDEX>
{
	typedef unsigned int value_type;
	static constexpr value_type value = ERROR_BASIC_UNEXISTED_CRAFT_INDEX;
	static constexpr char* err_info = "unexisted son craft index";
	static constexpr char* err_info_cn = "工艺中不存在的子工艺索引";
};


#define ERROR_BASIC_UNEXISTED_ORDER_INDEX 13005
template<>
struct SunnyTcsErrorInfo<ERROR_BASIC_UNEXISTED_ORDER_INDEX>
{
	typedef unsigned int value_type;
	static constexpr value_type value = ERROR_BASIC_UNEXISTED_ORDER_INDEX;
	static constexpr char* err_info = "unexisted son order index";
	static constexpr char* err_info_cn = "订单中不存在的子订单索引";
};



//数据库相关错误信息，范围10000 到 12000
#define ERROR_DB_PROXY_UNCONNECTED 11000 //数据库代理未连接到数据库
template<>
struct SunnyTcsErrorInfo<ERROR_DB_PROXY_UNCONNECTED>
{
	typedef unsigned int value_type;
	static constexpr value_type value = ERROR_DB_PROXY_UNCONNECTED;
	static constexpr char* err_info = "DB server unlinked by DB proxy";
	static constexpr char* err_info_cn = "数据库代理未连接到数据库";
};



#define ERROR_DB_QUERY_FAILED 11001 //数据库操作返回失败
template<>
struct SunnyTcsErrorInfo<ERROR_DB_QUERY_FAILED>
{
	typedef unsigned int value_type;
	static constexpr value_type value = ERROR_DB_QUERY_FAILED;
	static constexpr char* err_info = "DB operation failed";
	static constexpr char* err_info_cn = "数据库操作返回失败";
};



#define ERROR_DB_JSON_ERROR_TYPE 11002 //数据库配置文件中错误的数据库类型
template<>
struct SunnyTcsErrorInfo<ERROR_DB_JSON_ERROR_TYPE>
{
	typedef unsigned int value_type;
	static constexpr value_type value = ERROR_DB_JSON_ERROR_TYPE;
	static constexpr char* err_info = "error DB type in DB config json";
	static constexpr char* err_info_cn = "数据库配置JSON中错误的数据库类型";
};





//图形库错误定义 范围14000 - 16000
#define ERROR_GRAPHICS_POINT_OUT_SCENE 15001 // 点的绘制坐标超过了场景尺寸
template<>
struct SunnyTcsErrorInfo<ERROR_GRAPHICS_POINT_OUT_SCENE>
{
	typedef unsigned int value_type;
	static constexpr value_type value = ERROR_GRAPHICS_POINT_OUT_SCENE;
	static constexpr char* err_info = "Point coordinate is out of scene when painting.";
	static constexpr char* err_info_cn = "点的绘制坐标超过了场景尺寸";
};


#define ERROR_GRAPHICS_PATH_OUT_SCENE 15002 // 路径的点坐标超过了场景尺寸
template<>
struct SunnyTcsErrorInfo<ERROR_GRAPHICS_PATH_OUT_SCENE>
{
	typedef unsigned int value_type;
	static constexpr value_type value = ERROR_GRAPHICS_PATH_OUT_SCENE;
	static constexpr char* err_info = "Point of path is out of scene when painting.";
	static constexpr char* err_info_cn = "路径的点坐标超过了场景尺寸";
};


#define ERROR_GRAPHICS_VEHICLE_OUT_SCENE 15003 // agv坐标超过了场景尺寸
template<>
struct SunnyTcsErrorInfo<ERROR_GRAPHICS_VEHICLE_OUT_SCENE>
{
	typedef unsigned int value_type;
	static constexpr value_type value = ERROR_GRAPHICS_VEHICLE_OUT_SCENE;
	static constexpr char* err_info = "Agv is out of scene when painting.";
	static constexpr char* err_info_cn = "agv坐标超过了场景尺寸";
};


#define ERROR_GRAPHICS_LOCATION_NO_LINK_POINT 15004 //工位没有可以依附的点
template<>
struct SunnyTcsErrorInfo<ERROR_GRAPHICS_LOCATION_NO_LINK_POINT>
{
	typedef unsigned int value_type;
	static constexpr value_type value = ERROR_GRAPHICS_LOCATION_NO_LINK_POINT;
	static constexpr char* err_info = "No point to link for location.";
	static constexpr char* err_info_cn = "当前位置没有工位可以依附的点";
};


#define ERROR_GRAPHICS_FROM_JSON_APPLY_ID_ERR 15011 //元素申请ID时错误
template<>
struct SunnyTcsErrorInfo<ERROR_GRAPHICS_FROM_JSON_APPLY_ID_ERR>
{
	typedef unsigned int value_type;
	static constexpr value_type value = ERROR_GRAPHICS_FROM_JSON_APPLY_ID_ERR;
	static constexpr char* err_info = "error in applying new id.";
	static constexpr char* err_info_cn = "元素申请ID时错误";
};


#define ERROR_GRAPHICS_COORSYS_FROM_JSON_NO_TAG 15021 // 坐标系JSON解析缺少必要的标签项
template<>
struct SunnyTcsErrorInfo<ERROR_GRAPHICS_COORSYS_FROM_JSON_NO_TAG>
{
	typedef unsigned int value_type;
	static constexpr value_type value = ERROR_GRAPHICS_COORSYS_FROM_JSON_NO_TAG;
	static constexpr char* err_info = "no tag in coordinate system json.";
	static constexpr char* err_info_cn = "坐标系JSON解析缺少必要的标签项";
};


#define ERROR_GRAPHICS_COORSYS_FROM_JSON_AXIS_ERR 15022 // 坐标系的xy轴错误或者冲突
template<>
struct SunnyTcsErrorInfo<ERROR_GRAPHICS_COORSYS_FROM_JSON_AXIS_ERR>
{
	typedef unsigned int value_type;
	static constexpr value_type value = ERROR_GRAPHICS_COORSYS_FROM_JSON_AXIS_ERR;
	static constexpr char* err_info = "axis of coordinate system error";
	static constexpr char* err_info_cn = "坐标系的xy轴错误或者冲突";
};



#define ERROR_GRAPHICS_POINT_FROM_JSON_NO_TAG 15041 //点JSON解析缺少必要的标签项
template<>
struct SunnyTcsErrorInfo<ERROR_GRAPHICS_POINT_FROM_JSON_NO_TAG>
{
	typedef unsigned int value_type;
	static constexpr value_type value = ERROR_GRAPHICS_POINT_FROM_JSON_NO_TAG;
	static constexpr char* err_info = "no tag in point json.";
	static constexpr char* err_info_cn = "点JSON解析缺少必要的标签项";
};








#define ERROR_GRAPHICS_PATH_FROM_JSON_NO_TAG 15061 //路径JSON解析缺少必要的标签项
template<>
struct SunnyTcsErrorInfo<ERROR_GRAPHICS_PATH_FROM_JSON_NO_TAG>
{
	typedef unsigned int value_type;
	static constexpr value_type value = ERROR_GRAPHICS_PATH_FROM_JSON_NO_TAG;
	static constexpr char* err_info = "no tag in path json.";
	static constexpr char* err_info_cn = "路径JSON解析缺少必要的标签项";
};



#define ERROR_GRAPHICS_PATH_FROM_JSON_START_POINT_NO_ID 15062 //路径所要求的起点ID在点集中不存在
template<>
struct SunnyTcsErrorInfo<ERROR_GRAPHICS_PATH_FROM_JSON_START_POINT_NO_ID>
{
	typedef unsigned int value_type;
	static constexpr value_type value = ERROR_GRAPHICS_PATH_FROM_JSON_START_POINT_NO_ID;
	static constexpr char* err_info = "path start id is unexisted in points hashmap.";
	static constexpr char* err_info_cn = "路径所要求的起点ID在点集中不存在";
};



#define ERROR_GRAPHICS_PATH_FROM_JSON_END_POINT_NO_ID 15063 //路径所要求的终点ID在点集中不存在
template<>
struct SunnyTcsErrorInfo<ERROR_GRAPHICS_PATH_FROM_JSON_END_POINT_NO_ID>
{
	typedef unsigned int value_type;
	static constexpr value_type value = ERROR_GRAPHICS_PATH_FROM_JSON_END_POINT_NO_ID;
	static constexpr char* err_info = "path end id is unexisted in points hashmap.";
	static constexpr char* err_info_cn = "路径所要求的终点ID在点集中不存在";
};


#define ERROR_GRAPHICS_PATH_FROM_JSON_CTRL_POINT_NO_ID 15064 //路径所要求的控制点ID在点集中不存在
template<>
struct SunnyTcsErrorInfo<ERROR_GRAPHICS_PATH_FROM_JSON_CTRL_POINT_NO_ID>
{
	typedef unsigned int value_type;
	static constexpr value_type value = ERROR_GRAPHICS_PATH_FROM_JSON_CTRL_POINT_NO_ID;
	static constexpr char* err_info = "path ctrl id is unexisted in points hashmap.";
	static constexpr char* err_info_cn = "路径所要求的控制点ID在点集中不存在";
};




#define ERROR_GRAPHICS_LOCATION_FROM_JSON_NO_TAG 15081 //工位JSON解析缺少必要的标签项
template<>
struct SunnyTcsErrorInfo<ERROR_GRAPHICS_LOCATION_FROM_JSON_NO_TAG>
{
	typedef unsigned int value_type;
	static constexpr value_type value = ERROR_GRAPHICS_LOCATION_FROM_JSON_NO_TAG;
	static constexpr char* err_info = "no tag in location json.";
	static constexpr char* err_info_cn = "工位JSON解析缺少必要的标签项";
};



#define ERROR_GRAPHICS_LOCATION_FROM_JSON_LINKPT_ERR 15082 //工位JSON解析缺少必要的标签项
template<>
struct SunnyTcsErrorInfo<ERROR_GRAPHICS_LOCATION_FROM_JSON_LINKPT_ERR>
{
	typedef unsigned int value_type;
	static constexpr value_type value = ERROR_GRAPHICS_LOCATION_FROM_JSON_LINKPT_ERR;
	static constexpr char* err_info = "no link point in location json.";
	static constexpr char* err_info_cn = "工位JSON解析中，不存在的连接点";
};



#define ERROR_GRAPHICS_VEHICLE_FROM_JSON_NO_TAG 15101 //车辆JSON解析缺少必要的标签项
template<>
struct SunnyTcsErrorInfo<ERROR_GRAPHICS_VEHICLE_FROM_JSON_NO_TAG>
{
	typedef unsigned int value_type;
	static constexpr value_type value = ERROR_GRAPHICS_VEHICLE_FROM_JSON_NO_TAG;
	static constexpr char* err_info = "no tag in vehicle json.";
	static constexpr char* err_info_cn = "车辆JSON解析缺少必要的标签项";
};


#define ERROR_GRAPHICS_VEHICLE_FROM_JSON_NO_CODE 15102 //车辆JSON解析缺少必要的标签项
template<>
struct SunnyTcsErrorInfo<ERROR_GRAPHICS_VEHICLE_FROM_JSON_NO_CODE>
{
	typedef unsigned int value_type;
	static constexpr value_type value = ERROR_GRAPHICS_VEHICLE_FROM_JSON_NO_CODE;
	static constexpr char* err_info = "no code in vehicle json.";
	static constexpr char* err_info_cn = "车辆JSON解析记录的车辆码ID不存在";
};



#define ERROR_GRAPHICS_MODEL_FROM_JSON_NO_TAG 15121 //车辆JSON解析缺少必要的标签项
template<>
struct SunnyTcsErrorInfo<ERROR_GRAPHICS_MODEL_FROM_JSON_NO_TAG>
{
	typedef unsigned int value_type;
	static constexpr value_type value = ERROR_GRAPHICS_MODEL_FROM_JSON_NO_TAG;
	static constexpr char* err_info = "no tag in model json.";
	static constexpr char* err_info_cn = "模型JSON解析缺少必要的标签项";
};


#define ERROR_GRAPHICS_CRAFT_BUILDING_RELATION_BETWEEN_ERR_SONCRAFTS 15501
template<>
struct SunnyTcsErrorInfo<ERROR_GRAPHICS_CRAFT_BUILDING_RELATION_BETWEEN_ERR_SONCRAFTS>
{
	typedef unsigned int value_type;
	static constexpr value_type value = ERROR_GRAPHICS_CRAFT_BUILDING_RELATION_BETWEEN_ERR_SONCRAFTS;
	static constexpr char* err_info = "build relationship between son crafts  owned by unsame owners .";
	static constexpr char* err_info_cn = "尝试在两个所属不同的子工序之间建立关系";
};


//异常处理，这里定义了本系统常用的 异常,异常时基于错误的， 错误不一定会产生异常，但异常一定是出现错误了
//配置异常，读取配置文件或者数据库配置数据时，遇到错误的数据 

template<unsigned int err ,bool cn/*中文？*/ = useChinese>
class SunnyTcsException : public std::exception {
public:
	static constexpr char* err_msg = cn ? SunnyTcsErrorInfo<err>::err_info_cn : SunnyTcsErrorInfo<err>::err_info;

	SunnyTcsException()
		:std::exception(err_msg)
	{}
	virtual ~SunnyTcsException() {}
};



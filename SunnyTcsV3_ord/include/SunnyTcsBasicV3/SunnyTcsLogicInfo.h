#pragma once
#include "sunnytcsbasicv3_global.h"
#include "SunnyTcsGeneralArg.hpp"
#include "SunnyTcsMapActualData.hpp"



namespace basic {



	//条件类型
	enum E_SunnyTcsConditionType {
		singleCondition = 1,
		vagueExpression = 2,
		preciseExpression = 3
	};


	//逻辑运算
	enum E_SunnyTcsLogicOperation {
		E_AND = 1, // &&
		E_OR = 2 // ||
	};


	//算数运算
	enum E_SunnyTcsComparisonOperation {
		EQUAL = 1, //==
		UNEQUAL = 2, //!=
		BIGGER = 3, //>
		SMALLER = 4, //<
		BIGGER_OR_EQUAL = 5, //>=
		SMALLER_OR_EQUAL = 6, //<=
		AND_OPERATION = 7,//&
		OR_OPERATION = 8//|
	};


	enum E_SunnyTcsConditionTarget {
		target_agv = 1,
		target_point = 2,
		target_path = 3,
		target_device = 4, //外围设备，包括主控
		target_line = 5,
		target_location = 6,
	};



	//用来对可以执行的条件 条件运算 条件参数类型 进行限定
	class SUNNYTCSBASICV3_EXPORT SunnyTcsLogicInfo
	{
	public:
		static const QMap<QString, int8_t>& get_conditionStr_conditionId_map()
		{
			return _conditionStr_conditionId;
		}
		static const QMap<E_SunnyTcsConditionTarget, QVector<int8_t>>& get_conditionTar_conditionId_map()
		{
			return _conditionTar_conditionId;
		}
		static const QMap<int8_t, QVector<E_SunnyTcsComparisonOperation>>& get_conditionId_compareOpe_map()
		{
			return _conditionId_compareOpe;
		}
		static const QMap<int8_t, E_ARG_TYPE>& get_conditionId_argType_map()
		{
			return _conditionId_argType;
		}
		static const QMap<QString, E_SunnyTcsLogicOperation>& get_logicOpeStr_logicOpe_map()
		{
			return _logicOpeStr_logOpe;
		}
		static const QMap<QString, E_SunnyTcsComparisonOperation>& get_compareOpeStr_compareOpe_map() {
			return _compareOpeStr_compareOpe;
		}
		static const QMap<QString, E_SunnyTcsConditionTarget>& get_conditionTarStr_conditionTar_map() {
			return _conditionTarStr_conditionTar;
		}

	protected:
		static bool _inited;
		static bool init() {
			conditionTar_conditionId_mapInit();
			conditionId_compareOpe_mapInit();
			conditionId_argType_mapInit();
			//str
			conditionStr_conditionId_mapInit();
			logicOpeStr_logicOpe_mapInit();
			compareOpeStr_compareOpe_mapInit();
			_conditionTarStr_conditionTar_mapInit();
			return true;
		}

		static QMap<QString, E_SunnyTcsConditionTarget> _conditionTarStr_conditionTar;
		static bool _conditionTarStr_conditionTar_mapInit() {
			_conditionTarStr_conditionTar.insert(CONDITION_TAR_AGV, target_agv);
			_conditionTarStr_conditionTar.insert(CONDITION_TAR_LINE, target_line);
			_conditionTarStr_conditionTar.insert(CONDITION_TAR_POINT, target_point);
			_conditionTarStr_conditionTar.insert(CONDITION_TAR_PATH, target_path);
			_conditionTarStr_conditionTar.insert(CONDITION_TAR_DEVICE, target_device);
			_conditionTarStr_conditionTar.insert(CONDITION_TAR_LOCATION, target_location);
			return true;
		}

		static QMap<QString, E_SunnyTcsComparisonOperation> _compareOpeStr_compareOpe;
		static bool compareOpeStr_compareOpe_mapInit() {
			_compareOpeStr_compareOpe.insert(CONDITION_COMPARE_EQUAL_STR, EQUAL);
			_compareOpeStr_compareOpe.insert(CONDITION_COMPARE_UNEQUAL_STR, UNEQUAL);
			_compareOpeStr_compareOpe.insert(CONDITION_COMPARE_BIGGER_STR, BIGGER);
			_compareOpeStr_compareOpe.insert(CONDITION_COMPARE_BIGGER_OR_EQUAL_STR, BIGGER_OR_EQUAL);
			_compareOpeStr_compareOpe.insert(CONDITION_COMPARE_SMALLER_STR, SMALLER);
			_compareOpeStr_compareOpe.insert(CONDITION_COMPARE_SMALLER_OR_EQUAL_STR, SMALLER_OR_EQUAL);
			_compareOpeStr_compareOpe.insert(CONDITION_COMPARE_AND_OPERATION_STR, AND_OPERATION);
			_compareOpeStr_compareOpe.insert(CONDITION_COMPARE_OR_OPERATION_STR, OR_OPERATION);
			return true;
		}

		static QMap<QString, E_SunnyTcsLogicOperation> _logicOpeStr_logOpe;
		static bool logicOpeStr_logicOpe_mapInit() {
			_logicOpeStr_logOpe.insert(QString(CONDITION_LOGICOPE_AND_STR), E_AND);
			_logicOpeStr_logOpe.insert(QString(CONDITION_LOGICOPE_OR_STR), E_OR);
			return true;
		}

		//str 与 条件id 的map
		static QMap<QString, int8_t> _conditionStr_conditionId;
		static bool conditionStr_conditionId_mapInit() {
			_conditionStr_conditionId.insert(QString(CONDITION_ID_STR), CONDITION_ID);
			_conditionStr_conditionId.insert(QString(CONDITION_HAS_AGV_STR), CONDITION_HAS_AGV);
			_conditionStr_conditionId.insert(QString(CONDITION_ABSPOS_STR), CONDITION_ABSPOS);
			_conditionStr_conditionId.insert(QString(CONDITION_RX_STR), CONDITION_RX);
			_conditionStr_conditionId.insert(QString(CONDITION_RY_STR), CONDITION_RY);
			_conditionStr_conditionId.insert(QString(CONDITION_LIFT_STR), CONDITION_LIFT);
			_conditionStr_conditionId.insert(QString(CONDITION_ERROR_STR), CONDITION_ERROR);
			_conditionStr_conditionId.insert(QString(CONDITION_WARNING_STR), CONDITION_WARNING);
			_conditionStr_conditionId.insert(QString(CONDITION_IN_PATH_STR), CONDITION_IN_PATH);
			_conditionStr_conditionId.insert(QString(CONDITION_IN_POINT_STR), CONDITION_IN_POINT);
			_conditionStr_conditionId.insert(QString(CONDITION_AGV_NAMAMODE_STR), CONDITION_AGV_NAMAMODE);
			_conditionStr_conditionId.insert(QString(CONDITION_LIMIT_SPEED_STR), CONDITION_LIMIT_SPEED);
			_conditionStr_conditionId.insert(QString(CONDITION_AGV_COUNT_STR), CONDITION_AGV_COUNT);
			_conditionStr_conditionId.insert(QString(CONDITION_POINT_NAGAMODE_STR), CONDITION_POINT_NAGAMODE);
			_conditionStr_conditionId.insert(QString(CONDITION_LINE_VAL_STR), CONDITION_LINE_VAL);
			return true;
		}

		//条件对象 与 条件
		static QMap<E_SunnyTcsConditionTarget, QVector<int8_t>> _conditionTar_conditionId;
		static bool conditionTar_conditionId_mapInit() {
			QVector<int8_t> agvs{
				CONDITION_ID ,
				CONDITION_ABSPOS ,
				CONDITION_RX ,
				CONDITION_RY ,
				CONDITION_LIFT ,
				CONDITION_ERROR ,
				CONDITION_WARNING ,
				CONDITION_IN_PATH ,
				CONDITION_IN_POINT ,
				CONDITION_AGV_NAMAMODE
			};

			QVector<int8_t> lines;
			lines << CONDITION_LINE_VAL << CONDITION_ID;

			QVector<int8_t> points;
			points << CONDITION_POINT_NAGAMODE << CONDITION_ID << CONDITION_HAS_AGV;

			QVector<int8_t> paths;
			paths << CONDITION_LIMIT_SPEED << CONDITION_AGV_COUNT << CONDITION_ID << CONDITION_HAS_AGV;

			QVector<int8_t> devices;

			QVector<int8_t> locations;

			_conditionTar_conditionId.insert(target_agv, agvs);
			_conditionTar_conditionId.insert(target_line, lines);
			_conditionTar_conditionId.insert(target_point, points);
			_conditionTar_conditionId.insert(target_path, paths);
			_conditionTar_conditionId.insert(target_device, devices);
			_conditionTar_conditionId.insert(target_location, locations);
			return true;
		}


		//条件与 运算方式集 的map
		static QMap<int8_t, QVector<E_SunnyTcsComparisonOperation>> _conditionId_compareOpe;
		static bool conditionId_compareOpe_mapInit() {
			//general
			QVector<E_SunnyTcsComparisonOperation> comparsionOpe{ EQUAL,UNEQUAL,BIGGER_OR_EQUAL,BIGGER,SMALLER_OR_EQUAL,SMALLER };
			QVector<E_SunnyTcsComparisonOperation> logicOpe;
			logicOpe << AND_OPERATION << OR_OPERATION;
			QVector<E_SunnyTcsComparisonOperation> allOpe{ EQUAL,UNEQUAL,BIGGER_OR_EQUAL,BIGGER,SMALLER_OR_EQUAL,SMALLER, AND_OPERATION,OR_OPERATION };

			_conditionId_compareOpe.insert(CONDITION_ID, comparsionOpe);
			_conditionId_compareOpe.insert(CONDITION_HAS_AGV, comparsionOpe);

			//agv
			_conditionId_compareOpe.insert(CONDITION_ABSPOS, comparsionOpe);
			_conditionId_compareOpe.insert(CONDITION_RX, comparsionOpe);
			_conditionId_compareOpe.insert(CONDITION_RY, comparsionOpe);
			_conditionId_compareOpe.insert(CONDITION_LIFT, comparsionOpe);
			_conditionId_compareOpe.insert(CONDITION_ERROR, logicOpe);
			_conditionId_compareOpe.insert(CONDITION_WARNING, logicOpe);
			_conditionId_compareOpe.insert(CONDITION_IN_PATH, comparsionOpe);
			_conditionId_compareOpe.insert(CONDITION_IN_POINT, comparsionOpe);
			_conditionId_compareOpe.insert(CONDITION_AGV_NAMAMODE, logicOpe);

			//path
			_conditionId_compareOpe.insert(CONDITION_LIMIT_SPEED, comparsionOpe);
			_conditionId_compareOpe.insert(CONDITION_AGV_COUNT, comparsionOpe);

			//point
			_conditionId_compareOpe.insert(CONDITION_POINT_NAGAMODE, comparsionOpe);

			//line
			_conditionId_compareOpe.insert(CONDITION_LINE_VAL, comparsionOpe);

			return true;
		}


		//条件 与 参数类型 的对应表
		static QMap<int8_t, E_ARG_TYPE> _conditionId_argType;
		static bool conditionId_argType_mapInit() {
			//general
			_conditionId_argType.insert(CONDITION_ID, E_ARG_TYPE::ARG_INT32);
			_conditionId_argType.insert(CONDITION_HAS_AGV, E_ARG_TYPE::ARG_BOOL);

			//agv
			_conditionId_argType.insert(CONDITION_ABSPOS, E_ARG_TYPE::ARG_INT32);
			_conditionId_argType.insert(CONDITION_RX, E_ARG_TYPE::ARG_INT32);
			_conditionId_argType.insert(CONDITION_RY, E_ARG_TYPE::ARG_INT32);
			_conditionId_argType.insert(CONDITION_LIFT, E_ARG_TYPE::ARG_INT32);
			_conditionId_argType.insert(CONDITION_ERROR, E_ARG_TYPE::ARG_INT32);
			_conditionId_argType.insert(CONDITION_WARNING, E_ARG_TYPE::ARG_INT32);
			_conditionId_argType.insert(CONDITION_IN_PATH, E_ARG_TYPE::ARG_INT32);
			_conditionId_argType.insert(CONDITION_IN_POINT, E_ARG_TYPE::ARG_INT32);
			_conditionId_argType.insert(CONDITION_AGV_NAMAMODE, E_ARG_TYPE::ARG_INT8);

			//path
			_conditionId_argType.insert(CONDITION_LIMIT_SPEED, E_ARG_TYPE::ARG_INT32);
			_conditionId_argType.insert(CONDITION_AGV_COUNT, E_ARG_TYPE::ARG_INT32);

			//point
			_conditionId_argType.insert(CONDITION_POINT_NAGAMODE, E_ARG_TYPE::ARG_INT8);

			//line
			_conditionId_argType.insert(CONDITION_LINE_VAL, E_ARG_TYPE::ARG_INT32);

			return true;
		}

	};

}


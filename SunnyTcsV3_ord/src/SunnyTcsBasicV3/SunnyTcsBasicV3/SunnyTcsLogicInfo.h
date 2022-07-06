#pragma once
#include "sunnytcsbasicv3_global.h"
#include "SunnyTcsGeneralArg.hpp"
#include "SunnyTcsMapActualData.hpp"



//logic
//1.条件对象的Str
#define CONDITION_TAR_AGV "agv"
#define CONDITION_TAR_POINT "point"
#define CONDITION_TAR_PATH "path"
#define CONDITION_TAR_LOCATION "location"


//2.算数运算的str
#define CONDITION_COMPARE_EQUAL_STR "=="
#define CONDITION_COMPARE_UNEQUAL_STR "!="
#define CONDITION_COMPARE_BIGGER_STR ">"
#define CONDITION_COMPARE_SMALLER_STR "<"
#define CONDITION_COMPARE_BIGGER_OR_EQUAL_STR ">="
#define CONDITION_COMPARE_SMALLER_OR_EQUAL_STR "<="
#define CONDITION_COMPARE_AND_OPERATION_STR "&"
#define CONDITION_COMPARE_OR_OPERATION_STR "|"


//3. 逻辑运算对象的str
#define CONDITION_LOGICOPE_AND_STR "&"
#define CONDITION_LOGICOPE_OR_STR "|"



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
		BIGGER = 4, //>
		SMALLER = 8, //<
		BIGGER_OR_EQUAL = 16, //>=
		SMALLER_OR_EQUAL = 32, //<=
		AND_OPERATION = 64,//&
		OR_OPERATION = 128//|
	};


	enum E_SunnyTcsConditionTarget {
		target_agv = 1,
		target_point = 2,
		target_path = 4,
		target_location = 8,
		target_master_control = 16, //主控

		target_line = 32,
		target_device = 64
	};


	template<typename T, typename J>
	static bool basicOperation(const T& cval, E_SunnyTcsComparisonOperation ope, const J& val) {
		switch (ope)
		{
		case EQUAL:
			return (cval == val);
		case UNEQUAL:
			return (cval != val);
		case BIGGER:
			return (cval > val);
		case SMALLER:
			return (cval < val);
		case BIGGER_OR_EQUAL:
			return (cval >= val);
		case SMALLER_OR_EQUAL:
			return (cval <= val);
		case AND_OPERATION:
			return (cval & val);
		case OR_OPERATION:
			return (cval | val);
		default:
			Q_ASSERT(0);
		}
		return false;
	}


	//逻辑base ,定义每种条件ID的处理方式，限制条件等
	template<qint64 condition_id>
	struct SunnyTcsLogicBase;


	//3.每种条件占据的位 ，最多64种，从1到64位 分布；
	//general
	#define	CONDITION_ID 0x01 //id 全部适用 
	#define CONDITION_ID_STR "id"
	template<>
	struct SunnyTcsLogicBase<CONDITION_ID> {

		static constexpr E_ARG_TYPE arg_value_type = ARG_INT32;
		static constexpr char* description = CONDITION_ID_STR; //文字描述
		static constexpr qint64 support_target = Epoint | Epath | Elocation | Evehicle; //支持对象
		static constexpr qint64 support_operation = EQUAL ; //所支持的运算方式

		typedef qint32 value_type;

		static bool check_aux(E_SunnyTcsMapObject_type target_type, E_SunnyTcsComparisonOperation ope, E_ARG_TYPE arg_type) {
			return (target_type & support_target) && (ope & support_operation) && (arg_type == arg_value_type);
		}

		//从前置条件中筛选出合适的对象
		static bool getTarget_aux(E_SunnyTcsMapObject_type target_type, E_SunnyTcsComparisonOperation ope, SunnyTcsArg& val,
			I_SunnyTcsActualData &data , QVector<I_SunnyTcsElementData*>& ret)
		{
			if (!( (qint64)target_type & support_target) || !((qint64)ope & support_operation)||val.getType() != arg_value_type ) {
				throw QString("");
			}
			ret.clear();
			value_type va = 0;
			val.constructInMem((void*)(&va), sizeof(value_type));
			I_SunnyTcsElementData* element = data.getElement(target_type, va);
			if (element)ret << element;
			return !ret.isEmpty();
		}

		//根据前置条件筛选出来的对象进行 后置条件判断
		static bool operate_aux(QVector<I_SunnyTcsElementData*>& target, E_SunnyTcsComparisonOperation ope , SunnyTcsArg& val ,I_SunnyTcsActualData &data) {
			//对运算符和比对值检查
			if (!((qint64)ope & support_operation) || val.getType() != arg_value_type) {
				throw QString("");
			}
			//获取比对值
			value_type va = 0;
			val.constructInMem((void*)(&va), sizeof(value_type));
			//ID检查，符合条件的只能有1个
			if (target.count() != 1) {
				return false;
			}
			I_SunnyTcsElementData* ptr = target.first();
			//检查对象的类型是否符合
			if (!(ptr->getTag()._eletype & support_target)) {
				return false;
			}
			//对象值和比对值的对比
			return ptr->getElementId() == va;
		}
	};



	//agv
#define CONDITION_ABSPOS 0x02
#define CONDITION_ABSPOS_STR "abspos"
	template<>
	struct SunnyTcsLogicBase<CONDITION_ABSPOS> {

		static constexpr E_ARG_TYPE arg_value_type = ARG_INT32;
		static constexpr char* description = CONDITION_ABSPOS_STR; //文字描述
		static constexpr qint64 support_target =  Evehicle; //支持对象
		static constexpr qint64 support_operation = EQUAL | UNEQUAL | BIGGER |BIGGER_OR_EQUAL |SMALLER |SMALLER_OR_EQUAL; //所支持的运算方式

		typedef qint32 value_type;

		static bool check_aux(E_SunnyTcsMapObject_type target_type, E_SunnyTcsComparisonOperation ope, E_ARG_TYPE arg_type) {
			return (target_type & support_target) && (ope & support_operation) && (arg_type == arg_value_type);
		}
	
		//从前置条件中筛选出合适的对象
		static bool getTarget_aux(E_SunnyTcsMapObject_type target_type, E_SunnyTcsComparisonOperation ope, SunnyTcsArg& val,
			I_SunnyTcsActualData &data, QVector<I_SunnyTcsElementData*>& ret)
		{
			if (!((qint64)target_type & support_target) || !((qint64)ope & support_operation) || val.getType() != arg_value_type) {
				throw QString("");
			}
			ret.clear();
			value_type va = 0;
			val.constructInMem((void*)(&va), sizeof(value_type));
			//本条件
			QHash<qint32, I_SunnyTcsAgvStat*> vehicles;
			data.agvStats(vehicles);
			for (auto iter : vehicles) {
				SunnyTcsAgvCoordinate&& coor = iter->getAgvCurCoor();
				if (coor._dim == E_ONE_DIMENSION && basicOperation( coor._x,ope,va ) ) {
					ret << iter;
				}
			}
			return !ret.isEmpty();
		}

		//根据前置条件筛选出来的对象进行 后置条件判断
		static bool operate_aux(QVector<I_SunnyTcsElementData*>& target, E_SunnyTcsComparisonOperation ope, SunnyTcsArg& val, I_SunnyTcsActualData &data) {
			//对运算符和比对值检查
			if (!((qint64)ope & support_operation) || val.getType() != arg_value_type) {
				throw QString("");
			}
			//获取比对值
			value_type va = 0;
			val.constructInMem((void*)(&va), sizeof(value_type));
			//逐个比对,要求所有元素都得通过检查
			for (auto iter : target) {
				//每个元素的类型进行检查
				if (!(iter->getTag()._eletype & support_target)) {
					return false;
				}
				//这个是车元素
				I_SunnyTcsAgvStat* agvStat = dynamic_cast<I_SunnyTcsAgvStat*>(iter);
				Q_ASSERT(agvStat);
				SunnyTcsAgvCoordinate&& coor = agvStat->getAgvCurCoor();
				//对其坐标值进行检查
				if (coor._dim != E_ONE_DIMENSION) {
					return false;
				}
				if (!basicOperation(coor._x, ope, va)) {
					return false;
				}
			}
			//所有元素均通过检查
			return true;
		}
		
	};


#define CONDITION_RX 0x04
#define CONDITION_RX_STR "rx"
	template<>
	struct SunnyTcsLogicBase<CONDITION_RX> {

		static constexpr E_ARG_TYPE arg_value_type = ARG_INT32;
		static constexpr char* description = CONDITION_RX_STR; //文字描述
		static constexpr qint64 support_target = Evehicle; //支持对象
		static constexpr qint64 support_operation = EQUAL | UNEQUAL | BIGGER | BIGGER_OR_EQUAL | SMALLER | SMALLER_OR_EQUAL; //所支持的运算方式

		typedef qint32 value_type;

		static bool check_aux(E_SunnyTcsMapObject_type target_type, E_SunnyTcsComparisonOperation ope, E_ARG_TYPE arg_type) {
			return (target_type & support_target) && (ope & support_operation) && (arg_type == arg_value_type);
		}

		//从前置条件中筛选出合适的对象
		static bool getTarget_aux(E_SunnyTcsMapObject_type target_type, E_SunnyTcsComparisonOperation ope, SunnyTcsArg& val,
			I_SunnyTcsActualData &data, QVector<I_SunnyTcsElementData*>& ret)
		{
			if (!((qint64)target_type & support_target) || !((qint64)ope & support_operation) || val.getType() != arg_value_type) {
				throw QString("");
			}
			ret.clear();
			value_type va = 0;
			val.constructInMem((void*)(&va), sizeof(value_type));
			//本条件
			QHash<qint32, I_SunnyTcsAgvStat*> vehicles;
			data.agvStats(vehicles);
			for (auto iter : vehicles) {
				SunnyTcsAgvCoordinate&& coor = iter->getAgvCurCoor();
				if (coor._dim == E_TWO_DIMENSION && basicOperation(coor._x, ope, va)) {
					ret << iter;
				}
			}
			return !ret.isEmpty();
		}

		//根据前置条件筛选出来的对象进行 后置条件判断
		static bool operate_aux(QVector<I_SunnyTcsElementData*>& target, E_SunnyTcsComparisonOperation ope, SunnyTcsArg& val, I_SunnyTcsActualData &data) {
			//对运算符和比对值检查
			if (!((qint64)ope & support_operation) || val.getType() != arg_value_type) {
				throw QString("");
			}
			//获取比对值
			value_type va = 0;
			val.constructInMem((void*)(&va), sizeof(value_type));
			//逐个比对,要求所有元素都得通过检查
			for (auto iter : target) {
				//每个元素的类型进行检查
				if (!(iter->getTag()._eletype & support_target)) {
					return false;
				}
				//这个是车元素
				I_SunnyTcsAgvStat* agvStat = dynamic_cast<I_SunnyTcsAgvStat*>(iter);
				Q_ASSERT(agvStat);
				SunnyTcsAgvCoordinate&& coor = agvStat->getAgvCurCoor();
				//对其坐标值进行检查
				if (coor._dim != E_TWO_DIMENSION) {
					return false;
				}
				if (!basicOperation(coor._x, ope, va)) {
					return false;
				}
			}
			//所有元素均通过检查
			return true;
		}

	};



#define CONDITION_RY 0x08
#define CONDITION_RY_STR "ry"
	template<>
	struct SunnyTcsLogicBase<CONDITION_RY> {

		static constexpr E_ARG_TYPE arg_value_type = ARG_INT32;
		static constexpr char* description = CONDITION_RY_STR; //文字描述
		static constexpr qint64 support_target = Evehicle; //支持对象
		static constexpr qint64 support_operation = EQUAL | UNEQUAL | BIGGER | BIGGER_OR_EQUAL | SMALLER | SMALLER_OR_EQUAL; //所支持的运算方式

		typedef qint32 value_type;

		static bool check_aux(E_SunnyTcsMapObject_type target_type, E_SunnyTcsComparisonOperation ope, E_ARG_TYPE arg_type) {
			return (target_type & support_target) && (ope & support_operation) && (arg_type == arg_value_type);
		}

		//从前置条件中筛选出合适的对象
		static bool getTarget_aux(E_SunnyTcsMapObject_type target_type, E_SunnyTcsComparisonOperation ope, SunnyTcsArg& val,
			I_SunnyTcsActualData &data, QVector<I_SunnyTcsElementData*>& ret)
		{
			if (!((qint64)target_type & support_target) || !((qint64)ope & support_operation) || val.getType() != arg_value_type) {
				throw QString("");
			}
			ret.clear();
			value_type va = 0;
			val.constructInMem((void*)(&va), sizeof(value_type));
			//本条件
			QHash<qint32, I_SunnyTcsAgvStat*> vehicles;
			data.agvStats(vehicles);
			for (auto iter : vehicles) {
				SunnyTcsAgvCoordinate&& coor = iter->getAgvCurCoor();
				if (coor._dim == E_TWO_DIMENSION && basicOperation(coor._y, ope, va)) {
					ret << iter;
				}
			}
			return !ret.isEmpty();
		}

		//根据前置条件筛选出来的对象进行 后置条件判断
		static bool operate_aux(QVector<I_SunnyTcsElementData*>& target, E_SunnyTcsComparisonOperation ope, SunnyTcsArg& val, I_SunnyTcsActualData &data) {
			//对运算符和比对值检查
			if (!((qint64)ope & support_operation) || val.getType() != arg_value_type) {
				throw QString("");
			}
			//获取比对值
			value_type va = 0;
			val.constructInMem((void*)(&va), sizeof(value_type));
			//逐个比对,要求所有元素都得通过检查
			for (auto iter : target) {
				//每个元素的类型进行检查
				if (!(iter->getTag()._eletype & support_target)) {
					return false;
				}
				//这个是车元素
				I_SunnyTcsAgvStat* agvStat = dynamic_cast<I_SunnyTcsAgvStat*>(iter);
				Q_ASSERT(agvStat);
				SunnyTcsAgvCoordinate&& coor = agvStat->getAgvCurCoor();
				//对其坐标值进行检查
				if (coor._dim != E_TWO_DIMENSION) {
					return false;
				}
				if (!basicOperation(coor._y, ope, va)) {
					return false;
				}
			}
			//所有元素均通过检查
			return true;
		}

	};


#define CONDITION_LIFT 0x10
#define CONDITION_LIFT_STR "lift"
	template<>
	struct SunnyTcsLogicBase<CONDITION_LIFT> {

		static constexpr E_ARG_TYPE arg_value_type = ARG_INT32;
		static constexpr char* description = CONDITION_LIFT_STR; //文字描述
		static constexpr qint64 support_target = Evehicle; //支持对象
		static constexpr qint64 support_operation = EQUAL | UNEQUAL | BIGGER | BIGGER_OR_EQUAL | SMALLER | SMALLER_OR_EQUAL; //所支持的运算方式

		typedef qint32 value_type;

		static bool check_aux(E_SunnyTcsMapObject_type target_type, E_SunnyTcsComparisonOperation ope, E_ARG_TYPE arg_type) {
			return (target_type & support_target) && (ope & support_operation) && (arg_type == arg_value_type);
		}

		//从前置条件中筛选出合适的对象
		static bool getTarget_aux(E_SunnyTcsMapObject_type target_type, E_SunnyTcsComparisonOperation ope, SunnyTcsArg& val,
			I_SunnyTcsActualData &data, QVector<I_SunnyTcsElementData*>& ret)
		{
			if (!((qint64)target_type & support_target) || !((qint64)ope & support_operation) || val.getType() != arg_value_type) {
				throw QString("");
			}
			ret.clear();
			value_type va = 0;
			val.constructInMem((void*)(&va), sizeof(value_type));
			//本条件
			QHash<qint32, I_SunnyTcsAgvStat*> vehicles;
			data.agvStats(vehicles);
			for (auto iter : vehicles) {
				qint32 lift = iter->getLift();
				if ( basicOperation(lift, ope, va)) {
					ret << iter;
				}
			}
			return !ret.isEmpty();
		}

		//根据前置条件筛选出来的对象进行 后置条件判断
		static bool operate_aux(QVector<I_SunnyTcsElementData*>& target, E_SunnyTcsComparisonOperation ope, SunnyTcsArg& val, I_SunnyTcsActualData &data) {
			//对运算符和比对值检查
			if (!((qint64)ope & support_operation) || val.getType() != arg_value_type) {
				throw QString("");
			}
			//获取比对值
			value_type va = 0;
			val.constructInMem((void*)(&va), sizeof(value_type));
			//逐个比对,要求所有元素都得通过检查
			for (auto iter : target) {
				//每个元素的类型进行检查
				if (!(iter->getTag()._eletype & support_target)) {
					return false;
				}
				//这个是车元素
				I_SunnyTcsAgvStat* agvStat = dynamic_cast<I_SunnyTcsAgvStat*>(iter);
				Q_ASSERT(agvStat);
				qint32 lift = agvStat->getLift();
				if (!basicOperation(lift, ope, va)) {
					return false;
				}
			}
			//所有元素均通过检查
			return true;
		}
	};



#define CONDITION_ERROR 0x20
#define CONDITION_ERROR_STR "error"
	template<>
	struct SunnyTcsLogicBase<CONDITION_ERROR> {

		static constexpr E_ARG_TYPE arg_value_type = ARG_INT64;
		static constexpr char* description = CONDITION_ERROR_STR; //文字描述
		static constexpr qint64 support_target = Evehicle; //支持对象
		static constexpr qint64 support_operation = EQUAL | UNEQUAL | AND_OPERATION |OR_OPERATION; //所支持的运算方式

		typedef qint64 value_type;

		static bool check_aux(E_SunnyTcsMapObject_type target_type, E_SunnyTcsComparisonOperation ope, E_ARG_TYPE arg_type) {
			return (target_type & support_target) && (ope & support_operation) && (arg_type == arg_value_type);
		}

		//从前置条件中筛选出合适的对象
		static bool getTarget_aux(E_SunnyTcsMapObject_type target_type, E_SunnyTcsComparisonOperation ope, SunnyTcsArg& val,
			I_SunnyTcsActualData &data, QVector<I_SunnyTcsElementData*>& ret)
		{
			if (!((qint64)target_type & support_target) || !((qint64)ope & support_operation) || val.getType() != arg_value_type) {
				throw QString("");
			}
			ret.clear();
			value_type va = 0;
			val.constructInMem((void*)(&va), sizeof(value_type));
			//本条件
			QHash<qint32, I_SunnyTcsAgvStat*> vehicles;
			data.agvStats(vehicles);
			for (auto iter : vehicles) {
				qint64 error = iter->getError();
				if (basicOperation(error, ope, va)) {
					ret << iter;
				}
			}
			return !ret.isEmpty();
		}

		//根据前置条件筛选出来的对象进行 后置条件判断
		static bool operate_aux(QVector<I_SunnyTcsElementData*>& target, E_SunnyTcsComparisonOperation ope, SunnyTcsArg& val, I_SunnyTcsActualData &data) {
			//对运算符和比对值检查
			if (!((qint64)ope & support_operation) || val.getType() != arg_value_type) {
				throw QString("");
			}
			//获取比对值
			value_type va = 0;
			val.constructInMem((void*)(&va), sizeof(value_type));
			//逐个比对,要求所有元素都得通过检查
			for (auto iter : target) {
				//每个元素的类型进行检查
				if (!(iter->getTag()._eletype & support_target)) {
					return false;
				}
				//这个是车元素
				I_SunnyTcsAgvStat* agvStat = dynamic_cast<I_SunnyTcsAgvStat*>(iter);
				Q_ASSERT(agvStat);
				qint64 error = agvStat->getError();
				if (!basicOperation(error, ope, va)) {
					return false;
				}
			}
			//所有元素均通过检查
			return true;
		}
	};


#define CONDITION_WARNING 0x40
#define CONDITION_WARNING_STR "warn"
	template<>
	struct SunnyTcsLogicBase<CONDITION_WARNING> {

		static constexpr E_ARG_TYPE arg_value_type = ARG_INT64;
		static constexpr char* description = CONDITION_WARNING_STR; //文字描述
		static constexpr qint64 support_target = Evehicle; //支持对象
		static constexpr qint64 support_operation = EQUAL | UNEQUAL | AND_OPERATION | OR_OPERATION; //所支持的运算方式

		typedef qint64 value_type;

		static bool check_aux(E_SunnyTcsMapObject_type target_type, E_SunnyTcsComparisonOperation ope, E_ARG_TYPE arg_type) {
			return (target_type & support_target) && (ope & support_operation) && (arg_type == arg_value_type);
		}

		//从前置条件中筛选出合适的对象
		static bool getTarget_aux(E_SunnyTcsMapObject_type target_type, E_SunnyTcsComparisonOperation ope, SunnyTcsArg& val,
			I_SunnyTcsActualData &data, QVector<I_SunnyTcsElementData*>& ret)
		{
			if (!((qint64)target_type & support_target) || !((qint64)ope & support_operation) || val.getType() != arg_value_type) {
				throw QString("");
			}
			ret.clear();
			value_type va = 0;
			val.constructInMem((void*)(&va), sizeof(value_type));
			//本条件
			QHash<qint32, I_SunnyTcsAgvStat*> vehicles;
			data.agvStats(vehicles);
			for (auto iter : vehicles) {
				qint64 error = iter->getWarning();
				if (basicOperation(error, ope, va)) {
					ret << iter;
				}
			}
			return !ret.isEmpty();
		}

		//根据前置条件筛选出来的对象进行 后置条件判断
		static bool operate_aux(QVector<I_SunnyTcsElementData*>& target, E_SunnyTcsComparisonOperation ope, SunnyTcsArg& val, I_SunnyTcsActualData &data) {
			//对运算符和比对值检查
			if (!((qint64)ope & support_operation) || val.getType() != arg_value_type) {
				throw QString("");
			}
			//获取比对值
			value_type va = 0;
			val.constructInMem((void*)(&va), sizeof(value_type));
			//逐个比对,要求所有元素都得通过检查
			for (auto iter : target) {
				//每个元素的类型进行检查
				if (!(iter->getTag()._eletype & support_target)) {
					return false;
				}
				//这个是车元素
				I_SunnyTcsAgvStat* agvStat = dynamic_cast<I_SunnyTcsAgvStat*>(iter);
				Q_ASSERT(agvStat);
				qint64 error = agvStat->getWarning();
				if (!basicOperation(error, ope, va)) {
					return false;
				}
			}
			//所有元素均通过检查
			return true;
		}
	};

#define CONDITION_IN_PATH 0x80
#define CONDITION_IN_PATH_STR "inpath"
	template<>
	struct SunnyTcsLogicBase<CONDITION_IN_PATH> {

		static constexpr E_ARG_TYPE arg_value_type = ARG_INT32;
		static constexpr char* description = CONDITION_IN_PATH_STR; //文字描述
		static constexpr qint64 support_target = Evehicle; //支持对象
		static constexpr qint64 support_operation = EQUAL ; //所支持的运算方式

		typedef qint32 value_type;

		static bool check_aux(E_SunnyTcsMapObject_type target_type, E_SunnyTcsComparisonOperation ope, E_ARG_TYPE arg_type) {
			return (target_type & support_target) && (ope & support_operation) && (arg_type == arg_value_type);
		}

		//从前置条件中筛选出合适的对象
		static bool getTarget_aux(E_SunnyTcsMapObject_type target_type, E_SunnyTcsComparisonOperation ope, SunnyTcsArg& val,
			I_SunnyTcsActualData &data, QVector<I_SunnyTcsElementData*>& ret)
		{
			if (!((qint64)target_type & support_target) || !((qint64)ope & support_operation) || val.getType() != arg_value_type) {
				throw QString("");
			}
			ret.clear();
			value_type va = 0;
			val.constructInMem((void*)(&va), sizeof(value_type));
			//本条件
			QHash<qint32, I_SunnyTcsAgvStat*> vehicles;
			data.agvStats(vehicles);
			for (auto iter : vehicles) {
				SunnyTcsMapObject_tag curPos = iter->getAgvCurPos();
				if ( curPos._eletype == Epath && basicOperation(curPos._id, ope, va)) {
					ret << iter;
				}
			}
			return !ret.isEmpty();
		}

		//根据前置条件筛选出来的对象进行 后置条件判断
		static bool operate_aux(QVector<I_SunnyTcsElementData*>& target, E_SunnyTcsComparisonOperation ope, SunnyTcsArg& val, I_SunnyTcsActualData &data) {
			//对运算符和比对值检查
			if (!((qint64)ope & support_operation) || val.getType() != arg_value_type) {
				throw QString("");
			}
			//获取比对值
			value_type va = 0;
			val.constructInMem((void*)(&va), sizeof(value_type));
			//逐个比对,要求所有元素都得通过检查
			for (auto iter : target) {
				//每个元素的类型进行检查
				if (!(iter->getTag()._eletype & support_target)) {
					return false;
				}
				//这个是车元素
				I_SunnyTcsAgvStat* agvStat = dynamic_cast<I_SunnyTcsAgvStat*>(iter);
				Q_ASSERT(agvStat);
				SunnyTcsMapObject_tag curPos = agvStat->getAgvCurPos();
				if ( curPos._eletype!= Epath || !basicOperation(curPos._id , ope, va)) {
					return false;
				}
			}
			//所有元素均通过检查
			return true;
		}
	};

#define CONDITION_IN_POINT 0x0100
#define CONDITION_IN_POINT_STR "inpoint"
	template<>
	struct SunnyTcsLogicBase<CONDITION_IN_POINT> {

		static constexpr E_ARG_TYPE arg_value_type = ARG_INT32;
		static constexpr char* description = CONDITION_IN_POINT_STR; //文字描述
		static constexpr qint64 support_target = Evehicle; //支持对象
		static constexpr qint64 support_operation = EQUAL; //所支持的运算方式

		typedef qint32 value_type;

		static bool check_aux(E_SunnyTcsMapObject_type target_type, E_SunnyTcsComparisonOperation ope, E_ARG_TYPE arg_type) {
			return (target_type & support_target) && (ope & support_operation) && (arg_type == arg_value_type);
		}

		//从前置条件中筛选出合适的对象
		static bool getTarget_aux(E_SunnyTcsMapObject_type target_type, E_SunnyTcsComparisonOperation ope, SunnyTcsArg& val,
			I_SunnyTcsActualData &data, QVector<I_SunnyTcsElementData*>& ret)
		{
			if (!((qint64)target_type & support_target) || !((qint64)ope & support_operation) || val.getType() != arg_value_type) {
				throw QString("");
			}
			ret.clear();
			value_type va = 0;
			val.constructInMem((void*)(&va), sizeof(value_type));
			//本条件
			QHash<qint32, I_SunnyTcsAgvStat*> vehicles;
			data.agvStats(vehicles);
			for (auto iter : vehicles) {
				SunnyTcsMapObject_tag curPos = iter->getAgvCurPos();
				if (curPos._eletype == Epoint && basicOperation(curPos._id, ope, va)) {
					ret << iter;
				}
			}
			return !ret.isEmpty();
		}

		//根据前置条件筛选出来的对象进行 后置条件判断
		static bool operate_aux(QVector<I_SunnyTcsElementData*>& target, E_SunnyTcsComparisonOperation ope, SunnyTcsArg& val, I_SunnyTcsActualData &data) {
			//对运算符和比对值检查
			if (!((qint64)ope & support_operation) || val.getType() != arg_value_type) {
				throw QString("");
			}
			//获取比对值
			value_type va = 0;
			val.constructInMem((void*)(&va), sizeof(value_type));
			//逐个比对,要求所有元素都得通过检查
			for (auto iter : target) {
				//每个元素的类型进行检查
				if (!(iter->getTag()._eletype & support_target)) {
					return false;
				}
				//这个是车元素
				I_SunnyTcsAgvStat* agvStat = dynamic_cast<I_SunnyTcsAgvStat*>(iter);
				Q_ASSERT(agvStat);
				SunnyTcsMapObject_tag curPos = agvStat->getAgvCurPos();
				if (curPos._eletype != Epoint || !basicOperation(curPos._id, ope, va)) {
					return false;
				}
			}
			//所有元素均通过检查
			return true;
		}
	};

#define CONDITION_AGV_NAMAMODE 0x0200
#define CONDITION_AGV_NAMAMODE_STR "agvnagamode"
	template<>
	struct SunnyTcsLogicBase<CONDITION_AGV_NAMAMODE> {

		static constexpr E_ARG_TYPE arg_value_type = ARG_INT32;
		static constexpr char* description = CONDITION_AGV_NAMAMODE_STR; //文字描述
		static constexpr qint64 support_target = Evehicle; //支持对象
		static constexpr qint64 support_operation = EQUAL|UNEQUAL|AND_OPERATION|OR_OPERATION; //所支持的运算方式

		typedef qint32 value_type;

		static bool check_aux(E_SunnyTcsMapObject_type target_type, E_SunnyTcsComparisonOperation ope, E_ARG_TYPE arg_type) {
			return (target_type & support_target) && (ope & support_operation) && (arg_type == arg_value_type);
		}

		//从前置条件中筛选出合适的对象
		static bool getTarget_aux(E_SunnyTcsMapObject_type target_type, E_SunnyTcsComparisonOperation ope, SunnyTcsArg& val,
			I_SunnyTcsActualData &data, QVector<I_SunnyTcsElementData*>& ret)
		{
			if (!((qint64)target_type & support_target) || !((qint64)ope & support_operation) || val.getType() != arg_value_type) {
				throw QString("");
			}
			ret.clear();
			value_type va = 0;
			val.constructInMem((void*)(&va), sizeof(value_type));
			//本条件
			QHash<qint32, I_SunnyTcsAgvStat*> vehicles;
			data.agvStats(vehicles);
			for (auto iter : vehicles) {
				SunnyTcsAgvCode code = iter->getAgvCode();
				if ( basicOperation(code._nagaMode, ope, va)) {
					ret << iter;
				}
			}
			return !ret.isEmpty();
		}

		//根据前置条件筛选出来的对象进行 后置条件判断
		static bool operate_aux(QVector<I_SunnyTcsElementData*>& target, E_SunnyTcsComparisonOperation ope, SunnyTcsArg& val, I_SunnyTcsActualData &data) {
			//对运算符和比对值检查
			if (!((qint64)ope & support_operation) || val.getType() != arg_value_type) {
				throw QString("");
			}
			//获取比对值
			value_type va = 0;
			val.constructInMem((void*)(&va), sizeof(value_type));
			//逐个比对,要求所有元素都得通过检查
			for (auto iter : target) {
				//每个元素的类型进行检查
				if (!(iter->getTag()._eletype & support_target)) {
					return false;
				}
				//这个是车元素
				I_SunnyTcsAgvStat* agvStat = dynamic_cast<I_SunnyTcsAgvStat*>(iter);
				Q_ASSERT(agvStat);
				SunnyTcsAgvCode code = agvStat->getAgvCode();
				if ( !basicOperation(code._nagaMode, ope, va)) {
					return false;
				}
			}
			//所有元素均通过检查
			return true;
		}
	};

	//point
#define CONDITION_POINT_NAGAMODE 0x0400
#define CONDITION_POINT_NAGAMODE_STR "pointnagamode"
	template<>
	struct SunnyTcsLogicBase<CONDITION_POINT_NAGAMODE> {

		static constexpr E_ARG_TYPE arg_value_type = ARG_INT32;
		static constexpr char* description = CONDITION_POINT_NAGAMODE_STR; //文字描述
		static constexpr qint64 support_target = Epoint; //支持对象
		static constexpr qint64 support_operation = EQUAL | UNEQUAL | AND_OPERATION | OR_OPERATION; //所支持的运算方式

		typedef qint32 value_type;

		static bool check_aux(E_SunnyTcsMapObject_type target_type, E_SunnyTcsComparisonOperation ope, E_ARG_TYPE arg_type) {
			return (target_type & support_target) && (ope & support_operation) && (arg_type == arg_value_type);
		}

		//从前置条件中筛选出合适的对象
		static bool getTarget_aux(E_SunnyTcsMapObject_type target_type, E_SunnyTcsComparisonOperation ope, SunnyTcsArg& val,
			I_SunnyTcsActualData &data, QVector<I_SunnyTcsElementData*>& ret)
		{
			if (!((qint64)target_type & support_target) || !((qint64)ope & support_operation) || val.getType() != arg_value_type) {
				throw QString("");
			}
			ret.clear();
			value_type va = 0;
			val.constructInMem((void*)(&va), sizeof(value_type));
			//本条件
			QHash<qint32, I_SunnyTcsVertex*> points;
			data.points(points);
			for (auto iter : points) {
				qint32 ptNagaMode = iter->getPointNaga();
				if (basicOperation(ptNagaMode, ope, va)) {
					ret << iter;
				}
			}
			return !ret.isEmpty();
		}

		//根据前置条件筛选出来的对象进行 后置条件判断
		static bool operate_aux(QVector<I_SunnyTcsElementData*>& target, E_SunnyTcsComparisonOperation ope, SunnyTcsArg& val, I_SunnyTcsActualData &data) {
			//对运算符和比对值检查
			if (!((qint64)ope & support_operation) || val.getType() != arg_value_type) {
				throw QString("");
			}
			//获取比对值
			value_type va = 0;
			val.constructInMem((void*)(&va), sizeof(value_type));
			//逐个比对,要求所有元素都得通过检查
			for (auto iter : target) {
				//每个元素的类型进行检查
				if (!(iter->getTag()._eletype & support_target)) {
					return false;
				}
				//这个是车元素
				I_SunnyTcsVertex* vertex = dynamic_cast<I_SunnyTcsVertex*>(iter);
				Q_ASSERT(vertex);
				qint32 ptNagaMode = vertex->getPointNaga();
				if (!basicOperation(ptNagaMode, ope, va)) {
					return false;
				}
			}
			//所有元素均通过检查
			return true;
		}
	};


	//path
#define CONDITION_LIMIT_SPEED 0x0800//路径限速
#define CONDITION_LIMIT_SPEED_STR "speedlimit"
	template<>
	struct SunnyTcsLogicBase<CONDITION_LIMIT_SPEED> {

		static constexpr E_ARG_TYPE arg_value_type = ARG_INT32;
		static constexpr char* description = CONDITION_LIMIT_SPEED_STR; //文字描述
		static constexpr qint64 support_target = Epath; //支持对象
		static constexpr qint64 support_operation = EQUAL | UNEQUAL |BIGGER |BIGGER_OR_EQUAL | SMALLER | SMALLER_OR_EQUAL; //所支持的运算方式

		typedef qint32 value_type;

		static bool check_aux(E_SunnyTcsMapObject_type target_type, E_SunnyTcsComparisonOperation ope, E_ARG_TYPE arg_type) {
			return (target_type & support_target) && (ope & support_operation) && (arg_type == arg_value_type);
		}

		//从前置条件中筛选出合适的对象
		static bool getTarget_aux(E_SunnyTcsMapObject_type target_type, E_SunnyTcsComparisonOperation ope, SunnyTcsArg& val,
			I_SunnyTcsActualData &data, QVector<I_SunnyTcsElementData*>& ret)
		{
			return false;
		}

		//根据前置条件筛选出来的对象进行 后置条件判断
		static bool operate_aux(QVector<I_SunnyTcsElementData*>& target, E_SunnyTcsComparisonOperation ope, SunnyTcsArg& val, I_SunnyTcsActualData &data) {
			return false;
		}
	};



	//path and point
#define CONDITION_AGV_COUNT 0x1000 //有几辆车在path上面
#define CONDITION_AGV_COUNT_STR "agvcount"
	template<>
	struct SunnyTcsLogicBase<CONDITION_AGV_COUNT> {

		static constexpr E_ARG_TYPE arg_value_type = ARG_INT32;
		static constexpr char* description = CONDITION_AGV_COUNT_STR; //文字描述
		static constexpr qint64 support_target = Epath | Epoint; //支持对象
		static constexpr qint64 support_operation = EQUAL | UNEQUAL | BIGGER | BIGGER_OR_EQUAL | SMALLER | SMALLER_OR_EQUAL; //所支持的运算方式

		typedef qint32 value_type;

		static bool check_aux(E_SunnyTcsMapObject_type target_type, E_SunnyTcsComparisonOperation ope, E_ARG_TYPE arg_type) {
			return (target_type & support_target) && (ope & support_operation) && (arg_type == arg_value_type);
		}

		//从前置条件中筛选出合适的对象
		static bool getTarget_aux(E_SunnyTcsMapObject_type target_type, E_SunnyTcsComparisonOperation ope, SunnyTcsArg& val,
			I_SunnyTcsActualData &data, QVector<I_SunnyTcsElementData*>& ret)
		{
			return false;
		}

		//根据前置条件筛选出来的对象进行 后置条件判断
		static bool operate_aux(QVector<I_SunnyTcsElementData*>& target, E_SunnyTcsComparisonOperation ope, SunnyTcsArg& val, I_SunnyTcsActualData &data) {
			return false;
		}
	};



	//线边
#define CONDITION_LINE_VAL 0x2000 //暂时
#define CONDITION_LINE_VAL_STR "lineval"
	template<>
	struct SunnyTcsLogicBase<CONDITION_LINE_VAL> {

		static constexpr E_ARG_TYPE arg_value_type = ARG_INT32;
		static constexpr char* description = CONDITION_LINE_VAL_STR; //文字描述
		static constexpr qint64 support_target = Euls; //支持对象
		static constexpr qint64 support_operation = EQUAL | UNEQUAL | AND_OPERATION |OR_OPERATION; //所支持的运算方式

		typedef qint32 value_type;

		static bool check_aux(E_SunnyTcsMapObject_type target_type, E_SunnyTcsComparisonOperation ope, E_ARG_TYPE arg_type) {
			return (target_type & support_target) && (ope & support_operation) && (arg_type == arg_value_type);
		}

		//从前置条件中筛选出合适的对象
		static bool getTarget_aux(E_SunnyTcsMapObject_type target_type, E_SunnyTcsComparisonOperation ope, SunnyTcsArg& val,
			I_SunnyTcsActualData &data, QVector<I_SunnyTcsElementData*>& ret)
		{
			return false;
		}

		//根据前置条件筛选出来的对象进行 后置条件判断
		static bool operate_aux(QVector<I_SunnyTcsElementData*>& target, E_SunnyTcsComparisonOperation ope, SunnyTcsArg& val, I_SunnyTcsActualData &data) {
			return false;
		}
	};






	//用来对可以执行的条件 条件运算 条件参数类型 进行限定
	class SUNNYTCSBASICV3_EXPORT SunnyTcsLogicInfo
	{
	public:
		static const QMap<QString, qint64>& get_conditionStr_conditionId_map()
		{
			return _conditionStr_conditionId;
		}
		static const QMap<E_SunnyTcsMapObject_type, qint64>& get_conditionTar_conditionId_map()
		{
			return _conditionTar_conditionId;
		}
		static const QMap<qint64, qint64>& get_conditionId_compareOpe_map()
		{
			return _conditionId_compareOpe;
		}
		static const QMap<qint64, E_ARG_TYPE>& get_conditionId_argType_map()
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

		static const QMap<QString, E_SunnyTcsMapObject_type>& get_conditionTarStr_conditionTar_map() {
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

		static QMap<QString, E_SunnyTcsMapObject_type> _conditionTarStr_conditionTar;
		static bool _conditionTarStr_conditionTar_mapInit() {
			_conditionTarStr_conditionTar.insert(CONDITION_TAR_AGV, Evehicle);
			_conditionTarStr_conditionTar.insert(CONDITION_TAR_POINT, Epoint);
			_conditionTarStr_conditionTar.insert(CONDITION_TAR_PATH, Epath);
			_conditionTarStr_conditionTar.insert(CONDITION_TAR_LOCATION, Elocation);
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
			_logicOpeStr_logOpe.insert(CONDITION_LOGICOPE_AND_STR, E_AND);
			_logicOpeStr_logOpe.insert(CONDITION_LOGICOPE_OR_STR, E_OR);
			return true;
		}

		//str 与 条件id 的map
		static QMap<QString, qint64> _conditionStr_conditionId;
		static bool conditionStr_conditionId_mapInit() {
			//all
			_conditionStr_conditionId.insert(CONDITION_ID_STR, CONDITION_ID);
			//vehicle
			_conditionStr_conditionId.insert(CONDITION_ABSPOS_STR, CONDITION_ABSPOS);
			_conditionStr_conditionId.insert(CONDITION_RX_STR, CONDITION_RX);
			_conditionStr_conditionId.insert(CONDITION_RY_STR, CONDITION_RY);
			_conditionStr_conditionId.insert(CONDITION_LIFT_STR, CONDITION_LIFT);
			_conditionStr_conditionId.insert(CONDITION_ERROR_STR, CONDITION_ERROR);
			_conditionStr_conditionId.insert(CONDITION_WARNING_STR, CONDITION_WARNING);
			_conditionStr_conditionId.insert(CONDITION_IN_PATH_STR, CONDITION_IN_PATH);
			_conditionStr_conditionId.insert(CONDITION_IN_POINT_STR, CONDITION_IN_POINT);
			_conditionStr_conditionId.insert(CONDITION_AGV_NAMAMODE_STR, CONDITION_AGV_NAMAMODE);
			//point
			_conditionStr_conditionId.insert(CONDITION_POINT_NAGAMODE_STR, CONDITION_POINT_NAGAMODE);
			//path
			_conditionStr_conditionId.insert(CONDITION_LIMIT_SPEED_STR, CONDITION_LIMIT_SPEED);
			//point and path
			_conditionStr_conditionId.insert(CONDITION_AGV_COUNT_STR, CONDITION_AGV_COUNT);
			//主控
			_conditionStr_conditionId.insert(CONDITION_LINE_VAL_STR, CONDITION_LINE_VAL);
			return true;
		}

		//条件对象 与 条件
		static QMap<E_SunnyTcsMapObject_type,qint64> _conditionTar_conditionId;
		static bool conditionTar_conditionId_mapInit() {
			_conditionTar_conditionId.insert(Evehicle,
				CONDITION_ID |
				CONDITION_ABSPOS |
				CONDITION_RX |
				CONDITION_RY |
				CONDITION_LIFT |
				CONDITION_ERROR |
				CONDITION_WARNING |
				CONDITION_IN_PATH |
				CONDITION_IN_POINT |
				CONDITION_AGV_NAMAMODE );
			_conditionTar_conditionId.insert(Epoint, CONDITION_POINT_NAGAMODE | CONDITION_AGV_COUNT | CONDITION_ID );
			_conditionTar_conditionId.insert(Epath, CONDITION_LIMIT_SPEED | CONDITION_AGV_COUNT | CONDITION_ID );
			_conditionTar_conditionId.insert(Elocation, 0);
			return true;
		}


		//条件与 运算方式集 的map
		static QMap<qint64, qint64> _conditionId_compareOpe;
		static bool conditionId_compareOpe_mapInit() {
			//general
			_conditionId_compareOpe.insert(CONDITION_ID, SunnyTcsLogicBase<CONDITION_ID>::support_operation);
			//agv
			_conditionId_compareOpe.insert(CONDITION_ABSPOS, SunnyTcsLogicBase<CONDITION_ABSPOS>::support_operation);
			_conditionId_compareOpe.insert(CONDITION_RX, SunnyTcsLogicBase<CONDITION_RX>::support_operation);
			_conditionId_compareOpe.insert(CONDITION_RY, SunnyTcsLogicBase<CONDITION_RY>::support_operation);
			_conditionId_compareOpe.insert(CONDITION_LIFT, SunnyTcsLogicBase<CONDITION_LIFT>::support_operation);
			_conditionId_compareOpe.insert(CONDITION_ERROR, SunnyTcsLogicBase<CONDITION_ERROR>::support_operation);
			_conditionId_compareOpe.insert(CONDITION_WARNING, SunnyTcsLogicBase<CONDITION_WARNING>::support_operation);
			_conditionId_compareOpe.insert(CONDITION_IN_PATH, SunnyTcsLogicBase<CONDITION_IN_PATH>::support_operation);
			_conditionId_compareOpe.insert(CONDITION_IN_POINT, SunnyTcsLogicBase<CONDITION_IN_POINT>::support_operation);
			_conditionId_compareOpe.insert(CONDITION_AGV_NAMAMODE, SunnyTcsLogicBase<CONDITION_AGV_NAMAMODE>::support_operation);
			//point
			_conditionId_compareOpe.insert(CONDITION_POINT_NAGAMODE, SunnyTcsLogicBase<CONDITION_POINT_NAGAMODE>::support_operation);
			//path
			_conditionId_compareOpe.insert(CONDITION_LIMIT_SPEED, SunnyTcsLogicBase<CONDITION_LIMIT_SPEED>::support_operation);
			//point and path
			_conditionId_compareOpe.insert(CONDITION_AGV_COUNT, SunnyTcsLogicBase<CONDITION_AGV_COUNT>::support_operation);
			//line
			_conditionId_compareOpe.insert(CONDITION_LINE_VAL, SunnyTcsLogicBase<CONDITION_LINE_VAL>::support_operation);
			return true;
		}


		//条件 与 参数类型 的对应表
		static QMap<qint64, E_ARG_TYPE> _conditionId_argType;
		static bool conditionId_argType_mapInit() {
			//general
			_conditionId_argType.insert(CONDITION_ID,SunnyTcsLogicBase<CONDITION_ID>::arg_value_type);
			//agv
			_conditionId_argType.insert(CONDITION_ABSPOS, SunnyTcsLogicBase<CONDITION_ABSPOS>::arg_value_type);
			_conditionId_argType.insert(CONDITION_RX, SunnyTcsLogicBase<CONDITION_RX>::arg_value_type);
			_conditionId_argType.insert(CONDITION_RY, SunnyTcsLogicBase<CONDITION_RY>::arg_value_type);
			_conditionId_argType.insert(CONDITION_LIFT, SunnyTcsLogicBase<CONDITION_LIFT>::arg_value_type);
			_conditionId_argType.insert(CONDITION_ERROR, SunnyTcsLogicBase<CONDITION_ERROR>::arg_value_type);
			_conditionId_argType.insert(CONDITION_WARNING, SunnyTcsLogicBase<CONDITION_WARNING>::arg_value_type);
			_conditionId_argType.insert(CONDITION_IN_PATH, SunnyTcsLogicBase<CONDITION_IN_PATH>::arg_value_type);
			_conditionId_argType.insert(CONDITION_IN_POINT, SunnyTcsLogicBase<CONDITION_IN_POINT>::arg_value_type);
			_conditionId_argType.insert(CONDITION_AGV_NAMAMODE, SunnyTcsLogicBase<CONDITION_AGV_NAMAMODE>::arg_value_type);
			//point
			_conditionId_argType.insert(CONDITION_POINT_NAGAMODE, SunnyTcsLogicBase<CONDITION_POINT_NAGAMODE>::arg_value_type);
			//path
			_conditionId_argType.insert(CONDITION_LIMIT_SPEED, SunnyTcsLogicBase<CONDITION_LIMIT_SPEED>::arg_value_type);
			//point and path
			_conditionId_argType.insert(CONDITION_AGV_COUNT, SunnyTcsLogicBase<CONDITION_AGV_COUNT>::arg_value_type);
			//line
			_conditionId_argType.insert(CONDITION_LINE_VAL, SunnyTcsLogicBase<CONDITION_LINE_VAL>::arg_value_type);
			return true;
		}

	};

}


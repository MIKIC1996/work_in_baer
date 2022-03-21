#pragma once


#include "SunnyTcsGeneralArg.hpp"
#include "SunnyTcsLibGeneral.hpp"
#include "SunnyTcsMapGeneral.hpp"


#define JSON_ACTION_COMMAND_ID "commandId"
#define JSON_ACTION_COMMAND_CODE "commandCode"
#define JSON_ACTION_IS_INORDER "isInOrder"
#define JSON_ACTION_IS_UPDATED "isUpdated"
#define JSON_ACTION_TYPE "actionType"
#define JSON_ACTION_STATUS "actionStatus"
#define JSON_ACTION_ARGS "actionArgs"
#define JSON_ACTION_DISTRIBUTION "actionDistribution"

#define ACTION_PARAMSSET_MAX basic::actionParamsSetMax 

namespace   basic {

	//Ĭ����������Ϊ7��������Ժ�������Ļ�������ʱ����
	//Ϊʲô��ʹ��QVector<SunnyTcsArg>�� ��Ϊ�����о�̫ӷ���ˣ����������������ǹ̶��ģ������ܻ�̫�࣬û��Ҫ��һ��Vector,����ʱ�������伴��
	//�ֽ׶�7�������Ѿ�������������,�Ժ������˿�������
	typedef std::tuple<
		SunnyTcsArg,
		SunnyTcsArg,
		SunnyTcsArg,
		SunnyTcsArg,
		SunnyTcsArg,
		SunnyTcsArg,
		SunnyTcsArg
	> SunnyTcsParamsSet;

	static constexpr quint16 actionParamsSetMax = std::tuple_size<SunnyTcsParamsSet>::value;

	
	//��������
	enum E_SunnyTcsActionType {
		Eagv = 0,
		Enotify = 1,
		Ewait = 2
	};


	//ָ��״̬
	enum E_SunnyTcsActionStatus {
		Eunsend = 0,
		Ealready_send = 5,
		Erecived = 1,
		Edoing = 2,
		Efinished = 3,
		Eunexecutable = 4
	};


	template<typename _Tuple, int _Index>
	struct TupleInit_int32 {
		static void application(_Tuple& t ) { //�Զ������ ��������application
			static_assert( _Index >= 0 && _Index < std::tuple_size<_Tuple>::value ,"out of Tuple range");
			std::get<_Index>(t) = SunnyTcsArg( ARG_INT32 );
		}
	};


	//��ֵԪ�����⸲��
	struct TupleInit_int32_f {
		template<typename _Tuple, int _Index>
		struct apply : TupleInit_int32<_Tuple,_Index> {}; //�Զ������Ԫ������ apply
	};



	template<typename _Tuple,typename _Ty,int _index = std::tuple_size<_Tuple>::value -1>
	struct initTuple {
		static void init(_Tuple& t, _Ty val) {
			static_assert(_index >= 0 && _index < std::tuple_size<_Tuple>::value, " out of tuple range.");
			initTuple<_Tuple,_Ty,_index -1 > :: init(t, val);
			std::get<_index>(t) = val;
		}
	};


	template<typename _Tuple, typename _Ty>
	struct initTuple<_Tuple,_Ty,0> {
		static void init(_Tuple& t, _Ty val) {
			std::get<0>(t) = val;
		}
	};



	//ָ��ӿ�,���ǵ��˷����ԣ��ӿڵ���ƺ���ȷ��
	class A_SunnyTcsCommand {

	}; 

	//ָ��
	class SUNNYTCSBASICV3_EXPORT SunnyTcsAction:public A_SunnyTcsCommand
	{
	public:
		//default
		SunnyTcsAction()
			:A_SunnyTcsCommand(), _commandId(0), _commandCode(),
			_params(), _paramType(ARG_INT32), _isInOrder(true),
			_isUpdated(false),_actionType(Eagv),_status(Eunsend)
		{
			Tuple_for_each<TupleInit_int32_f, SunnyTcsParamsSet>::for_each(_params);
		}

		//ctor
		explicit SunnyTcsAction(E_ARG_TYPE type) 
			:A_SunnyTcsCommand(), _commandId(0), _commandCode(),
			_params(), _paramType(type), _isInOrder(true),
			_isUpdated(false), _actionType(Eagv), _status(Eunsend)
		{
			initTuple<SunnyTcsParamsSet, SunnyTcsArg>::init(_params, SunnyTcsArg(type));
		}
		//copy ctor
		SunnyTcsAction(const SunnyTcsAction&) = default;
		//operator =
		SunnyTcsAction& operator=(const SunnyTcsAction&) = default;
		//detor
		virtual ~SunnyTcsAction() {}
		//operator ==
		bool operator==(const SunnyTcsAction& rhs) const {
			bool ok = true;
			do {
				ok &= (_isInOrder == rhs._isInOrder);
				if (!ok)break;
				ok &= (_actionType == rhs._actionType);
				if (!ok)break;
				ok &= (_commandId == rhs._commandId);
				if (!ok)break;
				ok &= (_commandCode == rhs._commandCode);
				if (!ok)break;
				ok &= (_params == rhs._params);
				if (!ok)break;
			} while (0);
			return ok;
		}

		//getter
		inline bool isInOrder()const { return _isInOrder; }
		inline bool isUpdated()const { return _isUpdated; }
		template<int index>
		SunnyTcsArg getParam_meta()const {
			return std::get<index>(_params);
		}

		//setter
		template<int index,typename T>
		bool setParams_meta(const T& value) {
			SunnyTcsArg vtoa(value);
			setParams_meta<index>(vtoa);
		}

		template<int index>
		bool setParams_meta(const SunnyTcsArg& param) {
			if (param.getType() != _paramType) {
				return false;
			}
			std::get<index>(_params) = param;
			return true;
		}
		void setOrder(bool is) { _isInOrder = is; }
		void setUpdated(bool is) { _isUpdated = is; }


		//json
		virtual QJsonObject toJson()const {
			QJsonObject jobj;
			return jobj;
		}

		virtual bool fromJson(QJsonObject& jobj, QString& err) {
			return true;
		}


		void updateStatus(E_SunnyTcsActionStatus status) {
			_status = status;
			_isUpdated = true;
		}

		void setStatus(E_SunnyTcsActionStatus status) {
			_status = status;
		}

		QString toString()const;

	protected:
		qint16 _commandId; //ָ��ID
		QString _commandCode;//ָ����
		E_ARG_TYPE _paramType; //��������
		SunnyTcsParamsSet _params;//������
		bool _isInOrder;//�Ƿ�Ϊʱ��ָ��
		bool _isUpdated;//�Ƿ�����ˣ������˾ͷ���ȥ
		E_SunnyTcsActionType _actionType;//ָ������
		E_SunnyTcsActionStatus _status;//ָ��״̬
	};


}

	
	
		
	
	
	






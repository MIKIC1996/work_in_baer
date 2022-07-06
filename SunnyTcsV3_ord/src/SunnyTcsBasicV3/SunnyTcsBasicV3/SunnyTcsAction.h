#pragma once


#include "SunnyTcsTypeArg.h"
#include "SunnyTcsMapGeneral.hpp"




namespace basic {

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
		SunnyTcsArg,
		SunnyTcsArg
	> SunnyTcsParamsSet;

	//ָ�������������������
	static constexpr qint32 actionParamsSetMax = std::tuple_size<SunnyTcsParamsSet>::value;

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
			std::get<_Index>(t) = SunnyTcsArg(0);
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
	class SUNNYTCSBASICV3_EXPORT A_SunnyTcsCommand {
	public:
		static constexpr qint32 action_params_count = actionParamsSetMax;
		static QMap<E_ARG_TYPE, QString> supportArgTyps;
		static bool mapInitFunc();
		static bool mapInit;
	}; 


	//ָ��
	class SUNNYTCSBASICV3_EXPORT SunnyTcsAction:public A_SunnyTcsCommand
	{
	public:
		static QMap<QString, SunnyTcsAction> actionSample;//��֧�ֵ�ָ������
		static bool sampleInitFunc();
		static bool sampleInit;
		

		//default ctor
		SunnyTcsAction();
		//ctor ����ָ���������ͣ�ָ��ID,ָ����
		explicit SunnyTcsAction(qint16 commandId, QString commandCode, QString description="");
		//copy ctor
		SunnyTcsAction(const SunnyTcsAction&) = default;
		//detor
		virtual ~SunnyTcsAction() {}
		//operator =
		SunnyTcsAction& operator=(const SunnyTcsAction&) = default;
		//operator ==
		bool operator==(const SunnyTcsAction& rhs) const;

		//getter
		inline qint16 getCommandId()const { return _commandId; }
		inline QString getCommandCode()const { return _commandCode; }
		inline E_SunnyTcsActionStatus getCommandStatus()const { return _status; }
		inline E_SunnyTcsActionType getCommandType()const { return _actionType; }
		inline QString getDescription()const { return _description; }

		inline bool isInOrder()const { return _isInOrder; }
		inline bool isUpdated()const { return _isUpdated; }
		template<int index>
		SunnyTcsArg getParam_meta()const { return std::get<index>(_params);}
		SunnyTcsArg getParam(int ct) {
			Q_ASSERT(ct >= 0 && ct <= SunnyTcsAction::action_params_count);
			return getParam_aux<SunnyTcsParamsSet>(ct, _params);
		}

		//setter
		void setOrder(bool is) { _isInOrder = is; }
		void setUpdated(bool is) { _isUpdated = is; }
		void setCommandCode(QString code) { _commandCode = code; }
		void setCommandId(qint16 cid) { _commandId = cid; }
		void updateStatus(E_SunnyTcsActionStatus status) {
			_status = status;
			_isUpdated = true;
		}
		void setStatus(E_SunnyTcsActionStatus status) { _status = status; }
		//���ò���
		template<int index,typename T>
		void setParams_meta(const T& value) {
			SunnyTcsArg vtoa(value);
			std::get<index>(_params) = value;
		}

		template<typename _Ty>
		void setParams(int ct, const _Ty val) {
			setParam_aux(ct, _params, val);
		}
		
		//json
		virtual QJsonObject toJson()const;
		virtual bool fromJson(QJsonObject& jobj, QString& err);
		//��ȡ������Ϣ
		QString toString()const;

	protected:
		//����tuple��ʵ��ԭ��д�������л�ȡ�����ĺ���
		template<typename _tupleTy>
		SunnyTcsArg getParam_aux(int ct, _tupleTy& tup)
		{
			using base = typename _tupleTy::_Mybase;
			return ct == 0 ? std::get<0>(tup) : getParam_aux(ct - 1, (base&)(tup));
		}


		SunnyTcsArg getParam_aux(int ct, std::tuple<SunnyTcsArg>& tup) {
			Q_ASSERT(ct == 0);
			return std::get<0>(tup);
		}

		template<typename _tupleTy,typename _Ty>
		void setParam_aux(int ct, _tupleTy& tup, const _Ty& val) {
			using base = typename _tupleTy::_Mybase;
			ct == 0 ? std::get<0>(tup)=val : setParam_aux(ct - 1, (base&)tup ,val);
			
		}

		template< typename _Ty>
		void setParam_aux(int ct, std::tuple<SunnyTcsArg>& tup, const _Ty& val) {
			Q_ASSERT(ct == 0);
			std::get<0>(tup) = val;
		}

		//���л�����غ���
		template<int index = 0>
		void getParamsJsonArray(QJsonArray& jobj) const{
			jobj.append(std::get<index>(_params).toJson());
			getParamsJsonArray<index + 1>(jobj);
		}

		template<>
		void getParamsJsonArray<action_params_count - 1>(QJsonArray& jobj) const{
			jobj.append(std::get<action_params_count - 1>(_params).toJson());
		}

		template<int index =0>
		bool setParamsByJsonArray(QJsonArray& jarr ,QString& err) {
			if (!SunnyTcsTypeArgBuilder::buildTypeArgFromJson(std::get<index>(_params), jarr[index].toObject(),err))return false;
			return setParamsByJsonArray<index + 1>(jarr,err);
		}

		template<>
		bool setParamsByJsonArray<action_params_count - 1>(QJsonArray& jarr, QString& err) {
			return SunnyTcsTypeArgBuilder::buildTypeArgFromJson(std::get<action_params_count - 1>(_params), jarr[action_params_count - 1].toObject(), err);
		}

	protected:
		qint16 _commandId; //ָ��ID
		QString _commandCode;//ָ����
		QString _description;//ָ������
		SunnyTcsParamsSet _params;//������
		bool _isInOrder;//�Ƿ�Ϊʱ��ָ��
		bool _isUpdated;//�Ƿ�����ˣ������˾ͷ���ȥ
		E_SunnyTcsActionType _actionType;//ָ������
		E_SunnyTcsActionStatus _status;//ָ��״̬
	};


}

	
	
		
	
	
	






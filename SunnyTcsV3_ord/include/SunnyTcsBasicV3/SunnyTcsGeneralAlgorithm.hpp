#pragma once
#include "SunnyTcsMapActualData.hpp"
#include "SunnyTcsCraft.h"

namespace basic {

	//�������ӿ�
	class I_SunnyTcsDispatchAlgorithm {
	public:
		explicit I_SunnyTcsDispatchAlgorithm(qint32 id) :_algorithmId(id) {}
		I_SunnyTcsDispatchAlgorithm(const I_SunnyTcsDispatchAlgorithm&) = delete;
		virtual ~I_SunnyTcsDispatchAlgorithm() {}
		I_SunnyTcsDispatchAlgorithm& operator=(const I_SunnyTcsDispatchAlgorithm&) = delete;

		virtual bool dispatch(basic::SunnyTcsCraft& route, basic::I_SunnyTcsActualData* data, qint32& targetAgv) = 0;

		virtual inline qint32 getId()const {
			return _algorithmId;
		}

	protected:
		qint32 _algorithmId;//�㷨ID;
	};


	//·���滮���ӿ�
	class I_SunnyTcsRouteAlgorithm {
	public:
		explicit I_SunnyTcsRouteAlgorithm(qint32 id) :_routerId(id){}
		I_SunnyTcsRouteAlgorithm(const I_SunnyTcsRouteAlgorithm&) = delete;
		virtual ~I_SunnyTcsRouteAlgorithm() {}
		I_SunnyTcsRouteAlgorithm& operator=(const I_SunnyTcsRouteAlgorithm&) = delete;

		//flag��־λ���㷨���Լ�ȥ����
		virtual bool route(basic::SunnyTcsCraft& route, basic::I_SunnyTcsActualData* data) = 0;

		virtual inline qint32 getId()const {
			return _routerId;
		}
	
	protected:
		qint32 _routerId;

	};


}
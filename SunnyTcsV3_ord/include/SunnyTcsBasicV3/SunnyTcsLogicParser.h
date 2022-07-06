#pragma once
#include "SunnyTcsVagueCondition.h"

namespace basic {


	//������ʽ�������ӿ�
	class  I_SunnyTcsLogicParser
	{
	public:
		I_SunnyTcsLogicParser() {}
		I_SunnyTcsLogicParser(const I_SunnyTcsLogicParser&) = delete;
		virtual ~I_SunnyTcsLogicParser() {}
		I_SunnyTcsLogicParser& operator=(const I_SunnyTcsLogicParser&) = delete;

		virtual std::shared_ptr<I_SunnyTcsCondition> parseLogicStr(QString str, QString& err)const = 0;
	};


}




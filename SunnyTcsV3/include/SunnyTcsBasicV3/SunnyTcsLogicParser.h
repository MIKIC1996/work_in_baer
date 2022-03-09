#pragma once
#include "SunnyTcsVagueCondition.h"

namespace basic {


	//正则表达式解析器接口
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




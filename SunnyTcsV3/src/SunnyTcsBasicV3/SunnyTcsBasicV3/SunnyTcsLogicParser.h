#pragma once
#include "SunnyTcsVagueCondition.h"

namespace basic {


	//条件表达式解析器接口
	class  I_SunnyTcsLogicParser
	{
	public:
		I_SunnyTcsLogicParser() {}
		I_SunnyTcsLogicParser(const I_SunnyTcsLogicParser&) = delete;
		virtual ~I_SunnyTcsLogicParser() {}
		I_SunnyTcsLogicParser& operator=(const I_SunnyTcsLogicParser&) = delete;

		virtual std::shared_ptr<I_SunnyTcsCondition> parseLogicStr(QString str, QString& err)const = 0;
	};



	// 基于正则表达式的条件表达式解析器实现
	//字符串案例
	//{ {[<AGV>(ID = 1,POS=300)(ERROR=1)] || [<AGV>(ID = 1,POS=300)(ERROR=1)]} && [<AGV>(ID=1,POS=300)(ERROR=1)] } && [<AGV>(ID=1,POS=300)(ERROR=1)]"
	class SUNNYTCSBASICV3_EXPORT SunnyTcsCoreLogicParser :public I_SunnyTcsLogicParser
	{
	public:
		typedef SunnyTcsSingleCondition SingleConditon;

		// 通过 I_SunnyTcsLogicParser 继承
		virtual std::shared_ptr<I_SunnyTcsCondition> parseLogicStr(QString str, QString& err) const override { return nullptr; }
		
		//分析单个条件
		virtual std::shared_ptr<I_SunnyTcsCondition> parseSingleConditionStr(QString str, QString& err) const { return nullptr; }
		
	};


}




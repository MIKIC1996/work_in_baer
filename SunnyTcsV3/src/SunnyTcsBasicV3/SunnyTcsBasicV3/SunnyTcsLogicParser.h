#pragma once
#include "SunnyTcsVagueCondition.h"

namespace basic {


	//�������ʽ�������ӿ�
	class  I_SunnyTcsLogicParser
	{
	public:
		I_SunnyTcsLogicParser() {}
		I_SunnyTcsLogicParser(const I_SunnyTcsLogicParser&) = delete;
		virtual ~I_SunnyTcsLogicParser() {}
		I_SunnyTcsLogicParser& operator=(const I_SunnyTcsLogicParser&) = delete;

		virtual std::shared_ptr<I_SunnyTcsCondition> parseLogicStr(QString str, QString& err)const = 0;
	};



	// ����������ʽ���������ʽ������ʵ��
	//�ַ�������
	//{ {[<AGV>(ID = 1,POS=300)(ERROR=1)] || [<AGV>(ID = 1,POS=300)(ERROR=1)]} && [<AGV>(ID=1,POS=300)(ERROR=1)] } && [<AGV>(ID=1,POS=300)(ERROR=1)]"
	class SUNNYTCSBASICV3_EXPORT SunnyTcsCoreLogicParser :public I_SunnyTcsLogicParser
	{
	public:
		typedef SunnyTcsSingleCondition SingleConditon;

		// ͨ�� I_SunnyTcsLogicParser �̳�
		virtual std::shared_ptr<I_SunnyTcsCondition> parseLogicStr(QString str, QString& err) const override { return nullptr; }
		
		//������������
		virtual std::shared_ptr<I_SunnyTcsCondition> parseSingleConditionStr(QString str, QString& err) const { return nullptr; }
		
	};


}




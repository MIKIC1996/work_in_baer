#include "SunnyTcsMapModel.h"


namespace core {


	SunnyTcsMapModel::SunnyTcsMapModel(
		std::shared_ptr<I_SunnyTcsRunner> runner,
		std::shared_ptr<I_SunnyTcsCraftAgency> agency,
		std::shared_ptr<I_SunnyTcsMsgSender> sender,
		std::shared_ptr<I_SunnyTcsLogger> loger)
		:A_SunnyTcsModelData(nullptr),
		I_SunnyTcsActualData(),
		I_SunnyTcsExecutor(runner),
		I_SunnyTcsCraftRecivier(NODE_ID_MODEL, agency),
		I_SunnyTcsMsgMember(NODE_ID_MODEL, sender),
		I_SunnyTcsLoggerUser(loger)
		
	{
		//model Ҫִ����Щ����
		/*
			1.model Ҫ��ͨѶ�� ��������Ϣ���д��������Գ� ����· ����� �޸ĸ��¡� ������Խ��������߳�ȥ������ôÿ����Դ��Ҫ���� ��
			2.model �� ��·���㣬�� ����ȫ���ƣ����� ִ�������ܷ��ʣ�ֻ��ͨ��agvStat�� vertex �� Edge ��ӷ����� ���ݣ���������������ȡ��������ʱ����Ҫ������ÿ����Դ����
				�������������ִ�����߳�ִ�У���Ҫ�����̰߳�ȫ��
			3.model �Զ��� ���У�ȡ��ͷ���д�������model���߳�����{
				�Զ���������Ҫ�����������ڳ��� �����������⣬ֻ��һ��ִ�������Է��� ���������������� ����
			
			}
		*/
	}

	SunnyTcsMapModel::~SunnyTcsMapModel()
	{
	}

	bool SunnyTcsMapModel::judgeSingleCondition(const SunnyTcsSingleCondition & conditon) const
	{
		return false;
	}

	void SunnyTcsMapModel::agvStats(QMap<qint32, SunnyTcsAgvStat>& ref) const
	{
	}

	void SunnyTcsMapModel::points(QMap<qint32, SunnyTcsVertex>& ref) const
	{
	}

	void SunnyTcsMapModel::paths(QMap<qint32, SunnyTcsEdge>& ref) const
	{
	}

	void SunnyTcsMapModel::uls(QString ulsCode, QMap<qint32, SunnyTcsUlsData>& ref) const
	{
	}










}



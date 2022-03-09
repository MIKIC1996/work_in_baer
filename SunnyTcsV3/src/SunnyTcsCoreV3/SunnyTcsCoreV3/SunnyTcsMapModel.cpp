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
		//model 要执行那些事情
		/*
			1.model 要对通讯器 传来的消息进行处理，包括对车 、线路 、点的 修改更新。 这个可以交给额外线程去做，那么每个资源都要上锁 ，
			2.model 对 线路，点，车 有完全控制，其他 执行器不能访问，只能通过agvStat、 vertex 和 Edge 间接访问其 数据（拷贝副本），获取所有数据时，需要轮流对每个资源上锁
				这个操作由其他执行器线程执行，需要考虑线程安全。
			3.model 对订单 队列，取其头进行处理，这是model主线程任务{
				对订单对象需要先上锁，由于除了 订单中心以外，只有一款执行器可以访问 这个订单，不会出现 死锁
			
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



#include "SunnyTcsDispatcher.h"


namespace core {


	/*执行器范式
	while (1) {
	_que.lock
	if(_que.count()==0){  //辅助线程退出
	_que.unlock;
	continue;
	}
	ptr = _que.first

	if (ptr.trylock) { //锁定成功，
	if(ptr.status != OK)//状态不正确
	{
	_que.popfirst;//扔出去
	_center->insertToMap();//插到对应的队列里面
	_que.unlock;
	}
	else {//正确
	_que.pushBack(ptr);
	_que.popfirst;//扔到最后面
	_que.unlock;
	ptr处理。。。
	ptr->unlock();
	}
	}
	else  {//订单锁失败 //辅助线程退出
	_que.pushBack(ptr);
	_que.popfirst;//扔到最后面
	_que.unlock;
	continue //去遍历第二个
	}
	}
	*/


	A_SunnyTcsDispatcher::A_SunnyTcsDispatcher(std::shared_ptr<I_SunnyTcsActualData> acData,
		std::shared_ptr<I_SunnyTcsRunner> runner,
		std::shared_ptr<I_SunnyTcsCraftAgency> agency,
		std::shared_ptr<I_SunnyTcsMsgSender> sender,
		std::shared_ptr<I_SunnyTcsLogger> loger)
		:I_SunnyTcsExecutor(runner),
		I_SunnyTcsCraftRecivier(NODE_ID_DISPATCHER,agency),
		I_SunnyTcsMsgMember(NODE_ID_DISPATCHER,sender),
		I_SunnyTcsLoggerUser(loger)
	{

	}

	A_SunnyTcsDispatcher::~A_SunnyTcsDispatcher()
	{

	}


	SunnyTcsDispatcher_general::SunnyTcsDispatcher_general(
		std::shared_ptr<I_SunnyTcsActualData> acData,
		std::shared_ptr<I_SunnyTcsRunner> runner,
		std::shared_ptr<I_SunnyTcsCraftAgency> agency,
		std::shared_ptr<I_SunnyTcsMsgSender> sender,
		std::shared_ptr<I_SunnyTcsLogger> loger)
		:A_SunnyTcsDispatcher(acData,runner,agency,sender,loger)
	{
	}


	void SunnyTcsDispatcher_general::msgHandle()
	{
	}


}



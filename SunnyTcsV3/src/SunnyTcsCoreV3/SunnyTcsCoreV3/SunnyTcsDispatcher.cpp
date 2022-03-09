#include "SunnyTcsDispatcher.h"


namespace core {


	/*ִ������ʽ
	while (1) {
	_que.lock
	if(_que.count()==0){  //�����߳��˳�
	_que.unlock;
	continue;
	}
	ptr = _que.first

	if (ptr.trylock) { //�����ɹ���
	if(ptr.status != OK)//״̬����ȷ
	{
	_que.popfirst;//�ӳ�ȥ
	_center->insertToMap();//�嵽��Ӧ�Ķ�������
	_que.unlock;
	}
	else {//��ȷ
	_que.pushBack(ptr);
	_que.popfirst;//�ӵ������
	_que.unlock;
	ptr��������
	ptr->unlock();
	}
	}
	else  {//������ʧ�� //�����߳��˳�
	_que.pushBack(ptr);
	_que.popfirst;//�ӵ������
	_que.unlock;
	continue //ȥ�����ڶ���
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



#pragma once

#include "SunnyTcsDataCenterGeneral.hpp"

using namespace basic;

//�������־�����
typedef SunnyTcsThreadSeed_basic<bool(int /* �����������ָ��ÿ�����д�����ٴβ�ѯ���� */ )> SunnyTcsDbThreadSeed_bool_int;  
typedef SunnyTcsThreadSeed_basic<void(int)> SunnyTcsDbThreadSeed_void_int;


//�����Ƿ���Ҫ����ѯ�ɹ���񷵻� ѡ����ʵ�seed
#define DB_DRIVER_NEED_RET

#ifdef DB_DRIVER_NEED_RET
static constexpr bool needRet = true;
#else
static constexpr bool needRet = false;
#endif // DEBUG

using SunnyTcsDbThreadSeed_default = typename std::_If<needRet, SunnyTcsDbThreadSeed_bool_int, SunnyTcsDbThreadSeed_void_int>::type;


//datacenter �Ĺ����߳�
class SunnyTcsDbDriver 
	: protected SunnyTcsDbThreadSeed_default,/*�����̳У����ֱ�ӵ�seed�������޷���֤�̰߳�ȫ*/
	  public QThread
{
public:
	SunnyTcsDbDriver();
	virtual ~SunnyTcsDbDriver();

	//�̳�QThread
	virtual void run() override;

	template< typename _Callable,typename... _Args> //����ģ�岻��Ϊvirtual�����Բ��ö���driver�ӿڣ���ֹ�˶�̬�������_callable����Ϊ std::function<bool(void)>...,�о�̫����
	void submitToDriver(_Callable&& f , _Args... num) //����ת�����ã�Ϊ�˱�֤�̰߳�ȫ
	{
		std::lock_guard<QMutex> guard(_lock); //��Ӷ��̱߳���
		this->submit(std::forward<_Callable>(f), std::forward<_Args>(num)...);
	}

	void* getResultBufferPtr() {
		return this->getResultPtr();
	}

protected:
	QMutex _lock;//�Է���һ
};


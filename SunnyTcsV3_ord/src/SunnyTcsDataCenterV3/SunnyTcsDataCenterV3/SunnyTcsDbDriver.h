#pragma once

#include "SunnyTcsDataCenterGeneral.hpp"

using namespace basic;

//下面两种均可以
typedef SunnyTcsThreadSeed_basic<bool(int /* 这个参数用于指定每次运行处理多少次查询请求 */ )> SunnyTcsDbThreadSeed_bool_int;  
typedef SunnyTcsThreadSeed_basic<void(int)> SunnyTcsDbThreadSeed_void_int;


//按照是否需要将查询成功与否返回 选择合适的seed
#define DB_DRIVER_NEED_RET

#ifdef DB_DRIVER_NEED_RET
static constexpr bool needRet = true;
#else
static constexpr bool needRet = false;
#endif // DEBUG

using SunnyTcsDbThreadSeed_default = typename std::_If<needRet, SunnyTcsDbThreadSeed_bool_int, SunnyTcsDbThreadSeed_void_int>::type;


//datacenter 的工作线程
class SunnyTcsDbDriver 
	: protected SunnyTcsDbThreadSeed_default,/*保护继承，外界直接调seed函数，无法保证线程安全*/
	  public QThread
{
public:
	SunnyTcsDbDriver();
	virtual ~SunnyTcsDbDriver();

	//继承QThread
	virtual void run() override;

	template< typename _Callable,typename... _Args> //函数模板不能为virtual，所以不好定义driver接口，阻止了多态，如果把_callable定死为 std::function<bool(void)>...,感觉太笨重
	void submitToDriver(_Callable&& f , _Args... num) //参数转发调用，为了保证线程安全
	{
		std::lock_guard<QMutex> guard(_lock); //添加多线程保护
		this->submit(std::forward<_Callable>(f), std::forward<_Args>(num)...);
	}

	void* getResultBufferPtr() {
		return this->getResultPtr();
	}

protected:
	QMutex _lock;//以防万一
};


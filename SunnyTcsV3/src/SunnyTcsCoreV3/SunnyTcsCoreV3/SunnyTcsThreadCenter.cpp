#include "SunnyTcsThreadCenter.h"


core::SunnyTcsThreadCenter::SunnyTcsThreadCenter(qint32 count, qint32 msleep)
	:_count(count)
{
	for (int i = 0; i < count; ++i) {
		_seeds.append(std::make_shared<SunnyTcsCoreSeed>(msleep));
	}
}


void core::SunnyTcsThreadCenter::submitTask(SunnyTcsCoreSeed::Task func, int cirCount, bool isMainLine)
{
	int freeSeedIndex = 0;
	int currentMostFree = INT_MAX;
	//Ñ°ÕÒ×î¿ÕÏÐµÄseed
	std::for_each(_seeds.begin(), _seeds.end(), [&freeSeedIndex, &currentMostFree, this](std::shared_ptr<SunnyTcsCoreSeed> ptr)->void {
		if (ptr->getLoad() < currentMostFree) {
			freeSeedIndex = _seeds.indexOf(ptr);
		}
	});

	bool isSubmited = false;
	while (!isSubmited) {
		//³¢ÊÔËø
		if (_seeds[freeSeedIndex]->tryLock()) {
			_seeds[freeSeedIndex]->submit(func,cirCount,isMainLine);
			_seeds[freeSeedIndex]->unlock();
			isSubmited = true;
		}else {//ËøÊ§°Ü¾ÍÊÔÊÔÏÂÒ»¸ö
			freeSeedIndex = ((freeSeedIndex + 1 >= _count) ? 0 : (freeSeedIndex + 1));
		}
	}
}
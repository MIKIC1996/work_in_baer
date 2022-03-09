#include "SunnyTcsDbDriver.h"



SunnyTcsDbDriver::SunnyTcsDbDriver()
	:SunnyTcsDbThreadSeed_default(),QThread()
{
}


SunnyTcsDbDriver::~SunnyTcsDbDriver()
{
}



void SunnyTcsDbDriver::run() 
{
	while (!isInterruptionRequested()) {
		this->work();
		this->msleep(100); //����100ms
	}
	quit();
	wait();
}

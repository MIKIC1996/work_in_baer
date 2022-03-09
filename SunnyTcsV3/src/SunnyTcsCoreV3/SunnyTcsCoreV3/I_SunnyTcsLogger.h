#pragma once
#include "SunnyTcsCoreV3.h"
#include "I_SunnyTcsRunner.h"

namespace core {


	//ÈÕÖ¾¼ÇÂ¼Æ÷
	class I_SunnyTcsLogger:public I_SunnyTcsExecutor{
	public:
		I_SunnyTcsLogger(std::shared_ptr<I_SunnyTcsRunner> runner);
		I_SunnyTcsLogger(const I_SunnyTcsExecutor&) = delete;
		virtual ~I_SunnyTcsLogger() {}
		I_SunnyTcsLogger& operator=(const I_SunnyTcsLogger&) = delete;

		virtual void logInfo(QString& info) = 0;

	};


	class I_SunnyTcsLoggerUser {
	public:
		I_SunnyTcsLoggerUser(std::shared_ptr<I_SunnyTcsLogger> loger) :_logger(loger) {}

		virtual void recordLog(QString& info) {
			_logger->logInfo(info);
		}

	protected:
		std::shared_ptr< I_SunnyTcsLogger> _logger;
	};



}



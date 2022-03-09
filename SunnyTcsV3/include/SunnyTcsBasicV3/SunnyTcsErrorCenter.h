#pragma once
#include "sunnytcsbasicv3_global.h"

namespace basic {


	class SunnyTcsErrorCenter
	{
	public:
		//根据错误码查询错误描述，没有就返回空
		static QString searchDescriptionByCode(QString errCode) {
			std::lock_guard<std::mutex> guard(_lock);
			if (!_errorMap->keys().contains(errCode)) {
				return QString();
			}
			return (*_errorMap)[errCode];

		}

		//对错误信息的注册
		static bool registerErrorCode(QString code, QString description) {
			std::lock_guard<std::mutex> guard(_lock);
			if (!_errorMap) {
				_errorMap = new QMap<QString, QString>();
			}
			if (_errorMap->keys().contains(code)) {
				return false;
			}
			_errorMap->insert(code, description);
			return true;
		}

		//摧毁
		static void destory() {
			std::lock_guard<std::mutex> guard(_lock);
			delete _errorMap;
			_errorMap = nullptr;
		}

		SunnyTcsErrorCenter() {}
		virtual ~SunnyTcsErrorCenter() {}

	protected:
		static std::mutex _lock;
		static QMap<QString, QString>* _errorMap;//错误表

	};

}




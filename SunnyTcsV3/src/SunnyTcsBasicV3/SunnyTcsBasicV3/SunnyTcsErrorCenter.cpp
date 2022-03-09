#include "SunnyTcsErrorCenter.h"

std::mutex basic::SunnyTcsErrorCenter::_lock;

QMap<QString, QString>* basic::SunnyTcsErrorCenter::_errorMap = nullptr;
#include "SunnyTcsLogicInfo.h"

namespace basic {

		QMap<qint64, E_ARG_TYPE> SunnyTcsLogicInfo::_conditionId_argType;
		QMap<qint64, qint64> SunnyTcsLogicInfo::_conditionId_compareOpe;
		QMap<E_SunnyTcsMapObject_type, qint64> SunnyTcsLogicInfo::_conditionTar_conditionId;
		QMap<QString, qint64> SunnyTcsLogicInfo::_conditionStr_conditionId;
		QMap<QString, E_SunnyTcsLogicOperation> SunnyTcsLogicInfo::_logicOpeStr_logOpe;
		QMap<QString, E_SunnyTcsComparisonOperation> SunnyTcsLogicInfo::_compareOpeStr_compareOpe;
		QMap<QString, E_SunnyTcsMapObject_type> SunnyTcsLogicInfo::_conditionTarStr_conditionTar;
		bool SunnyTcsLogicInfo::_inited = SunnyTcsLogicInfo::init();
	
}

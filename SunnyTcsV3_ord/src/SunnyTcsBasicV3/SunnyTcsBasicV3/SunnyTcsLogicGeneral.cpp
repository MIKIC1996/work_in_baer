#include "SunnyTcsLogicGeneral.hpp"

void basic::SunnyTcsConditionValue::bindDealFuncByConditionId(qint32 conditionId)
{
	if (conditionId == CONDITION_ID) {
		_checkFuncPtr = SunnyTcsLogicBase<CONDITION_ID>::check_aux;
		_getTargetFuncPtr = SunnyTcsLogicBase<CONDITION_ID>::getTarget_aux;
		_operateFuncPtr = SunnyTcsLogicBase<CONDITION_ID>::operate_aux;
	}
	else if (conditionId == CONDITION_ABSPOS) {
		_checkFuncPtr = SunnyTcsLogicBase<CONDITION_ABSPOS>::check_aux;
		_getTargetFuncPtr = SunnyTcsLogicBase<CONDITION_ABSPOS>::getTarget_aux;
		_operateFuncPtr = SunnyTcsLogicBase<CONDITION_ABSPOS>::operate_aux;
	}
	else if (conditionId == CONDITION_RX) {
		_checkFuncPtr = SunnyTcsLogicBase<CONDITION_RX>::check_aux;
		_getTargetFuncPtr = SunnyTcsLogicBase<CONDITION_RX>::getTarget_aux;
		_operateFuncPtr = SunnyTcsLogicBase<CONDITION_RX>::operate_aux;
	}
	else if (conditionId == CONDITION_RY) {
		_checkFuncPtr = SunnyTcsLogicBase<CONDITION_RY>::check_aux;
		_getTargetFuncPtr = SunnyTcsLogicBase<CONDITION_RY>::getTarget_aux;
		_operateFuncPtr = SunnyTcsLogicBase<CONDITION_RY>::operate_aux;
	}
	else if (conditionId == CONDITION_LIFT) {
		_checkFuncPtr = SunnyTcsLogicBase<CONDITION_LIFT>::check_aux;
		_getTargetFuncPtr = SunnyTcsLogicBase<CONDITION_LIFT>::getTarget_aux;
		_operateFuncPtr = SunnyTcsLogicBase<CONDITION_LIFT>::operate_aux;
	}
	else if (conditionId == CONDITION_ERROR) {
		_checkFuncPtr = SunnyTcsLogicBase<CONDITION_ERROR>::check_aux;
		_getTargetFuncPtr = SunnyTcsLogicBase<CONDITION_ERROR>::getTarget_aux;
		_operateFuncPtr = SunnyTcsLogicBase<CONDITION_ERROR>::operate_aux;
	}
}

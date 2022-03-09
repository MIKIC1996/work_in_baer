#pragma once
#include "SunnyTcsCoreV3.h"





using namespace basic;

namespace core {



	//字符串案例
	//{ {[<AGV>(ID = 1,POS=300)(ERROR=1)] || [<AGV>(ID = 1,POS=300)(ERROR=1)]} && [<AGV>(ID=1,POS=300)(ERROR=1)] } && [<AGV>(ID=1,POS=300)(ERROR=1)]"
	class SUNNYTCSCOREV3_EXPORT SunnyTcsCoreLogicParser :public I_SunnyTcsLogicParser
	{
	public:
		typedef SunnyTcsSingleCondition SingleConditon;


		// 通过 I_SunnyTcsLogicParser 继承
		virtual std::shared_ptr<I_SunnyTcsCondition> parseLogicStr(QString str, QString & err) const override
		{
			QString proto = str;
			qint32 counter = 0;
			QMap<qint32, std::shared_ptr<I_SunnyTcsCondition>> singlesAndVagues;

			//singles
			QRegExp exp1("\\[<\\w+>\\(.+\\)\\(.+\\)\\]");
			int pos = 0;
			while ((pos = exp1.indexIn(proto, pos)) != -1) {
				std::shared_ptr<I_SunnyTcsCondition> singleConditionPtr = parseSingleConditionStr(exp1.cap(0), err);
				if (!singleConditionPtr) {
					err = "";
					return nullptr;
				}
				singlesAndVagues.insert(counter, singleConditionPtr);

				pos += exp1.matchedLength();
				int index = str.indexOf(exp1.cap(0));
				str.replace(index, exp1.cap(0).count(), QString::number(counter));
				++counter;
			}
			//str = {1& {2|3} }

			QString temp = str;
			QRegExp exp2(("\\{[^\\{\\}]+\\}"));
			QRegExp exp3("[\\d+");
			QRegExp exp4("[&|]");
			pos = 0;
			int pos2 = 0;
			//{1|2&3}
			while ((exp2.indexIn(temp)) != -1) {
				std::shared_ptr<SunnyTcsVagueCondition> vague = std::make_shared<SunnyTcsVagueCondition>();//vague对象
				QString tempStr = exp2.cap(0);
				pos2 = 0;
				while ((pos2 = exp3.indexIn(tempStr, pos2)) != -1) {
					bool ok = true;
					qint32 key = exp3.cap(0).toInt(&ok);
					if (!ok || !singlesAndVagues.keys().contains(key)) {
						err = "";
						return nullptr;
					}
					vague->appendCondition(singlesAndVagues[key]);

					pos2 += exp3.matchedLength();

				}
				pos2 = 0;
				while ((pos2 = exp4.indexIn(tempStr, pos2)) != -1) {
					if (exp4.cap(0) == CONDITION_LOGICOPE_AND_STR) {
						vague->appendOperation(E_AND);
					}
					else {
						vague->appendOperation(E_OR);
					}
					pos2 += exp4.matchedLength();
				}

				if (vague->conditionCount() != vague->operationCount() + 1) {
					err = "";
					return nullptr;
				}
				singlesAndVagues.insert(counter, vague);
				temp.replace(temp.indexOf(tempStr), tempStr.count(), QString::number(counter));//不要去改str
				++counter;
			}

			return singlesAndVagues[--counter];
		}



		//分析单个条件
		virtual std::shared_ptr<I_SunnyTcsCondition> parseSingleConditionStr(QString str, QString& err) const
		{
			QRegExp exp1("\\[<\\w+>\\(.+\\)\\(.+\\)\\]");
			if (exp1.indexIn(str) == -1) {
				err = "";
				return nullptr;
			}

			//对单个条件进行详细解析
			QRegExp exp2("<[^<>]+>");
			std::shared_ptr<SingleConditon> conditionPtr;
			//target解析
			if (exp2.indexIn(str) != -1) {
				QString tarStr = exp2.cap(0);
				tarStr = tarStr.mid(1, tarStr.count() - 2);
				if (tarStr == CONDITION_TAR_AGV) {
					conditionPtr = std::make_shared<SingleConditon>(target_agv);
				}
				else if (tarStr == CONDITION_TAR_LINE) {
					conditionPtr = std::make_shared<SingleConditon>(target_line);
				}
				else if (tarStr == CONDITION_TAR_POINT) {
					conditionPtr = std::make_shared<SingleConditon>(target_point);
				}
				else if (tarStr == CONDITION_TAR_PATH) {
					conditionPtr = std::make_shared<SingleConditon>(target_path);
				}
				else if (tarStr == CONDITION_TAR_DEVICE) {
					conditionPtr = std::make_shared<SingleConditon>(target_device);
				}
				else {
					err = "";
					return nullptr;
				}
			}
			else {//没有指定tar
				err = "no tar get";
				return nullptr;
			}


			//prefix and suffix解析
			QRegExp exp3("\\([^\\(\\)]+\\)");
			QRegExp exp4("[\\(,]{1}[^\\(\\),]+[\\),]{1}");
			QRegExp exp5(" \w+[^=!<>&|] ");
			int pos = 0;
			int pos2 = 0;
			bool isPrefixFinished = false;
			//(error==1,pos==1)
			while ((pos = exp3.indexIn(str, pos)) != -1) {
				QString presuf = exp3.cap(0);
				pos2 = 0;
				//对prefix 和 suffix 中的 单条件进行处理 error==1
				while ((pos2 = exp4.indexIn(presuf, pos2)) != -1) {
					QString sc = exp4.cap(0).mid(1, exp4.cap(0).count() - 2);
					//error
					QRegExp exp5("\\w+");
					int tempPos = exp5.indexIn(sc);
					if (tempPos == -1) {
						err = "";
						return nullptr;
					}
					QString conditionIdStr = exp5.cap(0);
					if (!SunnyTcsLogicInfo::get_conditionStr_conditionId_map().keys().contains(conditionIdStr)) {
						err = "";
						return nullptr;
					}
					int8_t conditionId = SunnyTcsLogicInfo::get_conditionStr_conditionId_map()[conditionIdStr];

					//==
					QRegExp exp6("[!=&|<>]+");
					tempPos = exp6.indexIn(sc);
					if (tempPos == -1) {
						err = "";
						return nullptr;
					}
					QString compareOpeStr = exp6.cap(0);
					if (!SunnyTcsLogicInfo::get_compareOpeStr_compareOpe_map().keys().contains(compareOpeStr)) {
						err = "";
						return nullptr;
					}
					E_SunnyTcsComparisonOperation ope = SunnyTcsLogicInfo::get_compareOpeStr_compareOpe_map()[compareOpeStr];
					if (!SunnyTcsLogicInfo::get_conditionId_compareOpe_map()[conditionId].contains(ope)) {
						err = "";
						return nullptr;
					}

					// 1
					QRegExp exp7("[!=&|<>]{1}\\w+");
					tempPos = exp7.indexIn(sc);
					if (tempPos == -1) {
						err = "";
						return nullptr;
					}
					QString valStr = exp7.cap(0).mid(1, exp7.cap(0).count() - 1);
					E_ARG_TYPE argType = SunnyTcsLogicInfo::get_conditionId_argType_map()[conditionId];
					SunnyTcsArg valArg;
					bool ok = true;
					switch (argType)
					{
					case ARG_UNDEFINED:
						err = "";
						return nullptr;
						break;
					case ARG_CHAR:
						err = "";
						return nullptr;
						break;
					case ARG_BOOL:
						!isPrefixFinished ?
							ok &= conditionPtr->setPrefixOption(conditionId, ope, (valStr.toInt(&ok) != 0 ? true : false)) :
							ok &= conditionPtr->setSuffixOption(conditionId, ope, (valStr.toInt(&ok) != 0 ? true : false));
						if (!ok) {
							err = "";
							return nullptr;
						}
						break;
					case ARG_MIXED:
						err = "";
						return nullptr;
						break;
					case ARG_INT8:
						!isPrefixFinished ?
							ok &= conditionPtr->setPrefixOption(conditionId, ope, static_cast<int8_t>(valStr.toShort(&ok))) :
							ok &= conditionPtr->setSuffixOption(conditionId, ope, static_cast<int8_t>(valStr.toShort(&ok)));
						if (!ok) {
							err = "";
							return nullptr;
						}
						break;
					case ARG_INT16:
						!isPrefixFinished ?
							ok &= conditionPtr->setPrefixOption(conditionId, ope, static_cast<int16_t>(valStr.toShort(&ok))) :
							ok &= conditionPtr->setSuffixOption(conditionId, ope, static_cast<int16_t>(valStr.toShort(&ok)));
						if (!ok) {
							err = "";
							return nullptr;
						}
						break;
					case ARG_INT32:
						!isPrefixFinished ?
							ok &= conditionPtr->setPrefixOption(conditionId, ope, static_cast<int32_t>(valStr.toInt(&ok))) :
							ok &= conditionPtr->setSuffixOption(conditionId, ope, static_cast<int32_t>(valStr.toInt(&ok)));
						if (!ok) {
							err = "";
							return nullptr;
						}
						break;
					case ARG_INT64:
						!isPrefixFinished ?
							ok &= conditionPtr->setPrefixOption(conditionId, ope, static_cast<int64_t>(valStr.toLongLong(&ok))) :
							ok &= conditionPtr->setSuffixOption(conditionId, ope, static_cast<int64_t>(valStr.toLongLong(&ok)));
						if (!ok) {
							err = "";
							return nullptr;
						}
						break;
					case ARG_UINT8:
						!isPrefixFinished ?
							ok &= conditionPtr->setPrefixOption(conditionId, ope, static_cast<uint8_t>(valStr.toUShort(&ok))) :
							ok &= conditionPtr->setSuffixOption(conditionId, ope, static_cast<uint8_t>(valStr.toUShort(&ok)));
						if (!ok) {
							err = "";
							return nullptr;
						}
						break;
					case ARG_UINT16:
						!isPrefixFinished ?
							ok &= conditionPtr->setPrefixOption(conditionId, ope, static_cast<uint16_t>(valStr.toUShort(&ok))) :
							ok &= conditionPtr->setSuffixOption(conditionId, ope, static_cast<uint16_t>(valStr.toUShort(&ok)));
						if (!ok) {
							err = "";
							return nullptr;
						}
						break;
					case ARG_UINT32:
						!isPrefixFinished ?
							ok &= conditionPtr->setPrefixOption(conditionId, ope, static_cast<uint32_t>(valStr.toUInt(&ok))) :
							ok &= conditionPtr->setSuffixOption(conditionId, ope, static_cast<uint32_t>(valStr.toUInt(&ok)));
						if (!ok) {
							err = "";
							return nullptr;
						}
						break;
					case ARG_UINT64:
						!isPrefixFinished ?
							ok &= conditionPtr->setPrefixOption(conditionId, ope, static_cast<uint64_t>(valStr.toULongLong(&ok))) :
							ok &= conditionPtr->setSuffixOption(conditionId, ope, static_cast<uint64_t>(valStr.toULongLong(&ok)));
						if (!ok) {
							err = "";
							return nullptr;
						}
						break;
					case ARG_QBYTEARRAY:
						err = "";
						return nullptr;
						break;
					case ARG_QSTRING:
						err = "";
						return nullptr;
						break;
					default:
						break;
					}
					pos2 += exp4.matchedLength();
					pos2 -= 2;
				}
				isPrefixFinished = true;//前缀已完成
				pos += exp3.matchedLength();
			}


			return conditionPtr;
		}




	};

}



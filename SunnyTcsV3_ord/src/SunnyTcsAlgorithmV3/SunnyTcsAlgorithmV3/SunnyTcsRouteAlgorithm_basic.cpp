#include "SunnyTcsRouteAlgorithm_basic.h"


algorithm::SunnyTcsRouteAlgorithm_basic::SunnyTcsRouteAlgorithm_basic()
	:I_SunnyTcsRouteAlgorithm(1)
{
}

bool algorithm::SunnyTcsRouteAlgorithm_basic::route(SunnyTcsCraft & route,I_SunnyTcsActualData * data)
{
// 	if (route.getCurrentStatus() != ERrouting) {
// 		route.setErrorMsg(ERROR_ALGORITHM_ROUTE_ORDER_STATUS_ERROR);
// 		return false;
// 	}
// 
//  	QMap<qint32, QList<SunnyTcsVertex>> tos;
//  	data->tos(tos);
// 
// 	//获取接下来要规划的路径
// 	SunnyTcsRoute::Pts  routeToBeRouting;
// 	route.getCurrentRoute()->getNextRouteNeedRouting(routeToBeRouting);
// 
// 	//地图加载不全，或者没有要进行规划的路径
// 	if (tos.isEmpty() || routeToBeRouting.isEmpty()) {
// 		route.setCurrentStatus(ERFailed);
// 		route.setErrorMsg(ERROR_ALGORITHM_ROUTE_ORDER_NONEED_TOROUTE);
// 		return false;
// 	}
// 	SunnyTcsRoute::Pts pts_ret;
// 	
// 	QList<qint32> ret_step;
// 	auto iter = routeToBeRouting.begin();
// 	while ( iter != routeToBeRouting.end()) {
// 		//添加该段的起点
// 		if ((iter + 1) == routeToBeRouting.end()) {
// 			pts_ret.append(*(iter + 1));
// 			break;//最后一个点不必去计算了
// 		}
// 		ret_step.clear();
// 		if (!routeBetweenTwoPoints(iter->_id, (iter + 1)->_id, data, ret_step)) {
// 			route.setCurrentStatus(ERFailed);
// 			route.setErrorMsg(ERROR_ALGORITHM_ROUTE_NOROUTE_TOPLAN);
// 			return false;
// 		}
// 		ret_step.removeLast();
// 		//移除最后一个点，ret_step如果只有一个值，就说明source==target,这时候就ret就什么都没添加，下次会自动把targe加上的
// 		bool ok = true;
// 		auto pter = ret_step.begin();
// 		while (pter != ret_step.end()) {
// 			pts_ret.append( data->getVertexById(*pter,ok));
// 			if (!ok) {
// 				route.setErrorMsg(ERROR_ALGORITHM_ROUTE_ACTUALDATA_ERROR);
// 				return false;
// 			}
// 			++pter;
// 		}
// 	}
// 	//到这一步，ret至少有一个点
// 	route.getCurrentRoute()->setNextRoute(pts_ret);
// 	route.setCurrentStatus(ERworking);//路径规划成功
	return true;
}



qint32 algorithm::SunnyTcsRouteAlgorithm_basic::getId() const
{
	return ALGORITHM_ROUTE_BASIC_ID;
}

bool algorithm::SunnyTcsRouteAlgorithm_basic::routeBetweenTwoPoints(qint32 source, qint32 target,
	basic::I_SunnyTcsActualData * data,QList<qint32>& ret)
{
// 	if (source == target) {
// 		ret.append(source);
// 		return true;
// 	}
// 
// 	QMap<qint32, QList<SunnyTcsVertex>> tos;
// 	data->tos(tos);
// 	if (tos.isEmpty()){
// 		return false;
// 	}
// 
// 	//记录前往每个点的最小花费
// 	QMap<qint32, qint32> costSoFar; //<qint32 ptId,qint32 cost>								 	
// 	costSoFar[source] = 0;							 	
// 	costSoFar[target] = INT_MAX;
// 
// 	//记录还没遍历过的 点 pair<qint32 cost,qint32 ptid>
// 	std::priority_queue < std::pair<qint32, qint32>, std::vector<std::pair<qint32, qint32>>, std::greater<std::pair<qint32, qint32>>> fronter;
// 	fronter.push(std::pair<qint32, qint32>(0, source));
// 
// 	//记录每个点的前置点
// 	QMap<qint32, qint32> cameFrom;
// 
// 	bool ok = true;
// 
//  	while (!fronter.empty())
//  	{
//  		qint32 current = fronter.top().second;
// 		fronter.pop();
//  
// 		//找到了
// 		if (current == target) {
// 			break;
// 		}
// 
// 		if (!tos.keys().contains(current)) {
// 			return false;
// 		}
// 
//  		QList<SunnyTcsVertex>& currentTos = tos[current];
// 
//  		for (SunnyTcsVertex& next : currentTos)
//  		{
// 			qint32 newCost = costSoFar[current] + data->getEdgeByFromAndTo(current, next._id, ok)._len;
// 			 
// 			if (!ok) {
// 				//不存在从current 到 next 的edge
// 				return false;
// 			}
// 
//  			
//  			if (!costSoFar.contains(next._id) || newCost < costSoFar[next._id])
// 			{
// 				costSoFar[next._id] = newCost;
// 				fronter.push(std::pair<qint32, qint32>(newCost, next._id));
// 				cameFrom[next._id] = current;
// 			}
//  		}
//  	}
// 
//  	if (cameFrom.keys().contains(target) && costSoFar[target] < INT_MAX )
// 	{
// 		qint32 current = target;
// 		while (current != source)
// 		{
// 			ret.append(current);
// 			current = cameFrom[current];
// 		}
// 		ret.append(source);
// 		std::reverse(ret.begin(), ret.end());
// 		return true;
// 	}

	return false;
}

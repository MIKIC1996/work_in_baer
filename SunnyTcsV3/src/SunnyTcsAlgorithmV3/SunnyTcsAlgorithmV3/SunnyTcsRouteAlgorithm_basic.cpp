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
// 	//��ȡ������Ҫ�滮��·��
// 	SunnyTcsRoute::Pts  routeToBeRouting;
// 	route.getCurrentRoute()->getNextRouteNeedRouting(routeToBeRouting);
// 
// 	//��ͼ���ز�ȫ������û��Ҫ���й滮��·��
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
// 		//��Ӹöε����
// 		if ((iter + 1) == routeToBeRouting.end()) {
// 			pts_ret.append(*(iter + 1));
// 			break;//���һ���㲻��ȥ������
// 		}
// 		ret_step.clear();
// 		if (!routeBetweenTwoPoints(iter->_id, (iter + 1)->_id, data, ret_step)) {
// 			route.setCurrentStatus(ERFailed);
// 			route.setErrorMsg(ERROR_ALGORITHM_ROUTE_NOROUTE_TOPLAN);
// 			return false;
// 		}
// 		ret_step.removeLast();
// 		//�Ƴ����һ���㣬ret_step���ֻ��һ��ֵ����˵��source==target,��ʱ���ret��ʲô��û��ӣ��´λ��Զ���targe���ϵ�
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
// 	//����һ����ret������һ����
// 	route.getCurrentRoute()->setNextRoute(pts_ret);
// 	route.setCurrentStatus(ERworking);//·���滮�ɹ�
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
// 	//��¼ǰ��ÿ�������С����
// 	QMap<qint32, qint32> costSoFar; //<qint32 ptId,qint32 cost>								 	
// 	costSoFar[source] = 0;							 	
// 	costSoFar[target] = INT_MAX;
// 
// 	//��¼��û�������� �� pair<qint32 cost,qint32 ptid>
// 	std::priority_queue < std::pair<qint32, qint32>, std::vector<std::pair<qint32, qint32>>, std::greater<std::pair<qint32, qint32>>> fronter;
// 	fronter.push(std::pair<qint32, qint32>(0, source));
// 
// 	//��¼ÿ�����ǰ�õ�
// 	QMap<qint32, qint32> cameFrom;
// 
// 	bool ok = true;
// 
//  	while (!fronter.empty())
//  	{
//  		qint32 current = fronter.top().second;
// 		fronter.pop();
//  
// 		//�ҵ���
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
// 				//�����ڴ�current �� next ��edge
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

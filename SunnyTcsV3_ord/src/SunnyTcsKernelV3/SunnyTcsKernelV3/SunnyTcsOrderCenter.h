#pragma once
#include "SunnyTcsKernelGeneral.h"

using namespace basic;



class SunnyTcsOrderCenter : public I_SunnyTcsOrderCenter {
public:

	// 通过 I_SunnyTcsOrderCenter 继承
	virtual void addNewTemplate(SunnyTcsCraft * craft) override;

	virtual void removeTemplate(quint64 templateId) override;

	virtual void addNewOrder(SunnyTcsOrder * order) override;

	virtual void addNewOrder(quint64 templateId) override;

	virtual void changeOrderStatus(quint64 orderId, E_SunnyTcsRouteStatus status) override;

	virtual void modifyOrderPriority(quint16 level) override;


protected:
	QHash< quint64, std::shared_ptr<SunnyTcsCraft>> _templates;// 已知模板
	QHash< quint64, std::shared_ptr<SunnyTcsOrder>> _orders; // 所有订单 ,理想情况应该使用unique_ptr,保存订单的副本的目的,是为了方便客端取消


};


#pragma once
#include "SunnyTcsKernelGeneral.h"

using namespace basic;



class SunnyTcsOrderCenter : public I_SunnyTcsOrderCenter {
public:

	// ͨ�� I_SunnyTcsOrderCenter �̳�
	virtual void addNewTemplate(SunnyTcsCraft * craft) override;

	virtual void removeTemplate(quint64 templateId) override;

	virtual void addNewOrder(SunnyTcsOrder * order) override;

	virtual void addNewOrder(quint64 templateId) override;

	virtual void changeOrderStatus(quint64 orderId, E_SunnyTcsRouteStatus status) override;

	virtual void modifyOrderPriority(quint16 level) override;


protected:
	QHash< quint64, std::shared_ptr<SunnyTcsCraft>> _templates;// ��֪ģ��
	QHash< quint64, std::shared_ptr<SunnyTcsOrder>> _orders; // ���ж��� ,�������Ӧ��ʹ��unique_ptr,���涩���ĸ�����Ŀ��,��Ϊ�˷���Ͷ�ȡ��


};


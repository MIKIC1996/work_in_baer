#pragma once
#include "sunnytcsgraphicv3_global.h"

using namespace basic;

class SunnyTcsGraphicsSonCraft;


//�������ָ���� һЩ����ͼ�ε�����
struct SunnyTcsCraftPaintingAttribution {

	qint32 _sonCraftWid = 300;
	qint32 _sonCraftHei = 200;
	QColor _sonCraftMainRectLeftColor = QColor(45,45,45,100);
	QColor _sonCraftMainRectRightColor= QColor(30,30,30,100);
	qint32 _sonCraftTabHeight = 35;
	qint32 _sonCraftRectRadius = 20;
	 QColor _sonCraftTabLeftColor = QColor(255, 255, 0, 100); //tab��ɫ
	 QColor _sonCraftTabRightColor = QColor(120, 50, 50, 100);//tab��ɫ
	 QColor _sonCraftTabBackColor = QColor(230, 230, 230, 200); //tab����ɫ
	 QColor _sonCraftTabBackColor_to = QColor(230, 230, 230, 0);

};



//����������࣬���⻹�� ��ͼ���Խ����˹涨
class  SunnyTcsRouteIndexer : public SunnyTcsGeneralIdManager {
public:
	friend class SunnyTcsGraphicsSonCraft;

	SunnyTcsRouteIndexer() :SunnyTcsGeneralIdManager() {}
	SunnyTcsRouteIndexer(const SunnyTcsRouteIndexer&) = default;
	virtual ~SunnyTcsRouteIndexer() {}
	SunnyTcsRouteIndexer& operator=(const SunnyTcsRouteIndexer&) = default;

protected:
	//���麯��
	virtual void appendRoute(qint32 index, SunnyTcsSonCraft* route) = 0;
	SunnyTcsCraftPaintingAttribution _paintAttribution;

};











class SUNNYTCSGRAPHICV3_EXPORT SunnyTcsCraftGraphicsItem :public QGraphicsItem
{
public:
	//ctor
	SunnyTcsCraftGraphicsItem()
		:QGraphicsItem(nullptr)
	{
		setFlags(QGraphicsItem::ItemIsMovable
			| QGraphicsItem::ItemIsSelectable
			| QGraphicsItem::ItemIsFocusable
			| QGraphicsItem::ItemSendsGeometryChanges
		);
	}
	//copy ctor
	SunnyTcsCraftGraphicsItem(const SunnyTcsCraftGraphicsItem&) = default;
	//dtor
	virtual ~SunnyTcsCraftGraphicsItem() {}
	//assignment
	SunnyTcsCraftGraphicsItem& operator=(const SunnyTcsCraftGraphicsItem&) = default;


	// ͨ�� QGraphicsItem �̳�
	virtual QRectF boundingRect() const override = 0;
	virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = Q_NULLPTR) override = 0;
	QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;//������scene����


};

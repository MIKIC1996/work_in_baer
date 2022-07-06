#pragma once
#include "sunnytcsgraphicv3_global.h"

using namespace basic;

class SunnyTcsGraphicsSonCraft;


//这个类中指定了 一些绘制图形的属性
struct SunnyTcsCraftPaintingAttribution {

	qint32 _sonCraftWid = 300;
	qint32 _sonCraftHei = 200;
	QColor _sonCraftMainRectLeftColor = QColor(45,45,45,100);
	QColor _sonCraftMainRectRightColor= QColor(30,30,30,100);
	qint32 _sonCraftTabHeight = 35;
	qint32 _sonCraftRectRadius = 20;
	 QColor _sonCraftTabLeftColor = QColor(255, 255, 0, 100); //tab左色
	 QColor _sonCraftTabRightColor = QColor(120, 50, 50, 100);//tab右色
	 QColor _sonCraftTabBackColor = QColor(230, 230, 230, 200); //tab背后色
	 QColor _sonCraftTabBackColor_to = QColor(230, 230, 230, 0);

};



//获得索引的类，另外还对 绘图属性进行了规定
class  SunnyTcsRouteIndexer : public SunnyTcsGeneralIdManager {
public:
	friend class SunnyTcsGraphicsSonCraft;

	SunnyTcsRouteIndexer() :SunnyTcsGeneralIdManager() {}
	SunnyTcsRouteIndexer(const SunnyTcsRouteIndexer&) = default;
	virtual ~SunnyTcsRouteIndexer() {}
	SunnyTcsRouteIndexer& operator=(const SunnyTcsRouteIndexer&) = default;

protected:
	//纯虚函数
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


	// 通过 QGraphicsItem 继承
	virtual QRectF boundingRect() const override = 0;
	virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = Q_NULLPTR) override = 0;
	QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;//限制在scene以内


};

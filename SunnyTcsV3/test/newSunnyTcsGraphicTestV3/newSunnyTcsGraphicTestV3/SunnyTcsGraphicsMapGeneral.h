#pragma once
#include "SunnyTcsGraphicsGeneral.h"

using namespace basic;

//mapItem 的 超类
//存在意义在于，保证所有的地图图形对象继承于此，就可以安全的进行dynamic_cast转换，从而调用特有的虚函数，知道图形是什么类型
class SunnyTcsMapGraphicItem :public QGraphicsItem
{
public:
	//ctor
	SunnyTcsMapGraphicItem()
		:QGraphicsItem(nullptr)
	{
		setFlags(QGraphicsItem::ItemIsMovable
			| QGraphicsItem::ItemIsSelectable
			| QGraphicsItem::ItemIsFocusable);
	}
	//copy ctor
	SunnyTcsMapGraphicItem(const SunnyTcsMapGraphicItem&) = default;
	//dtor
	virtual ~SunnyTcsMapGraphicItem() {}
	//assignment
	SunnyTcsMapGraphicItem& operator=(const SunnyTcsMapGraphicItem&) = default;

	// 通过 QGraphicsItem 继承
	virtual QRectF boundingRect() const override = 0;

	virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = Q_NULLPTR) override = 0;

	//下述两个函数，用以区分选取到的元素类型
	virtual SunnyTcsMapObject_tag getItemTag()const = 0;
	qint32 getItemId()const { return getItemTag()._id; }
};



//模型状态
enum E_SunnyTcsModelEditStatus {
	E_EDIT = 1, //编辑状态
	E_RUNNING = 2 //运行状态
};



//地图gui调整器，也是图形模型的超类，定义了各种尺寸，以及模型状态
//存在意义，通过该超类，子图形元素对象，可以得知当前模型的状态，以及各项绘制尺寸，从而合理调用painter函数
class SunnyTcsMapAdjuster
{
public:
	
	SunnyTcsMapAdjuster(qint32 wid, qint32 hei, qint32 resolution)
		:_sceneWid(wid), _sceneHei(hei), _resolution(resolution),_status(E_EDIT),
		_ptIdCounter(0),_phIdCounter(0),_locIdCounter(0),_veIdCounter(0)
	{

	}

	qint32 nextPtId()const {
		return ++_ptIdCounter;
	}

	qint32 nextPhId()const {
		return ++_phIdCounter;
	}

	qint32 nextLocId()const {
		return ++_locIdCounter;
	}

	qint32 nextVeId() const {
		return ++_veIdCounter;
	}


	//状态
	E_SunnyTcsModelEditStatus _status = E_EDIT;

	//地图宽高 区块分辨率
	qreal _sceneWid;		//scene 宽
	qreal _sceneHei;		//scene 高		
	qreal _resolution;		//区块分辨率

	//背景色
	QColor _backColor = QColor(60, 60, 60); 
	//select 选中的颜色必须统一
	QColor _item_select_color = QColor(247, 198, 54);
	//报警色也必须统一
	QColor _item_warning_color = Qt::red; 
	//报错颜色
	QColor _item_error_color = Qt::red;

protected:
	mutable qint32 _ptIdCounter;
	mutable qint32 _phIdCounter;
	mutable qint32 _locIdCounter;
	mutable qint32 _veIdCounter;
};
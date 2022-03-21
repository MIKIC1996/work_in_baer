#pragma once
#include "sunnytcsgraphicv3_global.h"


#define GRAPHICS_LOW_ZVALUE 0
#define GRAPHICS_COORSYS_ZVALUE  1
#define GRAPHICS_PATH_ZVALUE 2 
#define GRAPHICS_POINT_ZVALUE 3
#define GRAPHICS_LOCATION_ZVALUE 4
#define GRAPHICS_VEHICLE_ZVALUE 5
#define GRAPHICS_SELECT_ZVALUE 6


using namespace basic;

//mapItem 的 超类
//存在意义在于，保证所有的地图图形对象继承于此，就可以安全的进行dynamic_cast转换，从而调用特有的虚函数，知道图形是什么类型
class SunnyTcsMapGraphicItem :public QGraphicsItem
{
public:
	//ctor
	SunnyTcsMapGraphicItem(QString name)
		:QGraphicsItem(nullptr), _name(name)
	{
		setFlags(QGraphicsItem::ItemIsMovable
			| QGraphicsItem::ItemIsSelectable
			| QGraphicsItem::ItemIsFocusable
			| QGraphicsItem::ItemSendsGeometryChanges
		);
	}
	//copy ctor
	SunnyTcsMapGraphicItem(const SunnyTcsMapGraphicItem&) = default;
	//dtor
	virtual ~SunnyTcsMapGraphicItem() {}
	//assignment
	SunnyTcsMapGraphicItem& operator=(const SunnyTcsMapGraphicItem&) = default;

	//getter 
	QString getName()const { return _name; }

	//setter
	void SetName(QString name) { _name = name; }

	// 通过 QGraphicsItem 继承
	virtual QRectF boundingRect() const override = 0;
	virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = Q_NULLPTR) override = 0;
	QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;//限制在scene以内


	//下述两个函数，用以区分选取到的元素类型
	virtual SunnyTcsMapObject_tag getItemTag()const = 0;
	qint32 getItemId()const { return getItemTag()._id; }

protected:
	QString _name; //名字

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
		:_sceneWid(wid), _sceneHei(hei), _resolution(resolution), _status(E_EDIT),_groupIdCounter(0),
		_ptIdCounter(0), _phIdCounter(0), _locIdCounter(0), _veIdCounter(0), _isAutoTrafficControlOpen(true),
		_ptIdQueue(),_phIdQueue(),_locIdQueue(),_veIdQueue(),_groupIdQueue()
	{
		if (resolution < 500) { //最小精度0.5m
			_resolution = 500;
		}
		else if (resolution > 100000) { //最大精度100m
			_resolution = 100000;
		}
	}

	//getter
	inline qint32 getWidth()const {
		return _sceneWid;
	}

	inline qint32 getHeight()const {
		return _sceneHei;
	}

	inline qint32 getResolution()const {
		return _resolution;
	}

	inline bool isTrackActived()const {
		return _isTrackActived;
	}

	//获取ID
	qint32 nextGroupId() const{
		if (!_groupIdQueue.empty()) {
			qint32 top = _groupIdQueue.top();
			_groupIdQueue.pop();
			return top;
		}
		return ++_groupIdCounter;
	}

	qint32 nextPtId()const {
		if (!_ptIdQueue.empty()) {
			qint32 top = _ptIdQueue.top();
			_ptIdQueue.pop();
			return top;
		}
		return ++_ptIdCounter;
	}

	qint32 nextPhId()const {
		if (!_phIdQueue.empty()) {
			qint32 top = _phIdQueue.top();
			_phIdQueue.pop();
			return top;
		}
		return ++_phIdCounter;
	}

	qint32 nextLocId()const {
		if (!_locIdQueue.empty()) {
			qint32 top = _locIdQueue.top();
			_locIdQueue.pop();
			return top;
		}
		return ++_locIdCounter;
	}

	qint32 nextVeId() const {
		if (!_veIdQueue.empty()) {
			qint32 top = _veIdQueue.top();
			_veIdQueue.pop();
			return top;
		}
		return ++_veIdCounter;
	}

	bool isAutoTrafficControlOpen()const { return _isAutoTrafficControlOpen; }
	E_SunnyTcsModelEditStatus getEditStatus()const { return _status; }


	//setter
	void setIsTrackActived(bool is) { _isTrackActived = is; }

	void setEditStatus(E_SunnyTcsModelEditStatus status) { _status = status; }
	void setAutoTrafficControlOpen(bool is) { _isAutoTrafficControlOpen = is; }

	//归还ID
	void returnGroupId(qint32 id)const {
		_groupIdQueue.push(id);
	}

	void returnPtId(qint32 id)const {
		_ptIdQueue.push(id);
	}

	void returnPhId(qint32 id)const {
		_phIdQueue.push(id);
	}

	void returnLocId(qint32 id)const {
		_locIdQueue.push(id);
	}

	void returnVeId(qint32 id)const {
		_veIdQueue.push(id);
	}

	


	
	//地图宽高 区块分辨率
	qint32 _sceneWid;		//scene 宽
	qint32 _sceneHei;		//scene 高		
	qint32 _resolution;		//区块分辨率
	//背景色
	QColor _backColor = QColor(60, 60, 60); 
	//select 选中的颜色必须统一
	QColor _item_select_color = QColor(247, 198, 54);
	//报警色也必须统一
	QColor _item_warning_color = Qt::red; 
	//报错颜色
	QColor _item_error_color = Qt::red;

protected:

	//是否启动自动交通管制
	bool _isAutoTrafficControlOpen;
	//状态
	E_SunnyTcsModelEditStatus _status = E_EDIT;

	bool _isTrackActived = false;

	mutable qint32 _groupIdCounter;
	mutable qint32 _ptIdCounter;
	mutable qint32 _phIdCounter;
	mutable qint32 _locIdCounter;
	mutable qint32 _veIdCounter;
	mutable std::priority_queue<qint32, std::vector<qint32>, std::greater<qint32>> _groupIdQueue;//组ID
	mutable std::priority_queue<qint32 ,std::vector<qint32>,std::greater<qint32>> _ptIdQueue;//当对象被删除，会归还ID,以供后续使用
	mutable std::priority_queue<qint32, std::vector<qint32>, std::greater<qint32>> _phIdQueue;
	mutable std::priority_queue<qint32, std::vector<qint32>, std::greater<qint32>> _locIdQueue;
	mutable std::priority_queue<qint32, std::vector<qint32>, std::greater<qint32>> _veIdQueue;

};



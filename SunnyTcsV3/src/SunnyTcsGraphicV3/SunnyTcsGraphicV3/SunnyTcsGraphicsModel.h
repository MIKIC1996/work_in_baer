#pragma once
#include "SunnyTcsGraphicsVehicle.h"
#include "SunnyTcsGraphicsVehicleLib.h"



class SUNNYTCSGRAPHICV3_EXPORT SunnyTcsGraphicsSelectAera :public QGraphicsItem {
public:
	enum selectAera {
		ERect = 1, // 方框选择
		EPolygon=2 //多边形选择
	};

	SunnyTcsGraphicsSelectAera(selectAera aera,QPointF first,QPointF second):QGraphicsItem(nullptr), _curAera(aera),_tracks(){
		_tracks << QPointF(0,0) << QPointF(0,0);
		setFlags(
			 QGraphicsItem::ItemIsSelectable
			| QGraphicsItem::ItemIsFocusable
		);
		this->setPos(first);
	//	this->setZValue(GRAPHICS_SELECT_ZVALUE);
	}
	SunnyTcsGraphicsSelectAera(const SunnyTcsGraphicsSelectAera&) = default;
	virtual ~SunnyTcsGraphicsSelectAera(){}
	SunnyTcsGraphicsSelectAera& operator=(const SunnyTcsGraphicsSelectAera&) = default;

	inline selectAera getSelectType()const { return _curAera; }

	// 通过 QGraphicsItem 继承
//	virtual QPainterPath shape()const override;
	virtual QRectF boundingRect() const override ;
	virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = Q_NULLPTR) override ;

	void updateAera(QPointF pt) {
		switch (_curAera)
		{
		case SunnyTcsGraphicsSelectAera::ERect:
			_tracks.count() < 2 ? _tracks.append(pt) : _tracks[1] = QPointF(pt.x()-this->pos().x(),pt.y()-this->pos().y()) ;
			break;
		case SunnyTcsGraphicsSelectAera::EPolygon:
			_tracks.append(QPointF(pt.x() - this->pos().x(), pt.y() - this->pos().y()));
			break;
		default:
			break;
		}
	}
protected:
	selectAera _curAera; //当前选择模式
	QVector<QPointF> _tracks; //轨迹
};



//图像显示模型
class SUNNYTCSGRAPHICV3_EXPORT SunnyTcsGraphicsModel :public SunnyTcsMapAdjuster, public QGraphicsScene
{
public:
	//ctor
	SunnyTcsGraphicsModel(quint64 id, QString name, qint32 wid = 100000, qint32 hei = 100000, qint32 resolution = 10000);
	//copy ctor
	SunnyTcsGraphicsModel(const SunnyTcsGraphicsModel&) = delete;
	//detor
	virtual ~SunnyTcsGraphicsModel() {}
	//assignment
	SunnyTcsGraphicsModel& operator=(const SunnyTcsGraphicsModel&) = delete;

	//getter
	inline E_SunnyTcsModelEditStatus getStatus()const {
		return _status;
	}

	inline qint32 getWidth()const {
		return _sceneWid;
	}

	inline qint32 getHeight()const {
		return _sceneHei;
	}

	inline qint32 getResolution()const {
		return _resolution;
	}

	bool isPaintingPath()const {
		return _pathTemp;
	}

	bool isOutOfSceneRect(QPointF pt) const;//坐标是否超出了场景范围
	const SunnyTcsGraphicsCoorSys* getCoorSys()const { return _cs; }
	const QHash<qint32, SunnyTcsGraphicsPoint*>& getPoints()const { return _pts; }
	const QHash<qint32, SunnyTcsGraphicsPath*>& getPaths()const { return _phs; }
	const QHash<qint32, SunnyTcsGraphicsLocation*>& getLocations()const { return _locs; }
	const QHash<qint32, SunnyTcsGraphicsVehicle*>& getVehicles()const { return _ves; }

	QList<SunnyTcsGraphicsPoint*> selectedPointItems();
	QList<SunnyTcsGraphicsPath*> selectedPathItems();
	QList<SunnyTcsGraphicsLocation*> selectedLocationItems();
	QList<SunnyTcsGraphicsVehicle*> selectedVehicleItems();

	//setter
	//设置场景的status,有编辑状态和运行中状态两种
	void setStatus(E_SunnyTcsModelEditStatus st) {_status = st;}

	//设置长和宽
	void setWidAndHei(qint32 wid, qint32 hei);
	void setResolution(qint32 res) {_resolution = res;}

	//设置图形属性
	void setItemFlags( QGraphicsItem::GraphicsItemFlags flags , E_SunnyTcsMapObject_type tar = Enotype);//设置item属性
	void setAllItemSelected(bool is , E_SunnyTcsMapObject_type tar = Enotype);

	

	//更新点的实时坐标
	void updatePointRxy();

	//坐标系操作
	void xAxisMirror() { _cs->mirrorX(); }
	void yAxisMirror() { _cs->mirrorY(); }
	void rotateAxis() { _cs->rotate(); }

	//对齐函数
	void leftAlign();
	void rightAlign();
	void topAlign();
	void bottomAlign();

	//选择函数
	bool isSelecting()const {return _aera ? true : false;}
	void addSelectAera(SunnyTcsGraphicsSelectAera::selectAera type, QPointF first);
	void updateSelectAera(QPointF pt, bool isEnd = false);

	//添加元素
	SunnyTcsGraphicsPoint* addGraphicsPoint(QPointF pt) throw(SunnyTcsException<ERROR_GRAPHICS_POINT_OUT_SCENE>);
	SunnyTcsGraphicsPath* addGraphicsPath(QPointF pt )	throw(SunnyTcsException<ERROR_GRAPHICS_PATH_OUT_SCENE>);
	SunnyTcsGraphicsPath* updateTempPath(QPointF pt, bool isArch, qint32 flag = 1);//更新temp path , 是否是曲线，flag -- 更新path:1 设置值:2，取消:3
	SunnyTcsGraphicsLocation* addGraphicsLocation(QPointF pt );
	SunnyTcsGraphicsVehicle* addGraphicsVehicle(QPointF pt ,SunnyTcsAgvCode code);

	bool addGraphicsPoint(SunnyTcsGraphicsPoint* item); //重载形式
	bool addGraphicsPath(SunnyTcsGraphicsPath* item);//重载形式
	bool addGraphicsLocation(SunnyTcsGraphicsLocation* item);//重载形式
	bool addGraphicsVehicle(SunnyTcsGraphicsVehicle* item);//重载形式

	//删除元素
	bool deleteGraphicsItem(SunnyTcsMapGraphicItem* item);
	bool deleteGraphicsPoint(SunnyTcsGraphicsPoint* item);
	bool deleteGraphicsPath(SunnyTcsGraphicsPath* item);
	bool deleteGraphicsLocation(SunnyTcsGraphicsLocation* item);
	bool deleteGraphicsVehicle(SunnyTcsGraphicsVehicle* item);

	//移除元素，不删除
	bool removeGraphicsPoint(SunnyTcsMapGraphicItem* item);
	bool removeGraphicsPath(SunnyTcsGraphicsPath* item);
	bool removeGraphicsLocation(SunnyTcsGraphicsLocation* item);
	bool removeGraphicsVehicle(SunnyTcsGraphicsVehicle* item);

	//点等比例分布
	void xEqualDistributionOfPoints();
	void yEqualDistributionOfPoints();


protected:
	void drawBackground(QPainter *painter, const QRectF &rect);

protected:
	quint64 _id; //id 可以自己生成,推荐使用时间
	QString _name;//模型名由客端提供

	SunnyTcsGraphicsPoint* _pathTempPoint;
	SunnyTcsGraphicsPath* _pathTemp;

	//选区
	SunnyTcsGraphicsSelectAera* _aera;

	SunnyTcsGraphicsCoorSys* _cs;
	QHash<qint32, SunnyTcsGraphicsPoint*> _pts;
	QHash<qint32, SunnyTcsGraphicsPath*> _phs;
	QHash<qint32, SunnyTcsGraphicsLocation*> _locs;
	QHash<qint32, SunnyTcsGraphicsVehicle*> _ves;
	
};


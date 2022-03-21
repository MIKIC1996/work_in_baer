#pragma once
#include "SunnyTcsGraphicsVehicle.h"
#include "SunnyTcsGraphicsVehicleLib.h"


//选择区
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



//groups
class SUNNYTCSGRAPHICV3_EXPORT SunnyTcsMapGroups : public SunnyTcsItemGroup{
public:
	//ctor
	SunnyTcsMapGroups(SunnyTcsMapAdjuster* ad , QString name) :SunnyTcsItemGroup(ad->nextGroupId(),name),_ad(ad){}
	//detor
	virtual ~SunnyTcsMapGroups() {
		_ad->returnGroupId(_id);
	}

protected:
	SunnyTcsMapAdjuster* _ad;
};



//图像显示模型,虽然和内核模型类一样都是负责管理 地图元素，但是两者负责的业务有很大不同，所以没有从 内核模型继承
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
	inline QString getName()const { return _name; }

	bool isPaintingPath()const {//是否正在画路径
		return _pathTemp;
	}

	QPointF getTrackPoint(QPointF pt)const {
		SunnyTcsAgvCoordinate&& rxy = _cs->transformToReality(SunnyTcsAgvCoordinate(E_TWO_DIMENSION , pt.x(),pt.y()));//将场景坐标转换为 现实坐标
		qint32 stepx = rxy._x / _resolution;
		qint32 stepy = rxy._y / _resolution;
		qint32 inayx = rxy._x % _resolution;
		qint32 inayy = rxy._y % _resolution;
		qreal inaccuracyAllowed = _resolution * 0.1;

		if ((qAbs(inayx) > inaccuracyAllowed && _resolution - qAbs(inayx) > inaccuracyAllowed) || 
			(qAbs(inayy) > inaccuracyAllowed && _resolution - qAbs(inayy) > inaccuracyAllowed)) {
			return pt;
		}

		if (qAbs( inayx) >qAbs( _resolution - inaccuracyAllowed)) {
			if (stepx == 0) {
				stepx += inayx > 0 ? 1 : -1;
			}
			else {
				stepx += stepx > 0 ? 1 : -1;
			}
		}
		if ( qAbs(inayy) >qAbs( _resolution - inaccuracyAllowed)) {
			if (stepy == 0) {
				stepy += inayy > 0 ? 1 : -1;
			}
			else {
				stepy += stepy > 0 ? 1 : -1;
			}
		}
		rxy._x = stepx * _resolution;
		rxy._y = stepy * _resolution;
		SunnyTcsAgvCoordinate&& sxy = _cs->transformToScene(rxy);
		return QPointF(sxy._x, sxy._y);
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

	//提供坐标转换方法
	SunnyTcsAgvCoordinate transformRealityToScene(const SunnyTcsAgvCoordinate& rxy);
	SunnyTcsAgvCoordinate transformSceneToReality(const SunnyTcsAgvCoordinate& sxy);

	//setter
	void setName(QString name) { _name = name; }
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
	//组操作
	const QHash<qint32, SunnyTcsMapGroups*>& getGroup(E_SunnyTcsMapObject_type type)const;
	void addItemGroup(E_SunnyTcsMapObject_type type, QString name = QString(""));
	void removeItemGroup(E_SunnyTcsMapObject_type type, qint32 id);
	//添加元素
	SunnyTcsGraphicsPoint* addGraphicsPoint(QPointF pt) throw(SunnyTcsException<ERROR_GRAPHICS_POINT_OUT_SCENE>);
	SunnyTcsGraphicsPath* addGraphicsPath(QPointF pt )	throw(SunnyTcsException<ERROR_GRAPHICS_PATH_OUT_SCENE>);
	SunnyTcsGraphicsPath* updateTempPath(QPointF pt, bool isArch, qint32 flag = 1);//更新temp path , 是否是曲线，flag -- 更新path:1 设置值:2，取消:3
	SunnyTcsGraphicsLocation* addGraphicsLocation(QPointF pt );
	SunnyTcsGraphicsVehicle* addGraphicsVehicle(QPointF pt ,SunnyTcsAgvCode code);
	bool addGraphicsItems(SunnyTcsMapGraphicItem* item);
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
	bool remiveGraphicsItems(SunnyTcsMapGraphicItem* item);
	bool removeGraphicsPoint(SunnyTcsMapGraphicItem* item);
	bool removeGraphicsPath(SunnyTcsGraphicsPath* item);
	bool removeGraphicsLocation(SunnyTcsGraphicsLocation* item);
	bool removeGraphicsVehicle(SunnyTcsGraphicsVehicle* item);
	//点等比例分布
	void xEqualDistributionOfPoints();
	void yEqualDistributionOfPoints();
protected:
	//绘制场景背景
	void drawBackground(QPainter *painter, const QRectF &rect);
protected:
	quint64 _id; //id 可以自己生成,推荐使用时间
	QString _name;//模型名由客端提供
	//绘制曲线
	SunnyTcsGraphicsPoint* _pathTempPoint;
	SunnyTcsGraphicsPath* _pathTemp;
	//选区
	SunnyTcsGraphicsSelectAera* _aera;
	//管理的元素
	SunnyTcsGraphicsCoorSys* _cs;
	QHash<qint32, SunnyTcsGraphicsPoint*> _pts;
	QHash<qint32, SunnyTcsGraphicsPath*> _phs;
	QHash<qint32, SunnyTcsGraphicsLocation*> _locs;
	QHash<qint32, SunnyTcsGraphicsVehicle*> _ves;

	//group
	QHash<qint32, SunnyTcsMapGroups*> _ptGroups;//点组
	QHash<qint32, SunnyTcsMapGroups*> _phGroups;//路径组
	QHash<qint32, SunnyTcsMapGroups*> _locGroups;//工位组
	QHash<qint32, SunnyTcsMapGroups*> _veGroups;//车组
};


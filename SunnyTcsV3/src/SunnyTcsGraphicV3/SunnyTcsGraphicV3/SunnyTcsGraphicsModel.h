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
	SunnyTcsGraphicsModel(qint32 id, QString name, qint32 wid = 100000, qint32 hei = 100000, qint32 resolution = 10000);
	//copy ctor
	SunnyTcsGraphicsModel(const SunnyTcsGraphicsModel&) = delete;
	//detor
	virtual ~SunnyTcsGraphicsModel() {}
	//assignment
	SunnyTcsGraphicsModel& operator=(const SunnyTcsGraphicsModel&) = delete;

	//getter
	inline qint32 getId()const { return _id; }
	inline QString getTime()const { return _time; }
	inline QString getName()const { return _name; }
	inline bool isPaintingPath()const {return _pathTemp;}//是否正在画路径
	QPointF getTrackPoint(QPointF pt)const; //根据地图分辨率，将点修正到最近的网点，可以很方便绘制点。
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
	void updateTIme() {_time = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"); }
	void setId(qint32 id) { _id = id; }
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
	SunnyTcsGraphicsLocation* addGraphicsLocation(QPointF pt ) throw (SunnyTcsException<ERROR_GRAPHICS_LOCATION_NO_LINK_POINT>);
	SunnyTcsGraphicsVehicle* addGraphicsVehicle(QPointF pt, SunnyTcsAgvCode code) throw (SunnyTcsException<ERROR_GRAPHICS_VEHICLE_OUT_SCENE>);
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
	//检测点是否被路径和工位所使用
	bool checkIsPointUsedByPathOrLoc(qint32 ptId);
	//json
	virtual bool fromJson(QJsonObject& jobj, QString& err) {
		try
		{
			if (!jobj.contains(JSON_MAP_MODEL_ID) ||
				!jobj.contains(JSON_MAP_MODEL_NAME) ||
				!jobj.contains(JSON_MAP_MODEL_WIDTH) ||
				!jobj.contains(JSON_MAP_MODEL_HEIGHT) ||
				!jobj.contains(JSON_MAP_MODEL_RESOLUTION) ||
				!jobj.contains(JSON_MAP_MODEL_AUTO_TRAFFIC) ||
				!jobj.contains(JSON_MAP_MODEL_COORSYS) ||
				!jobj.contains(JSON_MAP_MODEL_POINTS) ||
				!jobj.contains(JSON_MAP_MODEL_PATHS) ||
				!jobj.contains(JSON_MAP_MODEL_LOCATIONS) ||
				!jobj.contains(JSON_MAP_MODEL_VEHICLES)
				) {
				throw QSTRING_GBK(SunnyTcsErrorInfo<ERROR_GRAPHICS_MODEL_FROM_JSON_NO_TAG>::err_info_cn);
				return false;
			}

			qint32 id = jobj[JSON_MAP_MODEL_ID].toInt();
			QString name = jobj[JSON_MAP_MODEL_NAME].toString();
			qint32 sceneWid = jobj[JSON_MAP_MODEL_WIDTH].toInt();
			qint32 sceneHei = jobj[JSON_MAP_MODEL_HEIGHT].toInt();
			qint32 res = jobj[JSON_MAP_MODEL_RESOLUTION].toInt();
			bool isAutoTcs = jobj[JSON_MAP_MODEL_AUTO_TRAFFIC].toBool();


			_id = id;
			_name = name;
			setWidAndHei(sceneWid, sceneHei);
			_resolution = res;
			_isAutoTrafficControlOpen = isAutoTcs;
			
			this->removeItem(_cs);
			delete _cs;
			_cs = new SunnyTcsGraphicsCoorSys(QPointF(0, 0), this);
			if (!_cs->fromJson(jobj[JSON_MAP_MODEL_COORSYS].toObject()))return false;

			QJsonArray ptsjarr = jobj[JSON_MAP_MODEL_POINTS].toArray();
			QHash<qint32, SunnyTcsPoint*> pts;
			for (auto iter : ptsjarr) {
				SunnyTcsGraphicsPoint* pt = new SunnyTcsGraphicsPoint(_cs, this);
				if (!pt->fromJson(iter.toObject()))return false;
				_pts.insert(pt->getElementId(), pt);
				pts.insert(pt->getElementId(), pt);
			}
			QJsonArray phsjarr = jobj[JSON_MAP_MODEL_PATHS].toArray();
			for (auto iter : phsjarr) {
				SunnyTcsGraphicsPath* ph = new SunnyTcsGraphicsPath(this, nullptr, nullptr);
				if (!ph->fromJson(iter.toObject(), pts))return false;
				_phs.insert(ph->getElementId(), ph);
			}
			QJsonArray locsjarr = jobj[JSON_MAP_MODEL_LOCATIONS].toArray();
			for (auto iter : locsjarr) {
				SunnyTcsGraphicsLocation* loc = new SunnyTcsGraphicsLocation(this, nullptr);
				loc->fromJson(iter.toObject(), pts);
				_locs.insert(loc->getElementId(), loc);

			}
			QJsonArray vesjarr = jobj[JSON_MAP_MODEL_VEHICLES].toArray();
			for (auto iter : vesjarr) {
				SunnyTcsGraphicsVehicle* ve = _veFactory->createVehicleByJson(iter.toObject(), _cs, this);
				if (!ve)return false;
				_ves.insert(ve->getItemId(), ve);
			}
			this->addItem(_cs);
			for (auto ptr : _pts) {
				this->addItem(ptr);
			}
			for (auto ptr : _phs) {
				this->addItem(ptr);
			}
			for (auto ptr : _locs) {
				this->addItem(ptr);
			}
			for (auto ptr : _ves) {
				this->addItem(ptr);
			}
			return true;
		}
		catch (QString e)
		{
			err = e;
			return false;
		}
	}

	virtual QJsonObject toJson()const {
		QJsonObject jobj;
		jobj[JSON_MAP_MODEL_ID] = _id;
		jobj[JSON_MAP_MODEL_NAME] = _name;
		jobj[JSON_MAP_MODEL_WIDTH] = _sceneWid;
		jobj[JSON_MAP_MODEL_HEIGHT] = _sceneHei;
		jobj[JSON_MAP_MODEL_RESOLUTION] = _resolution;
		jobj[JSON_MAP_MODEL_AUTO_TRAFFIC] = _isAutoTrafficControlOpen;
		jobj[JSON_MAP_MODEL_COORSYS] = _cs->toJson();
		QJsonArray ptsjarr;
		for (SunnyTcsGraphicsPoint* ptr : _pts) {
			ptsjarr.append(ptr->toJson());
		}
		jobj[JSON_MAP_MODEL_POINTS] = ptsjarr;
		QJsonArray phsjarr;
		for (SunnyTcsGraphicsPath* ptr : _phs) {
			phsjarr.append(ptr->toJson());
		}
		jobj[JSON_MAP_MODEL_PATHS] = phsjarr;
		QJsonArray locjarr;
		for (SunnyTcsGraphicsLocation* ptr:_locs){
			locjarr.append(ptr->toJson());
		}
		jobj[JSON_MAP_MODEL_LOCATIONS] = locjarr;
		QJsonArray vejarr;
		for (SunnyTcsGraphicsVehicle* ptr : _ves) {
			vejarr.append(ptr->toVehicleJson());
		}
		jobj[JSON_MAP_MODEL_VEHICLES] = vejarr;
		return jobj;
	}

	bool setImagePath(QString path);

protected:
	//绘制场景背景
	void drawBackground(QPainter *painter, const QRectF &rect) override;
	void releaseAllSource();
protected:
	qint32 _id; //id 可以自己生成,推荐使用时间
	QString _name;//模型名由客端提供
	QString _time;//修改时间
	//绘制曲线
	SunnyTcsGraphicsPoint* _pathTempPoint;
	SunnyTcsGraphicsPath* _pathTemp;
	//选区
	SunnyTcsGraphicsSelectAera* _aera;
	//车辆工厂
	I_SunnyTcsGraphicsVehicleFactory* _veFactory;
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

	//背景图片
	QString _backGroundPixmapPath;
	QImage _backGroundPixmap;
};


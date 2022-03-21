#pragma once
#include "SunnyTcsGraphicsVehicle.h"
#include "SunnyTcsGraphicsVehicleLib.h"


//ѡ����
class SUNNYTCSGRAPHICV3_EXPORT SunnyTcsGraphicsSelectAera :public QGraphicsItem {
public:
	enum selectAera {
		ERect = 1, // ����ѡ��
		EPolygon=2 //�����ѡ��
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

	// ͨ�� QGraphicsItem �̳�
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
	selectAera _curAera; //��ǰѡ��ģʽ
	QVector<QPointF> _tracks; //�켣
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



//ͼ����ʾģ��,��Ȼ���ں�ģ����һ�����Ǹ������ ��ͼԪ�أ��������߸����ҵ���кܴ�ͬ������û�д� �ں�ģ�ͼ̳�
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

	bool isPaintingPath()const {//�Ƿ����ڻ�·��
		return _pathTemp;
	}

	QPointF getTrackPoint(QPointF pt)const {
		SunnyTcsAgvCoordinate&& rxy = _cs->transformToReality(SunnyTcsAgvCoordinate(E_TWO_DIMENSION , pt.x(),pt.y()));//����������ת��Ϊ ��ʵ����
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

	bool isOutOfSceneRect(QPointF pt) const;//�����Ƿ񳬳��˳�����Χ
	const SunnyTcsGraphicsCoorSys* getCoorSys()const { return _cs; }
	const QHash<qint32, SunnyTcsGraphicsPoint*>& getPoints()const { return _pts; }
	const QHash<qint32, SunnyTcsGraphicsPath*>& getPaths()const { return _phs; }
	const QHash<qint32, SunnyTcsGraphicsLocation*>& getLocations()const { return _locs; }
	const QHash<qint32, SunnyTcsGraphicsVehicle*>& getVehicles()const { return _ves; }

	QList<SunnyTcsGraphicsPoint*> selectedPointItems();
	QList<SunnyTcsGraphicsPath*> selectedPathItems();
	QList<SunnyTcsGraphicsLocation*> selectedLocationItems();
	QList<SunnyTcsGraphicsVehicle*> selectedVehicleItems();

	//�ṩ����ת������
	SunnyTcsAgvCoordinate transformRealityToScene(const SunnyTcsAgvCoordinate& rxy);
	SunnyTcsAgvCoordinate transformSceneToReality(const SunnyTcsAgvCoordinate& sxy);

	//setter
	void setName(QString name) { _name = name; }
	//���ó�����status,�б༭״̬��������״̬����
	void setStatus(E_SunnyTcsModelEditStatus st) {_status = st;}
	//���ó��Ϳ�
	void setWidAndHei(qint32 wid, qint32 hei);
	void setResolution(qint32 res) {_resolution = res;}
	//����ͼ������
	void setItemFlags( QGraphicsItem::GraphicsItemFlags flags , E_SunnyTcsMapObject_type tar = Enotype);//����item����
	void setAllItemSelected(bool is , E_SunnyTcsMapObject_type tar = Enotype);
	//���µ��ʵʱ����
	void updatePointRxy();
	//����ϵ����
	void xAxisMirror() { _cs->mirrorX(); }
	void yAxisMirror() { _cs->mirrorY(); }
	void rotateAxis() { _cs->rotate(); }
	//���뺯��
	void leftAlign();
	void rightAlign();
	void topAlign();
	void bottomAlign();
	//ѡ����
	bool isSelecting()const {return _aera ? true : false;}
	void addSelectAera(SunnyTcsGraphicsSelectAera::selectAera type, QPointF first);
	void updateSelectAera(QPointF pt, bool isEnd = false);
	//�����
	const QHash<qint32, SunnyTcsMapGroups*>& getGroup(E_SunnyTcsMapObject_type type)const;
	void addItemGroup(E_SunnyTcsMapObject_type type, QString name = QString(""));
	void removeItemGroup(E_SunnyTcsMapObject_type type, qint32 id);
	//���Ԫ��
	SunnyTcsGraphicsPoint* addGraphicsPoint(QPointF pt) throw(SunnyTcsException<ERROR_GRAPHICS_POINT_OUT_SCENE>);
	SunnyTcsGraphicsPath* addGraphicsPath(QPointF pt )	throw(SunnyTcsException<ERROR_GRAPHICS_PATH_OUT_SCENE>);
	SunnyTcsGraphicsPath* updateTempPath(QPointF pt, bool isArch, qint32 flag = 1);//����temp path , �Ƿ������ߣ�flag -- ����path:1 ����ֵ:2��ȡ��:3
	SunnyTcsGraphicsLocation* addGraphicsLocation(QPointF pt );
	SunnyTcsGraphicsVehicle* addGraphicsVehicle(QPointF pt ,SunnyTcsAgvCode code);
	bool addGraphicsItems(SunnyTcsMapGraphicItem* item);
	bool addGraphicsPoint(SunnyTcsGraphicsPoint* item); //������ʽ
	bool addGraphicsPath(SunnyTcsGraphicsPath* item);//������ʽ
	bool addGraphicsLocation(SunnyTcsGraphicsLocation* item);//������ʽ
	bool addGraphicsVehicle(SunnyTcsGraphicsVehicle* item);//������ʽ
	//ɾ��Ԫ��
	bool deleteGraphicsItem(SunnyTcsMapGraphicItem* item);
	bool deleteGraphicsPoint(SunnyTcsGraphicsPoint* item);
	bool deleteGraphicsPath(SunnyTcsGraphicsPath* item);
	bool deleteGraphicsLocation(SunnyTcsGraphicsLocation* item);
	bool deleteGraphicsVehicle(SunnyTcsGraphicsVehicle* item);
	//�Ƴ�Ԫ�أ���ɾ��
	bool remiveGraphicsItems(SunnyTcsMapGraphicItem* item);
	bool removeGraphicsPoint(SunnyTcsMapGraphicItem* item);
	bool removeGraphicsPath(SunnyTcsGraphicsPath* item);
	bool removeGraphicsLocation(SunnyTcsGraphicsLocation* item);
	bool removeGraphicsVehicle(SunnyTcsGraphicsVehicle* item);
	//��ȱ����ֲ�
	void xEqualDistributionOfPoints();
	void yEqualDistributionOfPoints();
protected:
	//���Ƴ�������
	void drawBackground(QPainter *painter, const QRectF &rect);
protected:
	quint64 _id; //id �����Լ�����,�Ƽ�ʹ��ʱ��
	QString _name;//ģ�����ɿͶ��ṩ
	//��������
	SunnyTcsGraphicsPoint* _pathTempPoint;
	SunnyTcsGraphicsPath* _pathTemp;
	//ѡ��
	SunnyTcsGraphicsSelectAera* _aera;
	//�����Ԫ��
	SunnyTcsGraphicsCoorSys* _cs;
	QHash<qint32, SunnyTcsGraphicsPoint*> _pts;
	QHash<qint32, SunnyTcsGraphicsPath*> _phs;
	QHash<qint32, SunnyTcsGraphicsLocation*> _locs;
	QHash<qint32, SunnyTcsGraphicsVehicle*> _ves;

	//group
	QHash<qint32, SunnyTcsMapGroups*> _ptGroups;//����
	QHash<qint32, SunnyTcsMapGroups*> _phGroups;//·����
	QHash<qint32, SunnyTcsMapGroups*> _locGroups;//��λ��
	QHash<qint32, SunnyTcsMapGroups*> _veGroups;//����
};


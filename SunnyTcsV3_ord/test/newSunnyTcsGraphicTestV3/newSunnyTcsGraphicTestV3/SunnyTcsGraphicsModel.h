#pragma once
#include "SunnyTcsGraphicsVehicle.h"


class SunnyTcsGraphicsModel :public SunnyTcsMapAdjuster, public QGraphicsScene
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

	//setter
	//设置场景的status,有编辑状态和运行中状态两种
	void setStatus(E_SunnyTcsModelEditStatus st) {
		_status = st;
	}

	//设置长和宽
	void setWidAndHei(qint32 wid, qint32 hei) {
		_sceneWid = wid;
		_sceneHei = hei;
		this->setSceneRect(QRectF(-wid / 2, -hei / 2, wid, hei));
	}

	void setResolution(qint32 res) {
		_resolution = res;
	}

protected:
	void drawBackground(QPainter *painter, const QRectF &rect);


protected:
	quint64 _id; //id 可以自己生成
	QString _name;//模型名由客端提供

	SunnyTcsGraphicsCoorSys* _cs;
	QHash<qint32, SunnyTcsGraphicsPoint*> _pts;
	QHash<qint32, SunnyTcsGraphicsPath*> _phs;
	QHash<qint32, SunnyTcsGraphicsLocation*> _locs;

};


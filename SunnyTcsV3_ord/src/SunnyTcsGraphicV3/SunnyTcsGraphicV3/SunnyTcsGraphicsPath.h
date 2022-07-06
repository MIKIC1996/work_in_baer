#pragma once

#include "SunnyTcsGraphicsPoint.h"

#define GRAPHICS_PATH_SHAPE_BIGGER 1200


class SUNNYTCSGRAPHICV3_EXPORT SunnyTcsGraphicsPath :public SunnyTcsPath ,public SunnyTcsMapGraphicItem
{
public:
	//PATH
	static constexpr qint32 _ph_ex_wid = 1200;
	static constexpr qint32 _ph_selected_wid = 650;						
	static constexpr qint32 _ph_arrow_len = 400;						//路劲箭头宽
	static constexpr qint32 _ph_dash_wid = 100;							//虚线线宽
	static constexpr qint32 _ph_arrow_move = 1500;						//箭头偏移
	static const QColor _ph_back_color;
	static const QColor _ph_selected_color;
	static const QColor _ph_dash_color ;

	//ctor
	SunnyTcsGraphicsPath(
		const SunnyTcsMapAdjuster* ad,
		const SunnyTcsGraphicsPoint* start,
		const SunnyTcsGraphicsPoint* end,
		const SunnyTcsGraphicsPoint* ctrl = nullptr
	);
	//copy ctor
	SunnyTcsGraphicsPath(const SunnyTcsGraphicsPath&) = delete;
	//dector
	virtual ~SunnyTcsGraphicsPath() {
		_ad->returnPhId(_id);
	}
	//assignment
	SunnyTcsGraphicsPath operator=(SunnyTcsGraphicsPath&) = delete;

	//getter
	inline bool isStartNew()const { return _isStartNew; }
	inline bool isCtrlNew()const { return _isCtrlNew; }
	inline bool isEndNew()const { return _isEndNew; }

	//setter
	void setIsStartNew(bool is) { _isStartNew = is; }
	void setIsCtrlNew(bool is) { _isCtrlNew = is; }
	void setIsEndNew(bool is) { _isEndNew = is; }

	// 通过 SunnyTcsMapGraphicItem 继承
	virtual QRectF boundingRect() const override;
	virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = Q_NULLPTR) override;
	virtual SunnyTcsMapObject_tag getItemTag() const override;
	virtual QPainterPath shape()const override;

	// 通过 SunnyTcsPath 继承
	virtual bool fromJson(QJsonObject& jobj , const QHash<qint32 , SunnyTcsPoint*>& pts)override {
		if (
			!jobj.contains(JSON_MAP_PATH_ID) ||
			!jobj.contains(JSON_MAP_PATH_NAME) ||
			!jobj.contains(JSON_MAP_PATH_SPT_POSI_DIRECTION) ||
			!jobj.contains(JSON_MAP_PATH_SPT_NEGA_DIRECTION) ||
			!jobj.contains(JSON_MAP_PATH_POSI_SPD) ||
			!jobj.contains(JSON_MAP_PATH_NEGA_SPD) ||
			!jobj.contains(JSON_MAP_PATH_IS_SCAN_ACTIVED) ||
			!jobj.contains(JSON_MAP_PATH_POSI_SCAN) ||
			!jobj.contains(JSON_MAP_PATH_NEGA_SCAN) ||
			!jobj.contains(JSON_MAP_PATH_ST_ID) ||
			!jobj.contains(JSON_MAP_PATH_ED_ID) ||
			!jobj.contains(JSON_MAP_PATH_CT_ID)
			) {
			throw QSTRING_GBK(SunnyTcsErrorInfo<ERROR_GRAPHICS_LOCATION_FROM_JSON_NO_TAG>::err_info_cn);
			return false;
		}

		qint32 id = jobj[JSON_MAP_PATH_ID].toInt();
		if (id != _id) {
			if (_ad->applyForPathId(id)) {
				_ad->returnPhId(_id);
			}
			else {
				throw QSTRING_GBK(SunnyTcsErrorInfo<ERROR_GRAPHICS_FROM_JSON_APPLY_ID_ERR>::err_info_cn)
					+ QSTRING_GBK(": path apply id %1").arg(QString::number(id));
				return false;
			}
		}
		
		QString name = jobj[JSON_MAP_PATH_NAME].toString();
		bool isSptPosi = jobj[JSON_MAP_PATH_SPT_POSI_DIRECTION].toBool();
		bool isSptNega = jobj[JSON_MAP_PATH_SPT_NEGA_DIRECTION].toBool();
		qint32 posiSpd = jobj[JSON_MAP_PATH_POSI_SPD].toInt();
		qint32 negaSpd = jobj[JSON_MAP_PATH_NEGA_SPD].toInt();
		bool isScanActived = jobj[JSON_MAP_PATH_IS_SCAN_ACTIVED].toBool();
		qint32 posiScan = jobj[JSON_MAP_PATH_POSI_SCAN].toInt();
		qint32 negaScan = jobj[JSON_MAP_PATH_NEGA_SCAN].toInt();
		qint32 startId = jobj[JSON_MAP_PATH_ST_ID].toInt();
		qint32 endId = jobj[JSON_MAP_PATH_ED_ID].toInt();
		qint32 ctrlId = jobj[JSON_MAP_PATH_CT_ID].toInt();

		if (!pts.contains(startId) || startId == endId || startId == ctrlId) {
			throw QSTRING_GBK(SunnyTcsErrorInfo<ERROR_GRAPHICS_PATH_FROM_JSON_START_POINT_NO_ID>::err_info_cn) 
				+QString(": path %1 ,start id %2").arg(QString::number(id)).arg(QString::number(startId));
			return false;
		}

		if (!pts.contains(endId) || endId == ctrlId) {
			throw QSTRING_GBK(SunnyTcsErrorInfo<ERROR_GRAPHICS_PATH_FROM_JSON_END_POINT_NO_ID>::err_info_cn)
				+ QString(": path %1 ,end id %2").arg(QString::number(id)).arg(QString::number(endId));
			return false;
		}

		if (!pts.contains(ctrlId) && ctrlId != 0) {
			throw QSTRING_GBK(SunnyTcsErrorInfo<ERROR_GRAPHICS_PATH_FROM_JSON_CTRL_POINT_NO_ID>::err_info_cn)
				+ QString(": path %1 ,ctrl id %2").arg(QString::number(id)).arg(QString::number(ctrlId));
			return false;
		}

		_start = pts[startId];
		_end = pts[endId];
		
		const SunnyTcsGraphicsPoint* stptr = dynamic_cast<const SunnyTcsGraphicsPoint*>(_start);
		const SunnyTcsGraphicsPoint* edptr = dynamic_cast<const SunnyTcsGraphicsPoint*>(_end);
		this->setPos((stptr->pos().x() + edptr->pos().x()) / 2, (stptr->pos().y() + edptr->pos().y()) / 2);

		_ctrl = ctrlId == 0 ? nullptr : pts[ctrlId];
		_id = id;
		_name = name;
		_isSupportPositive = isSptPosi;
		_isSupportNegative = isSptNega;
		_positiveSpeed = posiSpd;
		_negativeSpeed = negaSpd;
		_isScanAeraActived = isScanActived;
		_positiveScanAera = posiScan;
		_negativeScanAera = negaScan;
		return true;
	}

	virtual QJsonObject toJson()const override {
		QJsonObject jobj;
		jobj[JSON_MAP_PATH_ID] = _id;
		jobj[JSON_MAP_PATH_NAME] = _name;
		jobj[JSON_MAP_PATH_SPT_POSI_DIRECTION] = _isSupportPositive;
		jobj[JSON_MAP_PATH_SPT_NEGA_DIRECTION] = _isSupportNegative;
		jobj[JSON_MAP_PATH_POSI_SPD] = _positiveSpeed;
		jobj[JSON_MAP_PATH_NEGA_SPD] = _negativeSpeed;
		jobj[JSON_MAP_PATH_IS_SCAN_ACTIVED] = _isScanAeraActived;
		jobj[JSON_MAP_PATH_POSI_SCAN] = _positiveScanAera;
		jobj[JSON_MAP_PATH_NEGA_SCAN] = _negativeScanAera;
		jobj[JSON_MAP_PATH_ST_ID] = _start->getElementId();
		jobj[JSON_MAP_PATH_ED_ID] = _end->getElementId();
		if (!_ctrl) {
			jobj[JSON_MAP_PATH_CT_ID] = 0;
		}
		else {
			jobj[JSON_MAP_PATH_CT_ID] = _ctrl->getElementId();
		}
		return jobj;
	}

private:
	QPolygonF getArrow(QPointF from, QPointF to);

protected:
	//记录三点是否是新点
	bool _isStartNew;
	bool _isCtrlNew;
	bool _isEndNew;

	//上次记录的三点
	QPointF _last_start;
	QPointF _last_end;
	QPointF _last_ctrl;
	//上次记录的箭头，重画的时候如果三点与之前相同，就不需要重新计算了
	QPolygonF _arrow_start;
	QPolygonF _arrow_end;

	const SunnyTcsMapAdjuster* _ad;
};


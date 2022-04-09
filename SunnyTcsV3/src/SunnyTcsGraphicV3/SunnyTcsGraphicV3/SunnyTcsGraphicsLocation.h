#pragma once

#include "SunnyTcsGraphicsPath.h"


class SUNNYTCSGRAPHICV3_EXPORT SunnyTcsGraphicsLocation :public SunnyTcsLocation ,public SunnyTcsMapGraphicItem
{
public:
	static void setImage(const char* path) {
		_image = QImage(path);
	}

	static void setImageSelected(const char* path) {
		_image_selected = QImage(path);
	}

	static const QColor _loc_dash_color;
	static constexpr qint32 _loc_dash_wid = 100;

	static constexpr qint32 _loc_ex_wid = 3000;
	static constexpr qint32 _loc_line_wid = 100;
	static const QColor _loc_ex_color;

protected:
	static QImage _image;
	static QImage _image_selected;


public:
	//ctor
	SunnyTcsGraphicsLocation(const SunnyTcsMapAdjuster* ad ,const SunnyTcsGraphicsPoint* pt);
	//copy ctor
	SunnyTcsGraphicsLocation(const SunnyTcsGraphicsLocation&) = delete;
	//detor
	virtual ~SunnyTcsGraphicsLocation() {
		_ad->returnLocId(_id);
	}
	//assignment
	SunnyTcsGraphicsLocation& operator=(const SunnyTcsGraphicsLocation&) = delete;

	// 通过 SunnyTcsMapGraphicItem 继承
	virtual QRectF boundingRect() const override;
	virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = Q_NULLPTR) override;
	virtual SunnyTcsMapObject_tag getItemTag() const override;

	// 通过 SunnyTcsLocation 继承
	virtual bool fromJson(QJsonObject& jobj, const QHash<qint32, SunnyTcsPoint*>& pts) override
	{
		if (!jobj.contains(JSON_MAP_LOC_ID) ||
			!jobj.contains(JSON_MAP_LOC_NAME) ||
			!jobj.contains(JSON_MAP_LOC_LINK_PT)||
			!jobj.contains(JSON_MAP_LOC_ACTIONS)||
			!jobj.contains(JSON_MAP_LOC_SCENE_X)||
			!jobj.contains(JSON_MAP_LOC_SCENE_Y)
			) {
			throw QSTRING_GBK(SunnyTcsErrorInfo<ERROR_GRAPHICS_LOCATION_FROM_JSON_NO_TAG>::err_info_cn);
			return false;
		}
		qint32 id = jobj[JSON_MAP_LOC_ID].toInt();
		if (id != _id) {
			if (_ad->applyForLocId(id)) {
				_ad->returnLocId(_id);
			}
			else {
				throw QSTRING_GBK(SunnyTcsErrorInfo<ERROR_GRAPHICS_FROM_JSON_APPLY_ID_ERR>::err_info_cn)
					+ QSTRING_GBK(": location apply id %1").arg(QString::number(id));
				return false;
			}
		}
		
		QString name = jobj[JSON_MAP_LOC_NAME].toString();
		qint32 lkPtId = jobj[JSON_MAP_LOC_LINK_PT].toInt();
		if (!pts.keys().contains(lkPtId)) {
			throw QSTRING_GBK(SunnyTcsErrorInfo<ERROR_GRAPHICS_LOCATION_FROM_JSON_LINKPT_ERR>::err_info_cn)
				+ QString("location %1 ,link pt %2").arg(QString::number(id)).arg(QString::number(lkPtId));
			return false;
		}
		QJsonArray jarr = jobj[JSON_MAP_LOC_ACTIONS].toArray();
		this->clear();
		for (auto& ter : jarr) {
			SunnyTcsAction ac;
			QString err;
			if (!ac.fromJson(ter.toObject(), err)) {
				this->clear();
				throw QSTRING_GBK("指令解析错误") + err;
				return false;
			}
			this->append(ac);
		}
		_id = id;
		_name = name;
		_linkedPt = pts[lkPtId];
		this->setPos(jobj[JSON_MAP_LOC_SCENE_X].toInt(),jobj[JSON_MAP_LOC_SCENE_Y].toInt());
		return true;
	}
	

	virtual QJsonObject toJson()const override 
	{ 
		QJsonObject jobj;
		jobj[JSON_MAP_LOC_ID] = _id;
		jobj[JSON_MAP_LOC_NAME] = _name;
		jobj[JSON_MAP_LOC_LINK_PT] = _linkedPt->getElementId();
		QJsonArray jarr;
		auto iter = this->begin();
		while (iter != this->end()) {
			jarr.append(iter->toJson());
			++iter;
		}
		jobj[JSON_MAP_LOC_ACTIONS] = jarr;
		jobj[JSON_MAP_LOC_SCENE_X] = (qint32)(this->pos().x());
		jobj[JSON_MAP_LOC_SCENE_Y] = (qint32)(this->pos().y());
		return jobj;
	}

protected:
	const SunnyTcsMapAdjuster* _ad;

	

};


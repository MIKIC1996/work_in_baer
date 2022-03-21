#pragma once


#include "SunnyTcsGraphicsMapGeneral.h"


class SUNNYTCSGRAPHICV3_EXPORT SunnyTcsGraphicsCoorSys :public SunnyTcsCoorSys, public SunnyTcsMapGraphicItem
{
public:
	//CS ��������Ƴߴ�
	static constexpr qint32 _cs_axis_len = 1000;	//�����᳤				
	static constexpr qint32 _cs_axis_wid = 100;		//�������߿�				
	static constexpr qint32 _cs_arrow_len = 250;	//�������ͷ�߳�		
	static constexpr qint32 _cs_ex_rect_wid = 800;	//�ⷽ��			
	static constexpr qint32 _cs_in_rect_wid = 800;	//�ڷ���	
	static const QColor _cs_default_color ; //Ĭ����ɫ

	//ctor
	SunnyTcsGraphicsCoorSys(QPointF pt, const SunnyTcsMapAdjuster* ad, qint32 id = 1);
	//copy ctor
	SunnyTcsGraphicsCoorSys(const SunnyTcsGraphicsCoorSys&) = delete;
	//dtor
	virtual ~SunnyTcsGraphicsCoorSys() {}
	//assignment
	SunnyTcsGraphicsCoorSys& operator=(SunnyTcsGraphicsCoorSys&) = delete;


	// ͨ�� SunnyTcsMapGraphicItem �̳�
	virtual QRectF boundingRect() const override;
	virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = Q_NULLPTR) override;
	virtual SunnyTcsMapObject_tag getItemTag() const override;


	//ͨ�� SunnyTcsCoorSys �̳�
	virtual SunnyTcsAgvCoordinate transformToScene(SunnyTcsAgvCoordinate reality)const override;
	virtual SunnyTcsAgvCoordinate transformToReality(SunnyTcsAgvCoordinate scene) const override;
	virtual bool fromJson(QJsonObject& jobj)override {
		if (!jobj.contains(JSON_MAP_CS_ID) ||
			!jobj.contains(JSON_MAP_CS_NAME) ||
			!jobj.contains(JSON_MAP_CS_SCENE_X) ||
			!jobj.contains(JSON_MAP_CS_SCENE_Y) ||
			!jobj.contains(JSON_MAP_CS_AXIS_X) ||
			!jobj.contains(JSON_MAP_CS_AXIS_Y)
			) {
			return false;
		}
		qint32 id = jobj[JSON_MAP_CS_ID].toInt();
		QString name = jobj[JSON_MAP_CS_NAME].toString();
		qint32 rx = jobj[JSON_MAP_CS_SCENE_X].toInt();
		qint32 ry = jobj[JSON_MAP_CS_SCENE_Y].toInt();
		qint32 xpos = jobj[JSON_MAP_CS_AXIS_X].toInt();
		qint32 ypos = jobj[JSON_MAP_CS_AXIS_Y].toInt();
		if (xpos < 1 || xpos >4 || ypos < 1 || ypos >4)return false;
		E_SunnyTcsAxisDirection xaxis = static_cast<E_SunnyTcsAxisDirection>(xpos);
		E_SunnyTcsAxisDirection yaxis = static_cast<E_SunnyTcsAxisDirection>(ypos);
		//����ֵ
		_id = id;
		_name = name;
		this->setPos(rx, ry);
		_xpos = xaxis;
		_ypos = yaxis;
		return true;
	}


	virtual QJsonObject toJson()const override
	{
		QJsonObject jobj;
		jobj[JSON_MAP_CS_ID] = _id;
		jobj[JSON_MAP_CS_NAME] = _name;
		qint32 rx = this->pos().x();
		qint32 ry = this->pos().y();
		jobj[JSON_MAP_CS_SCENE_X] = rx;
		jobj[JSON_MAP_CS_SCENE_Y] = ry;
		jobj[JSON_MAP_CS_AXIS_X] = static_cast<qint32>(_xpos);
		jobj[JSON_MAP_CS_AXIS_Y] = static_cast<qint32>(_ypos);
		return jobj;
	}

private:
	QPolygonF getArrow(int direction);

protected:
	const SunnyTcsMapAdjuster* _ad; //ͼ��ģ�͵Ľӿ�
};


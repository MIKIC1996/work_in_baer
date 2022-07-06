#pragma once

#include "SunnyTcsGraphicsPoint.h"



class SunnyTcsGraphicsPath :public SunnyTcsPath ,public SunnyTcsMapGraphicItem
{
public:
	//PATH
	static constexpr qint32 _ph_ex_wid = 1200;
	static constexpr qint32 _ph_selected_wid = 650;						
	static constexpr qint32 _ph_arrow_len = 400;						//·����ͷ��
	static constexpr qint32 _ph_dash_wid = 100;							//�����߿�
	static constexpr qint32 _ph_arrow_move = 1500;						//��ͷƫ��
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
	virtual ~SunnyTcsGraphicsPath() {}
	//assignment
	SunnyTcsGraphicsPath operator=(SunnyTcsGraphicsPath&) = delete;

	// ͨ�� SunnyTcsMapGraphicItem �̳�
	virtual QRectF boundingRect() const override;
	virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = Q_NULLPTR) override;
	virtual SunnyTcsMapObject_tag getItemTag() const override;


private:
	QPolygonF getArrow(QPointF from, QPointF to);

protected:
	//�ϴμ�¼������
	QPointF _last_start;
	QPointF _last_end;
	QPointF _last_ctrl;
	//�ϴμ�¼�ļ�ͷ���ػ���ʱ�����������֮ǰ��ͬ���Ͳ���Ҫ���¼�����
	QPolygonF _arrow_start;
	QPolygonF _arrow_end;

	const SunnyTcsMapAdjuster* _ad;
};


#pragma once
#include "SunnyTcsGraphicsCoorSys.h"



class SUNNYTCSGRAPHICV3_EXPORT SunnyTcsGraphicsPoint : public SunnyTcsPoint ,public SunnyTcsMapGraphicItem
{
public:
	//PT
	static constexpr qint32 _pt_ex_wid = 1200;							//Բ���߿�
	static constexpr qint32 _pt_rect_wid = 800;							//Բ��ֱ��
	static constexpr qint32 _pt_back_wid = 2000;							//��Բ��ֱ��
	static constexpr qint32 _pt_park_wid = 3000;							//ͣ��Բֱ��
	static constexpr qint32 _pt_text_rect_len = 16000;						//������巽��
	static constexpr qint32 _pt_text_rect_wid = 1000;						//������巽���
	static constexpr qint32 _pt_font_size = 400;							//�����С

	static const QColor _pt_back_color;		//��ɫ
	static const QColor _pt_ex_color;		//Բ����ɫ
	static const QColor _pt_rect_color ;	//��Բ��ɫ
	static const QColor _pt_select_color ;	//ѡ����ɫ
	static const QColor _pt_park_color ;	//�ؾ�����ɫ

	static const QColor _pt_rubbon_color ;	
	static const QColor _pt_ine_color;
	static const QColor _pt_laser_color ;
	static const QColor _pt_help_color;


	//ctor
	SunnyTcsGraphicsPoint( const SunnyTcsGraphicsCoorSys* cs, const SunnyTcsMapAdjuster* ad, QPointF pt = QPointF(0, 0));

	SunnyTcsGraphicsPoint(const SunnyTcsGraphicsPoint&) = delete;

	virtual ~SunnyTcsGraphicsPoint() {
		qDebug() << "delete point";
		_ad->returnPtId(_id);
	}

	SunnyTcsGraphicsPoint& operator=(const SunnyTcsGraphicsPoint&) = delete;

	//�õ���������
	SunnyTcsAgvCoordinate getSceneXy()const;

	//�ӵ�ǰ��Sx Sy�����RX RY ֻ��ͼ�ο�����Ҫ�õ������������Ϊ����ϵ���ƶ�����ʱ����Ҫʵʱ����rx ry
	void updateData();

	// ͨ�� SunnyTcsMapGraphicItem �̳�
	virtual QRectF boundingRect() const override;
	virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = Q_NULLPTR) override;
	virtual SunnyTcsMapObject_tag getItemTag() const override;
	
protected:
	const SunnyTcsMapAdjuster* _ad;
	
	
};


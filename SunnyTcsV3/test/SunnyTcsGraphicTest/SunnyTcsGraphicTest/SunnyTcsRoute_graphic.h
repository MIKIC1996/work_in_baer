#pragma once

#include "SunnyTcsCraftGraphicGeneral.h"

using namespace basic;

namespace graphic {

	//craft Ҳ�� scene
	class SunnyTcsCraft_graphic;
	class SunnyTcsRoute_graphic :public SunnyTcsRoute, public SunnyTcsCraftGraphicsItem
	{
	public:
		friend class SunnyTcsCraft_graphic;
		
		//�ྲ̬���ݣ�����ͼ�����
		static QHash<E_SunnyTcsRouteStatus, QString> _status_string_hash;//��������״̬
		static QHash<E_SunnyTcsRouteStatus, QColor> _status_color_hash;//����״̬ ��ʾ��������ɫ
		static const QString _statusPrefix;
		static const QString _agvPrefix;
		static const qreal _rectRadius;//Բ�ǰ뾶
		static const qreal _lineWid; //�߿�
		static const qreal _wid; //���
		static const qreal _height; //���
		static const qreal _tabHeight; //ͷ��tab��
		static const QColor _lineColor; //�߿���ɫ
		static const QColor _tabLeftColor; //tab��ɫ
		static const QColor _tabRightColor;//tab��ɫ
		static const QColor _tabBackColor; //װ��ɫ1
		static const QColor _tabBackColor_to;//װ��ɫ2
		static const QColor _tabShadowColor; //tab��Ӱɫ
		static const QColor _selectedColor;//ѡ��ɫ
		static const QColor _leftColor; //������ɫ
		static const QColor _rightColor;//������ɫ 								
		static bool _inited; //���Դ�����ʼ������
		static bool init();//��ʼ������
		
	public:
		SunnyTcsRoute_graphic(SunnyTcsCraftIndexer * indexer, QPointF pt = QPointF(0, 0));
		virtual ~SunnyTcsRoute_graphic();

		// ͨ�� QGraphicsItem �̳�
		virtual QRectF boundingRect() const override;
		virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = Q_NULLPTR) override;
		virtual qint32 getGraphicsIndex()const override {
			return this->getIndex();
		}

		QPointF recvPoint()const {
			QPointF recvpt(-_wid* 0.43, -_height / 2 + _tabHeight / 2);
			return QPointF(this->pos().x() + recvpt.x(), this->pos().y() + recvpt.y());
		}

		QPointF sendPoint()const { 
			QPointF sendpt(_wid*0.46, _height*0.01);
			return QPointF(this->pos().x() + sendpt.x(), this->pos().y() + sendpt.y());
		}

	protected:
		QRectF nextTextRect(qint32 index) {
			qreal start_x = -_wid / 2 + 30;
			qreal start_y = -_height / 2 + 50;

			const qreal text_height = 20;
			const qreal text_wid = 210;
			start_y += index * (text_height + 10);
			return QRectF(start_x, start_y, text_wid, text_height);
		}

		QString _name;

	};


	
	//�Ӷ���������
	class SunnyTcsLinkLine_graphic : public SunnyTcsCraftGraphicsItem
	{
	public:
		friend class SunnyTcsCraft_graphic;
		
		static const QColor _lineColor;
		static const qreal _lineWid;
		static const QColor _lineColor_selected;
		static const qreal _lineWid_selected;

	public:
		SunnyTcsLinkLine_graphic(qint32 index, SunnyTcsRoute_graphic* from, SunnyTcsRoute_graphic* to = nullptr);

		virtual ~SunnyTcsLinkLine_graphic() {
			qDebug() << "line release;";
		}
		
		virtual qint32 getGraphicsIndex()const override {
			return _index;
		}

		void setToPoint(QPointF to) {
			_toPt = to;
		}

		// ͨ�� SunnyTcsCraftGraphicsItem �̳�
		virtual QRectF boundingRect() const override;
		virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = Q_NULLPTR) override;

	protected:
		QPolygonF getArrow(QPointF from, QPointF to);



	protected:
		qint32 _index;
		
		SunnyTcsRoute_graphic *_from;
		SunnyTcsRoute_graphic *_to;
		QPointF _fromPt;//scene���� ����ͼ�α�������
		QPointF _toPt;//scene���� ����ͼ�α�������
	};


}



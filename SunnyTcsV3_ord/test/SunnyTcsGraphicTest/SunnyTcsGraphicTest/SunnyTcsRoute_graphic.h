#pragma once

#include "SunnyTcsCraftGraphicGeneral.h"

using namespace basic;

namespace graphic {

	//craft 也是 scene
	class SunnyTcsCraft_graphic;
	class SunnyTcsRoute_graphic :public SunnyTcsRoute, public SunnyTcsCraftGraphicsItem
	{
	public:
		friend class SunnyTcsCraft_graphic;
		
		//类静态数据，用以图形描绘
		static QHash<E_SunnyTcsRouteStatus, QString> _status_string_hash;//用以描述状态
		static QHash<E_SunnyTcsRouteStatus, QColor> _status_color_hash;//按照状态 显示顶部栏颜色
		static const QString _statusPrefix;
		static const QString _agvPrefix;
		static const qreal _rectRadius;//圆角半径
		static const qreal _lineWid; //线宽
		static const qreal _wid; //框宽
		static const qreal _height; //框高
		static const qreal _tabHeight; //头顶tab高
		static const QColor _lineColor; //边框颜色
		static const QColor _tabLeftColor; //tab左色
		static const QColor _tabRightColor;//tab右色
		static const QColor _tabBackColor; //装饰色1
		static const QColor _tabBackColor_to;//装饰色2
		static const QColor _tabShadowColor; //tab阴影色
		static const QColor _selectedColor;//选中色
		static const QColor _leftColor; //主框左色
		static const QColor _rightColor;//主框右色 								
		static bool _inited; //用以触发初始化函数
		static bool init();//初始化函数
		
	public:
		SunnyTcsRoute_graphic(SunnyTcsCraftIndexer * indexer, QPointF pt = QPointF(0, 0));
		virtual ~SunnyTcsRoute_graphic();

		// 通过 QGraphicsItem 继承
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


	
	//子订单连接线
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

		// 通过 SunnyTcsCraftGraphicsItem 继承
		virtual QRectF boundingRect() const override;
		virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = Q_NULLPTR) override;

	protected:
		QPolygonF getArrow(QPointF from, QPointF to);



	protected:
		qint32 _index;
		
		SunnyTcsRoute_graphic *_from;
		SunnyTcsRoute_graphic *_to;
		QPointF _fromPt;//scene坐标 ，非图形本身坐标
		QPointF _toPt;//scene坐标 ，非图形本身坐标
	};


}



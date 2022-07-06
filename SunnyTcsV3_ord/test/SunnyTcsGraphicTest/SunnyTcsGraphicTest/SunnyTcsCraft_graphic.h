#pragma once


#include "SunnyTcsRoute_graphic.h"

using namespace basic;

namespace graphic {

	
	class SunnyTcsCraft_graphic : public SunnyTcsCraft, public QGraphicsScene
	{
	public:
		SunnyTcsCraft_graphic(qint32 len, qint32 wid) :SunnyTcsCraft(), QGraphicsScene(), _linkLines(), _curLine(nullptr)
		{
			this->setSceneRect(QRectF(-len / 2, -wid / 2, len, wid));
		}


		virtual ~SunnyTcsCraft_graphic() {}

		

		virtual qint32 addRoute()override {
			SunnyTcsRoute_graphic* rt = new SunnyTcsRoute_graphic(this);//���������ӹ��� ����
			this->addItem(rt);
			return rt->getIndex();
		}

		qint32 addRoute(QPointF pt) {
			SunnyTcsRoute_graphic* rt = new SunnyTcsRoute_graphic(this, pt);//���������ӹ��� ����
			this->addItem(rt);
			return rt->getIndex();
		}

		bool removeGraphicItem(QPointF pt) {
			SunnyTcsCraftGraphicsItem* item = dynamic_cast<SunnyTcsCraftGraphicsItem*>( this->itemAt(pt, QTransform()) );
			if (item->getGraphicsItemType() != EROUTE) {
				return false;
			}
			
		}

		virtual bool removeRoute(qint32 index)override {
// 			if (_routes.keys().contains(index)) {
// 				if (_rootRoute == _routes[index]) {
// 					return false;
// 				}
// 				else if (_curRoute == _routes[index])
// 				{
// 					_curRoute == _rootRoute;
// 				}
// 
// 				for (auto& ter : _routes[index]->_sonRoutes) {//�������ӹ��� �� �ӹ�����
// 					Q_ASSERT(ter->_lastRoutes.keys().contains(index));//ȥ���ӹ��� �� ������
// 					ter->_lastRoutes.remove(index);
// 				}
// 				for (auto& ter : _routes[index]->_lastRoutes) {
// 					Q_ASSERT(ter->_sonRoutes.keys().contains(index));//ȥ�������յ� ������
// 					ter->_sonRoutes.remove(index);
// 				}
// 				_routes[index]->_indexer = nullptr;
// 
// 				delete _routes[index];
// 				_routes.remove(index);
// 			}
 			return true;
		}


		qint32 addLinkLine(QPointF pt);

		qint32 addLinkLine(qint32 fromIndex, qint32 toIndex = 0);


		SunnyTcsLinkLine_graphic* getCurrentLinkingLine() {
			return _curLine;
		}

		void setCurrentLinkingLineEndRoute(QPointF pt);

		void setCurrentLinkingLineEnd(QPointF pt) {
			if (_curLine) {
				_curLine->setToPoint(pt);
			}
		}

		//�����Ƿ���ƶ� ��ѡ��
		void setItemsMoveSelectFlags(bool open);
		

		//�̳� 
		void drawBackground(QPainter *painter, const QRectF &rect) override{
			QPen pen;
			pen.setColor(Qt::black);
			pen.setWidth(2);
			painter->setPen(pen);
			painter->fillRect(this->sceneRect(), QColor(60, 60, 60));

		}

	protected:
		qint32 _len;
		qint32 _wid;
		QString _name;
		//linklines
		SunnyTcsLinkLine_graphic* _curLine;//��ǰ�����ߣ�������ڣ����Ǵ�������ģʽ
		QHash<qint32,SunnyTcsLinkLine_graphic*> _linkLines;

	};


}




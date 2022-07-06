#pragma once

#include "stafix.h"
#include "SunnyTcsCoorSys_graphic.h"
#include "SunnyTcsPoint_graphic.h"
#include "SunnyTcsPath_graphic.h"
#include "SunnyTcsVehicle_normal_graphic.h"


using namespace basic;
using namespace core;

//scene
class SunnyTcsMapGraphicsScene 
	:public A_SunnyTcsModelData, public QGraphicsScene
{
public:
	SunnyTcsMapGraphicsScene(qint32 id ,qint32 wid, qint32 hei, qint32 resolution=1000,QObject* parent = 0) 
		:A_SunnyTcsModelData(nullptr,id, wid, hei,resolution) ,
		QGraphicsScene(parent) {

		this->setSceneRect(-wid / 2, -hei / 2, wid, hei);
		_ad = new SunnyTcsMapAdjuster(wid,hei,resolution);
		_cs = new SunnyTcsMapCoorSys_graphic(QPointF(0, 0),_ad ,1 );
		addItem(_cs);
		update();
	}

	//更新
	void updateScene(){
		this->updatePoint();
		this->update();
	}

	//设置场景的status,有编辑状态和运行中状态两种
	void setStatus(E_SunnyTcsModelEditStatus st) {
		_ad->_status = st;
	}
	
	//设置长和宽
	void setLenAndWid(qint32 wid, qint32 hei) {
		_len = wid;
		_wid = hei;
		_ad->resetSceneSize(wid, hei,_resolution);
		this->setSceneRect(QRectF(-wid / 2, -hei / 2, wid, hei));
	}

	

	//更新点
	void updatePoint() {
		auto iter = _pts.begin();
		while (iter != _pts.end()) {
			dynamic_cast<SunnyTcsPoint_graphic*>(*iter)->updateData();
			++iter;
		}
	}

	//镜像X
	void mirrorX() {
		_cs->mirrorX();
		updatePoint();
		update();
	}

	//镜像Y
	void mirrorY() {
		_cs->mirrorY();
		updatePoint();
		update();
	}

	//旋转轴
	void rotateCoordinateSystem() {
		_cs->rotate();
		updatePoint();
		update();
	}

	void changDirectionForSelectedPath(qint32 id) {
		

	}


	void setPointType(qint32 type) {
// 		if (type != 1 && type != 2) {
// 			return;
// 		}
// 		for (auto& pt : _pts) {
// 			if (selectedItems().contains(pt)) {
// 				pt->setType(type);
// 			}
// 		}
// 		update();
	}

	void setVehicleAngle(qint32 val) {
// 		for (auto& path : _ves) {
// 			if (selectedItems().contains(path)) {
// 				path->setAngle(val);
// 			}
// 		}
// 		update();
	}

	void removeAll() {
	}


	SunnyTcsPoint_graphic* getPtById(qint32 id) {
		return dynamic_cast<SunnyTcsPoint_graphic*>( _pts[id] );
	}

	

	qint32 addTcsPointItem(QPointF pos) {
		SunnyTcsPoint_graphic* pt = new SunnyTcsPoint_graphic(_cs, ++_ptIdCounter, _ad,7,pos);
		_pts.insert(pt->getId(), pt);
		addItem(pt);
		update();
		return pt->getId();
	}


	SunnyTcsMapItem_graphic* getItemAt(QPointF pt){
		return dynamic_cast<SunnyTcsMapItem_graphic*>(this->itemAt(pt,QTransform()));
	}


	qint32 addTcsVehicleItem(QPointF pt) {
		SunnyTcsVehicle_normal_graphic* ve = new SunnyTcsVehicle_normal_graphic(_cs, ++_veIdCounter, _ad, pt);
		_ves.insert(ve->getId(), ve);
		addItem(ve);
		update();
		return ve->getId();
	}

	qint32 addTcsPathItem(bool isArc,QString& err = QString()) {
		QList<QGraphicsItem*>&& selects = selectedItems();
		if (selects.count() != 2) {
			//err
			return -1;
		}
		SunnyTcsMapItem_graphic* first = dynamic_cast<SunnyTcsMapItem_graphic*>(selects[0]);
		SunnyTcsMapItem_graphic* last = dynamic_cast<SunnyTcsMapItem_graphic*>(selects[1]);

		if (!first ||
			!last ||
			first->getItemTag()._eletype != Epoint ||
			last->getItemTag()._eletype != Epoint 
			) {
			//err
			return -1;
		}
		QPointF firstPos = first->pos();
		QPointF lastPos = last->pos();

		SunnyTcsPoint_graphic* firstPt = dynamic_cast<SunnyTcsPoint_graphic*>(first);
		SunnyTcsPoint_graphic* lastPt = dynamic_cast<SunnyTcsPoint_graphic*>(last);
		if (!firstPt ||
			!lastPt ||
			firstPt->getNagetiveMode() == 0 ||
			lastPt->getNagetiveMode() == 0 
			)
		{
			return -1;
		}

		SunnyTcsPoint_graphic* helpPt = nullptr;
		if (isArc) {
			QPointF helpPos((firstPos.x() + lastPos.x()) / 2 , (firstPos.y() + lastPos.y()) / 2 );
			helpPt = new SunnyTcsPoint_graphic(_cs, ++_ptIdCounter, _ad, 0, helpPos);
			this->addItem(helpPt);
			_pts.insert(helpPt->getId(), helpPt);
		}
		

		SunnyTcsPath_graphic * path = new SunnyTcsPath_graphic(++_phIdCounter, _ad,
			firstPt,lastPt,helpPt
		);
		this->addItem(path);
		_paths.insert(path->getId(), path);
		return path->getId();
	}


	void setItemsMoveSelectFlags(bool open)
	{
		for (auto ter : this->items()) {
			Q_ASSERT(ter);
			ter->setFlags(open ?
				(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable) :
				(ter->flags() &~(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsFocusable))
			);
		}
	}


	// QGraphicsScene interface
protected:
	void drawBackground(QPainter *painter, const QRectF &rect) {
		//qDebug() << "drawBackground scene";
		painter->fillRect(this->sceneRect(), QColor(63, 72, 101));

		qreal wid = _ad->getSceneWid();
		qreal hei = _ad->getSceneHei();
		qreal res = _ad->getResolution();
		qreal cur_x = _cs->pos().x();
		qreal cur_y = _cs->pos().y();
		qreal dis_x_left = qAbs(cur_x - (-wid / 2.0));
		qreal dis_x_right = qAbs(wid / 2.0 - cur_x);
		qreal dis_y_down = qAbs(hei / 2.0 - cur_y);
		qreal dis_y_up = qAbs(cur_y - (-hei / 2.0));

		QPen pen;
		pen.setWidth(101.0);
		pen.setColor(QColor(83, 92, 121));
		painter->setPen(pen);
		QFont font;
		font.setPixelSize(600);
		painter->setFont(font);
		QPen textPen;
		textPen.setColor(Qt::white);

		bool axis_x_right = _cs->getAxisDirectionX() == Eright || _cs->getAxisDirectionY() == Eright;
		bool axis_y_up = _cs->getAxisDirectionX() == Eup || _cs->getAxisDirectionY() == Eup;

		for (qreal i = 0; i < dis_x_left; i += res) {
			painter->drawLine(QPointF(cur_x -i, -hei/2.0), QPointF(cur_x -i, hei / 2.0));
			painter->setPen(textPen);
			painter->drawText(QRectF(cur_x -i + 500.0, cur_y + 500, 3000.0, 3000.0), QString::number(axis_x_right ? -i : i) + QString("mm"));
			painter->setPen(pen);
		}

		for (qreal i = 0; i < dis_x_right; i += res) {
			painter->drawLine(QPointF(cur_x+i, -hei / 2.0), QPointF(cur_x+i, hei / 2.0));
			painter->setPen(textPen);
			painter->drawText(QRectF(cur_x + i + 500.0,cur_y + 500, 3000.0, 3000.0), QString::number(axis_x_right ? i : -i) + QString("mm")) ;
			painter->setPen(pen);
		}

		for (qreal i = 0; i < dis_y_down; i += res) {
			painter->drawLine(QPointF(-wid/2.0,cur_y + i), QPointF(wid / 2.0, cur_y + i));
			painter->setPen(textPen);
			painter->drawText(QRectF(cur_x + 500.0,cur_y + i + 500.0, 3000.0, 3000.0), QString::number(axis_y_up ? -i : i) + QString("mm"));
			painter->setPen(pen);
		}

		for (qreal i = 0; i < dis_y_up; i += res) {
			painter->drawLine(QPointF(-wid / 2.0 , cur_y -i), QPointF(wid/2.0, cur_y -i));
			painter->setPen(textPen);
			painter->drawText(QRectF(cur_x + 500.0,cur_y -i + 500.0, 3000.0, 3000.0), QString::number(axis_y_up ? i : -i) + QString("mm"));
			painter->setPen(pen);
		}



	}

	virtual QJsonObject toJson()const override {
		QJsonObject jobj;
		jobj[JSON_MAP_MODEL_ID] = _modelId;
		jobj[JSON_MAP_MODEL_NAME] = _name;
		jobj[JSON_MAP_MODEL_WIDTH] = _wid;
		jobj[JSON_MAP_MODEL_HEIGHT] = _len;

		return jobj;

	}
	

private:
	SunnyTcsMapCoorSys_graphic* _cs;
	SunnyTcsMapAdjuster* _ad;

	QMap<qint32, SunnyTcsAgvCode> _veCodes;//从数据库中同步而来
	QString _name;

	//id 计数器
	qint32 _ptIdCounter = 0;
	qint32 _phIdCounter = 0;
	qint32 _locIdCounter = 0;
	qint32 _veIdCounter = 0;


	

};


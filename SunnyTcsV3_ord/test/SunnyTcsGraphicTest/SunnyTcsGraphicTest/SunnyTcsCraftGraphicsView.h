#pragma once

#include "SunnyTcsCraftGraphicsScene.h"


using namespace basic;


class SunnyTcsCraftGraphicsView :public QGraphicsView {
	Q_OBJECT
public:
	SunnyTcsCraftGraphicsView(QWidget* parent) :QGraphicsView(parent) {
		 setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		 setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		setCursor(Qt::PointingHandCursor);
		setRenderHint(QPainter::Antialiasing);
		setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

		
		
	}


	

	// QWidget interface
protected:
	void mousePressEvent(QMouseEvent *event) {
		emit mousePress(mapToScene(event->pos()));
		QGraphicsView::mousePressEvent(event);
	}

	void mouseMoveEvent(QMouseEvent *event) {
		emit mouseMove(mapToScene(event->pos()));
		QGraphicsView::mouseMoveEvent(event);
	}


	void mouseReleaseEvent(QMouseEvent *event) {
		emit mouseRelease(mapToScene(event->pos()));
		QGraphicsView::mouseReleaseEvent(event);
	}

	void mouseDoubleClickEvent(QMouseEvent *event) {
		emit mouseDouClick(mapToScene(event->pos()));
		QGraphicsView::mouseDoubleClickEvent(event);
	}

	void wheelEvent(QWheelEvent *event) {
		emit wheelChange(event->angleDelta().y());
	}

signals:
	void mousePress(QPointF pt);
	void mouseMove(QPointF pt);
	void mouseDouClick(QPointF pt);
	void mouseRelease(QPointF pt);
	void wheelChange(int angle);
};





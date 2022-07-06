#include "SunnyTcsCraft_graphic.h"


qint32 graphic::SunnyTcsCraft_graphic::addLinkLine(QPointF pt)
{
	SunnyTcsCraftGraphicsItem* item = dynamic_cast<SunnyTcsCraftGraphicsItem*>(itemAt(pt,QTransform()));
	if (item && item->getGraphicsItemType()==EROUTE) {
		return this->addLinkLine(item->getGraphicsIndex(), 0);
	}
	return 0;
}


qint32 graphic::SunnyTcsCraft_graphic::addLinkLine(qint32 fromIndex, qint32 toIndex)
{
	Q_ASSERT(_routes.keys().contains(fromIndex) && (toIndex == 0 || _routes.keys().contains(toIndex)));

	SunnyTcsRoute_graphic* to = toIndex == 0 ? nullptr : dynamic_cast<SunnyTcsRoute_graphic*>(_routes[toIndex]);
	SunnyTcsLinkLine_graphic* linePtr = new SunnyTcsLinkLine_graphic(this->getNextIndex(),
		dynamic_cast<SunnyTcsRoute_graphic*>(_routes[fromIndex]), to);

	if (toIndex == 0) { _curLine = linePtr; }//没有指定线段的去向
	this->addItem(linePtr);
	return linePtr->getGraphicsIndex();
}



void graphic::SunnyTcsCraft_graphic::setCurrentLinkingLineEndRoute(QPointF pt)
{
	if (_curLine) {
		SunnyTcsCraftGraphicsItem* item = dynamic_cast<SunnyTcsCraftGraphicsItem*>(this->itemAt(pt, QTransform()));
		if (item && item->getGraphicsItemType() == EROUTE) {
			Q_ASSERT(_routes.keys().contains(item->getGraphicsIndex()));
			SunnyTcsRoute_graphic* toRoute = dynamic_cast<SunnyTcsRoute_graphic*>(item);
			Q_ASSERT(toRoute);
			_curLine->_to = toRoute;
			(*_curLine->_from) << *toRoute;
			_linkLines.insert(_curLine->getGraphicsIndex(), _curLine);
			_curLine = nullptr;
		}
		else {
			this->removeItem(_curLine);
			delete _curLine;
			_curLine = nullptr;
		}
	}
}

void graphic::SunnyTcsCraft_graphic::setItemsMoveSelectFlags(bool open)
{
	for (auto ter : this->_routes) {
		SunnyTcsCraftGraphicsItem* item = dynamic_cast<SunnyTcsCraftGraphicsItem*>(ter);
		Q_ASSERT(item);
		item->setFlags(open ?
			(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable) :
			(item->flags() &~(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable))
		);
	}
}

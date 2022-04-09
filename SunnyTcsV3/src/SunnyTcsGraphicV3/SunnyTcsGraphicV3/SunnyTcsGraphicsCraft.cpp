#include "SunnyTcsGraphicsCraft.h"




void SunnyTcsGraphicsCraft::appendRoute(qint32 index, SunnyTcsSonCraft * route)
{
	_allSonCrafts.insert(index, route);
}

void SunnyTcsGraphicsCraft::drawBackground(QPainter * painter, const QRectF & rect)
{
	painter->fillRect(this->sceneRect(), QColor(70, 80, 110));
}

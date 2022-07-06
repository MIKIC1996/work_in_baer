#pragma once

#include "sunnytcsgraphicv3_global.h"
#include "SunnyTcsGraphicsSonCraft.h"

using namespace basic;









class SUNNYTCSGRAPHICV3_EXPORT SunnyTcsGraphicsCraft : public QGraphicsScene , public SunnyTcsCraft ,public SunnyTcsRouteIndexer
{
public:
	SunnyTcsGraphicsCraft(QString craftId):QGraphicsScene(nullptr),SunnyTcsCraft(craftId),SunnyTcsRouteIndexer() {
		setSceneRect(-1000 , -800, 2000, 1600);
		update();
	}
	
	
	virtual ~SunnyTcsGraphicsCraft() {}


	//��������ز����Ƕ���ͨ�����ĵ��ã�ʹ�ø��ӷ��㣬���Ǽ������ϸ�ASSERT���Ի��쳣����������������ѡһ
	//operator[]
	SunnyTcsGraphicsSonCraft& operator[](qint32 index) throw (SunnyTcsException<ERROR_BASIC_UNEXISTED_CRAFT_INDEX>)
	{
		SunnyTcsGraphicsSonCraft* ptr = getCraft(index);
		if (!ptr) throw SunnyTcsException<ERROR_BASIC_UNEXISTED_CRAFT_INDEX>();
		return *ptr;
	}

	const SunnyTcsGraphicsSonCraft& operator[](qint32 index)const throw (SunnyTcsException<ERROR_BASIC_UNEXISTED_CRAFT_INDEX>)
	{
		const SunnyTcsGraphicsSonCraft* ptr = getCraft(index);
		if (!ptr) throw SunnyTcsException<ERROR_BASIC_UNEXISTED_CRAFT_INDEX>();
		return *ptr;
	}

	SunnyTcsGraphicsSonCraft* getCraft(qint32 index) {
		return _allSonCrafts.contains(index) ? dynamic_cast<SunnyTcsGraphicsSonCraft*>(_allSonCrafts[index]) : nullptr;
	}

	const SunnyTcsGraphicsSonCraft* getCraft(qint32 index)const {
		return _allSonCrafts.contains(index) ? dynamic_cast<const SunnyTcsGraphicsSonCraft*>(_allSonCrafts[index]) : nullptr;
	}


	qint32 indexOf(SunnyTcsGraphicsSonCraft*  ptr)const {
		SunnyTcsSonCraft* basePtr = dynamic_cast<SunnyTcsSonCraft*>(ptr);
		Q_ASSERT(basePtr); 
		return _allSonCrafts.values().contains(ptr) ? -1 : _allSonCrafts.key(basePtr);
	}


	qint32 appendNewSonCraft(QPointF pt) {
		SunnyTcsGraphicsSonCraft* sPtr = new SunnyTcsGraphicsSonCraft(this);
		sPtr->setPos(pt);
		this->addItem(sPtr);
		return sPtr->getIndex();
		this->update();
	}


protected:
	// ͨ�� SunnyTcsRouteIndexer �̳�
	virtual void appendRoute(qint32 index, SunnyTcsSonCraft * route) override;
	// ͨ�� QGraphicsScene �̳�
	void drawBackground(QPainter *painter, const QRectF &rect) override;
	

};


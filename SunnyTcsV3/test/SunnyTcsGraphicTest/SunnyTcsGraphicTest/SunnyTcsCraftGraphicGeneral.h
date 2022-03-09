#pragma once

#include "stafix.h"



namespace graphic {
	
	enum E_SunnyTcsGraphicsItemType {
		EROUTE =1,
		ELINKLINE =2
	};


	class SunnyTcsCraftGraphicsItem :public QGraphicsItem {
	public:

		SunnyTcsCraftGraphicsItem(E_SunnyTcsGraphicsItemType type) : QGraphicsItem(nullptr),_type(type) {
			setFlags(QGraphicsItem::ItemIsMovable
				| QGraphicsItem::ItemIsSelectable
				| QGraphicsItem::ItemIsFocusable);
		}
		SunnyTcsCraftGraphicsItem(const SunnyTcsCraftGraphicsItem&) = default;
		virtual ~SunnyTcsCraftGraphicsItem() {}
		SunnyTcsCraftGraphicsItem& operator=(const SunnyTcsCraftGraphicsItem&) = default;

		E_SunnyTcsGraphicsItemType getGraphicsItemType()const {
			return _type;
		}

		virtual qint32 getGraphicsIndex()const = 0;

		// Í¨¹ý QGraphicsItem ¼Ì³Ð
		virtual QRectF boundingRect() const override = 0;
		virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = Q_NULLPTR) override = 0;
		

	protected:
		const E_SunnyTcsGraphicsItemType _type;

	};


	

}
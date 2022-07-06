#pragma once

#include "SunnyTcsGraphicsCraftGeneral.h"



using namespace basic;




class SUNNYTCSGRAPHICV3_EXPORT SunnyTcsGraphicsSonCraft : public SunnyTcsCraftGraphicsItem, public SunnyTcsSonCraft
{
public:
	//ctor
	SunnyTcsGraphicsSonCraft(SunnyTcsRouteIndexer* indexer = nullptr) : SunnyTcsSonCraft(), _indexer(indexer) {
		if (_indexer) {
			_index = _indexer->getNextId();
			_indexer->appendRoute(_index, this);
		}
	}

	//copy ctor
	SunnyTcsGraphicsSonCraft(const SunnyTcsGraphicsSonCraft& rhs) = delete;

	//detor
	virtual ~SunnyTcsGraphicsSonCraft() {
		if (_indexer) {
			_indexer->returnId(_index);
		}
	}

	//operator=
	SunnyTcsGraphicsSonCraft& operator=(const SunnyTcsGraphicsSonCraft&) = delete;


	//运算符重载操作是对普通函数的调用，使用更加方便，但是检查更加严格（ASSERT断言或异常），你可以视情况二选一
	//operator[]
	SunnyTcsGraphicsSonCraft& operator[](qint32 index) throw (SunnyTcsException<ERROR_BASIC_UNEXISTED_CRAFT_INDEX>)
	{
		SunnyTcsGraphicsSonCraft* ptr = dynamic_cast<SunnyTcsGraphicsSonCraft*>(this->getSonCraft(index));
		if(!ptr)throw SunnyTcsException<ERROR_BASIC_UNEXISTED_CRAFT_INDEX>();
		return *ptr;
	}

	SunnyTcsGraphicsSonCraft* getSonCraft(qint32 index) {
		return _sonRoutes.contains(index) ? dynamic_cast<SunnyTcsGraphicsSonCraft*>(_sonRoutes[index]) : nullptr;
	}

	//operator<<
	SunnyTcsGraphicsSonCraft& operator<<(SunnyTcsGraphicsSonCraft& son) throw (SunnyTcsException<ERROR_GRAPHICS_CRAFT_BUILDING_RELATION_BETWEEN_ERR_SONCRAFTS>)
	{
		if (!pushSonCraft(&son)) {
			throw SunnyTcsException<ERROR_GRAPHICS_CRAFT_BUILDING_RELATION_BETWEEN_ERR_SONCRAFTS>();
		}
		return *this;
	}

	bool pushSonCraft(SunnyTcsGraphicsSonCraft* son) {
		if (this == son || _indexer != son->_indexer)return false;
		_sonRoutes.insert(son->getIndex(), son);
		son->_lastRoutes.insert(_index, this);
		return true;
	}

	//operator>>
	SunnyTcsGraphicsSonCraft& operator >> (SunnyTcsGraphicsSonCraft& son) throw (SunnyTcsException<ERROR_BASIC_UNEXISTED_CRAFT_INDEX>) {
		if (!popSonCraft(&son)) {
			throw SunnyTcsException<ERROR_BASIC_UNEXISTED_CRAFT_INDEX>();
		}
		return *this;
	}


	bool popSonCraft(SunnyTcsGraphicsSonCraft* sc) {
		if (sc == this || _indexer != sc->_indexer || 
			!_sonRoutes.contains(sc->getIndex()||
				!sc->_lastRoutes.contains(_index)))return false;
		_sonRoutes.remove(sc->getIndex());
		sc->_lastRoutes.remove(_index);
		return true;
	}




	// 通过 SunnyTcsCraftGraphicsItem 继承
	virtual QRectF boundingRect() const override;
	virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = Q_NULLPTR) override;

protected:
	SunnyTcsRouteIndexer* _indexer;
};










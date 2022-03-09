#pragma once
#include "SunnyTcsCraft_graphic.h"

using namespace basic;

namespace graphic {

	class SunnyTcsCraftGraphicsScene : public QGraphicsScene
	{
	public:
		explicit SunnyTcsCraftGraphicsScene(SunnyTcsCraft_graphic* craft = nullptr) :QGraphicsScene(nullptr), _currentCraft(craft) {}
		SunnyTcsCraftGraphicsScene(const SunnyTcsCraftGraphicsScene&) = default;
		virtual ~SunnyTcsCraftGraphicsScene() {}
		SunnyTcsCraftGraphicsScene& operator=(const SunnyTcsCraftGraphicsScene&) = default;


		void resetCraft(SunnyTcsCraft_graphic* craft =nullptr) {
// 			if (craft&& craft != _currentCraft) {
// 				_currentCraft = craft;
// 			}
// 
// 			if (_currentCraft) {
// 				
// 				for (SunnyTcsRoute* ter : _currentCraft->_routes) {
// 					SunnyTcsRoute_graphic* gter = dynamic_cast<SunnyTcsRoute_graphic*>(ter);
// 					if (!this->items().contains(gter)) {
// 						this->addItem(gter);
// 					}	
// 				}
// 			}
// 			this->update();
		}

		
		void drawBackground(QPainter *painter, const QRectF &rect) {

			painter->fillRect(this->sceneRect(), QColor(60, 60, 60));

		}

	protected:
		SunnyTcsCraft_graphic* _currentCraft;

	};

}




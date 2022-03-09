#pragma once
#include "sunnytcsgraphicv3_global.h"


#define GRAPHICS_LOW_ZVALUE 0
#define GRAPHICS_COORSYS_ZVALUE  1
#define GRAPHICS_PATH_ZVALUE 2 
#define GRAPHICS_POINT_ZVALUE 3
#define GRAPHICS_LOCATION_ZVALUE 4
#define GRAPHICS_VEHICLE_ZVALUE 5
#define GRAPHICS_SELECT_ZVALUE 6


using namespace basic;

//mapItem �� ����
//�����������ڣ���֤���еĵ�ͼͼ�ζ���̳��ڴˣ��Ϳ��԰�ȫ�Ľ���dynamic_castת�����Ӷ��������е��麯����֪��ͼ����ʲô����
class SunnyTcsMapGraphicItem :public QGraphicsItem
{
public:
	//ctor
	SunnyTcsMapGraphicItem(QString name)
		:QGraphicsItem(nullptr), _name(name)
	{
		setFlags(QGraphicsItem::ItemIsMovable
			| QGraphicsItem::ItemIsSelectable
			| QGraphicsItem::ItemIsFocusable
			| QGraphicsItem::ItemSendsGeometryChanges
		);
	}
	//copy ctor
	SunnyTcsMapGraphicItem(const SunnyTcsMapGraphicItem&) = default;
	//dtor
	virtual ~SunnyTcsMapGraphicItem() {}
	//assignment
	SunnyTcsMapGraphicItem& operator=(const SunnyTcsMapGraphicItem&) = default;

	//getter 
	QString getName()const { return _name; }

	//setter
	void SetName(QString name) { _name = name; }

	// ͨ�� QGraphicsItem �̳�
	virtual QRectF boundingRect() const override = 0;
	virtual void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = Q_NULLPTR) override = 0;
	QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;//������scene����


	//����������������������ѡȡ����Ԫ������
	virtual SunnyTcsMapObject_tag getItemTag()const = 0;
	qint32 getItemId()const { return getItemTag()._id; }

protected:
	QString _name; //����

};



//ģ��״̬
enum E_SunnyTcsModelEditStatus {
	E_EDIT = 1, //�༭״̬
	E_RUNNING = 2 //����״̬
};



//��ͼgui��������Ҳ��ͼ��ģ�͵ĳ��࣬�����˸��ֳߴ磬�Լ�ģ��״̬
//�������壬ͨ���ó��࣬��ͼ��Ԫ�ض��󣬿��Ե�֪��ǰģ�͵�״̬���Լ�������Ƴߴ磬�Ӷ��������painter����
class SunnyTcsMapAdjuster
{
public:
	
	SunnyTcsMapAdjuster(qint32 wid, qint32 hei, qint32 resolution)
		:_sceneWid(wid), _sceneHei(hei), _resolution(resolution),_status(E_EDIT),
		_ptIdCounter(0),_phIdCounter(0),_locIdCounter(0),_veIdCounter(0)
	{

	}

	//��ȡID
	qint32 nextPtId()const {
		if (!_ptIdQueue.empty()) {
			qint32 top = _ptIdQueue.top();
			_ptIdQueue.pop();
			return top;
		}
		return ++_ptIdCounter;
	}

	qint32 nextPhId()const {
		if (!_phIdQueue.empty()) {
			qint32 top = _phIdQueue.top();
			_phIdQueue.pop();
			return top;
		}
		return ++_phIdCounter;
	}

	qint32 nextLocId()const {
		if (!_locIdQueue.empty()) {
			qint32 top = _locIdQueue.top();
			_locIdQueue.pop();
			return top;
		}
		return ++_locIdCounter;
	}

	qint32 nextVeId() const {
		if (!_veIdQueue.empty()) {
			qint32 top = _veIdQueue.top();
			_veIdQueue.pop();
			return top;
		}
		return ++_veIdCounter;
	}

	//�黹ID
	void returnPtId(qint32 id)const {
		_ptIdQueue.push(id);
	}

	void returnPhId(qint32 id)const {
		_phIdQueue.push(id);
	}

	void returnLocId(qint32 id)const {
		_locIdQueue.push(id);
	}

	void returnVeId(qint32 id)const {
		_veIdQueue.push(id);
	}

	//״̬
	E_SunnyTcsModelEditStatus _status = E_EDIT;

	//��ͼ��� ����ֱ���
	qreal _sceneWid;		//scene ��
	qreal _sceneHei;		//scene ��		
	qreal _resolution;		//����ֱ���

	//����ɫ
	QColor _backColor = QColor(60, 60, 60); 
	//select ѡ�е���ɫ����ͳһ
	QColor _item_select_color = QColor(247, 198, 54);
	//����ɫҲ����ͳһ
	QColor _item_warning_color = Qt::red; 
	//������ɫ
	QColor _item_error_color = Qt::red;

protected:
	mutable qint32 _ptIdCounter;
	mutable qint32 _phIdCounter;
	mutable qint32 _locIdCounter;
	mutable qint32 _veIdCounter;

	mutable std::priority_queue<qint32 ,std::vector<qint32>,std::greater<qint32>> _ptIdQueue;//������ɾ������黹ID,�Թ�����ʹ��
	mutable std::priority_queue<qint32, std::vector<qint32>, std::greater<qint32>> _phIdQueue;
	mutable std::priority_queue<qint32, std::vector<qint32>, std::greater<qint32>> _locIdQueue;
	mutable std::priority_queue<qint32, std::vector<qint32>, std::greater<qint32>> _veIdQueue;

};
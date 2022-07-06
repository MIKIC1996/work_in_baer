#pragma once

#include <QMainWindow>
#include "ui_SunnyTcsMapEditor.h"
#include "SunnyTcsSupervisoryV3_general.h"
#include "SunnyTcsDockWidget.h"
#include "SunnyTcsLocationEditWidget.h"


class SunnyTcsTreeWidgetItem :public QTreeWidgetItem{
public:
	enum ContentType {
		EmapItem = 1,
		EgroupItem = 2
	};
	//ctor
	SunnyTcsTreeWidgetItem(QTreeWidgetItem* parent) :QTreeWidgetItem(parent) {}
	
	//��ȡ���item���������������
	virtual ContentType getContentType()const = 0;

};



//��������ITEM����̳�


//������item����̳�
class SunnyTcsObjectTreeWidgetMapItem : public QTreeWidgetItem {
public:
	SunnyTcsObjectTreeWidgetMapItem(const SunnyTcsMapGraphicItem* item, QTreeWidgetItem *parent = nullptr)
		:QTreeWidgetItem(parent),_item(item){
		this->setText(0,item->getName());
	}

	virtual ~SunnyTcsObjectTreeWidgetMapItem() {
		qDebug() << "SunnyTcsObjectTreeWidgetItem clear";
	}

	//getter
	const SunnyTcsMapGraphicItem* getItem()const { return _item; }
	//setter
	void setItem(const SunnyTcsMapGraphicItem* item) { _item = item; }

private:
	const SunnyTcsMapGraphicItem* _item;
};


//��ͼ�༭��������
class SunnyTcsMapEditor : public QMainWindow
{
	Q_OBJECT
public:
	SunnyTcsMapEditor(QWidget *parent = Q_NULLPTR);
	~SunnyTcsMapEditor();

	//��ʼ��
	void init();

	//�������Ƴ�ģ��
	void setModel(const QJsonObject& mapJson);
	void setModel(SunnyTcsGraphicsModel* model);
	void removeCurrentModel();

private:
	//���� object treewidget
	void updateObjectTreeWidget();
	void addObjectInTreeWidget(const SunnyTcsMapGraphicItem* item);
	void delObjectInTreeWidget(const SunnyTcsMapGraphicItem* item);
	void setCurrenctTreeItemInTreeWidget(const SunnyTcsMapGraphicItem* item);
	void initObjectTreeWidget();

	//�������Ա༭��
	void updateAttribute(SunnyTcsMapGraphicItem* item);
	void updateAttribute(SunnyTcsGraphicsVehicle* item);
	void updateAttribute(SunnyTcsGraphicsPoint* item);
	void updateAttribute(SunnyTcsGraphicsPath* item);
	void updateAttribute(SunnyTcsGraphicsLocation* item);
	void updateModelAttribute(); //ģ����
	void updatePointsGroupAttribute(); //����
	void updatePathsGroupAttribute();	//·����
	void updateLocationGroupAttribute();	//��λ��
	void setPointAttribution();
	void setPathAttribution();
	void setLocationAttribution();
	void setVehicleAttribution();

	//��ʼ��ui
	void initUi();
	void initPointAttributionTable();
	void initPathAttributionTable();
	void initLocationAttributionTable();
	void initVehicleAttributionTable();
	void initModelAttributionTable();

	//�����ź����
	void linkSignalsAndSlots();
	//��ʼ������
	void initOperation();
	//��ťʹ��
	void disableAllButtion();//�����߶εȲ��������з�����а�ť
	void enableAllButtion();//������ɺ��������а�ť

	//����
	void removeItemWhenMousePressed(QPointF pt);
	void paintSelectAeraWhenMousePressed(QPointF pt);
	void paintPointWhenMousePressed(QPointF pt);
	void paintPathWhenMousePressed(QPointF pt);
	void paintLocationWhenMousePressed(QPointF pt);
	void paintVehicleWhenMousePressed(QPointF pt);
	//���ӵ��ɾ�����ʱ��Խ��������Ϣ���в���
	void updatePointInfoWhenEditPoint();


	//�ۺ���
private slots :
	//������
	void onMouseMove(QPointF pt);
	void onMouseRelease(QPointF pt);
	void onMousePress(QPointF pt);
	void onWheelChange(int angle);

	//��ͼ�������
	//ѡȡ����
	void onPaintDefaultTbtnClicked();
	void onPaintSelectTbtnClicked();
	void onPaintCancelSelectTbtnClicked();

	void onPaintMoveTbtnClicked();
	void onPaintMoveCsTbtnClicked();
	void onPaintDeleteTbtnClicked();

	//ͼ��Ԫ��
	void onPaintPointTbtnClicked();
	void onPaintDirPathTbtnClicked();
	void onPaintArchPathTbtnClicked();
	void onPaintLocationTbtnClicked();
	void onPaintVehicleTbtnClicked();
	
	//��������


	//�˵���
	//�༭ѡ��
	void flushUndoRedoAcnEnable();
	void onUndoAcnTriggered();
	void onRedoAcnTriggered();
	void updateTempUserOperationStack();//�ڳ���������µĲ���,��ô֮ǰ�����Ķ����Ͳ��ñ����ˣ�Ҫɾ��

	//����ѡ��
	void onPaintPointAcnTriggered();
	void onPaintDirLineAcnTriggered();
	void onPaintArchLineAcnTriggered();
	void onPaintLocationAcnTriggered();
	void onMenuDelSelectedAcnTriggered();
	void onMenuClearMapAcnTriggered();
	void onMenuAddVehicleAcnTriggered();
	void onMenuToolSelectAcnTriggered();
	void onMenuToolAntiSelectAcnTriggered();
	void onMenuToolMoveAcnTriggered();
	void onMenuToolMoveCsAcnTriggered();

	//��ͼѡ��
	void onMenuPanelPaintAcnTriggered();
	void onMenuPanelObjectgAcnTriggered();
	void onMenuPanelAttributeAcnTriggered();
	void onMenuPanelGroupAcnTriggered();

	//ѡ��ѡ��
	

	//������
	void onNewFileAcnTriggered();
	void onSaveAcnTriggered();
	void onCloseAcnTriggered();

	void onSetBackImageAcnTriggered();

	//����ϵ����
	void onXAxisAcnTriggered();
	void onYAxisAcnTriggered();
	void onAxisRotateAcnTriggered();

	//���亯��
	void onLeftAlignAcnTriggered();
	void onRightAlignAcnTriggered();
	void onTopAlignAcnTriggered();
	void onBottomAlignAcnTriggered();

	//�Ų�����
	void onEqualDistributionAcnTriggered();
	void onYEqualDistributionAcnTriggered();

	//����鿴��
	void onObjectTreeWidItemPressed(QTreeWidgetItem* item, int column);
	void onObjectTreeWidCurrentItemChanged(QTreeWidgetItem* current, QTreeWidgetItem* previous);
	void onObjectTreeWidNewGroupAcnTriggered();

	//���Ա༭��
	void onAttributeOkTbtnClicked();
	void onAttributeLocAddTbtnClicked();
	void onAttributeLocDecTbtnClicked();
	void onAttributeLocAcnEditClicked();
	void onAttributeFlushClicked();//ˢ��

private:
	Ui::SunnyTcsMapEditor ui;
	SunnyTcsGraphicsModel* _model;
	
	//�˵���
	//�༭ѡ��
	QStack<SunnyTcsUserInterfaceOperation> _operations;//֧�ֳ��������� 
	QStack<SunnyTcsUserInterfaceOperation> _tempOperations;

	//��ͼ������
	QButtonGroup* _paintTbtnGroup;

	//�ƶ�����
	QHash<SunnyTcsMapGraphicItem*, QPointF> _startMovePosition;
	QList<QGraphicsItem*> _currentSelected;

	//�������Ƴ�ʼ��
	QMenu* _paintVehicleMenu;//��ͼ������ѡ���agv�б�
	QList<QAction*> _menuAddVehicleAcnList; //��ӳ�����actions���˵����ͻ�ͼ ��������Щaction,
	SunnyTcsAgvCode _currentAgvCode;

	//����鿴��
	//�Ҽ��˵���
	QMenu* _ObjectTreeWidPointMenu;
	QList<QAction*> _objectTreeActionList;
	E_SunnyTcsMapObject_type _newGrouptype;//��Ҫ�������������

	//���Ա༭��
	SunnyTcsMapGraphicItem* _currentEditingItem = nullptr;

	//״̬��
	QCheckBox* _trackCbox;

	//�ⲿ����
	SunnyTcsLocationEditWidget* _locEditWidget  ;

};

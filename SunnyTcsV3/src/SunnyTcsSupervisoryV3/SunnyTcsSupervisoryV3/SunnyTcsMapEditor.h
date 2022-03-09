#pragma once

#include <QMainWindow>
#include "ui_SunnyTcsMapEditor.h"
#include "SunnyTcsSupervisoryV3_general.h"
#include "SunnyTcsDockWidget.h"






//������item����̳�
class SunnyTcsObjectTreeWidgetItem : public QTreeWidgetItem {
public:
	SunnyTcsObjectTreeWidgetItem(qint32 id ,QString name,  QTreeWidgetItem *parent = nullptr):QTreeWidgetItem(parent){
		_id = id;
		this->setText(0,name);
	}

	virtual ~SunnyTcsObjectTreeWidgetItem() {}

	qint32 getId()const { return _id; }
	void setId(qint32 id) { _id = id; }

private:
	qint32 _id;
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


	//���� object treewidget
	void updateObjectTreeWidget();
	void addObjectInTreeWidget(qint32 id, QString name, E_SunnyTcsMapObject_type type);
	void delObjectInTreeWidget(qint32 id, E_SunnyTcsMapObject_type type);
	void clearObjectTreeWidget();


	//�������Ա༭��
	void updateAttribute(SunnyTcsGraphicsVehicle* item);
	void updateAttribute(SunnyTcsGraphicsPoint* item);
	void updateAttribute(SunnyTcsGraphicsPath* item);
	void updateAttribute(SunnyTcsGraphicsLocation* item);

private:
	//��ʼ��ui
	void initUi();
	//�����ź����
	void linkSignalsAndSlots();
	//��ʼ������
	void initOperation();

	//����
	void paintPointWhenMousePressed(QPointF pt);

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
	void onPaintMoveTbtnClicked();
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

	//��ͼѡ��
	void onToolPanelPaintAcnTriggered();
	void onToolPanelObjectgAcnTriggered();
	void onToolPanelAttributeAcnTriggered();
	void onToolPanelGroupAcnTriggered();


	//������
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


	//���Ա༭��
	void onAttributeOkTbtnClicked();
	void onAttributeFlushClicked();
	
	

private:
	QButtonGroup* _paintTbtnGroup;

	//�������Ƴ�ʼ��
	QMenu* _paintVehicleMenu;//��ͼ������ѡ���agv�б�
	QList<QAction*> _menuAddVehicleAcnList; //��ӳ�����actions���˵����ͻ�ͼ ��������Щaction,
	SunnyTcsAgvCode _currentAgvCode;

	//����鿴��
	//�Ҽ��˵���
	QMenu* _ObjectTreeWidPointMenu;


	Ui::SunnyTcsMapEditor ui;
	SunnyTcsGraphicsModel* _model;


	//֧�� ���������� 
	QStack<SunnyTcsUserInterfaceOperation> _operations;
	QStack<SunnyTcsUserInterfaceOperation> _tempOperations;
	

};

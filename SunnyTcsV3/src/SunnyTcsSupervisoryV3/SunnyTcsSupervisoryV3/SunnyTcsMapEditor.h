#pragma once

#include <QMainWindow>
#include "ui_SunnyTcsMapEditor.h"
#include "SunnyTcsSupervisoryV3_general.h"
#include "SunnyTcsDockWidget.h"






//对象数item对象继承
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



//地图编辑器主界面
class SunnyTcsMapEditor : public QMainWindow
{
	Q_OBJECT
public:
	SunnyTcsMapEditor(QWidget *parent = Q_NULLPTR);
	~SunnyTcsMapEditor();

	//初始化
	void init();


	//更新 object treewidget
	void updateObjectTreeWidget();
	void addObjectInTreeWidget(qint32 id, QString name, E_SunnyTcsMapObject_type type);
	void delObjectInTreeWidget(qint32 id, E_SunnyTcsMapObject_type type);
	void clearObjectTreeWidget();


	//更新属性编辑器
	void updateAttribute(SunnyTcsGraphicsVehicle* item);
	void updateAttribute(SunnyTcsGraphicsPoint* item);
	void updateAttribute(SunnyTcsGraphicsPath* item);
	void updateAttribute(SunnyTcsGraphicsLocation* item);

private:
	//初始化ui
	void initUi();
	//连接信号与槽
	void linkSignalsAndSlots();
	//初始化点赞
	void initOperation();

	//画点
	void paintPointWhenMousePressed(QPointF pt);

	//槽函数
private slots :
	//鼠标操作
	void onMouseMove(QPointF pt);
	void onMouseRelease(QPointF pt);
	void onMousePress(QPointF pt);
	void onWheelChange(int angle);

	//绘图界面操作
	//选取工具
	void onPaintDefaultTbtnClicked();
	void onPaintMoveTbtnClicked();
	void onPaintDeleteTbtnClicked();

	//图形元素
	void onPaintPointTbtnClicked();
	void onPaintDirPathTbtnClicked();
	void onPaintArchPathTbtnClicked();
	void onPaintLocationTbtnClicked();
	void onPaintVehicleTbtnClicked();
	
	//其他工具


	//菜单栏
	//编辑选项
	void onUndoAcnTriggered();
	void onRedoAcnTriggered();
	void updateTempUserOperationStack();//在撤销后进行新的操作,那么之前撤销的动作就不用保存了，要删除

	//工具选项
	void onPaintPointAcnTriggered();
	void onPaintDirLineAcnTriggered();
	void onPaintArchLineAcnTriggered();
	void onPaintLocationAcnTriggered();
	void onMenuDelSelectedAcnTriggered();
	void onMenuClearMapAcnTriggered();
	void onMenuAddVehicleAcnTriggered();

	//视图选项
	void onToolPanelPaintAcnTriggered();
	void onToolPanelObjectgAcnTriggered();
	void onToolPanelAttributeAcnTriggered();
	void onToolPanelGroupAcnTriggered();


	//工具栏
	//坐标系函数
	void onXAxisAcnTriggered();
	void onYAxisAcnTriggered();
	void onAxisRotateAcnTriggered();

	//对其函数
	void onLeftAlignAcnTriggered();
	void onRightAlignAcnTriggered();
	void onTopAlignAcnTriggered();
	void onBottomAlignAcnTriggered();

	//排布函数
	void onEqualDistributionAcnTriggered();
	void onYEqualDistributionAcnTriggered();

	//对象查看器
	void onObjectTreeWidItemPressed(QTreeWidgetItem* item, int column);
	void onObjectTreeWidCurrentItemChanged(QTreeWidgetItem* current, QTreeWidgetItem* previous);


	//属性编辑器
	void onAttributeOkTbtnClicked();
	void onAttributeFlushClicked();
	
	

private:
	QButtonGroup* _paintTbtnGroup;

	//车辆绘制初始化
	QMenu* _paintVehicleMenu;//绘图面板可以选择的agv列表
	QList<QAction*> _menuAddVehicleAcnList; //添加车辆的actions，菜单栏和绘图 都引用这些action,
	SunnyTcsAgvCode _currentAgvCode;

	//对象查看器
	//右键菜单栏
	QMenu* _ObjectTreeWidPointMenu;


	Ui::SunnyTcsMapEditor ui;
	SunnyTcsGraphicsModel* _model;


	//支持 撤销与重做 
	QStack<SunnyTcsUserInterfaceOperation> _operations;
	QStack<SunnyTcsUserInterfaceOperation> _tempOperations;
	

};

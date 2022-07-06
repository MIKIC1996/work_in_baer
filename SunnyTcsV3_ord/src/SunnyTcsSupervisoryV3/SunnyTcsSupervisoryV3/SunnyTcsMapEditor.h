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
	
	//获取这个item所包含对象的类型
	virtual ContentType getContentType()const = 0;

};



//对象树组ITEM对象继承


//对象数item对象继承
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


//地图编辑器主界面
class SunnyTcsMapEditor : public QMainWindow
{
	Q_OBJECT
public:
	SunnyTcsMapEditor(QWidget *parent = Q_NULLPTR);
	~SunnyTcsMapEditor();

	//初始化
	void init();

	//设置与移除模型
	void setModel(const QJsonObject& mapJson);
	void setModel(SunnyTcsGraphicsModel* model);
	void removeCurrentModel();

private:
	//更新 object treewidget
	void updateObjectTreeWidget();
	void addObjectInTreeWidget(const SunnyTcsMapGraphicItem* item);
	void delObjectInTreeWidget(const SunnyTcsMapGraphicItem* item);
	void setCurrenctTreeItemInTreeWidget(const SunnyTcsMapGraphicItem* item);
	void initObjectTreeWidget();

	//更新属性编辑器
	void updateAttribute(SunnyTcsMapGraphicItem* item);
	void updateAttribute(SunnyTcsGraphicsVehicle* item);
	void updateAttribute(SunnyTcsGraphicsPoint* item);
	void updateAttribute(SunnyTcsGraphicsPath* item);
	void updateAttribute(SunnyTcsGraphicsLocation* item);
	void updateModelAttribute(); //模型组
	void updatePointsGroupAttribute(); //点组
	void updatePathsGroupAttribute();	//路径组
	void updateLocationGroupAttribute();	//工位组
	void setPointAttribution();
	void setPathAttribution();
	void setLocationAttribution();
	void setVehicleAttribution();

	//初始化ui
	void initUi();
	void initPointAttributionTable();
	void initPathAttributionTable();
	void initLocationAttributionTable();
	void initVehicleAttributionTable();
	void initModelAttributionTable();

	//连接信号与槽
	void linkSignalsAndSlots();
	//初始化动作
	void initOperation();
	//按钮使能
	void disableAllButtion();//绘制线段等操作过程中封禁所有按钮
	void enableAllButtion();//绘制完成后，启用所有按钮

	//画点
	void removeItemWhenMousePressed(QPointF pt);
	void paintSelectAeraWhenMousePressed(QPointF pt);
	void paintPointWhenMousePressed(QPointF pt);
	void paintPathWhenMousePressed(QPointF pt);
	void paintLocationWhenMousePressed(QPointF pt);
	void paintVehicleWhenMousePressed(QPointF pt);
	//增加点和删除点的时候对界面相关信息进行操作
	void updatePointInfoWhenEditPoint();


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
	void onPaintSelectTbtnClicked();
	void onPaintCancelSelectTbtnClicked();

	void onPaintMoveTbtnClicked();
	void onPaintMoveCsTbtnClicked();
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
	void flushUndoRedoAcnEnable();
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
	void onMenuToolSelectAcnTriggered();
	void onMenuToolAntiSelectAcnTriggered();
	void onMenuToolMoveAcnTriggered();
	void onMenuToolMoveCsAcnTriggered();

	//视图选项
	void onMenuPanelPaintAcnTriggered();
	void onMenuPanelObjectgAcnTriggered();
	void onMenuPanelAttributeAcnTriggered();
	void onMenuPanelGroupAcnTriggered();

	//选择选项
	

	//工具栏
	void onNewFileAcnTriggered();
	void onSaveAcnTriggered();
	void onCloseAcnTriggered();

	void onSetBackImageAcnTriggered();

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
	void onObjectTreeWidNewGroupAcnTriggered();

	//属性编辑器
	void onAttributeOkTbtnClicked();
	void onAttributeLocAddTbtnClicked();
	void onAttributeLocDecTbtnClicked();
	void onAttributeLocAcnEditClicked();
	void onAttributeFlushClicked();//刷新

private:
	Ui::SunnyTcsMapEditor ui;
	SunnyTcsGraphicsModel* _model;
	
	//菜单栏
	//编辑选项
	QStack<SunnyTcsUserInterfaceOperation> _operations;//支持撤销与重做 
	QStack<SunnyTcsUserInterfaceOperation> _tempOperations;

	//绘图面板相关
	QButtonGroup* _paintTbtnGroup;

	//移动触发
	QHash<SunnyTcsMapGraphicItem*, QPointF> _startMovePosition;
	QList<QGraphicsItem*> _currentSelected;

	//车辆绘制初始化
	QMenu* _paintVehicleMenu;//绘图面板可以选择的agv列表
	QList<QAction*> _menuAddVehicleAcnList; //添加车辆的actions，菜单栏和绘图 都引用这些action,
	SunnyTcsAgvCode _currentAgvCode;

	//对象查看器
	//右键菜单栏
	QMenu* _ObjectTreeWidPointMenu;
	QList<QAction*> _objectTreeActionList;
	E_SunnyTcsMapObject_type _newGrouptype;//新要创建的组的类型

	//属性编辑器
	SunnyTcsMapGraphicItem* _currentEditingItem = nullptr;

	//状态栏
	QCheckBox* _trackCbox;

	//外部窗口
	SunnyTcsLocationEditWidget* _locEditWidget  ;

};

#pragma once
#include "SunnyTcsSupervisoryV3_general.h"


class SunnyTcsDockWidget :public QDockWidget
{
public:
	explicit SunnyTcsDockWidget(QWidget* parent = nullptr) :QDockWidget(parent){
		

	}
	virtual ~SunnyTcsDockWidget() {}
};



#define  ICON_WIDTH     20
#define  ICON_HEIGHT    20
#define  BUTTON_WIDTH   30
#define  BUTTON_HEIGHT  30
#define  TITLE_HEIGHT   30


class SunnyTcsTitleBar :public QWidget {
public:
	Q_OBJECT
public:
	SunnyTcsTitleBar(QWidget *parent);
	void SetTitleBackground(QColor ColorL, QColor ColorR); // 供外部调用设置标题栏背景
	void SetTitleContent(QString content); // ……………设置标题栏内容
	void SetTitleIcon(QString iconPath);   // ……………设置标题栏图标

	public slots:
	void ShowSmall();      //槽函数，最小化
	void ShowMaxRestore(); // 槽函数 ，最大化或者还原
protected:
	void mousePressEvent(QMouseEvent *e);           // 鼠标点击事件
	void mouseMoveEvent(QMouseEvent *e);            // 鼠标移动事件
	void mouseDoubleClickEvent(QMouseEvent *e);     // 鼠标双击事件

private:

	void InitTitleBar();                 // 初始化标题栏
	void paintEvent(QPaintEvent *event); // 重载绘画函数

	bool m_MaxNormal;

	QToolButton *m_Minimize;             // 最小化按钮
	QToolButton *m_Maximize;             // 最大化按钮
	QToolButton *m_Close;                // 关闭按钮

	QPixmap *m_ClosePix;	//关闭按钮的图片

	QPixmap *m_RestorePix;  // 还原按钮的图片
	QPixmap *m_MaxPix;      // 最大化按钮的图片

	QPixmap *m_MinPix;      // 最小化按钮的图片

	QPoint m_StartPos;      // 记录窗口开始的位置
	QPoint m_ClickPos;

	QLabel *m_TitleIcon;    // 标题栏图标
	QLabel *m_TitleConten;  // 标题栏标题
	QLabel m_TitleLabel;

	QColor m_ColorL;         // 标题栏渐变色
	QColor m_ColorR;         // 标题栏渐变色

	QWidget *m_Parent;       //父窗体

};
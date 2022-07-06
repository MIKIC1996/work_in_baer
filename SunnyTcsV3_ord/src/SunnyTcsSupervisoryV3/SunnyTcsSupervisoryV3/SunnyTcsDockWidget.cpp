#include "SunnyTcsDockWidget.h"



SunnyTcsTitleBar::SunnyTcsTitleBar(QWidget *parent) :m_ColorL(QColor(0, 0, 0)),
m_ColorR(QColor(255, 255, 255)) // 初始化渐变色（白->黑渐变）
{

	this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);  // 隐藏默认的标题栏
	m_Parent = parent;       // 获取标题栏的父窗体，用来控制窗口放大，缩小，关闭等行为
	m_MaxNormal = false;     // 初始化窗口不是最大化状态
	InitTitleBar();          // 初始化标题栏

							 // 连接标题栏三个按钮到相应的槽函数中
	connect(m_Close, SIGNAL(clicked()), m_Parent, SLOT(close()));
	connect(m_Minimize, SIGNAL(clicked()), this, SLOT(ShowSmall()));
	connect(m_Maximize, SIGNAL(clicked()), this, SLOT(ShowMaxRestore()));
}


void SunnyTcsTitleBar::InitTitleBar()
{
	m_Close = new QToolButton(this);                              // 关闭按钮
	m_ClosePix = new QPixmap(":/resource/res/qss/editor.qss");               // 关闭按钮图片
	m_Close->setIcon(*m_ClosePix);
	m_Close->setToolTip("关闭");                                   // 显示提示文字
	m_Close->setIconSize(QSize(ICON_WIDTH, ICON_HEIGHT));         // 设置图片的大小
	m_Close->setFixedSize(m_ClosePix->size());                   // 设置按钮大小为图片的大小
	m_Close->setStyleSheet("border-style:flat");                 // 设置按钮背景透明

	m_Maximize = new QToolButton(this);                          // 最大化按钮
	m_MaxPix = new QPixmap(":/resource/res/qss/editor.qss");
	m_RestorePix = new QPixmap(":/resource/res/qss/editor.qss");
	m_Maximize->setIcon(*m_MaxPix);
	m_Maximize->setToolTip("最大化");
	m_Maximize->setIconSize(QSize(ICON_WIDTH, ICON_HEIGHT));
	m_Maximize->setFixedSize(m_MaxPix->size());
	m_Maximize->setStyleSheet("border-style:flat");

	m_Minimize = new QToolButton(this);                         // 最小化按钮
	m_MinPix = new QPixmap(":/resource/res/qss/editor.qss");
	m_Minimize->setIcon(*m_MinPix);
	m_Minimize->setToolTip("最小化");
	m_Minimize->setIconSize(QSize(ICON_WIDTH, ICON_HEIGHT));
	m_Minimize->setFixedSize(m_MinPix->size());
	m_Minimize->setStyleSheet("border-style:flat");

	m_TitleConten = new QLabel(this);                          // 标题栏文字
	QFont TitleFont;
	TitleFont.setPointSize(12);
	m_TitleConten->setFont(TitleFont);
	m_TitleConten->setText(tr("t"));

	m_TitleIcon = new QLabel(this);                            // 标题栏左上角图标
	m_TitleIcon->setPixmap(QPixmap(":/resource/res/qss/editor.qss"));


	QHBoxLayout *hbox = new QHBoxLayout(this);           // 新建水平容器，把所有控件放在容器中
	hbox->addWidget(m_TitleIcon);
	hbox->addWidget(m_TitleConten);
	hbox->addWidget(m_Minimize);
	hbox->addWidget(m_Maximize);
	hbox->addWidget(m_Close);

	hbox->setSpacing(5);                      // 设置容器的属性，标题栏高度等
	hbox->setContentsMargins(5, 2, 5, 2);
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	this->setFixedHeight(TITLE_HEIGHT);
	this->setStyleSheet("border-style:flat");
	setAttribute(Qt::WA_TranslucentBackground);

}

/*用于重新绘制标题栏，当外部调用了设置标题栏相关属性的函数时调用*/
void SunnyTcsTitleBar::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);

	QLinearGradient linearGradient(QPointF(0, 0), QPointF(0, this->height()));

	// 设置渐变的颜色，如果m_ColorL和m_ColorR相同时为纯色，而不是渐变色
	linearGradient.setColorAt(0, m_ColorL);
	linearGradient.setColorAt(1, m_ColorR);

	linearGradient.setSpread(QGradient::ReflectSpread);
	painter.setBrush(linearGradient);
	
	QPainterPath pathBack;                 // 先在QPainterPath画图，再用QPainter显示出来
	pathBack.setFillRule(Qt::WindingFill);
	pathBack.addRoundedRect(QRect(0, 0, this->width(), this->height()), 0, 0);
	painter.drawPath(pathBack);

}

// 最小化
void SunnyTcsTitleBar::ShowSmall()
{
	parentWidget()->showMinimized();
}

//最大化/还原
void SunnyTcsTitleBar::ShowMaxRestore()
{
	if (m_MaxNormal) {
		parentWidget()->showNormal();
		m_MaxNormal = !m_MaxNormal;
		m_Maximize->setToolTip("最大化");
		m_Maximize->setIcon(*m_MaxPix);
	}
	else {
		parentWidget()->showMaximized();
		m_Maximize->setToolTip("向下还原");
		m_MaxNormal = !m_MaxNormal;
		m_Maximize->setIcon(*m_RestorePix);
	}
}

// 当鼠标点击了标题栏，记录下当时的位置
void SunnyTcsTitleBar::mousePressEvent(QMouseEvent *e)
{
	m_StartPos = e->globalPos();
	m_ClickPos = mapToParent(e->pos());
}

// 鼠标移动
void SunnyTcsTitleBar::mouseMoveEvent(QMouseEvent *e)
{
	if (m_MaxNormal)  // 如果处于最大化状态，则不能移动
		return;
	parentWidget()->move(e->globalPos() - m_ClickPos);
}

// 双击鼠标左键和放大按钮效果一致
void SunnyTcsTitleBar::mouseDoubleClickEvent(QMouseEvent *e)
{
	if (e->button() == Qt::LeftButton)
	{
		ShowMaxRestore();
	}
}



//设置标题栏的渐变色
void SunnyTcsTitleBar::SetTitleBackground(QColor ColorL, QColor ColorR)
{
	m_ColorL = ColorL;
	m_ColorR = ColorR;

	update();     // 通知更改，系统自动条用PainterEvent()函数
}


// 设置标题栏显示的文字
void SunnyTcsTitleBar::SetTitleContent(QString content)
{
	m_TitleConten->setText(content);
}

// 设置标题栏左上角的图标
void SunnyTcsTitleBar::SetTitleIcon(QString iconPath)
{
	QPixmap map(iconPath);
	m_TitleIcon->setPixmap(map);

}


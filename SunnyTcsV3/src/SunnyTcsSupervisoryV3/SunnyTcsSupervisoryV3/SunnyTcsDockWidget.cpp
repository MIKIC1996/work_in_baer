#include "SunnyTcsDockWidget.h"



SunnyTcsTitleBar::SunnyTcsTitleBar(QWidget *parent) :m_ColorL(QColor(0, 0, 0)),
m_ColorR(QColor(255, 255, 255)) // ��ʼ������ɫ����->�ڽ��䣩
{

	this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);  // ����Ĭ�ϵı�����
	m_Parent = parent;       // ��ȡ�������ĸ����壬�������ƴ��ڷŴ���С���رյ���Ϊ
	m_MaxNormal = false;     // ��ʼ�����ڲ������״̬
	InitTitleBar();          // ��ʼ��������

							 // ���ӱ�����������ť����Ӧ�Ĳۺ�����
	connect(m_Close, SIGNAL(clicked()), m_Parent, SLOT(close()));
	connect(m_Minimize, SIGNAL(clicked()), this, SLOT(ShowSmall()));
	connect(m_Maximize, SIGNAL(clicked()), this, SLOT(ShowMaxRestore()));
}


void SunnyTcsTitleBar::InitTitleBar()
{
	m_Close = new QToolButton(this);                              // �رհ�ť
	m_ClosePix = new QPixmap(":/resource/res/qss/editor.qss");               // �رհ�ťͼƬ
	m_Close->setIcon(*m_ClosePix);
	m_Close->setToolTip("�ر�");                                   // ��ʾ��ʾ����
	m_Close->setIconSize(QSize(ICON_WIDTH, ICON_HEIGHT));         // ����ͼƬ�Ĵ�С
	m_Close->setFixedSize(m_ClosePix->size());                   // ���ð�ť��СΪͼƬ�Ĵ�С
	m_Close->setStyleSheet("border-style:flat");                 // ���ð�ť����͸��

	m_Maximize = new QToolButton(this);                          // ��󻯰�ť
	m_MaxPix = new QPixmap(":/resource/res/qss/editor.qss");
	m_RestorePix = new QPixmap(":/resource/res/qss/editor.qss");
	m_Maximize->setIcon(*m_MaxPix);
	m_Maximize->setToolTip("���");
	m_Maximize->setIconSize(QSize(ICON_WIDTH, ICON_HEIGHT));
	m_Maximize->setFixedSize(m_MaxPix->size());
	m_Maximize->setStyleSheet("border-style:flat");

	m_Minimize = new QToolButton(this);                         // ��С����ť
	m_MinPix = new QPixmap(":/resource/res/qss/editor.qss");
	m_Minimize->setIcon(*m_MinPix);
	m_Minimize->setToolTip("��С��");
	m_Minimize->setIconSize(QSize(ICON_WIDTH, ICON_HEIGHT));
	m_Minimize->setFixedSize(m_MinPix->size());
	m_Minimize->setStyleSheet("border-style:flat");

	m_TitleConten = new QLabel(this);                          // ����������
	QFont TitleFont;
	TitleFont.setPointSize(12);
	m_TitleConten->setFont(TitleFont);
	m_TitleConten->setText(tr("t"));

	m_TitleIcon = new QLabel(this);                            // ���������Ͻ�ͼ��
	m_TitleIcon->setPixmap(QPixmap(":/resource/res/qss/editor.qss"));


	QHBoxLayout *hbox = new QHBoxLayout(this);           // �½�ˮƽ�����������пؼ�����������
	hbox->addWidget(m_TitleIcon);
	hbox->addWidget(m_TitleConten);
	hbox->addWidget(m_Minimize);
	hbox->addWidget(m_Maximize);
	hbox->addWidget(m_Close);

	hbox->setSpacing(5);                      // �������������ԣ��������߶ȵ�
	hbox->setContentsMargins(5, 2, 5, 2);
	setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	this->setFixedHeight(TITLE_HEIGHT);
	this->setStyleSheet("border-style:flat");
	setAttribute(Qt::WA_TranslucentBackground);

}

/*�������»��Ʊ����������ⲿ���������ñ�����������Եĺ���ʱ����*/
void SunnyTcsTitleBar::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);

	QLinearGradient linearGradient(QPointF(0, 0), QPointF(0, this->height()));

	// ���ý������ɫ�����m_ColorL��m_ColorR��ͬʱΪ��ɫ�������ǽ���ɫ
	linearGradient.setColorAt(0, m_ColorL);
	linearGradient.setColorAt(1, m_ColorR);

	linearGradient.setSpread(QGradient::ReflectSpread);
	painter.setBrush(linearGradient);
	
	QPainterPath pathBack;                 // ����QPainterPath��ͼ������QPainter��ʾ����
	pathBack.setFillRule(Qt::WindingFill);
	pathBack.addRoundedRect(QRect(0, 0, this->width(), this->height()), 0, 0);
	painter.drawPath(pathBack);

}

// ��С��
void SunnyTcsTitleBar::ShowSmall()
{
	parentWidget()->showMinimized();
}

//���/��ԭ
void SunnyTcsTitleBar::ShowMaxRestore()
{
	if (m_MaxNormal) {
		parentWidget()->showNormal();
		m_MaxNormal = !m_MaxNormal;
		m_Maximize->setToolTip("���");
		m_Maximize->setIcon(*m_MaxPix);
	}
	else {
		parentWidget()->showMaximized();
		m_Maximize->setToolTip("���»�ԭ");
		m_MaxNormal = !m_MaxNormal;
		m_Maximize->setIcon(*m_RestorePix);
	}
}

// ��������˱���������¼�µ�ʱ��λ��
void SunnyTcsTitleBar::mousePressEvent(QMouseEvent *e)
{
	m_StartPos = e->globalPos();
	m_ClickPos = mapToParent(e->pos());
}

// ����ƶ�
void SunnyTcsTitleBar::mouseMoveEvent(QMouseEvent *e)
{
	if (m_MaxNormal)  // ����������״̬�������ƶ�
		return;
	parentWidget()->move(e->globalPos() - m_ClickPos);
}

// ˫���������ͷŴ�ťЧ��һ��
void SunnyTcsTitleBar::mouseDoubleClickEvent(QMouseEvent *e)
{
	if (e->button() == Qt::LeftButton)
	{
		ShowMaxRestore();
	}
}



//���ñ������Ľ���ɫ
void SunnyTcsTitleBar::SetTitleBackground(QColor ColorL, QColor ColorR)
{
	m_ColorL = ColorL;
	m_ColorR = ColorR;

	update();     // ֪ͨ���ģ�ϵͳ�Զ�����PainterEvent()����
}


// ���ñ�������ʾ������
void SunnyTcsTitleBar::SetTitleContent(QString content)
{
	m_TitleConten->setText(content);
}

// ���ñ��������Ͻǵ�ͼ��
void SunnyTcsTitleBar::SetTitleIcon(QString iconPath)
{
	QPixmap map(iconPath);
	m_TitleIcon->setPixmap(map);

}


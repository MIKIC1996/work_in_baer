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
	void SetTitleBackground(QColor ColorL, QColor ColorR); // ���ⲿ�������ñ���������
	void SetTitleContent(QString content); // �������������ñ���������
	void SetTitleIcon(QString iconPath);   // �������������ñ�����ͼ��

	public slots:
	void ShowSmall();      //�ۺ�������С��
	void ShowMaxRestore(); // �ۺ��� ����󻯻��߻�ԭ
protected:
	void mousePressEvent(QMouseEvent *e);           // ������¼�
	void mouseMoveEvent(QMouseEvent *e);            // ����ƶ��¼�
	void mouseDoubleClickEvent(QMouseEvent *e);     // ���˫���¼�

private:

	void InitTitleBar();                 // ��ʼ��������
	void paintEvent(QPaintEvent *event); // ���ػ滭����

	bool m_MaxNormal;

	QToolButton *m_Minimize;             // ��С����ť
	QToolButton *m_Maximize;             // ��󻯰�ť
	QToolButton *m_Close;                // �رհ�ť

	QPixmap *m_ClosePix;	//�رհ�ť��ͼƬ

	QPixmap *m_RestorePix;  // ��ԭ��ť��ͼƬ
	QPixmap *m_MaxPix;      // ��󻯰�ť��ͼƬ

	QPixmap *m_MinPix;      // ��С����ť��ͼƬ

	QPoint m_StartPos;      // ��¼���ڿ�ʼ��λ��
	QPoint m_ClickPos;

	QLabel *m_TitleIcon;    // ������ͼ��
	QLabel *m_TitleConten;  // ����������
	QLabel m_TitleLabel;

	QColor m_ColorL;         // ����������ɫ
	QColor m_ColorR;         // ����������ɫ

	QWidget *m_Parent;       //������

};
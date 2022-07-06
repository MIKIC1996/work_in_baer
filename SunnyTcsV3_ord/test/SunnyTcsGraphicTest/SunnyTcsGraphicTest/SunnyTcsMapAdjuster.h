#pragma once
#include "stafix.h"


using namespace basic;
using namespace core;


//ģ��״̬
enum E_SunnyTcsModelEditStatus {
	E_EDIT = 1, //�༭״̬
	E_RUNNING = 2 //����״̬
};

//��ͼgui������
class SunnyTcsMapAdjuster
{
public:
	SunnyTcsMapAdjuster(qint32 wid,qint32 hei,qint32 resolution )
		:_sceneWid(wid),_sceneHei(hei),_resolution(resolution)
	{
		reset();
		//����״̬ɫ��ʼ��
		_ve_status_color_hash.insert(Eunconnected, Qt::gray);
		_ve_status_color_hash.insert(Econnected_outline, QColor(71, 122, 238));
		_ve_status_color_hash.insert(Econnected_inline, QColor(71, 122, 238));
		_ve_status_color_hash.insert(Eworking, QColor(71, 122, 238));
	}

	inline qreal getSceneWid()const { return _sceneWid; }
	inline qreal getSceneHei()const { return _sceneHei; }
	inline qreal getResolution()const { return _resolution; }
	inline E_SunnyTcsModelEditStatus getModelEditStatus()const { return _status; }

	void resetSceneSize(qint32 wid, qint32 hei , qint32 resolution) {
		_sceneWid = wid;
		_sceneHei = hei;
		_resolution = resolution;
		reset();
	}

	void setModelEditStatus(E_SunnyTcsModelEditStatus st) {
		_status = st;
	}

private:
	//����Ԫ�صĴ�С������ scene�Ĵ�С��̬������
	void reset() {
		_cs_axis_len = _sceneWid / 40.0;
		_cs_axis_wid = _sceneWid / 400.0;
		_cs_arrow_len = _sceneWid / 80.0;
		_cs_ex_rect_wid = _sceneWid / 30.0;
		_cs_in_rect_wid = _sceneWid / 40.0;
	}

public:
	
	QColor _general_warning = Qt::red;
	QColor _backColor = QColor(60, 60, 60);



	qreal _sceneWid;		//scene ��
	qreal _sceneHei;		//scene ��		
	qreal _resolution;		//����ֱ���
		

	//״̬
	E_SunnyTcsModelEditStatus _status = E_EDIT;
	

	//select
	QColor _item_select_color = QColor(247, 198,54);

	//CS
	qreal _cs_axis_len;		//�����᳤				
	qreal _cs_axis_wid;		//�������߿�				
	qreal _cs_arrow_len;	//�������ͷ�߳�		
	qreal _cs_ex_rect_wid;	//�ⷽ��			
	qreal _cs_in_rect_wid;	//�ڷ���			
	QColor _cs_default_color = Qt::gray;

	//PT
	qreal _pt_ex_wid = 1200;							//Բ���߿�
	qreal _pt_rect_wid = 800;							//Բ��ֱ��
	qreal _pt_back_wid = 2000;							//��Բ��ֱ��
	qreal _pt_park_wid = 3000;							//ͣ��Բֱ��
	QColor _pt_back_color = QColor(49, 57, 77,200);		//��ɫ
	QColor _pt_ex_color = QColor(186,205,255);			//Բ����ɫ
	QColor _pt_rect_color = QColor(75,130,255);			//��Բ��ɫ
	QColor _pt_select_color = Qt::yellow;				//ѡ����ɫ
	QColor _pt_park_color = QColor(218,134,129, 100);	//ͣ������ɫ
 	qreal _pt_text_rect_len = 16000;						//������巽��
  	qreal _pt_text_rect_wid = 1200;						//������巽���
  	qreal _pt_font_size = 400;							//�����С
	QColor _pt_rubbon_color = Qt::blue; 
	QColor _pt_ine_color =Qt::red;
	QColor _pt_laser_color = Qt::green;		
	QColor _pt_help_color = Qt::gray;


	//PATH
	qreal _ph_selected_wid = 650;
	QColor _ph_selected_color = QColor(75, 130, 255);	
	QColor _ph_dash_color = QColor(100, 100, 120, 100);		
	qreal _ph_arrow_len = 400;							//·����ͷ��
	qreal _ph_dash_wid = 100;							//�����߿�
	qreal _ph_arrow_move = 1500;							//��ͷƫ��


	//VE
	qreal _ve_rect_long_wid = 1800;
	qreal _ve_rect_short_wid = 1400;
	qreal _ve_line_wid = 0;
	QColor _ve_ladar_color = QColor(42,87,191,150);//�״�Ȧ����ɫ
	QColor _ve_ladar_warn_color = QColor(218, 134, 129, 200); //�״���ײ��ɫ
	QColor _ve_ladar_from_color = QColor(0, 0, 0, 0);
	QColor _ve_ladar_deco_color = QColor(200, 200, 255,50);

	QColor _ve_back_color = Qt::white; //���ĵ�ɫ
	QMap<E_SunnyTcsVehicleStatus, QColor> _ve_status_color_hash; //����״̬ɫ ��
	QColor _ve_error_color = Qt::red; //�������ɫ
	QColor _ve_warning_color = Qt::red;	//��������ɫ
	qreal _ve_text_len = 5000;
	qreal _ve_text_hei = 1800;
	qreal _ve_font_size =500; //����ĳߴ�

	qreal _ve_info_rect_wid = 7000;
	qreal _ve_info_rect_hei = 8000;
};
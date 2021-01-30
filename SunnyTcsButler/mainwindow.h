#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QFile>
#include <QDebug>
#include <iostream>
#include <memory>
#include <QTimer>
#include <QMap>

#include <QMessageBox>
#include "sunnytcsservice.h"
#include "sunnytcsconfig.h"
#include "sunnytcsfilesetdig.h"
#include <QFileDialog>
#include <configsetdig.h>
#include "sunnytcsconfigcenter.h"
#include "sunnytcsitemlinkdig.h"
#include "sunnytcsprocedureconfigdig.h"
#include "sunnytcsprocedureexedig.h"

#define TIMER_CYCLE 250

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    inline qint64 getTimerCycle()const{return _timerCycle;}
    inline void setTimerCycle(qint64 cycle){this->_timerCycle=cycle;}
    void initUI();

    void readParams();
    void saveParams();

private slots:
    void on_MaintabIndex_changed(int index);
    void on_startBtn_clicked();
    void on_closeBtn_clicked();
    void on_startAll_clicked();
    void on_closeAll_clicked();
    void on_loadBtn_clicked();
    void on_configModifyBtn_clicked();//配置修改
    void on_fileModifyBtn_clicked();
    void on_center_map_changed();
    void on_center_procedure_changed();

    void on_configSetDig_setOk(SunnyTcsConfig* file);
    void on_configSetDig_closed();

    void on_fileSetDig_setOk();
    void on_fileSetDig_setCancel();

    void on_flushCycle_clicked();

    void on_service_retSignal(int ret);

    void on_Btn_createPro_clicked();
    void on_Btn_modifyPro_clicked();
    void on_Btn_exePro_clicked();
    void on_Btn_deletePro_clicked();
    void on_timer_timeout();
    int askState(const char* name);



private:
    QList<QString> _serviceName;//0 kernel 1 broker 3 datacenter 4 logCenter 5 connector
    QString _paramsFilePath="";
    const QString _closedStyle="QGroupBox{background-color:rgb(245,245,245);border-radius:10px;}QLabel{background-color:rgb(245,245,245);border-radius:10px;}";
    const QString _openingStyle="QGroupBox{background-color:rgb(200,200,20);border-radius:10px;}QLabel{background-color:rgb(200,200,20);border-radius:10px;}";
    const QString _openedStyle="QGroupBox{background-color:rgb(210,210,245);border-radius:10px;}QLabel{background-color:rgb(210,210,245);border-radius:10px;}";
    const QString _closingStyle="QGroupBox{background-color:rgb(250,130,130);border-radius:10px;}QLabel{background-color:rgb(250,130,130);border-radius:10px;}";
    const qint8 _serverCount=5;
    qint8 _askOne=0;

    qint8 _kernelState=SERVICE_STOPPED;
    qint8 _brokerState=SERVICE_STOPPED;
    qint8 _dataState=SERVICE_STOPPED;
    qint8 _logState=SERVICE_STOPPED;
    qint8 _interState=SERVICE_STOPPED;

    Ui::MainWindow *ui;
    QList<std::shared_ptr<SunnyTcsService>> m_services;
    std::shared_ptr<SunnyTcsConfigCenter> _configCenter;
    QTimer *_timer;
    qint64 _timerCycle=TIMER_CYCLE;
    ConfigSetDig* _configDig=nullptr;
    SunnyTcsFileSetDig* _fileDig=nullptr;
    SunnyTcsProcedureExeDig* _exeDig=nullptr;

    SunnyTcsProcedure* tempProcedure=nullptr;//临时编辑的流程

    SunnyTcsProcedureConfigDig* _procedureConfigDig=nullptr;




    // QWidget interface
protected:
    void closeEvent(QCloseEvent *event);
};

#endif // MAINWINDOW_H

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QObject>
#include <QFileInfo>
#include <QDebug>
/**************************************************
*

*
***************************************************/
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_services.append(std::make_shared<SunnyTcsService>());
    m_services.append(std::make_shared<SunnyTcsService>());
    m_services.append(std::make_shared<SunnyTcsService>());
    m_services.append(std::make_shared<SunnyTcsService>());
    m_services.append(std::make_shared<SunnyTcsService>());
    _configCenter=std::make_shared<SunnyTcsConfigCenter>(QDir::currentPath()+"/config_set/config_pre.xml"
                                                         ,QDir::currentPath()+"/config_set/procedure_pre.xml");

    _paramsFilePath=QDir::currentPath()+"/config_set/butler_params.xml";
    readParams();
    _timer=new QTimer(this);
    _timer->start(_timerCycle);
    initUI();

    _configDig=new ConfigSetDig();
    _fileDig=new SunnyTcsFileSetDig();
    _procedureConfigDig=new SunnyTcsProcedureConfigDig();
    _exeDig=new SunnyTcsProcedureExeDig();

    //信号连接-----------------------------
    connect(ui->main_tabwidget,SIGNAL(currentChanged(int)),this,SLOT(on_MaintabIndex_changed(int)));

    connect(ui->kernel_start,SIGNAL(clicked()),this,SLOT(on_startBtn_clicked()));
    connect(ui->broker_start,SIGNAL(clicked()),this,SLOT(on_startBtn_clicked()));
    connect(ui->data_start,SIGNAL(clicked()),this,SLOT(on_startBtn_clicked()));
    connect(ui->log_start,SIGNAL(clicked()),this,SLOT(on_startBtn_clicked()));
    connect(ui->super_start,SIGNAL(clicked()),this,SLOT(on_startBtn_clicked()));
    connect(ui->inter_start,SIGNAL(clicked()),this,SLOT(on_startBtn_clicked()));
    connect(ui->start_all,SIGNAL(clicked()),this,SLOT(on_startAll_clicked()));
    connect(ui->close_all,SIGNAL(clicked()),this,SLOT(on_closeAll_clicked()));
    connect(ui->load_btn,SIGNAL(clicked()),this,SLOT(on_loadBtn_clicked()));
    connect(ui->modify_btn,SIGNAL(clicked()),this,SLOT(on_configModifyBtn_clicked()));
    connect(ui->file_modify_btn,SIGNAL(clicked()),this,SLOT(on_fileModifyBtn_clicked()));
    connect(ui->exeProBtn,SIGNAL(clicked()),this,SLOT(on_Btn_exePro_clicked()));
    connect(ui->kernel_close,SIGNAL(clicked()),this,SLOT(on_closeBtn_clicked()));
    connect(ui->broker_close,SIGNAL(clicked()),this,SLOT(on_closeBtn_clicked()));
    connect(ui->data_close,SIGNAL(clicked()),this,SLOT(on_closeBtn_clicked()));
    connect(ui->log_close,SIGNAL(clicked()),this,SLOT(on_closeBtn_clicked()));
    connect(ui->super_close,SIGNAL(clicked()),this,SLOT(on_closeBtn_clicked()));
    connect(ui->inter_close,SIGNAL(clicked()),this,SLOT(on_closeBtn_clicked()));
    connect(&(*_configDig),&ConfigSetDig::setOk,&(*_configCenter),&SunnyTcsConfigCenter::on_configDig_setOK);
    connect(ui->flush_cycle,SIGNAL(clicked()),this,SLOT(on_flushCycle_clicked()));
    connect(ui->createProBtn,SIGNAL(clicked()),this,SLOT(on_Btn_createPro_clicked()));
    connect(ui->modifyProBtn,SIGNAL(clicked()),this,SLOT(on_Btn_modifyPro_clicked()));
    connect(_timer,SIGNAL(timeout()),this,SLOT(on_timer_timeout()));
    connect(&(*_procedureConfigDig),&SunnyTcsProcedureConfigDig::procedureSave,&(*_configCenter),&SunnyTcsConfigCenter::on_procedureSave,Qt::DirectConnection);
    connect(&(*_procedureConfigDig),&SunnyTcsProcedureConfigDig::procedureClose,&(*_configCenter),&SunnyTcsConfigCenter::on_procedureClose,Qt::DirectConnection);

    connect(&(*_configCenter),&SunnyTcsConfigCenter::configPathMap_changed,this,&MainWindow::on_center_map_changed,Qt::DirectConnection);
    connect(&(*_configCenter),&SunnyTcsConfigCenter::procedureMap_changed,this,&MainWindow::on_center_procedure_changed,Qt::DirectConnection);
    for(std::shared_ptr<SunnyTcsService> m_service:m_services){
        connect(&(*m_service),&SunnyTcsService::retSignal,this,&MainWindow::on_service_retSignal,Qt::DirectConnection);
    }
    //------------------------------------------------------


    int ret=_configCenter->readConfig();

   // QMessageBox::information(0,"tip",QString::number(ret));


//    qDebug()<<qApp->applicationDirPath();
//    SunnyTcsConfig fon("D://H_ALL1230.xml");
//    int ret=fon.load();
//    qDebug()<<"****************************************";
//    ret=fon.readValue();
//    qDebug()<<ret;
}


/**************************************************
*

*
***************************************************/
MainWindow::~MainWindow()
{
    saveParams();
    delete ui;
    _timer->stop();
    delete _timer;
    _configDig->close();
    delete _configDig;
    _fileDig->close();
    delete _fileDig;
    _procedureConfigDig->close();
    delete _procedureConfigDig;
    _exeDig->close();
    delete _exeDig;
}


/**************************************************
*

*
***************************************************/
void MainWindow::initUI()
{
    this->setWindowTitle("SunnyTcsButler");
    this->setFixedSize(this->width(),this->height());
    this->setStyleSheet("MainWindow{background-color:rgb(255,255,255);}");

    ui->home_tab->setStyleSheet("background-color:rgb(245,245,245);");
    ui->config_tab->setStyleSheet("background-color:rgb(245,245,245);");
    //ui->help_tab->setStyleSheet("background-color:rgb(245,245,245);");

    QString boxStyle=_closedStyle;
    ui->kernel_box->setStyleSheet(boxStyle);
    ui->broker_box->setStyleSheet(boxStyle);
    ui->data_box->setStyleSheet(boxStyle);
    ui->log_box->setStyleSheet(boxStyle);
    ui->inter_box->setStyleSheet(boxStyle);
    ui->super_box->setStyleSheet(boxStyle);

    ui->config_table->setColumnWidth(0,180);
    ui->config_table->setColumnWidth(1,180);

    //样式表设置，以后再说
//    QFile styleSheet(":/new/prefix1/res/qss/qqsss.qss");
//    if (!styleSheet.open(QIODevice::ReadOnly))
//    {
//        qDebug()<<"/?????";
//        return;
//    }
    //    qApp->setStyleSheet(styleSheet.readAll());
}

void MainWindow::readParams()
{
    do{
        _serviceName.clear();
        QFile file(_paramsFilePath);
        if(!file.open(QFile::WriteOnly|QFile::Truncate)){
            break;
        }
        QXmlStreamReader xsr(&file);
        xsr.readNextStartElement();
        if(xsr.name().toString()!="root"){
            break;
        }
        xsr.readNextStartElement();
        if(xsr.name().toString()!="kernel"){
            break;
        }
        _serviceName.append(xsr.readElementText());

        xsr.readNextStartElement();
        if(xsr.name().toString()!="broker"){
            break;
        }
        _serviceName.append(xsr.readElementText());

        xsr.readNextStartElement();
        if(xsr.name().toString()!="dataCenter"){
            break;
        }
        _serviceName.append(xsr.readElementText());

        xsr.readNextStartElement();
        if(xsr.name().toString()!="logCenter"){
            break;
        }
        _serviceName.append(xsr.readElementText());

        xsr.readNextStartElement();
        if(xsr.name().toString()!="connector"){
            break;
        }
        _serviceName.append(xsr.readElementText());


    }while(0);
    _serviceName.clear();
    _serviceName.append("SunnyTCS Kernel");
    _serviceName.append("SunnyTCS broker");
    _serviceName.append("SunnyTCS DataCenter");
    _serviceName.append("SunnyTCS LogCenter");
    _serviceName.append("SunnyTCS IntegraConnector");
}

void MainWindow::saveParams()
{
    QFile file(_paramsFilePath);
    if(!file.open(QFile::WriteOnly|QFile::Truncate)){
        return;
    }
    QXmlStreamWriter xsw(&file);
    xsw.setAutoFormatting(true);
    xsw.writeStartDocument();
    xsw.writeStartElement("root");

    xsw.writeTextElement("kernel",_serviceName.at(0));
    xsw.writeTextElement("broker",_serviceName.at(1));
    xsw.writeTextElement("dataCenter",_serviceName.at(2));
    xsw.writeTextElement("logCenter",_serviceName.at(3));
    xsw.writeTextElement("connector",_serviceName.at(4));

    xsw.writeEndElement();
    file.close();
}


/**************************************************
*

*
***************************************************/
void MainWindow::on_MaintabIndex_changed(int index)
{
    ui->main_widget->setCurrentIndex(index);
}


/**************************************************
*

*
***************************************************/
void MainWindow::on_startBtn_clicked()
{

    QString send=sender()->objectName();

    if(send=="kernel_start"){
        if(_kernelState==SERVICE_RUNNING||_kernelState==SERVICE_START_PENDING){
            QMessageBox::information(this,"tip","has been running or is starting");
            return;
        }
        if(m_services.at(0)->isRunning()){
            QMessageBox::information(this,"tip","busy");
            return;
        }

        m_services.at(0)->setMode(MODE_START);
        m_services.at(0)->setName(_serviceName.at(0));
        m_services.at(0)->start();
    }else if(send=="broker_start"){
        if(_brokerState==SERVICE_RUNNING||_kernelState==SERVICE_START_PENDING){
            QMessageBox::information(this,"tip","has been running or is starting");
            return;
        }
        if(m_services.at(1)->isRunning()){
            QMessageBox::information(this,"tip","busy");
            return;
        }
        m_services.at(1)->setMode(MODE_START);
        m_services.at(1)->setName(_serviceName.at(1));
        m_services.at(1)->start();
    }else if(send=="data_start"){
        if(_dataState==SERVICE_RUNNING||_kernelState==SERVICE_START_PENDING){
            QMessageBox::information(this,"tip","has been running or is starting");
            return;
        }
        if(m_services.at(2)->isRunning()){
            QMessageBox::information(this,"tip","busy");
            return;
        }
        m_services.at(2)->setMode(MODE_START);
        m_services.at(2)->setName(_serviceName.at(2));
        m_services.at(2)->start();
    }else if(send=="log_start"){
        if(_logState==SERVICE_RUNNING||_kernelState==SERVICE_START_PENDING){
            QMessageBox::information(this,"tip","has been running or is starting");
            return;
        }
        if(m_services.at(3)->isRunning()){
            QMessageBox::information(this,"tip","busy");
            return;
        }
        m_services.at(3)->setMode(MODE_START);
        m_services.at(3)->setName(_serviceName.at(3));
        m_services.at(3)->start();
    }else if(send=="inter_start"){
        if(_interState==SERVICE_RUNNING||_kernelState==SERVICE_START_PENDING){
            QMessageBox::information(this,"tip","has been running or is starting");
            return;
        }
        if(m_services.at(4)->isRunning()){
            QMessageBox::information(this,"tip","busy");
            return;
        }
        m_services.at(4)->setMode(MODE_START);
        m_services.at(4)->setName(_serviceName.at(4));
        m_services.at(4)->start();
    }else if(send=="super_start"){
        qDebug()<<"super star";
    }

}


/**************************************************
*

*
***************************************************/
void MainWindow::on_closeBtn_clicked()
{
    if(QMessageBox::Ok != QMessageBox::information(this,"tip","确定要关闭该服务吗？",QMessageBox::No,QMessageBox::Ok))
        return;
    QString send=sender()->objectName();

    if(send=="kernel_close"){
        if(_kernelState==SERVICE_STOPPED||_kernelState==SERVICE_STOP_PENDING){
            QMessageBox::information(this,"tip","has stopped or is stopping");
            return;
        }
        if(m_services.at(0)->isRunning()){
            QMessageBox::information(this,"tip","busy");
            return;
        }

        m_services.at(0)->setMode(MODE_CLOSE);
        m_services.at(0)->setName(_serviceName.at(0));
        m_services.at(0)->start();
    }else if(send=="broker_close"){
        if(_brokerState==SERVICE_STOPPED||_kernelState==SERVICE_STOP_PENDING){
            QMessageBox::information(this,"tip","has stopped or is stopping");
            return;
        }
        if(m_services.at(1)->isRunning()){
            QMessageBox::information(this,"tip","busy");
            return;
        }
        m_services.at(1)->setMode(MODE_CLOSE);
        m_services.at(1)->setName(_serviceName.at(1));
        m_services.at(1)->start();
    }else if(send=="data_close"){
        if(_dataState==SERVICE_STOPPED||_kernelState==SERVICE_STOP_PENDING){
            QMessageBox::information(this,"tip","has stopped or is stopping");
            return;
        }
        if(m_services.at(2)->isRunning()){
            QMessageBox::information(this,"tip","busy");
            return;
        }
        m_services.at(2)->setMode(MODE_CLOSE);
        m_services.at(2)->setName(_serviceName.at(2));
        m_services.at(2)->start();
    }else if(send=="log_close"){
        if(_logState==SERVICE_STOPPED||_kernelState==SERVICE_STOP_PENDING){
            QMessageBox::information(this,"tip","has stopped or is stopping");
            return;
        }
        if(m_services.at(3)->isRunning()){
            QMessageBox::information(this,"tip","busy");
            return;
        }
        m_services.at(3)->setMode(MODE_CLOSE);
        m_services.at(3)->setName(_serviceName.at(3));
        m_services.at(3)->start();
    }else if(send=="inter_close"){
        if(_interState==SERVICE_STOPPED||_kernelState==SERVICE_STOP_PENDING){
            QMessageBox::information(this,"tip","has stopped or is stopping");
            return;
        }
        if(m_services.at(4)->isRunning()){
            QMessageBox::information(this,"tip","busy");
            return;
        }
        m_services.at(4)->setMode(MODE_CLOSE);
        m_services.at(4)->setName(_serviceName.at(4));
        m_services.at(4)->start();
    }else if(send=="super_close"){
        qDebug()<<"super star";
    }

}

/**************************************************
*

*
***************************************************/
void MainWindow::on_startAll_clicked()
{
    if(QMessageBox::Ok != QMessageBox::information(this,"tip","are you sure to start all services?",QMessageBox::No,QMessageBox::Ok))
        return;
    if(_kernelState!=SERVICE_RUNNING||_kernelState!=SERVICE_START_PENDING)
        emit ui->kernel_start->click();
    if(_brokerState!=SERVICE_RUNNING||_brokerState!=SERVICE_START_PENDING)
        emit ui->broker_start->click();
    if(_dataState!=SERVICE_RUNNING||_dataState!=SERVICE_START_PENDING)
        emit ui->data_start->click();
    if(_logState!=SERVICE_RUNNING||_logState!=SERVICE_START_PENDING)
        emit ui->log_start->click();
    if(_interState!=SERVICE_RUNNING||_interState!=SERVICE_START_PENDING)
        emit ui->inter_start->click();
}

/**************************************************
*

*
***************************************************/
void MainWindow::on_closeAll_clicked()
{
//    if(QMessageBox::Ok != QMessageBox::information(this,"tip","are you sure to close all services?",QMessageBox::No,QMessageBox::Ok))
//        return;
//    if(_kernelState!=SERVICE_STOPPED||_kernelState!=SERVICE_STOP_PENDING)
//        emit ui->kernel_close->click();
//    if(_brokerState!=SERVICE_STOPPED||_brokerState!=SERVICE_STOP_PENDING)
//        emit ui->broker_close->click();
//    if(_dataState!=SERVICE_STOPPED||_dataState!=SERVICE_STOP_PENDING)
//        emit ui->data_close->click();
//    if(_logState!=SERVICE_STOPPED||_logState!=SERVICE_STOP_PENDING)
//        emit ui->log_close->click();
//    if(_interState!=SERVICE_STOPPED||_interState!=SERVICE_STOP_PENDING)
//        emit ui->inter_close->click();


}


/**************************************************
*

*
***************************************************/
void MainWindow::on_loadBtn_clicked()
{
    QString path=QFileDialog::getOpenFileName(this,"open",QDir::currentPath(),"config(*.xml;*.json)");
    if(path.isEmpty())
        return;
    if(!_configCenter->pathCheck(path)){
        QMessageBox::information(0,"tip",QString("this file has been configed"));
        return;
    }
    SunnyTcsConfig* file=new SunnyTcsConfig(path);
    if(file->getType()==0){
        qDebug()<<"?????????????000";
        file->load();
        file->readValue();
    }else if(file->getType()==1){
        qDebug()<<"?????????????111";
        file->load();
    }


    //_configCenter->addConfig(file);
    _configDig->setFile(file);
    _configDig->show();
}


/**************************************************
*

*
***************************************************/
void MainWindow::on_configModifyBtn_clicked()
{

    qint32 row=ui->config_table->currentRow();
    if(row<0){
        return;
    }
    if(ui->config_table->item(row,1)){
        QString path=ui->config_table->item(row,1)->text();
        SunnyTcsConfig* con = _configCenter->reLoadConfig(path);
        if(con){
            _configDig->setFile(con);
            _configDig->show();
        }
    }
}


/**************************************************
*

*
***************************************************/
void MainWindow::on_fileModifyBtn_clicked()
{
    if(ui->config_table->currentRow()<0){
        return;
    }
    qDebug()<<"scccccc";
    qint32 row=ui->config_table->currentRow();
    qDebug()<<row;
    QString path=ui->config_table->item(row,1)->text();
    SunnyTcsConfig* con = _configCenter->reLoadConfig(path);
    if(con){
        _fileDig->setFile(con);
        _fileDig->show();
    }
}




/**************************************************
*

*
***************************************************/
void MainWindow::on_center_map_changed()
{
    ui->config_table->setRowCount(0);
    const QMap<QString,SunnyTcsConfig*>* map=_configCenter->getConfigMap();
    for(QString key:map->keys()){
        ui->config_table->setRowCount(ui->config_table->rowCount()+1);
        ui->config_table->setItem(ui->config_table->rowCount()-1,1,new QTableWidgetItem(key));
        ui->config_table->setItem(ui->config_table->rowCount()-1,0,new QTableWidgetItem(map->value(key)->getFileRemarks()));
    }
}


/**************************************************
*

*
***************************************************/
void MainWindow::on_center_procedure_changed()
{
    ui->procedureList->clear();
    const QMap<QString,SunnyTcsProcedure*>* map=_configCenter->getProcedureMap();
    for(QString key:map->keys()){
        qDebug()<<key;
        ui->procedureList->addItem(key);
    }
}


/**************************************************
*

*
***************************************************/
void MainWindow::on_configSetDig_setOk(SunnyTcsConfig* file)
{

//    _configDig=nullptr;
//    _configDig->close();
}


/**************************************************
*

*
***************************************************/
void MainWindow::on_configSetDig_closed()
{

}


/**************************************************
*

*
***************************************************/
void MainWindow::on_fileSetDig_setOk()
{

}


/**************************************************
*

*
***************************************************/
void MainWindow::on_fileSetDig_setCancel()
{

}


/**************************************************
*

*
***************************************************/
void MainWindow::on_flushCycle_clicked()
{

}


/**************************************************
*
*#define NO_THIS_SERVICE 0X00//无该项服务
#define CANT_OPEN_MANAGER 0x01//无法打开服务管理器
#define QUERY_SERVICESTATUS_ERROR 0x02//服务状态获取错误
#define SERVICE_ALREADY_RUNNING 0x03//服务已经在运行或开启中
#define START_SERVICE_ERROR 0x04//服务启动失败
#define SERVICE_NO_ERROR 0x05//成功
#define SERVICE_OUTOF_TIME 0x06//超时
#define SERVICE_ALREADY_STOP 0x07//服务已经关闭或关闭中
#define STOP_SERVICE_ERROR 0x08//关闭服务失败
*
***************************************************/
void MainWindow::on_service_retSignal(int ret)
{
//    switch(ret){
//    case NO_THIS_SERVICE:
//        QMessageBox::information(0,"tip","NO_THIS_SERVICE");
//        break;
//    case CANT_OPEN_MANAGER:
//        QMessageBox::information(0,"tip","CANT_OPEN_MANAGER");
//        break;
//    case QUERY_SERVICESTATUS_ERROR:
//        QMessageBox::information(0,"tip","QUERY_SERVICESTATUS_ERROR");
//        break;
//    case SERVICE_ALREADY_RUNNING:
//        QMessageBox::information(0,"tip","SERVICE_ALREADY_RUNNING");
//        break;
//    case START_SERVICE_ERROR:
//        QMessageBox::information(0,"tip","START_SERVICE_ERROR");
//        break;
//    case SERVICE_NO_ERROR:
//        QMessageBox::information(0,"tip","OPERATE_SUCCESS");
//        break;
//    case SERVICE_OUTOF_TIME:
//        QMessageBox::information(0,"tip","SERVICE_OUTOF_TIME");
//        break;
//    case SERVICE_ALREADY_STOP:
//        QMessageBox::information(0,"tip","SERVICE_ALREADY_STOP");
//        break;
//    case STOP_SERVICE_ERROR:
//        QMessageBox::information(0,"tip","STOP_SERVICE_ERROR");
//        break;
//    default:
//        QMessageBox::information(0,"tip","UNKNOW_ERROR");
    //        }
}


/**************************************************
*

*
***************************************************/
void MainWindow::on_Btn_createPro_clicked()
{

    if(!_procedureConfigDig->isHidden())
    {
        qDebug()<<"showing";
        return;
    }
    _procedureConfigDig->setProcedureFile(_configCenter->createNewProcedure());
    _procedureConfigDig->show();
}


/**************************************************
*

*
***************************************************/
void MainWindow::on_Btn_modifyPro_clicked()
{
    if(ui->procedureList->currentRow()<0){
        return;
    }
    QString proName = ui->procedureList->currentItem()->text();
    SunnyTcsProcedure* pro=_configCenter->getProcedure(proName);
    _procedureConfigDig->setProcedureFile(pro);
    _configCenter->removeProcedure(pro->getProcedureName());
    _configCenter->setTempProcedure(pro);
    _procedureConfigDig->show();
}

void MainWindow::on_Btn_exePro_clicked()
{
    if(ui->procedureList->currentRow()<0){
        return;
    }
    QString proName = ui->procedureList->currentItem()->text();
    SunnyTcsProcedure* pro=_configCenter->getProcedure(proName);
    _exeDig->setProcedureFile(pro);
    _exeDig->show();
}

void MainWindow::on_Btn_deletePro_clicked()
{
    if(ui->procedureList->currentRow()<0){
        return;
    }
    QString proName = ui->procedureList->currentItem()->text();
    _configCenter->removeProcedure(proName);
    _configCenter->saveConfig();
}


/***************************************************************
#define SERVICE_STOPPED                        0x00000001
#define SERVICE_START_PENDING                  0x00000002
#define SERVICE_STOP_PENDING                   0x00000003
#define SERVICE_RUNNING                        0x00000004
#define SERVICE_CONTINUE_PENDING               0x00000005
#define SERVICE_PAUSE_PENDING                  0x00000006
#define SERVICE_PAUSED                         0x00000007
***************************************************************/
void MainWindow::on_timer_timeout()
{
    int ret;
    switch(_askOne){
    case 0:
        ret=askState("SunnyTCS Kernel");
        if(ret==SERVICE_STOPPED){
            ui->kernel_state->setText("state:not running");
            ui->kernel_box->setStyleSheet(_closedStyle);
            _kernelState=SERVICE_STOPPED;
        }else if(ret==SERVICE_RUNNING){
            ui->kernel_state->setText("state:running");
            ui->kernel_box->setStyleSheet(_openedStyle);
            _kernelState=SERVICE_RUNNING;
        }else if(ret==SERVICE_START_PENDING){
            ui->kernel_state->setText("state:starting");
            ui->kernel_box->setStyleSheet(_openingStyle);
            _kernelState=SERVICE_START_PENDING;
        }else if(ret==SERVICE_STOP_PENDING){
            ui->kernel_state->setText("state:closing");
            ui->kernel_box->setStyleSheet(_closingStyle);
            _kernelState=SERVICE_STOP_PENDING;
        }
        break;
    case 1:
        ret=askState("SunnyTCS Broker");
        if(ret==SERVICE_STOPPED){
            ui->broker_state->setText("state:not running");
            ui->broker_box->setStyleSheet(_closedStyle);
            _brokerState=SERVICE_STOPPED;
        }else if(ret==SERVICE_RUNNING){
            ui->broker_state->setText("state:running");
            ui->broker_box->setStyleSheet(_openedStyle);
            _brokerState=SERVICE_RUNNING;
        }else if(ret==SERVICE_START_PENDING){
            ui->broker_state->setText("state:starting");
            ui->broker_box->setStyleSheet(_openingStyle);
            _brokerState=SERVICE_START_PENDING;
        }else if(ret==SERVICE_STOP_PENDING){
            ui->broker_state->setText("state:closing");
            ui->broker_box->setStyleSheet(_closingStyle);
            _brokerState=SERVICE_STOP_PENDING;
        }
        break;
    case 2:
        ret=askState("SunnyTCS DataCenter");
        if(ret==SERVICE_STOPPED){
            ui->data_state->setText("state:not running");
            ui->data_box->setStyleSheet(_closedStyle);
            _dataState=SERVICE_STOPPED;
        }else if(ret==SERVICE_RUNNING){
            ui->data_state->setText("state:running");
            ui->data_box->setStyleSheet(_openedStyle);
            _dataState=SERVICE_RUNNING;
        }else if(ret==SERVICE_START_PENDING){
            ui->data_state->setText("state:starting");
            ui->data_box->setStyleSheet(_openingStyle);
            _dataState=SERVICE_START_PENDING;
        }else if(ret==SERVICE_STOP_PENDING){
            ui->data_state->setText("state:closing");
            ui->data_box->setStyleSheet(_closingStyle);
            _dataState=SERVICE_STOP_PENDING;
        }
        break;
    case 3:
        ret=askState("SunnyTCS LogCenter");
        if(ret==SERVICE_STOPPED){
            ui->log_state->setText("state:not running");
            ui->log_box->setStyleSheet(_closedStyle);
            _logState=SERVICE_STOPPED;
        }else if(ret==SERVICE_RUNNING){
            ui->log_state->setText("state:running");
            ui->log_box->setStyleSheet(_openedStyle);
            _logState=SERVICE_RUNNING;
        }else if(ret==SERVICE_START_PENDING){
            ui->log_state->setText("state:starting");
            ui->log_box->setStyleSheet(_openingStyle);
            _logState=SERVICE_START_PENDING;
        }else if(ret==SERVICE_STOP_PENDING){
            ui->log_state->setText("state:closing");
            ui->log_box->setStyleSheet(_closingStyle);
            _logState=SERVICE_STOP_PENDING;
        }
        break;
    case 4:
        ret=askState("SunnyTCS IntegraConnector");
        if(ret==SERVICE_STOPPED){
            ui->connector_state->setText("state:not running");
            ui->inter_box->setStyleSheet(_closedStyle);
            _interState=SERVICE_STOPPED;
        }else if(ret==SERVICE_RUNNING){
            ui->connector_state->setText("state:running");
            ui->inter_box->setStyleSheet(_openedStyle);
            _interState=SERVICE_RUNNING;
        }else if(ret==SERVICE_START_PENDING){
            ui->connector_state->setText("state:starting");
            ui->inter_box->setStyleSheet(_openingStyle);
            _interState=SERVICE_START_PENDING;
        }else if(ret==SERVICE_STOP_PENDING){
            ui->connector_state->setText("state:closing");
            ui->inter_box->setStyleSheet(_closingStyle);
            _interState=SERVICE_STOP_PENDING;
        }
        break;
    default:
        break;
    }
    if(++_askOne==5){
        _askOne=0;
    }
}


/***************************************************************
#define SERVICE_STOPPED                        0x00000001
#define SERVICE_START_PENDING                  0x00000002
#define SERVICE_STOP_PENDING                   0x00000003
#define SERVICE_RUNNING                        0x00000004
#define SERVICE_CONTINUE_PENDING               0x00000005
#define SERVICE_PAUSE_PENDING                  0x00000006
#define SERVICE_PAUSED                         0x00000007
***************************************************************/
int MainWindow::askState(const char *name)//等下整合到service类里面取
{
    // 打开服务管理对象
    SC_HANDLE hSC = OpenSCManager( NULL,
        NULL, GENERIC_EXECUTE);
    if( hSC == NULL)
    {
        return -1;
    }
    // 打开服务
    char* nameData=const_cast<char*>(name);
    CString str = CString(nameData);
    USES_CONVERSION;
    LPCWSTR wszClassName = new WCHAR[str.GetLength()+1];
    wcscpy((LPTSTR)wszClassName,T2W((LPTSTR)str.GetBuffer(NULL)));
    str.ReleaseBuffer();

    SC_HANDLE hSvc = OpenService( hSC,wszClassName,
        SERVICE_START | SERVICE_QUERY_STATUS | SERVICE_STOP);
    if( hSvc == NULL)
    {
        CloseServiceHandle( hSC);
        return -1;
    }
    // 获得服务的状态
    SERVICE_STATUS status;
    if( QueryServiceStatus( hSvc, &status) == FALSE)
    {
        CloseServiceHandle( hSvc);
        CloseServiceHandle( hSC);
        return -1;
    }
    return status.dwCurrentState;
}

void MainWindow::closeEvent(QCloseEvent *event)
{

}




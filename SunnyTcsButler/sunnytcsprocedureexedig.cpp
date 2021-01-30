#include "sunnytcsprocedureexedig.h"
#include "ui_sunnytcsprocedureexedig.h"
#include <QMessageBox>

SunnyTcsProcedureExeDig::SunnyTcsProcedureExeDig(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SunnyTcsProcedureExeDig)
{
    ui->setupUi(this);
    connect(ui->nextBtn,SIGNAL(clicked()),this,SLOT(on_Btn_next_clicked()));
    connect(ui->saveBtn,SIGNAL(clicked()),this,SLOT(on_Btn_save_clicked()));

    ui->actionBox->setStyleSheet("QGroupBox{background-color:rgb(250,250,250);border-radius:10px;}");
    ui->exeBox->setStyleSheet("QGroupBox{background-color:rgb(250,250,250);border-radius:10px;}");
    ui->actionTEdit->setStyleSheet("background-color:rgb(250,250,250);border-radius:10px;color:gray;");
}

SunnyTcsProcedureExeDig::~SunnyTcsProcedureExeDig()
{
    delete ui;
}

qint8 SunnyTcsProcedureExeDig::setProcedureFile(SunnyTcsProcedure *pro)
{

    qDebug()<<"setProcedureFile1";
    _procedure=pro;
    openAllNeedFile();
    qDebug()<<"setProcedureFile2";
    const SunnyTcsProcedureAction* action=_procedure->getAction(_currentIndex);
    ui->A0_valueEdit->clear();
    qDebug()<<"setProcedureFile3";
    ui->actionBox->setTitle(action->getActionName());
    ui->actionTEdit->setPlainText(action->getActionExplain());
    ui->stackedWidget->setCurrentIndex((qint32)action->getActionType());
    qDebug()<<"setProcedureFile4";
    return 0;
}

//载入所有需要的文件
void SunnyTcsProcedureExeDig::openAllNeedFile()
{
    if(!_procedure){
        return;
    }
   for(QString path:_procedure->getAllRealitiveFile()){
       SunnyTcsConfig* config=new SunnyTcsConfig(path);
       int ret=config->load();
       if(ret!=0x00){
           QMessageBox::information(0,"tip",path+"文件打开失败");
           return;
       }
       if(config->getType()==0x00){
           ret=config->readValue();
           if(ret!=0x00){
               QMessageBox::information(0,"tip",path+"读取内容失败");
               return;
           }
       }
       _fileMap.insert(path,config);
   }

   QList<SunnyTcsProcedureAction*>* actionList =_procedure->getActionList();
   for(qint32 i=0;i<actionList->count();++i){
       SunnyTcsProcedureAction* action=actionList->at(i);
       QList<QString> actionFiles=actionList->at(i)->getFileList();
       _actionFileMap.insert(action,actionFiles);
   }
}



qint8 SunnyTcsProcedureExeDig::exeAction(qint8 type)
{
    return 0;
}



void SunnyTcsProcedureExeDig::on_Btn_next_clicked()
{
    const SunnyTcsProcedureAction* action=_procedure->getAction(_currentIndex);



    QMap<QString,QList<QString>> targetMap=action->getTargetMap();

    switch((qint32)action->getActionType()){
    case 0:{//修改值
        for(QString path:targetMap.keys()){
            SunnyTcsConfig* con = _fileMap.value(path);
            QList<QString> indexs=targetMap.value(path);
            for(QString index:indexs){
                SunnyTcsConfigItem* item=con->getChildByInfo(index);
                item->setValue(ui->A0_valueEdit->text());
                item->setValueType(action->getValueType());//只对Json修改值由类型要求
            }
        }
        }
        break;
    case 1:{

    }
        break;
    case 2:{

    }
        break;
    case 3:{

    }
        break;
    case 4:{

    }
        break;
    case 5:{

    }
        break;
    }

    _currentIndex++;
    if(_currentIndex==_procedure->getActionCount()){
        ui->nextBtn->setEnabled(false);
        return;
    }
    action=_procedure->getAction(_currentIndex);
    ui->A0_valueEdit->clear();
    ui->actionBox->setTitle(action->getActionName());
    ui->actionTEdit->setPlainText(action->getActionExplain());
    ui->stackedWidget->setCurrentIndex((qint32)action->getActionType());
}


void SunnyTcsProcedureExeDig::on_Btn_save_clicked()
{
    for(QString key:_fileMap.keys()){
        SunnyTcsConfig* con =  _fileMap.value(key);
        con->saveFile();
        con->releaseSelf();
        delete con;
    }
    _fileMap.clear();
    QMessageBox::information(0,"tip","保存成功");
    _currentIndex=0;
    ui->nextBtn->setEnabled(true);
    this->hide();
}

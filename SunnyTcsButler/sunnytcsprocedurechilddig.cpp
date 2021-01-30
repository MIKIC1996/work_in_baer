#include "sunnytcsprocedurechilddig.h"
#include "ui_sunnytcsprocedurechilddig.h"
#include <QMessageBox>

//++++++++++++++++++++++++++++++++++++++++++++
SunnyTcsProcedureChildDig::SunnyTcsProcedureChildDig(QString path, QWidget *parent):QWidget(parent)
  ,ui(new Ui::SunnyTcsProcedureChildDig)
{
    ui->setupUi(this);
    ui->treeWidget->header()->hide();
    _file=new SunnyTcsConfig(path);
    _file->load();
    if(_file->getType()==0x00){//xml读值
        _file->readValue();
    }
    loadFileUi();
    connect(ui->okBtn,SIGNAL(clicked()),this,SLOT(on_Btn_ok_clicked()));
}

//++++++++++++++++++++++++++++++++++++++++++++
SunnyTcsProcedureChildDig::~SunnyTcsProcedureChildDig()
{
    qDebug()<<"~~SunnyTcsProcedureChildDig";
    delete ui;
    if(_file){
        _file->releaseSelf();
        delete _file;
        _file=nullptr;
    }
    qDebug()<<"~~SunnyTcsProcedureChildDig end";
}

//++++++++++++++++++++++++++++++++++++++++++++
void SunnyTcsProcedureChildDig::loadFileUi()
{
    qDebug()<<"loadFileUi";
    if(!_file)
        return;
    if(_file->getType()==0){
        SunnyTcsConfigItem* content =_file->getContent();
        SunyTcsTreeItem *root=new SunyTcsTreeItem(content,QStringList()<<content->getName());
        ui->treeWidget->addTopLevelItem((QTreeWidgetItem*)root);
        //根据数据搭建 数据树
        if(content->isEndPoint()){
        }else{
            for(SunnyTcsConfigItem* item:*(content->getChildren())){
                loadTree(item,root);
            }
        }
    }else if(_file->getType()==1){
        SunnyTcsConfigItem* content =_file->getContent();
        SunyTcsTreeItem *root=new SunyTcsTreeItem(content,QStringList()<<content->getJsonName());
        ui->treeWidget->addTopLevelItem((QTreeWidgetItem*)root);
        //根据数据搭建 数据树
        if(content->isEndPoint()){
        }else{
            for(SunnyTcsConfigItem* item:*(content->getChildren())){
                loadTree(item,root);
            }
        }
    }
}

//++++++++++++++++++++++++++++++++++++++++++++
void SunnyTcsProcedureChildDig::setFile(SunnyTcsConfig *file)
{
    _file=file;
    if(_file)
        loadFileUi();
}

//++++++++++++++++++++++++++++++++++++++++++++
void SunnyTcsProcedureChildDig::on_Btn_ok_clicked()
{
    SunyTcsTreeItem* item=dynamic_cast<SunyTcsTreeItem*>(ui->treeWidget->currentItem());
    SunnyTcsConfigItem* configItem = item->getItem();
    switch(_currentAction){
    case 0:
        if(configItem->getType()==0 && !configItem->isEndPoint()){//如果该标签是xml文件的，并且不是节点标签（有子标签），则不行
            QMessageBox::information(0,"tip","修改值动作下，该标签是xml文件的，并且不是节点标签（有子标签）");
            return;
        }else if(configItem->getType()==1){//该标签是json文件下的，并且是一个json_object，无值可改
            if(configItem->getJsonType()==0){
                QMessageBox::information(0,"tip","该标签是json文件下的，并且是一个json_object");
                return;
            }else if(!configItem->isEndPoint()){//该标签是json文件下的，虽然不是json_object，但他的数据是json对象数组
                QMessageBox::information(0,"tip","该标签是json文件下的，虽然不是json_object，但他的数据是json对象数组");
                return;
            }
        }
        break;
    case 1:
        if(_file->getType()!=0){
            QMessageBox::information(0,"tip","xml添加动作只适用xml文件");
            return;
        }
        break;
    case 2:
        if(_file->getType()!=0){
            QMessageBox::information(0,"tip","xml删除动作只适用xml文件");
            return;
        }
        break;
    case 3://属性修改
        if(_file->getType()!=0){
            QMessageBox::information(0,"tip","属性修改只适用xml文件");
            return;
        }
        break;

    case 4:
        if(_file->getType()!=1){
            QMessageBox::information(0,"tip","json add action only support json file");
            return;
        }
        break;
    case 5:
        if(_file->getType()!=1){
            QMessageBox::information(0,"tip","json删除动作只适用json文件");
            return;
        }
        break;
    }

    emit childDigOk(_file->getPath(),item->getItem()->getIndexInfo());

}

//++++++++++++++++++++++++++++++++++++++++++++
void SunnyTcsProcedureChildDig::on_currentAction_changed(int action)
{
    qDebug()<<"on_currentAction_changed";
    _currentAction=action;
}


//++++++++++++++++++++++++++++++++++++++++++++
void SunnyTcsProcedureChildDig::closeEvent(QCloseEvent *event)
{
    qDebug()<<"closeEvent";

    emit childClose(_file->getPath());
}


//++++++++++++++++++++++++++++++++++++++++++++
void SunnyTcsProcedureChildDig::loadTree(SunnyTcsConfigItem *item,SunyTcsTreeItem* treeItem)
{
    if(item->getType()==0){
        QString in=item->getIndexInfo();

        if(item->isEndPoint()){
            treeItem->addChild(new SunyTcsTreeItem(item,QStringList()<<(item->getName()+" "+in)));
            return;
        }else{
            SunyTcsTreeItem *node=new SunyTcsTreeItem(item,QStringList()<<(item->getName()+" "+in));
            treeItem->addChild((QTreeWidgetItem*)node);
            for(SunnyTcsConfigItem*ite:*(item->getChildren())){
                loadTree(ite,node);
            }
            return;
        }
    }else if(item->getType()==1){
        QString in=item->getIndexInfo();

        if(item->isEndPoint()){
            treeItem->addChild(new SunyTcsTreeItem(item,QStringList()<<(item->getJsonName()+" "+in)));
            return;
        }else{
            SunyTcsTreeItem *node=new SunyTcsTreeItem(item,QStringList()<<(item->getJsonName()+" "+in));
            treeItem->addChild((QTreeWidgetItem*)node);
            for(SunnyTcsConfigItem*ite:*(item->getChildren())){
                loadTree(ite,node);
            }
            return;
        }
    }
}


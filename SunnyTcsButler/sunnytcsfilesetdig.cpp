#include "sunnytcsfilesetdig.h"
#include "ui_sunnytcsfilesetdig.h"
#include <QDir>


/*********************************************
*
*********************************************/
SunnyTcsFileSetDig::SunnyTcsFileSetDig(SunnyTcsConfig *config,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SunnyTcsFileSetDig)
{
    ui->setupUi(this);
    _file=config;
    this->setWindowTitle("文件修改");
    ui->treeWidget->header()->hide();
    ui->file_box->setStyleSheet("QGroupBox{background-color:rgb(250,250,250);border-radius:10px;}");
    ui->file_explain->setStyleSheet("background-color:rgb(250,250,250);border-radius:10px;color:gray;");
    ui->item_explain->setStyleSheet("background-color:rgb(250,250,250);border-radius:10px;color:gray;");
//    QPalette textPalette = ui->file_explain->palette();
//    textPalette.setColor(QPalette::WindowText,Qt::red);
//    ui->file_explain->setPalette(textPalette);
    ui->item_box->setStyleSheet("QGroupBox{background-color:rgb(250,250,250);border-radius:10px;}");
    ui->treeWidget->setStyleSheet("QTreeWidget{background-color:rgb(250,250,250);border-radius:10px;}");
    connect(ui->treeWidget,SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)),this,SLOT(on_currentNode_changed(QTreeWidgetItem*,QTreeWidgetItem*)));
    connect(ui->save_btn,SIGNAL(clicked()),this,SLOT(on_Btn_save_clicked()));
}


/*********************************************
*
*********************************************/
SunnyTcsFileSetDig::~SunnyTcsFileSetDig()
{
    delete ui;
}


/*********************************************
*
*********************************************/
qint8 SunnyTcsFileSetDig::loadFileUi()
{
    if(!_file)
        return 0x01;
    if(_file->getType()==0x00){
        qDebug()<<"set file 0x00";
        ui->file_explain->setPlainText(_file->getFileExplain());
        ui->file_box->setTitle(_file->getFileRemarks());
        ui->file_explain->appendPlainText("\n文件路径:"+_file->getPath());

        if(ui->treeWidget->topLevelItemCount()>0)
            ui->treeWidget->takeTopLevelItem(0);
        SunnyTcsConfigItem* content =_file->getContent();
        if(!content)
            return 0x02;
        QString remarks=content->getItemRemarks()==""?content->getName():content->getItemRemarks();
        SunyTcsTreeItem *root=new SunyTcsTreeItem(content,QStringList()<<remarks);
        ui->treeWidget->addTopLevelItem((QTreeWidgetItem*)root);
        //根据数据搭建 数据树
        if(content->isEndPoint()){
        }else{
            for(SunnyTcsConfigItem* item:*(content->getChildren())){
                loadTree(item,root);
            }
        }
        return 0x00;
    }else if(_file->getType()==0x01){
        qDebug()<<"set file 0x01";
        ui->file_explain->setPlainText(_file->getFileExplain());
        ui->file_box->setTitle(_file->getFileRemarks());
        ui->file_explain->appendPlainText("\n文件路径:"+_file->getPath());

        if(ui->treeWidget->topLevelItemCount()>0)
            ui->treeWidget->takeTopLevelItem(0);
        SunnyTcsConfigItem* content =_file->getContent();
        if(!content)
            return 0x02;
        QString remarks=content->getItemRemarks()==""?content->getJsonName():content->getItemRemarks();
        SunyTcsTreeItem *root=new SunyTcsTreeItem(content,QStringList()<<remarks);
        ui->treeWidget->addTopLevelItem((QTreeWidgetItem*)root);
        //根据数据搭建 数据树
        if(content->isEndPoint()){
        }else{
            for(SunnyTcsConfigItem* item:*(content->getChildren())){
                loadTree(item,root);
            }
        }
        return 0x00;
    }
}


/*********************************************
*
*********************************************/
void SunnyTcsFileSetDig::setFile(SunnyTcsConfig *file)
{
    if(file==nullptr){
        return;
    }
    _file=file;
    loadFileUi();

}

/*********************************************
*
*********************************************/
void SunnyTcsFileSetDig::loadTree(SunnyTcsConfigItem *item,SunyTcsTreeItem* treeItem)
{

    QString in=item->getIndexInfo();
    QString remarks;
    if(_file->getType()==0){
        remarks=item->getItemRemarks()==""?item->getName():item->getItemRemarks();
    }else if(_file->getType()==1){
        remarks=item->getItemRemarks()==""?item->getJsonName():item->getItemRemarks();
    }
    if(item->isEndPoint()){
        treeItem->addChild(new SunyTcsTreeItem(item,QStringList()<<(remarks)));
        return;
    }else{
        SunyTcsTreeItem *node=new SunyTcsTreeItem(item,QStringList()<<(remarks));
         treeItem->addChild((QTreeWidgetItem*)node);
        for(SunnyTcsConfigItem*ite:*(item->getChildren())){
            loadTree(ite,node);
        }
        return;
    }

}


/*********************************************
*
*********************************************/
void SunnyTcsFileSetDig::on_currentNode_changed(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    SunyTcsTreeItem* treeItem=(SunyTcsTreeItem*)current;
    if(!current)
        return;


    SunnyTcsConfigItem* item=treeItem->getItem();
    QString remark=item->getItemRemarks()==""?item->getName():item->getItemRemarks();
    ui->item_box->setTitle(QString("当前标签: %1").arg(remark));

    ui->item_explain->setPlainText(item->getExplain());
    ui->attributes_list->setRowCount(0);

    QXmlStreamAttributes* attributes=item->getItemAttributes();
    QMap<QString,QString>* attriMap=item->getAttributeRemarks();
    for(QString key:attriMap->keys()){
        ui->attributes_list->setRowCount(ui->attributes_list->rowCount()+1);
        ui->attributes_list->setItem(ui->attributes_list->rowCount()-1,0,new QTableWidgetItem(attriMap->value(key)));
        ui->attributes_list->setItem(ui->attributes_list->rowCount()-1,1,new QTableWidgetItem(attributes->value(key).toString()));
    }
    qDebug()<<item->getValue();
    ui->value_edit->setText(item->getValue());
}


/*********************************************
*
*********************************************/
void SunnyTcsFileSetDig::on_okBtn_clicked()
{
    _file->releaseSelf();
    _file->setPath("D://vc.xml");
    _file->saveFile();
    delete _file;
    emit file_setOk();
}


/*********************************************
*
*********************************************/
void SunnyTcsFileSetDig::on_cancelbtn_clicked()
{

}

/*********************************************
*
*********************************************/
void SunnyTcsFileSetDig::on_Btn_save_clicked()
{
    _file->setPath("D://vc.json");
    _file->saveFile();
    _file->releaseSelf();
    this->hide();
}

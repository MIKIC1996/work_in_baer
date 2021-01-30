#include "configsetdig.h"
#include "ui_configsetdig.h"


/**************************************************
*

*
***************************************************/
ConfigSetDig::ConfigSetDig(SunnyTcsConfig* con,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ConfigSetDig)
{
    ui->setupUi(this);
    this->setWindowTitle("文件配置");
    ui->treeWidget->header()->hide();
    _file=con;
    ui->attribute_list->setColumnWidth(0,ui->attribute_list->width()/2-10);
    ui->attribute_list->setColumnWidth(1,ui->attribute_list->width()/2-10);
    //this->setFixedSize(this->width(),this->height());
    connect(ui->treeWidget,SIGNAL(currentItemChanged(QTreeWidgetItem*,QTreeWidgetItem*)),this,SLOT(on_currentNode_changed(QTreeWidgetItem*,QTreeWidgetItem*)));
    connect(ui->ok_btn,SIGNAL(clicked()),this,SLOT(on_okBtn_clicked()));
    connect(ui->item_ok_btn,SIGNAL(clicked()),this,SLOT(on_item_okBtn_clicked()));
    connect(ui->cancel_btn,SIGNAL(clicked()),this,SLOT(on_cancelBtn_clicked()));
}


/**************************************************
*

*
***************************************************/
ConfigSetDig::~ConfigSetDig()
{
    delete ui;
}


/**************************************************
*
*
*
***************************************************/
void ConfigSetDig::loadTree(SunnyTcsConfigItem *item,SunyTcsTreeItem* treeItem)
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


/**************************************************
*
*
*
***************************************************/
void ConfigSetDig::setFile(SunnyTcsConfig *file)
{
    if(file==nullptr)
        return;
    if(ui->treeWidget->topLevelItemCount()>0)
        ui->treeWidget->takeTopLevelItem(0);//删除之前的文件根
    _file=file;
    ui->file_explain->setPlainText(file->getFileExplain());
    ui->file_remark_edit->setText(file->getFileRemarks());
    loadFileUI();
}


/**************************************************
*
*
*
***************************************************/
void ConfigSetDig::loadFileUI()
{
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


/**************************************************
*
*
*
***************************************************/
void ConfigSetDig::on_currentNode_changed(QTreeWidgetItem *current, QTreeWidgetItem *previous)
{
    if(_file->getType()==0){
        SunyTcsTreeItem* treeItem=(SunyTcsTreeItem*)current;
        if(!current)
            return;

        SunnyTcsConfigItem* item=treeItem->getItem();
        ui->item_Box->setTitle(QString("当前标签: %1").arg(item->getName()));

        //获取当前标签备注名
        ui->item_remark_edit->clear();
        if(!item->getItemRemarks().isEmpty()){
            ui->item_remark_edit->setText(item->getItemRemarks());
        }
        //获取当前标签解释
        ui->item_explain->clear();
        if(!item->getExplain().isEmpty()){
            ui->item_explain->setPlainText(item->getExplain());
        }

        //获取当前标签value类型
        if(!item->isEndPoint()){
            ui->data_type->setCurrentIndex(2);//无
            ui->data_type->setEnabled(false);
        }else{
            ui->data_type->setEnabled(true);
            ui->data_type->setCurrentIndex(item->getValueType());
        }

        if(!item->getExplain().isEmpty()){
            ui->item_explain->setPlainText(item->getExplain());
        }

        //设置属性备注
        ui->attribute_list->setRowCount(0);
        QMap<QString,QString>* remark=item->getAttributeRemarks();
        //qDebug()<<"mapcount"+QString::number(remark->count());
        if(remark->count()!=0){
            int row=0;
            ui->attribute_list->setRowCount(remark->count());
            for(QString name:remark->keys()){
                ui->attribute_list->setItem(row,0,new QTableWidgetItem(name));
                ui->attribute_list->setItem(row,1,new QTableWidgetItem(remark->value(name)));
                ++row;
            }
        }else{
            QXmlStreamAttributes* item_attr=item->getItemAttributes();
            for(qint32 i=0;i<item_attr->count();++i){
                ui->attribute_list->insertRow(ui->attribute_list->rowCount());
                ui->attribute_list->setItem(ui->attribute_list->rowCount()-1,0,new QTableWidgetItem(item_attr->at(i).name().toString()));
                ui->attribute_list->setItem(ui->attribute_list->rowCount()-1,1,new QTableWidgetItem(""));
                qDebug()<<item->getItemAttributes()->count();
                qDebug()<<item_attr->at(i).name().toString();
            }
        }

        //qDebug()<<item_attr->hasAttribute("Name");
        for(qint32 i=0;i<ui->attribute_list->rowCount();++i){
            ui->attribute_list->item(i,0)->setTextAlignment(Qt::AlignCenter);
        }
    }else if(_file->getType()==1){
        SunyTcsTreeItem* treeItem=(SunyTcsTreeItem*)current;
        if(!current)
            return;


        SunnyTcsConfigItem* item=treeItem->getItem();
        ui->item_Box->setTitle(QString("当前标签: %1").arg(item->getName()));

        //获取当前标签备注名
        ui->item_remark_edit->clear();
        if(!item->getItemRemarks().isEmpty()){
            ui->item_remark_edit->setText(item->getItemRemarks());
        }
        //获取当前标签解释
        ui->item_explain->clear();
        if(!item->getExplain().isEmpty()){
            ui->item_explain->setPlainText(item->getExplain());
        }

        //获取当前标签value类型
        if(!item->isEndPoint()){
            ui->data_type->setCurrentIndex(2);//无
            ui->data_type->setEnabled(false);
        }else{
            ui->data_type->setEnabled(true);
            ui->data_type->setCurrentIndex(item->getValueType());
        }

        if(!item->getExplain().isEmpty()){
            ui->item_explain->setPlainText(item->getExplain());
        }
    }
}

/**************************************************
*

*
***************************************************/
void ConfigSetDig::on_okBtn_clicked()
{
     on_item_okBtn_clicked();
     QString fileRemarks=ui->file_remark_edit->text();
     if(!fileRemarks.isEmpty())
         _file->setFileRemarks(fileRemarks);
     QString fileExplain=ui->file_explain->toPlainText();
     if(!fileExplain.isEmpty())
         _file->setFileExplain(fileExplain);
     this->hide();
     emit setOk(_file);


}

/**************************************************
*
标签项
  备注名
  解释
  属性表
  value类型
*
***************************************************/
void ConfigSetDig::on_item_okBtn_clicked()
{

    SunyTcsTreeItem* treeItem = dynamic_cast<SunyTcsTreeItem*>(ui->treeWidget->currentItem());
    if(treeItem==nullptr)
        return;
    SunnyTcsConfigItem* item=treeItem->getItem();
    //修改标签备注名
    if(!ui->item_remark_edit->text().isEmpty())
        item->setItemRemarks(ui->item_remark_edit->text());
    //修改标签解释
    if(!ui->item_explain->toPlainText().isEmpty())
        item->setExplain(ui->item_explain->toPlainText());
    //修改标签value数据类型
    if(ui->data_type->currentIndex()!=item->getValueType()){
        item->setValueType(ui->data_type->currentIndex());
    }
    //修改标签属性表
    bool remarkIsChanged=false;
    for(qint32 i=0;i<ui->attribute_list->rowCount();++i){
        if(!ui->attribute_list->item(i,1)->text().isEmpty()){
            remarkIsChanged=true;
            break;
        }
    }
    if(remarkIsChanged){
        QMap<QString,QString>* remarks=item->getAttributeRemarks();
        remarks->clear();
        for(qint32 i=0;i<ui->attribute_list->rowCount();++i){
            remarks->insert(ui->attribute_list->item(i,0)->text(),ui->attribute_list->item(i,1)->text());
        }
    }
}


/**************************************************
*释放 _file的内存空间
*
*
***************************************************/
void ConfigSetDig::on_cancelBtn_clicked()
{
    _file->releaseSelf();
    //delete _file;
    this->hide();
}


/**************************************************
*

*
***************************************************/
void ConfigSetDig::closeEvent(QCloseEvent *event)
{
    //_file=nullptr;
}

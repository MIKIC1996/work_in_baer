#include "sunnytcsprocedureconfigdig.h"
#include "ui_sunnytcsprocedureconfigdig.h"
#include <QFileDialog>
#include <QMessageBox>


//++++++++++++++++++++++++++++++++++++++++++++
SunnyTcsProcedureConfigDig::SunnyTcsProcedureConfigDig(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SunnyTcsProcedureConfigDig)
{
    ui->setupUi(this);

    connect(ui->openFileBtn,SIGNAL(clicked()),this,SLOT(on_fileOpenBtn_clicked()));
    connect(ui->addActionBtn,SIGNAL(clicked()),this,SLOT(on_Btn_addAction_clicked()));
    connect(ui->deleteActionBtn,SIGNAL(clicked()),this,SLOT(on_Btn_deleteAction_clicked()));
    connect(ui->createActionBtn,SIGNAL(clicked()),this,SLOT(on_Btn_createAction_clicked()));
    connect(ui->tabWidget,SIGNAL(currentChanged(int)),this,SLOT(on_currentTab_changed(int)));
    connect(ui->saveProcedureBtn,SIGNAL(clicked()),this,SLOT(on_Btn_saveProcedure_clicked()));
    connect(ui->Action_CBox,SIGNAL(currentIndexChanged(int)),this,SLOT(on_actionBox_changed(int)));
    connect(ui->addJsonCBox,SIGNAL(currentIndexChanged(int)),this,SLOT(on_addJsonCBox_changed(int)));
    connect(ui->attAddBtn,SIGNAL(clicked()),this,SLOT(on_Btn_attsAdd_clicked()));
    connect(ui->jsonValueBtn,SIGNAL(clicked()),this,SLOT(on_Btn_jsonValue_clicked()));
    connect(ui->deleteSelectedItemBtn,SIGNAL(clicked()),this,SLOT(on_Btn_deleteSelected_clicked()));
}


//++++++++++++++++++++++++++++++++++++++++++++
SunnyTcsProcedureConfigDig::~SunnyTcsProcedureConfigDig()
{
    qDebug()<<"~SunnyTcsProcedureConfigDig";
    delete ui;

    for(QString key:_childDigs.keys()){
        SunnyTcsProcedureChildDig *dig=_childDigs.value(key);
        if(dig)
            delete dig;
    }
    qDebug()<<"~SunnyTcsProcedureConfigDig end";
}


//++++++++++++++++++++++++++++++++++++++++++++
void SunnyTcsProcedureConfigDig::setProcedureFile(SunnyTcsProcedure *pro)
{
    qDebug()<<"setProcedureFile1";
    _procedure=pro;
    ui->proName->setText(pro->getProcedureName());
    ui->ProcedureNameEdit->setText(pro->getProcedureName());
    ui->proExplain->setPlainText(pro->getProcedureExplain());
    qDebug()<<"setProcedureFile2";
    qint32 tabCount=ui->tabWidget->tabBar()->count();
    for(int i=tabCount-1;i>=0;--i){
        ui->tabWidget->tabBar()->removeTab(i);
    }
    qDebug()<<"setProcedureFile3";
    if(_procedure->getActionCount()==0){
        _procedure->addAction(new SunnyTcsProcedureAction());
    }
    qDebug()<<"setProcedureFile4";
    for(qint32 i=0;i<_procedure->getActionCount();++i){
        ui->tabWidget->tabBar()->addTab(_procedure->getAction(i)->getActionName());
    }
    qDebug()<<"setProcedureFile5";
}




//++++++++++++++++++++++++++++++++++++++++++++
void SunnyTcsProcedureConfigDig::openFile(QString path)
{
    qDebug()<<"openFile";
    SunnyTcsProcedureChildDig* childDig=new SunnyTcsProcedureChildDig(path);
    qDebug()<<"new";
    ui->mdiArea->addSubWindow(childDig);
    _childDigs.insert(path,childDig);
    childDig->show();
    connect(childDig,SIGNAL(childDigOk(QString,QString)),this,SLOT(on_childOk(QString,QString)));
    connect(childDig,SIGNAL(childClose(QString)),this,SLOT(on_childClose(QString)));
    connect(ui->Action_CBox,SIGNAL(currentIndexChanged(int)),childDig,SLOT(on_currentAction_changed(int)));
}


//++++++++++++++++++++++++++++++++++++++++++++
void SunnyTcsProcedureConfigDig::closeEvent(QCloseEvent *event)
{
//    if(QMessageBox::Yes != QMessageBox::information(0,"tip","流程未保存，是否需要保存？",QMessageBox::Yes,QMessageBox::No)){
//        emit procedureClose();
//    }else{
//        emit procedureSave();
//    }
     emit procedureClose();
}




//++++++++++++++++++++++++++++++++++++++++++++
void SunnyTcsProcedureConfigDig::on_fileOpenBtn_clicked()
{
    qDebug()<<"dadadadad";
    QString path=QFileDialog::getOpenFileName(this,"open",QDir::currentPath(),"config(*.xml;*.json)");
    if(path.isEmpty())
        return;
    qDebug()<<"xsdfeqwf";
    if(_childDigs.keys().contains(path)){
        QMessageBox::information(0,"tip","文件已经打开");
        return;
    }
    openFile(path);
}

//++++++++++++++++++++++++++++++++++++++++++++
void SunnyTcsProcedureConfigDig::on_childOk(QString path, QString index)
{
    qDebug()<<"childOk";
    if(_indexMap.keys().contains(path)){
        if(_indexMap.value(path).contains(index)){
            qDebug()<<"on_childOk1";
            return;
        }
        QList<QString> list = _indexMap.value(path);
        list.append(index);
        _indexMap.insert(path,list);

        ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,new QTableWidgetItem(index));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,new QTableWidgetItem(path));
        return;
    }
    if(!_indexMap.keys().contains(path)){
        QList<QString> listPtr;
        listPtr.append(index);
        _indexMap.insert(path,listPtr);
        ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,new QTableWidgetItem(index));
        ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,new QTableWidgetItem(path));
        return;
    }
}

//++++++++++++++++++++++++++++++++++++++++++++
void SunnyTcsProcedureConfigDig::on_childClose(QString path)
{
    qDebug()<<"on_childClose";
    _childDigs.remove(path);
}

//++++++++++++++++++++++++++++++++++++++++++++
void SunnyTcsProcedureConfigDig::on_Btn_addAction_clicked()//保存动作
{
    qDebug()<<"save";
    if(!_procedure){
        return;
    }
    if(ui->tableWidget->rowCount()==0){
        QMessageBox::information(0,"tip","this action must be linked to 1 item at least");
        return;
    }
    if(ui->ActionNameEdit->text().isEmpty()){
        QMessageBox::information(0,"tip","action name is null");
        return;
    }
    if(ui->exeCountSBox->text().toInt()<=0){
        QMessageBox::information(0,"tip","执行次数不能为0");
        return;
    }
//    SunnyTcsProcedureAction* action=new SunnyTcsProcedureAction((SunnyTcsProcedureAction::PROCEDURE_ACTION_TYPE)ui->Action_CBox->currentIndex()
//                                                                ,ui->exeCountSBox->text().toInt()
//                                                                ,ui->ActionNameEdit->text()
//                                                                ,ui->ActionExplainPlainEdit->toPlainText());
    qint32 index=ui->tabWidget->currentIndex();
    SunnyTcsProcedureAction* ac=_procedure->getAction(index);

    ac->addTarget(&_indexMap);
    ac->setActionTypeByInt(ui->Action_CBox->currentIndex());
    ac->setActionName(ui->ActionNameEdit->text());
    ac->setActionExplain((ui->ActionExplainPlainEdit->toPlainText()));
    ac->setExeCount(ui->exeCountSBox->value());
    ac->setValueType(ui->A0_valueTypeCBox->currentIndex());

    if(ui->Action_CBox->currentIndex()==1)//添加xml 动作，保存附页额外信息
    {
        ac->setXmlName(ui->xmlNameEdit->text());
        QStringList atts;
        for(qint32 i=0;i<ui->xmlattsList->count();++i){
            atts.append(ui->xmlattsList->item(i)->text());
        }
        ac->setXmlAttributes(atts);
    }else if(ui->Action_CBox->currentIndex()==4){//添加json动作，保存附页信息
        ac->setJsonAddType(ui->addJsonCBox->currentIndex());
        QStringList values;
        QList<qint8> types;
        if(ac->getJsonAddType()==0){//添加对象
            for(qint32 i=0;i<ui->addJsonTable->rowCount();++i){
                values.append(ui->addJsonTable->item(i,0)->text());
                types.append(ui->addJsonTable->item(i,1)->text().toInt());
            }
            ac->setJsonValueList(values);
            ac->setJsonValueTypes(types);
        }else if(ac->getJsonAddType()==1){//添加值
            values.append(ui->addJsonTable->item(0,0)->text());
            types.append(ui->addJsonTable->item(0,1)->text().toInt());
            ac->setJsonValueList(values);
            ac->setJsonValueTypes(types);
        }
    }

    ui->tabWidget->tabBar()->setTabText(index,ac->getActionName());
    _indexMap.clear();
}



//++++++++++++++++++++++++++++++++++++++++++++
void SunnyTcsProcedureConfigDig::on_Btn_createAction_clicked()
{
    SunnyTcsProcedureAction *ac=new SunnyTcsProcedureAction();
    _procedure->addAction(ac);
    ui->tabWidget->tabBar()->addTab(ac->getActionName());
}




//++++++++++++++++++++++++++++++++++++++++++++
void SunnyTcsProcedureConfigDig::on_Btn_deleteAction_clicked()
{
    if(ui->tabWidget->tabBar()->count()==1){
        QMessageBox::information(0,"tip","cant delete all action");
        return;
    }
    qint32 index=ui->tabWidget->currentIndex();
    _procedure->deleteAction(index);
    ui->tabWidget->setCurrentIndex(index-1);
    ui->tabWidget->tabBar()->removeTab(index);
}




//++++++++++++++++++++++++++++++++++++++++++++
void SunnyTcsProcedureConfigDig::on_currentTab_changed(int index)
{
    qDebug()<<"on_currentTab_changed"+QString::number(index);

    SunnyTcsProcedureAction*ac= _procedure->getAction(index);
    if(ac){
        ui->tableWidget->setRowCount(0);

        ui->jsonValueEdit->clear();
        ui->addJsonTable->setRowCount(0);
        ui->A0_valueTypeCBox->setCurrentIndex(ac->getValueType());
        ui->ActionNameEdit->setText(ac->getActionName());
        ui->ActionExplainPlainEdit->setPlainText(ac->getActionExplain());
        ui->exeCountSBox->setValue(ac->getExeCount());
        ui->Action_CBox->setCurrentIndex((int)ac->getActionType());
        _indexMap=ac->getTargetMap();

        for(QString key:_indexMap.keys()){
            QList<QString> list=_indexMap.value(key);
            for(QString key2:list){
                ui->tableWidget->setRowCount(ui->tableWidget->rowCount()+1);
                ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,0,new QTableWidgetItem(key2));

                ui->tableWidget->setItem(ui->tableWidget->rowCount()-1,1,new QTableWidgetItem(key));
                qDebug()<<key2+"||"+key;
            }
        }
        if(ac->getActionType()==1){
            ui->xmlNameEdit->setText(ac->getXmlName());
            ui->xmlattsList->clear();
            for(QString att:ac->getXmlAttributes()){  
                ui->xmlattsList->addItem(att);
            }
        }else if(ac->getActionType()==4){
            ui->addJsonTable->setRowCount(0);
            ui->addJsonCBox->setCurrentIndex(ac->getJsonAddType());
            QStringList values=ac->getJsonValueList();
            QList<qint8> types=ac->getJsonAddValueList();
            for(qint32 i=0;i<values.count();++i){
                ui->addJsonTable->setRowCount(ui->addJsonTable->rowCount()+1);
                ui->addJsonTable->setItem(ui->addJsonTable->rowCount()-1,0,new QTableWidgetItem(values.at(i)));
                ui->addJsonTable->setItem(ui->addJsonTable->rowCount()-1,1,new QTableWidgetItem(QString::number(types.at(i))));
            }


        }

    }
}

//++++++++++++++++++++++++++++++++++++++++++++
void SunnyTcsProcedureConfigDig::on_Btn_saveProcedure_clicked()
{

    _procedure->setProcedureName(ui->ProcedureNameEdit->text());
    _procedure->setProcedureExplain(ui->proExplain->toPlainText());
    this->hide();
    emit procedureSave();
}

//++++++++++++++++++++++++++++++++++++++++++++
void SunnyTcsProcedureConfigDig::on_actionBox_changed(int index)
{
    if(index==1)
        ui->extraPageSWidget->setCurrentIndex(0);
    else if(index==4)
        ui->extraPageSWidget->setCurrentIndex(1);
    else
        ui->extraPageSWidget->setCurrentIndex(2);
}

//++++++++++++++++++++++++++++++++++++++++++++
void SunnyTcsProcedureConfigDig::on_addJsonCBox_changed(int index)
{
//    if(index==0)
//        ui->addJsonSWidget->setCurrentIndex(0);
//    else if(index==1){
//        ui->addJsonSWidget->setCurrentIndex(1);
//    }
}

//++++++++++++++++++++++++++++++++++++++++++++
void SunnyTcsProcedureConfigDig::on_Btn_attsAdd_clicked()
{
    ui->xmlattsList->addItem(ui->xmlAttEdit->text());
}

//++++++++++++++++++++++++++++++++++++++++++++
void SunnyTcsProcedureConfigDig::on_Btn_jsonValue_clicked()
{
    if(ui->addJsonCBox->currentIndex()==1&&ui->addJsonTable->rowCount()>0){
        QMessageBox::information(0,"tip","add json value only one is required");
        return;
    }
    ui->addJsonTable->setRowCount(ui->addJsonTable->rowCount()+1);
    ui->addJsonTable->setItem(ui->addJsonTable->rowCount()-1,0,new QTableWidgetItem(ui->jsonValueEdit->text()));
    ui->addJsonTable->setItem(ui->addJsonTable->rowCount()-1,1,new QTableWidgetItem(ui->jsonValueCBox->currentIndex()));
}

//++++++++++++++++++++++++++++++++++++++++++++
void SunnyTcsProcedureConfigDig::on_Btn_deleteSelected_clicked()
{
    int row=ui->tableWidget->currentRow();
    if(row==-1){
        QMessageBox::information(0,"tip","no any item selected");
        return;
    }
    ui->tableWidget->removeRow(row);
}

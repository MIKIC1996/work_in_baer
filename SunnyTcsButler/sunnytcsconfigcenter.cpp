#include "sunnytcsconfigcenter.h"
#include <QDir>
#include <QMessageBox>

/*****************************************************
*
*
******************************************************/
SunnyTcsConfigCenter::SunnyTcsConfigCenter(QString path,QString procedurePath,QObject *parent) : QObject(parent)
{
    _path=path;
    _procedurePath=procedurePath;
}


/*****************************************************
*
*
******************************************************/
SunnyTcsConfigCenter::~SunnyTcsConfigCenter()
{
    qDebug()<<"~SunnyTcsConfigCenter";
    for(QString key:_configMap.keys()){
        SunnyTcsConfig* con=_configMap.value(key);
        if(con!=nullptr){
            qDebug()<<"SunnyTcsConfigCenter0.3";
            con->releaseSelf();
            qDebug()<<"SunnyTcsConfigCenter0.5";
            delete con;
        }
    }
     qDebug()<<"~SunnyTcsConfigCenter end";
}


/*****************************************************
*读取总配置文件，初始化
*
******************************************************/
qint8 SunnyTcsConfigCenter::readConfig()
{
    //读取原来的配置，暂时废弃-------------------------
    QFile filec(_path);
    if(!filec.exists()){
        return 0x01;
    }
    if(!filec.open(QFile::ReadOnly|QFile::Text)){
        return 0x02;
    }
    QXmlStreamReader xsrc(&filec);
    if(!xsrc.readNextStartElement() || xsrc.name() != "root"){
        filec.close();
        return 0x03;
    }
    while(!xsrc.atEnd() && !xsrc.hasError() && xsrc.readNext()){
        if(!xsrc.isStartElement())
            continue;
        if(xsrc.name() != "config"){
            qDebug()<<xsrc.name();
            return 0x04;
        }
        QString name;
        QString path;
        QString configPath;
        QString explain;
        xsrc.readNextStartElement();
        if(xsrc.name()!="fileRemarks"){
            return 0x05;
        }else{
            name=xsrc.readElementText();
        }
        xsrc.readNextStartElement();
        if(xsrc.name()!="filePath"){
            return 0x06;
        }else{
            path=xsrc.readElementText();
        }
        xsrc.readNextStartElement();
        if(xsrc.name()!="configPath"){
           return 0x07;
        }
         configPath=xsrc.readElementText();
        xsrc.readNextStartElement();
        if(xsrc.name()!="fileExplain"){
            return 0x08;
        }
        explain=xsrc.readElementText();
        //插入读取的数据
        SunnyTcsConfig *con=new SunnyTcsConfig(path);

        con->setFileRemarks(name);
        con->setConfigPath(configPath);
        con->setFileExplain(explain);
        _configMap.insert(path,con);
    }
    emit configPathMap_changed();
    filec.close();




    //------------------------------直接用之前写好xml通用解析方法读取
   // qDebug()<<"read proce config";
    SunnyTcsConfig con(_procedurePath);
    con.load();
    con.readValue();
   // qDebug()<<"read proce config mid";
    SunnyTcsConfigItem* root=con.getContent();//根节点
    for(qint32 i=0;i<root->getChildren()->count();++i){
        //qDebug()<<"read proce config mid 1";
        SunnyTcsConfigItem* procedureItem=root->getChild(i);
        SunnyTcsProcedure *pro=new SunnyTcsProcedure();//--procedure
        QXmlStreamAttributes* atts = procedureItem->getItemAttributes();
        pro->setProcedureName(atts->value("name").toString());
        pro->setProcedureExplain(atts->value("explain").toString());
        //qDebug()<<"read proce config mid 11";
        for(qint32 j=0;j<procedureItem->getChildren()->count();++j){
            SunnyTcsConfigItem* actionItem=procedureItem->getChild(j);
            atts=actionItem->getItemAttributes();
            SunnyTcsProcedureAction *ac=new SunnyTcsProcedureAction();//---action
            QMap<QString,QList<QString>> indexMap;
            ac->setActionTypeByInt(atts->value("actionType").toInt());
            ac->setActionName(atts->value("actionName").toString());
            ac->setActionExplain(atts->value("actionExplain").toString());
            ac->setExeCount(atts->value("actionCount").toInt());
            ac->setValueType(atts->value("actionValueType").toInt());
            //qDebug()<<"read proce config mid 111";
            for(qint32 k=0;k<actionItem->getChildren()->count();++k){
                SunnyTcsConfigItem* targetItem=actionItem->getChild(k);//----target
                atts=targetItem->getItemAttributes();
                QString path=atts->value("path").toString();
                QList<QString> indexs;
               // qDebug()<<"read proce config mid 1111";
                for(qint32 l=0;l<targetItem->getChildren()->count();++l){
                   // qDebug()<<"read proce config mid 11111";
                    SunnyTcsConfigItem* indexItem=targetItem->getChild(l);
                    QString index=indexItem->getValue();
                    indexs.append(index);
                    //qDebug()<<"read proce config mid 11111 end";
                }
                indexMap.insert(path,indexs);

            }
            ac->addTarget(&indexMap);
            pro->addAction(ac);
        }
        _procedureMap.insert(pro->getProcedureName(),pro);
    }
    //qDebug()<<"read proce config end";
    con.releaseSelf();//释放数据内存
    emit procedureMap_changed();
    return 0;

}


/*****************************************************
*配置文件目录xml文件 的格式
* <root>
*   <config>
*       <fileRemarks></fileRemarks>
*       <filePath><filePath>
*       <configPath></configPath>
*       <fileExplain></fileExplain>
*   </config>
*
* </root>
*
******************************************************/
qint8 SunnyTcsConfigCenter::saveConfig()
{
    //----------原配置页保存，暂时废弃-------------
    if(_configMap.count()>0){
        QFile filec(_path);
        if(!filec.open(QFile::WriteOnly|QFile::Truncate)){
            return 0x01;
        }
        QXmlStreamWriter xswc(&filec);
        xswc.setAutoFormatting(true);
        xswc.writeStartDocument();
        xswc.writeStartElement("root");

        for(QString key:_configMap.keys()){
            xswc.writeStartElement("config");
            xswc.writeTextElement("fileRemarks",_configMap.value(key)->getFileRemarks());
            xswc.writeTextElement("filePath",key);
            xswc.writeTextElement("configPath",_configMap.value(key)->getConfigPath());
            xswc.writeTextElement("fileExplain",_configMap.value(key)->getFileExplain());
            xswc.writeEndElement();
        }
        xswc.writeEndElement();
        filec.close();
    }
    //----------------------------------------------
    QFile file(_procedurePath);
    qDebug()<<_procedurePath;
    if(!file.open(QFile::WriteOnly|QFile::Truncate)||!file.exists()){
        qDebug()<<"file open fail";
        return 0x01;
    }
    QXmlStreamWriter xsw(&file);
    xsw.setAutoFormatting(true);
    xsw.writeStartDocument();
    xsw.writeStartElement("root");
    qDebug()<<"111";
    for(QString Name:_procedureMap.keys()){
        SunnyTcsProcedure* pro=_procedureMap.value(Name);
        pro->saveProcedure(xsw);
    }
    xsw.writeEndElement();
    file.close();
    return 0x00;
}


/*****************************************************
*
*
******************************************************/
SunnyTcsConfig* SunnyTcsConfigCenter::reLoadConfig(QString path)
{
    if(!_configMap.contains(path)){
        QMessageBox::information(0,"tip","reLoadConfig error");
        return nullptr;
    }
    SunnyTcsConfig *con=_configMap.value(path);
    con->reload();
    return con;
}

/*****************************************************
*
*
******************************************************/
qint8 SunnyTcsConfigCenter::addConfig(SunnyTcsConfig *con)
{
//    if(_configPathMap.contains(con->getFileRemarks()))
//        return 0x01;
//    qDebug()<<"addconfig"+con->getFileRemarks();
//    qDebug()<<"addconfig"+con->getPath();
//    _configPathMap.insert(con->getFileRemarks(),con->getPath());
//    _configMap.insert(con->getFileRemarks(),con);
//    emit configPathMap_changed();
    return 0;
}

SunnyTcsProcedure *SunnyTcsConfigCenter::createNewProcedure()
{
    if(_tempProcedure){
        delete _tempProcedure;
        _tempProcedure=nullptr;
    }
    _tempProcedure=new SunnyTcsProcedure();
    return _tempProcedure;
}


/*****************************************************
*
*
******************************************************/
void SunnyTcsConfigCenter::on_configDig_setOK(SunnyTcsConfig *con)//configDig设置完成，需要更新configPathMap
{
    con->saveConfig();
    _configMap.insert(con->getPath(),con);
    con->releaseSelf();//完成配置保存后，释放数据内存
    this->saveConfig();//保存配置目录
    emit configPathMap_changed();//告诉界面，刷新以下配置表
}

/*****************************************************
*
*
******************************************************/
void SunnyTcsConfigCenter::on_procedureSave()
{

    qDebug()<<"on_procedureSave";
    if(!_tempProcedure)
        return;
    QString name=_tempProcedure->getProcedureName();
    if(_procedureMap.keys().contains(name)){
        _tempProcedure->setProcedureName(name+"_副本");
    }
    _procedureMap.insert(_tempProcedure->getProcedureName(),_tempProcedure);
    _tempProcedure=nullptr;
    this->saveConfig();
    emit procedureMap_changed();

}

/*****************************************************
*
*
******************************************************/
void SunnyTcsConfigCenter::on_procedureClose()
{
    if(_tempProcedure)
        delete _tempProcedure;
    _tempProcedure=nullptr;
}



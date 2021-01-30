#include "sunnytcsconfig.h"
#include <QDebug>
#include <QFileInfo>
#include <QDir>
#include <QMessageBox>

#define PARAMS_CONFIG "//params_config.xml"
#define ROOT_NODE "root_config"




/*************************************************************
*
*
**************************************************************/
SunnyTcsConfig::SunnyTcsConfig(QString path, QObject *parent):QObject(parent)
{
    //path.append(PARAMS_CONFIG);
    _path=path;
    QFileInfo fileInfo(_path);
    QString suffix=fileInfo.suffix();
    if(suffix=="xml"){
        QString configFileName=fileInfo.completeBaseName()+"_config.xml";
        _configPath=(QDir::currentPath()+"/config_set/"+configFileName);
        _fileRemarks=fileInfo.completeBaseName()+"_"+QDateTime::currentDateTime().toString();//默认文件备注名
        _type=0;
    }else if(suffix=="json"){
        QString configFileName=fileInfo.completeBaseName()+"_config.xml";
        _configPath=(QDir::currentPath()+"/config_set/"+configFileName);
        _fileRemarks=fileInfo.completeBaseName()+"_"+QDateTime::currentDateTime().toString();//默认文件备注名
        _type=1;
    }


}


/*************************************************************
*释放自己与所有子对象
*
**************************************************************/
void SunnyTcsConfig::releaseSelf()
{
    if(_content){
        int ret=_content->deleteAllChild();
        delete _content;
        _content=nullptr;
    }
}


/*************************************************************
**保存该xml文件的配置文件
* 保存路径： 可执行文件目录的xml_config文件夹下
* 保存名称： xml文件名_config.xml
* 格式
*  <root>
*   <path>xml文件路径</path>
*   <fileRemarks>文件备注名</fileRemarks>
*   <fileExplain>文件说明</fileExplain>
*   <item index=-1>  -1是根节点
*       <itemRemarks>标签备注名</itemRemarks>
*       <itemExplain>标签说明</itemExplain>
*       <attributeRemarks ></attributeRemarks>
*   </item>
*
*
* </root>
*
*
**************************************************************/
qint8 SunnyTcsConfig::saveConfig()
{
    QDir dir(_configPath.left(_configPath.lastIndexOf('/')));
    if(!dir.exists()){
        if(!dir.mkdir(_configPath)){
            qDebug()<<"saveConfig0x01";
            return 0x01;
        }
    }

    QFile file(_configPath);
    if(!file.open(QFile::WriteOnly|QFile::Truncate)){
        qDebug()<<"saveConfig0x02";
        return 0x02;
    }

    QXmlStreamWriter xsw(&file);
    xsw.setAutoFormatting(true);
    xsw.writeStartDocument();
    xsw.writeStartElement("root");
    _content->save(xsw);
    xsw.writeEndElement();
    file.close();
    return 0;
}

qint8 SunnyTcsConfig::saveFile()
{
    //qDebug()<<_type;
    if(_type==0x00){//保存成xml
        QDir dir(_path.left(_path.lastIndexOf('/')));
        if(!dir.exists()){
            if(!dir.mkdir(_path)){
                qDebug()<<"save0x01";
                return 0x01;
            }
        }
        QFile file(_path);
        if(!file.open(QFile::WriteOnly|QFile::Truncate)){
            qDebug()<<"save0x02";
            return 0x02;
        }

        QXmlStreamWriter xsw(&file);
        xsw.setAutoFormatting(true);
        xsw.writeStartDocument();
        _content->saveFile(xsw);
        file.close();
        return 0;

    }else if(_type==0x01){//保存成json
//        QString path = ".\\config\\templates.json";
//        QJsonArray jarr;
//        for(auto ot : _orderTemplates)
//        {
//            QJsonObject jo;
//            ot.writeToJson(jo);
//            jarr.append(jo);
//        }
//        QJsonObject temp;
//        temp["QuickStartOrder"] = _quickStartTemplate;
//        temp["Templates"] = jarr;
//        QJsonDocument jdoc(temp);
//        QFile file(path);
//        if(file.open(QIODevice::WriteOnly))
//        {
//            file.write(jdoc.toJson());
//            return true;
//        }
//        return false;

//        void SunnyTcsOrderTemplate::writeToJson(QJsonObject &json)
//        {
//            json[TEMPLATE_ID_ATTRIBUTE] = m_id;
//            json[ORDER_TYPE_ELEMENT] = m_orderType;
//            json[PRIORITY_ELEMENT] = m_priority;
//            json[TRANSPORT_MATERIAL_ELEMENT] = m_transportMaterial;
//            json[PEFER_VEHICLE_ELEMENT] = m_peferVehicle;
//            json[CYCLIC_ELEMENT] = m_isCyclic ? "YES" : "NO";
//            json[DELAY_SECONDS_ELEMENT] = static_cast<qint32>(m_delaySecs);
//            json[LTD_SECONDS_ELEMENT] = static_cast<qint32>(m_ltdSecondsToFinish);
//            json[QUICK_START_ELEMENT] = m_quickStartSupport ? "YES" : "NO";
//            QJsonArray jarr;
//            for(qint32 i = 0; i < m_throughPts.count(); ++i)
//            {
//                QJsonObject jo;
//                jo[PARK_POINT] = m_throughPts.at(i);
//                jo[PARK_LOCATION] = (i < m_throughLocations.count() ? m_throughLocations.at(i) : "N/A");
//                jarr.append(jo);
//            }
//            json[PARK_LOCATIONS] = jarr;
//        }

        QJsonObject jobj;
        qDebug()<<"111112421";
        if(_content)
            _content->writeToJson(&jobj);
        qDebug()<<"11222222421";
        QJsonDocument jdoc(jobj);
        QFile file(_path);
        if(!file.open(QFile::WriteOnly|QFile::Truncate))
        {
            qDebug()<<"???????";
            return 0x01;
        }
        file.write(jdoc.toJson());
        file.close();
        return 0;
    }
}


/*************************************************************
*解析xml文档的树形数据结构，以及标签属性值
*
**************************************************************/
qint8 SunnyTcsConfig::load()
{
    if(_type==0x00){//xml文件
        QFile file(_path);
        if(!file.open(QFile::ReadOnly|QFile::Text)){
            return 0x01;
        }
        QXmlStreamReader xsr(&file);
        _content=new SunnyTcsConfigItem();

        do{
            xsr.readNext();
        }while(!xsr.isStartElement());//获取到根节点
        _content->setName(xsr.name().toString());
        _content->setItemAttributes(new QXmlStreamAttributes(xsr.attributes()));//根节点属性集

        //-------------------------------
        QMap<QString,QString> map;
        for(qint32 i=0;i<xsr.attributes().count();++i){
            QString name=xsr.attributes().at(i).name().toString();
            map.insert(name,"");
        }
        _content->setAttributeRemarks(map);
        //-------------------------------

        //qDebug()<<"attr"+_content->getItemAttributes()->value("name").toString();
        do{
            xsr.readNext();
        }while(!xsr.isStartElement()&&!xsr.isEndElement());//获取下一点

        if(xsr.isEndElement()){
            return 0x00;//只有一个根节点
        }else if(xsr.isStartElement()){
            _content->loadItem(xsr,_content);
        }
        return 0x00;
        file.close();
    }else if(_type==0x01){//json文件
        QFile file(_path);
        if(!file.open(QFile::ReadOnly|QFile::Text)){
            return 0x01;
        }
        QJsonParseError jerror;
        QJsonDocument jdoc=QJsonDocument::fromJson(file.readAll(),&jerror);
        QJsonObject jObj=jdoc.object();
        _content =new SunnyTcsConfigItem(1);
        _content->setJsonName("JSON_OBJECT");
        _content->setJsonType(0);
        _content->setParent(nullptr);

        _content->loadItemByJson(_content,&jObj,nullptr);

        QList<qint32> index;

        _content->defineIndexForJson(index);


//        QJsonParseError je;
//        QJsonDocument jdoc=QJsonDocument::fromJson(file.readAll(),&je);
//        QJsonObject jobj=jdoc.object();//总对象

//        for(QString key:jobj.toVariantMap().keys()){//
//            qDebug()<<key;
//            qDebug()<<jobj.value(key).toString();
//            qDebug()<<jobj.value(key).toArray().count();//确定值的类型是不是数组
//        }
        return 0x00;

    }
}


/*************************************************************
*xml数据结构解析完成后才能调用该函数，对各标签内数据进行读取,确定索引
*
**************************************************************/
qint8 SunnyTcsConfig::readValue()
{
    if(_type==0x00){
        QFile file(_path);
        if(!file.open(QFile::ReadOnly|QFile::Text)){
            return 0x01;
        }
        QXmlStreamReader xsr(&file);

        QList<qint8> nodeIsEndList;
        QList<SunnyTcsConfigItem*> allNodeList;
        // qDebug()<<"---------------";

        if(_content->isEndPoint()){
            //map.insert(0,_content);
            nodeIsEndList.append(0);
            allNodeList.append(_content);
        }else{
            //map.insert(1,_content);
            nodeIsEndList.append(1);
            allNodeList.append(_content);
            _content->readItem(nodeIsEndList,allNodeList);
        }

        //确定每个标签的index
        for(SunnyTcsConfigItem* item:allNodeList){
            SunnyTcsConfigItem* ite=item;
            SunnyTcsConfigItem* parent=nullptr;
            QList<qint32>* itemIndexList=item->getIndexForDefine();
            itemIndexList->clear();
            QList<qint32> indexList;
            while(nullptr!=ite->getItemParent()){
                parent=ite->getItemParent();
                qint32 index=parent->getChildIndex(ite);
                indexList.append(index);
                ite=parent;
            }//ite最后是根节点
            for(qint32 i=indexList.count()-1;i>=0;--i){//反转一下就可以了
                itemIndexList->append(indexList.at(i));
            }
        }

        //读取标签值
        qint32 index=0;
        while(!xsr.atEnd()){
            xsr.readNext();
            if(xsr.isStartElement()){
                if(nodeIsEndList.at(index)==0){
                    //qDebug()<<allNodeList.at(index)->getName()+xsr.readElementText();
                    allNodeList.at(index)->setValue(xsr.readElementText());
                }else{
                    //qDebug()<<allNodeList.at(index)->getName()+"--";
                }
                ++index;
                //qDebug()<<xsr.name().toString()+"::"+xsr.readElementText();

            }
        }
        return 0x00;
    }else if(_type==0x01){//json文件只需要确定索引就行了

    }
}

/*************************************************************
*更具xml文件和xml_config文件重载数据树
*
**************************************************************/
qint8 SunnyTcsConfig::reload()
{
//    if(_content!=nullptr){
//        QMessageBox::information(0,"tip","_content error");
//        return 0x03;//数据树已存在，无需重载
//    }
    if(_type==0x00){
        int ret=this->load();
        if(ret!=0x00){
            QMessageBox::information(0,"tip","xml error");
            return 0x01;//xml文件问题
        }
        ret=this->readValue();
        if(ret!=0x00){
            QMessageBox::information(0,"tip","readValue error");
            return 0x01;
        }
        QFile xmlConfig(_configPath);
        if(!xmlConfig.open(QFile::ReadOnly|QFile::Text)){
            QMessageBox::information(0,"tip",_configPath);
            return 0x02;//xml_config文件问题
        }
        QXmlStreamReader xsr(&xmlConfig);
        if(!xsr.readNextStartElement() || xsr.name() != "root"){
            QMessageBox::information(0,"tip","root error");
            xmlConfig.close();
            return 0x03;
        }

        while(!xsr.atEnd() && !xsr.hasError() && xsr.readNext()){
            if(!xsr.isStartElement())
                continue;
            QString index;
            QString itemRemark;
            QString itemExplain;
            QMap<QString,QString> tempAttributes;
            if(xsr.name()!="item"){
                QMessageBox::information(0,"tip","item error");
                xmlConfig.close();
                return 0x04;
            }else{
                QXmlStreamAttributes att=xsr.attributes();
                if(!att.hasAttribute("index")||!att.hasAttribute("itemRemark")||!att.hasAttribute("itemExplain")){
                    QMessageBox::information(0,"tip","att error");
                    xmlConfig.close();
                    return 0x05;
                }
                index=xsr.attributes().value("index").toString();
                itemRemark=xsr.attributes().value("itemRemark").toString();
                itemExplain=xsr.attributes().value("itemExplain").toString();
                for(qint32 i=0;i<att.count();++i){
                    QString name=att.at(i).name().toString();
                    // qDebug()<<"----"+index+"------insert:"+name+"  "+att.value(name).toString();
                    if(name!="index"&&name!="itemRemark"&&name!="itemExplain"){
                        tempAttributes.insert(name,att.value(name).toString());
                    }
                }
            }

            SunnyTcsConfigItem *item=getChildByInfo(index);
            if(item==nullptr){
                //  qDebug()<<"null index"+index;
                xmlConfig.close();
                return 0x06;
            }
            //插入读取的数据
            item->setItemRemarks(itemRemark);
            item->setExplain(itemExplain);
            item->setAttributeRemarks(tempAttributes);
        }


        xmlConfig.close();
        return 0x00;
    }else if(_type==0x01){
        int ret=this->load();
        if(ret!=0x00){
            QMessageBox::information(0,"tip","xml error");
            return 0x01;//xml文件问题
        }

        QFile xmlConfig(_configPath);
        if(!xmlConfig.open(QFile::ReadOnly|QFile::Text)){
            QMessageBox::information(0,"tip",_configPath);
            return 0x02;//xml_config文件问题
        }
        QXmlStreamReader xsr(&xmlConfig);
        if(!xsr.readNextStartElement() || xsr.name() != "root"){
            QMessageBox::information(0,"tip","root error");
            xmlConfig.close();
            return 0x03;
        }

        while(!xsr.atEnd() && !xsr.hasError() && xsr.readNext()){
            if(!xsr.isStartElement())
                continue;
            QString index;
            QString itemRemark;
            QString itemExplain;
            QMap<QString,QString> tempAttributes;
            if(xsr.name()!="item"){
                QMessageBox::information(0,"tip","item error");
                xmlConfig.close();
                return 0x04;
            }else{
                QXmlStreamAttributes att=xsr.attributes();
                if(!att.hasAttribute("index")||!att.hasAttribute("itemRemark")||!att.hasAttribute("itemExplain")){
                    QMessageBox::information(0,"tip","att error");
                    xmlConfig.close();
                    return 0x05;
                }
                index=xsr.attributes().value("index").toString();
                itemRemark=xsr.attributes().value("itemRemark").toString();
                itemExplain=xsr.attributes().value("itemExplain").toString();
                for(qint32 i=0;i<att.count();++i){
                    QString name=att.at(i).name().toString();
                    // qDebug()<<"----"+index+"------insert:"+name+"  "+att.value(name).toString();
                    if(name!="index"&&name!="itemRemark"&&name!="itemExplain"){
                        tempAttributes.insert(name,att.value(name).toString());
                    }
                }
            }
            qDebug()<<"pi pei zhong";
            SunnyTcsConfigItem *item=getChildByInfo(index);
            if(item==nullptr){
                  qDebug()<<"null index"+index;
                xmlConfig.close();
                return 0x06;
            }
            //插入读取的数据
            item->setItemRemarks(itemRemark);
            item->setExplain(itemExplain);
            item->setAttributeRemarks(tempAttributes);
        }


        xmlConfig.close();
        return 0x00;
    }
}


/*************************************************************
*
*
**************************************************************/
SunnyTcsConfigItem *SunnyTcsConfig::getChild(QList<qint32> index)
{
    if(index.count()==1&&index.at(0)==-1)
        return _content;

    SunnyTcsConfigItem* current=_content;
    for(qint32 i:index){
        current = current->getChild(i);
        if(current==nullptr){
            break;
            qDebug()<<"cant find child,return nullptr";
            return nullptr;
        }
    }
    qDebug()<<"find children:"+ current->getJsonName();
    return current;
}


/*************************************************************
*
*
**************************************************************/
SunnyTcsConfigItem* SunnyTcsConfig::getChildByInfo(QString index)
{

    if(_content==nullptr){
        return nullptr;
    }
    if(index=="-1"){
        return _content;
    }

    index.remove(0,1);
    index.remove(index.count()-1,1);

    qint32 i;
    QList<qint32> ind;

    QStringList list=index.split(',');
    qDebug()<<list;
    for(QString in:list){
        i=in.toInt();
        ind.append(i);
    }
    return getChild(ind);
}







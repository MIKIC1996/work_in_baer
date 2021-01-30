#include "sunnytcsconfigitem.h"

/****************************************************
 *
 *
 *
 *
*****************************************************/
SunnyTcsConfigItem::SunnyTcsConfigItem(qint8 type,QObject *parent) : QObject(parent),m_children()
{
    this->_type=type;
}


/****************************************************
 *
 *
 *
 *
*****************************************************/
qint8 SunnyTcsConfigItem::loadItem(QXmlStreamReader &xsr, SunnyTcsConfigItem *current)
{
    if(_type==0){
        do{
            SunnyTcsConfigItem *item=new SunnyTcsConfigItem();
            item->setName(xsr.name().toString());
            item->setItemParent(current);
            current->addChild(item);
            //qDebug()<<"?"+item->getName();
            item->setItemAttributes(new QXmlStreamAttributes(xsr.attributes()));
            //-------------------------------
            QMap<QString,QString> map;
            for(qint32 i=0;i<xsr.attributes().count();++i){
                QString name=xsr.attributes().at(i).name().toString();
                map.insert(name,"");
            }
            item->setAttributeRemarks(map);
            //-------------------------------
           // qDebug()<<"attribute count:"+QString::number(xsr.attributes().count());
            do{//读取下一个节点
                xsr.readNext();
            }while(!xsr.isStartElement()&&!xsr.isEndElement());
            if(xsr.isEndElement()&&xsr.name().toString()==item->getName()){//item子节点结束
              //  qDebug()<<"/"+item->getName();
                do{//再读取下一个节点
                    xsr.readNext();
                }while(!xsr.isStartElement()&&!xsr.isEndElement());
                if(xsr.isEndElement()&&xsr.name().toString()==current->getName()){//下一个节点还是end节点
              //      qDebug()<<"//loadEnd"+xsr.name().toString();
                    return 0x03;
                }
                else{
               //     qDebug()<<"new--------";
                    continue;
                }
            }else if(xsr.isStartElement()){
             //   qDebug()<<"loadd";
                loadItem(xsr,item);
                do{
                    xsr.readNext();
                }while(!xsr.isStartElement()&&!xsr.isEndElement());//打到下一个节点
                if(xsr.isEndElement()&&xsr.name().toString()==current->getName()){
             //       qDebug()<<"//loadEnd"+xsr.name().toString();
                    return 0x03;
                }
            }
        }while(1);
    }else if(_type==1){

    }
}


/****************************************************
 *
 *
 *
 *
*****************************************************/
qint8 SunnyTcsConfigItem::readItem(QList<qint8>& list1,QList<SunnyTcsConfigItem*>& list2)
{
    for(SunnyTcsConfigItem* ite:this->m_children){
        if(ite->isEndPoint()){
            //map.insert(0,ite);
            list1.append(0);
            list2.append(ite);
            qDebug()<<ite->getName()+"is end point";
        }else{
            //map.insert(1,ite);
            //qDebug()<<1;
            list1.append(1);
            list2.append(ite);
            ite->readItem(list1,list2);
        }
    }
    return 0;
}


/****************************************************
 *
 *
 *
 *
*****************************************************/
qint8 SunnyTcsConfigItem::loadItemByJson(SunnyTcsConfigItem* current,QJsonObject* jObj,QJsonArray* jArr)
{
    qint8 jsonType=(current->getJsonType()+1)%2;
    if(jsonType==1){
        for(QString key:jObj->toVariantMap().keys()){//父母是0 json对象，他是1 json值
            SunnyTcsConfigItem* child=new SunnyTcsConfigItem(1);//设置ItemType
            child->setJsonType(jsonType);
            child->setJsonName(key);
            current->addChild(child);
            child->setItemParent(current);
            if(jObj->value(key).toArray().count()==0){

                child->setValue(jObj->value(key).toVariant().toString());
            }else{
                QJsonArray jarray=jObj->value(key).toArray();
                child->loadItemByJson(child,nullptr,&jarray);
            }
        }
    }else if(jsonType==0){
        for(auto ja:*jArr){
            QJsonObject jobject =ja.toObject();
            SunnyTcsConfigItem * child=new SunnyTcsConfigItem(1);
            child->setJsonType(jsonType);
            child->setJsonName(current->getJsonName()+" child_object");
            current->addChild(child);
            child->setItemParent(current);
            child->loadItemByJson(child,&jobject,nullptr);
        }
    }
    return 0;

}

/****************************************************
 *
 *
 *
 *
*****************************************************/
qint8 SunnyTcsConfigItem::writeToJson(QJsonObject *jobj, QJsonArray *jarr,QList<QJsonObject*>* jobjList,QList<QJsonArray*>* jarrList)//初次使用（jobj,nullptr）
{
    if(_jsonObjectType==0)//一个json 对象
    {
        qDebug()<<"_jsonObjectType 0";
        //第一次进来jarr不存在
        if(!jarr){//访问子值,只有在第一次访问总对象时不会有jarr,其后的对象必定属于某个值的数组
            QList<QJsonObject*>* joList=new QList<QJsonObject*>();
            QList<QJsonArray*>* jaList=new QList<QJsonArray*>();
            qDebug()<<"all object";
            for(SunnyTcsConfigItem* item:m_children){
                item->writeToJson(jobj,nullptr,joList,jaList);
            }
            for(qint32 m=0;m<joList->count();++m){
                delete joList->at(m);
            }
            for(qint32 n=0;n<jaList->count();++n){
                delete jaList->at(n);
            }

            return 0x00;
        }
        if(jarr){//存在，先加入上层数组
            qDebug()<<"child object";
            QJsonObject* jo=new QJsonObject();//先创建总对象
            jobjList->append(jo);
            for(SunnyTcsConfigItem* item:m_children){
                item->writeToJson(jo,nullptr,jobjList,jarrList);
            }
            jarr->append(*jo);
            return 0x00;
        }
    }else{//子值是一个json值 （jobj,nullptr）
        qDebug()<<"_jsonObjectType 1";
        if(isEndPoint()){//他存的是一个值
            qDebug()<<"value node";
            if(_valueType==0){//文本
                jobj->insert(_jsonName,m_value);
                qDebug()<<_jsonName+"||"+m_value;
                //QJsonValue::fromVariant()
                return 0;
            }
            if(_valueType==1){
                //jobj[_jsonName]=m_value.toInt();//xieru jobj
                jobj->insert(_jsonName,m_value.toInt());
                qDebug()<<_jsonName+"||"+m_value;
                return 0;
            }
        }else{//他存的是一个json对象数组
            qDebug()<<"value swit";

            //QJsonArray *ja=new QJsonArray();
            QJsonArray *ja=new QJsonArray();
            jarrList->append(ja);
            for(SunnyTcsConfigItem* item:m_children){
                item->writeToJson(nullptr,ja,jobjList,jarrList);
            }
//            for(qint32 i=0;i<ja->count();++i)
//                qDebug()<<ja->at(i).toString();
//            }
            jobj->insert(_jsonName,*ja);
            qDebug()<<"存数组了"+_jsonName+QString::number(ja->count());
            return 0;
        }
    }
}



/****************************************************
 *
 *
 *
 *
*****************************************************/
qint8 SunnyTcsConfigItem::deleteAllChild()
{
    if(m_children.count()==0){
        return 0x00;
    }else{
        for(SunnyTcsConfigItem* child:m_children){
            if(child->isEndPoint()){
                delete child;
                return 0x01;
            }else{
                int ret=child->deleteAllChild();
                delete child;
                return 0x01;
            }

        }
    }
}


/****************************************************
 *
 *
 *
 *
*****************************************************/
void SunnyTcsConfigItem::save(QXmlStreamWriter &xsw)
{
    //先写入自身
    xsw.writeStartElement("item");
    QString index=(m_parent==nullptr?"-1":this->getIndexInfo());
    qDebug()<<"save index "+index;
    qDebug()<<(m_parent==nullptr);
    xsw.writeAttribute("index",index);
    for(QString key:_attributeRemark.keys()){
        xsw.writeAttribute(key,_attributeRemark.value(key));
    }
    xsw.writeAttribute("itemRemark",_itemRemarks);
    xsw.writeAttribute("itemExplain",_explain);
    xsw.writeEndElement();

    //写入子类
    if(this->isEndPoint()){
        return;
    }else{
        for(SunnyTcsConfigItem* child:m_children){
            child->save(xsw);
        }
        return;
    }
}

/****************************************************
 *
 *
 *
 *
*****************************************************/
qint8 SunnyTcsConfigItem::saveFile(QXmlStreamWriter &xsw)
{
    if(_type==0x00){
        if(isEndPoint()){
            xsw.writeTextElement(m_name,m_value);
            for(QString key:_attributeValue.keys()){
                xsw.writeAttribute(key,_attributeValue.value(key));
            }
        }else{
            xsw.writeStartElement(m_name);
            for(QString key:_attributeValue.keys()){
                xsw.writeAttribute(key,_attributeValue.value(key));
            }
            for(qint32 i=0;i<m_children.count();++i){
                m_children.at(i)->saveFile(xsw);
            }
            xsw.writeEndElement();
        }
        return 0;
    }else if(_type=0x01){
        return 0x01;
    }
    return 0x01;

}


/****************************************************
 *
 *
 *
 *
*****************************************************/
qint8 SunnyTcsConfigItem::reLoadItem(QMap<QString, Rmap> &map)
{
//    QString index;
//    QString remark;
//    QString explain;
//    if(!this->getName()=="root"){
//        if(!_attributes->hasAttribute("index")||!_attributes->hasAttribute("itemRemark")||!_attributes->hasAttribute("itemExplain")){
//            return 0x01;
//        }
//    }

//    if(this->isEndPoint()){
//    }else{
//    }
    return 0;

}

void SunnyTcsConfigItem::defineIndexForJson(QList<qint32> index)
{
    for(qint32 i=0;i<m_children.count();++i){
        SunnyTcsConfigItem* item=m_children.at(i);
        QList<qint32> temp=index;
        temp.append(i);
        if(item->isEndPoint()){
            item->setIndex(temp);
        }else{
            item->setIndex(temp);
            item->defineIndexForJson(temp);
        }
    }
}




/****************************************************
 *
 *
 *
 *
*****************************************************/
QString SunnyTcsConfigItem::getIndexInfo() const
{
    if(m_parent==nullptr)
        return "(-1)";

    QString in("(");
    for(qint32 i:m_index){
        in+=(QString::number(i)+",");
    }
    in.remove(in.count()-1,1);
    in+=")";
    return in;
}

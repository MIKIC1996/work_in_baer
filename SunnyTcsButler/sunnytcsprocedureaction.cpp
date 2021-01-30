#include "sunnytcsprocedureaction.h"


//-------------------------------------------------------------------
SunnyTcsProcedureAction::SunnyTcsProcedureAction(QObject *parent) : QObject(parent)
{

}
//-------------------------------------------------------------------
SunnyTcsProcedureAction::SunnyTcsProcedureAction(SunnyTcsProcedureAction::PROCEDURE_ACTION_TYPE type, qint32 exeCount, QString name, QString explain)
{
    _type=type;
    _exeCount=exeCount;
    _name=name;
    _explain=explain;
}
//-------------------------------------------------------------------
SunnyTcsProcedureAction::SunnyTcsProcedureAction(qint32 type, qint32 exeCount, QString name, QString explain)
{
    setActionTypeByInt(type);
    _exeCount=exeCount;
    _name=name;
    _explain=explain;
}


//-------------------------------------------------------------------
qint8 SunnyTcsProcedureAction::updateTarget(QMap<QString, QList<QString> > *map)
{
    for(QString key:map->keys()){
        QList<QString> listPtr=/*const_cast<QList<QString>*>*/(map->value(key));
        _targetMap.insert(key,listPtr);
    }
    return 0;
}


//-------------------------------------------------------------------
qint8 SunnyTcsProcedureAction::addTarget(QString filePath, QList<QString> indexs)
{
    return 0;
}


//-------------------------------------------------------------------
qint8 SunnyTcsProcedureAction::addTarget(const QMap<QString, QList<QString>> *map)
{
    for(QString key:map->keys()){
        QList<QString> listPtr=/*const_cast<QList<QString>*>*/(map->value(key));
        _targetMap.insert(key,listPtr);
        for(QString index:listPtr){
            qDebug()<<index;
        }

    }
    return 0;
}

//-------------------------------------------------------------------
qint8 SunnyTcsProcedureAction::execAction()
{
    return 0;
}


//-------------------------------------------------------------------
qint8 SunnyTcsProcedureAction::saveAction(QXmlStreamWriter &xsw)
{
    xsw.writeStartElement("action");
    xsw.writeAttribute("actionName",_name);
    xsw.writeAttribute("actionExplain",_explain);
    xsw.writeAttribute("actionType",QString::number(_type));
    xsw.writeAttribute("actionCount",QString::number(_exeCount));
    xsw.writeAttribute("actionValueType",QString::number(_valueType));

//    QString _xmlName="";
    xsw.writeAttribute("addXmlName",_xmlName);
//    QStringList _xmlAttributes;
    QString atts;
    for(QString att:_xmlAttributes){
        atts+=(att+"|");
    }
    atts.remove(atts.count()-1,1);
    xsw.writeAttribute("addXmlAttributes",atts);

//    //添加Json
//    qint8 _JsonAddType=0; //0是添加对象 1是添加单个值
    xsw.writeAttribute("addJsonType",QString::number(_JsonAddType));
//    QStringList _JsonValueList;//添加对象 他的值列表 ；添加单个值，则只需要加一个
    QString values;
    for(QString value:_JsonValueList){
        values+=(value+"|");
    }
    values.remove(values.count()-1,1);
    xsw.writeAttribute("addJsonValueList",values);

    //    QList<qint8> _JsonValueTypeList;//添加值的类型，与上个list对应
    QString types;
    for(qint8 type:_JsonValueTypeList){
        types+=(QString::number(type)+"|");
    }
    types.remove(values.count()-1,1);
    xsw.writeAttribute("addJsonValueTypeList",types);




    for(QString key:_targetMap.keys()){
        xsw.writeStartElement("target");
        xsw.writeAttribute("path",key);
        for(QString index:_targetMap.value(key)){
            xsw.writeTextElement("index",index);
        }
        xsw.writeEndElement();
    }
    xsw.writeEndElement();
    return 0;
}



//-------------------------------------------------------------------
SunnyTcsProcedure::SunnyTcsProcedure(QObject *parent) :QObject(parent)
{

}


//-------------------------------------------------------------------
SunnyTcsProcedure::~SunnyTcsProcedure()
{
    releaseActionList();
}

//-------------------------------------------------------------------
qint8 SunnyTcsProcedure::releaseActionList()
{
    for(SunnyTcsProcedureAction* ac :_actionList){
        if(ac)
            delete ac;
    }
    return 0x00;
}

//-------------------------------------------------------------------
qint8 SunnyTcsProcedure::saveProcedure(QXmlStreamWriter& xsw)
{
    xsw.writeStartElement("procedure");
    xsw.writeAttribute("name",_name);
    xsw.writeAttribute("explain",_explain);
    for(SunnyTcsProcedureAction* ac:_actionList){
        ac->saveAction(xsw);
    }
    xsw.writeEndElement();
    return 0;
}

//-------------------------------------------------------------------
qint8 SunnyTcsProcedure::addAction(SunnyTcsProcedureAction *action)
{
    _actionList.append(action);
    return 0;
}

//-------------------------------------------------------------------
qint8 SunnyTcsProcedure::deleteAction(qint32 index)
{
    if(index<0||index>=_actionList.count()){
        return 0x01;
    }
    _actionList.removeAt(index);
    return 0;
}

//-------------------------------------------------------------------
QList<QString> SunnyTcsProcedure::getAllRealitiveFile()
{
    QList<QString> fileList;
    for(SunnyTcsProcedureAction* ac:_actionList){
        for(QString key :ac->getFileList()){
            if(!fileList.contains(key)){
                fileList.append(key);
            }
        }
    }
    return fileList;
}

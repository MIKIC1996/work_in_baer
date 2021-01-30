#ifndef SUNNYTCSPROCEDUREACTION_H
#define SUNNYTCSPROCEDUREACTION_H

#include <QObject>
#include <QMap>
#include "sunnytcsconfig.h"
#include <QXmlStreamReader>
#include <QXmlStreamWriter>

class SunnyTcsProcedureAction : public QObject
{
    Q_OBJECT
public:
    enum PROCEDURE_ACTION_TYPE{
        MODIFY_TYPE=0X00,//修改值类型只允许修改标签的值和 json对象下 某个值，不允许选择具有子标签的xml标签，以及不允许直接选择json对象
        ADD_XML_TYPE=0X01,//添加XML标签操作 ,选中某些个父标签，在这些标签下添加子标签，需要预先设定好 ：标签名 属性和值的name
        DELETE_XML_TYPE=0X02,//删除xml标签操作 ,选中某些个父标签，删除父标签下的某些标签 ，允许添加筛选条件 （标签名 属性）  包含 （值）
        ATTRIBUTE_MODIFY_TYPE=0X03,//属性修改类型，只对xml文件有效，且所选标签必须具有相同的属性列表
        Add_JSON_TYPE=0x04,//添加json对象或者值
        DELETE_JSON_TYPE=0X05//删除json对象或值
    };
    explicit SunnyTcsProcedureAction(QObject *parent = 0);
    SunnyTcsProcedureAction(PROCEDURE_ACTION_TYPE type,qint32 exeCount,QString name,QString explain);
    SunnyTcsProcedureAction(qint32 type,qint32 exeCount,QString name,QString explain);
    inline QString getActionName()const{return _name;}
    inline void setActionName(QString name){_name=name;}

    inline QString getActionExplain()const{return _explain;}
    inline void setActionExplain(QString explain){_explain=explain;}

    inline PROCEDURE_ACTION_TYPE getActionType()const{return _type;}
    inline void setActionType(PROCEDURE_ACTION_TYPE type){_type=type;}
    inline void setActionTypeByInt(qint32 type){
        switch(type){
        case 0x00:
            _type=MODIFY_TYPE;
            break;
        case 0x01:
            _type=ADD_XML_TYPE;
            break;
        case 0x02:
            _type=DELETE_XML_TYPE;
            break;
        case 0x03:
            _type=ATTRIBUTE_MODIFY_TYPE;
            break;
        case 0x04:
            _type=Add_JSON_TYPE;
            break;
        case 0X05:
            _type=DELETE_JSON_TYPE;
            break;

        }
    }
    inline qint32 getExeCount()const{return _exeCount;}
    inline void setExeCount(qint32 count){_exeCount=count;}

    qint8 updateTarget(QMap<QString,QList<QString>>* tar);//不用
    qint8 addTarget(QString filePath,QList<QString> indexs);
    qint8 addTarget(const QMap<QString,QList<QString>>* map);

    qint8 execAction();//执行该动作
    qint8 exeModifyAction(QMap<QString,SunnyTcsConfig*> configMap);
    qint8 exeAddXmlAction(QMap<QString,SunnyTcsConfig*> configMap);
    qint8 exedeleteXmlAction(QMap<QString,SunnyTcsConfig*> configMap);
    qint8 exeAttributesModifyAction(QMap<QString,SunnyTcsConfig*> configMap);
    qint8 addJsonAction(QMap<QString,SunnyTcsConfig*> configMap);
    qint8 deleteJsonAction(QMap<QString,SunnyTcsConfig*> configMap);

    qint8 saveAction(QXmlStreamWriter& xsw);

    QList<QString> getIndexsByPath(QString path){return _targetMap.value(path);}
    QMap<QString,QList<QString>> getTargetMap()const{return _targetMap;}
    inline QList<QString> getFileList(){return _targetMap.keys();}

    inline qint8 getValueType()const {return _valueType;}
    inline void setValueType(qint8 valueType){_valueType=valueType;}

    inline QString getXmlName()const{return _xmlName;}
    inline QStringList getXmlAttributes()const{return _xmlAttributes;}
    inline qint8 getJsonAddType()const{return _JsonAddType;}
    inline QStringList getJsonValueList()const{return _JsonValueList;}
    inline QList<qint8> getJsonAddValueList()const{return _JsonValueTypeList;}

    inline void setXmlName(QString xmlName){_xmlName=xmlName;}
    inline void setXmlAttributes(QStringList att){_xmlAttributes=att;}
    inline void setJsonAddType(qint8 add){_JsonAddType=add;}
    inline void setJsonValueList(QStringList list){_JsonValueList=list;}
    inline void setJsonValueTypes(QList<qint8> list){_JsonValueTypeList=list;}

signals:

public slots:

protected:
    PROCEDURE_ACTION_TYPE _type=MODIFY_TYPE;
    qint32 _exeCount=1;//执行次数
    QMap<QString,QList<QString>> _targetMap;//map<path,index> 目标文件夹的目标标签，如果以索引来定位，删除后索引变更呢？
                                                        //可以执行操作期间不更新索引，执行添加操作往后面加，索引按照最后一个索引目前记录索引来添加，
                                                        //执行流程之前对所有涉及文件的文件结构进行检查，确保索引的正确性；
                                                        //索引以QString记录，可以对应多条
    QList<SunnyTcsConfig*> targetPtrs;//对目标进行修改的指针
    QString _name="unnamed_Action";
    QString _explain="none explain";
    qint8 _valueType=0;//0 文本 1整型数

    //添加xml
    QString _xmlName="";
    QStringList _xmlAttributes;

    //添加Json
    qint8 _JsonAddType=0; //0是添加对象 1是添加单个值
    QStringList _JsonValueList;//添加对象 他的值列表 ；添加单个值，则只需要加一个
    QList<qint8> _JsonValueTypeList;//添加值的类型，与上个list对应

};



/*流程总配置文件+++++++++++++++++++++++++++++++++++++++++++++
的记录格式
流程设置完成后要保存2份文件 总流程配置文件 和 原文件拷贝（用来格式检查）

<root>
    <procedure name="名字" explain="说明" procedurePath="配置文件路径" > </procedure>
    <procedure name="名字" explain="说明" procedurePath="配置文件路径" > </procedure>
</root>

单个流程的记录格式
<root>

    <action type="" exeCount="" paths="目标文件路径集" indexs="目标索引集，与目标文件路径集匹配" value="值的修改”>
    </action>
    <action>
    </action>
    <action>
    </action>
    ……
</root>
+++++++++++++++++++++++++++++++++++++++++++++++++++++++*/
class SunnyTcsProcedure : public QObject{
    Q_OBJECT
public:
    explicit SunnyTcsProcedure(QObject* parent=0);
    ~SunnyTcsProcedure();
    inline QString getProcedureName()const{return _name;}
    inline void setProcedureName(QString name){this->_name=name;}
    inline QString getProcedureExplain()const{return _explain;}
    inline void setProcedureExplain(QString explain){this->_explain=explain;}

    QList<SunnyTcsProcedureAction*>* getActionList(){return &_actionList;}
    qint8 releaseActionList();
    qint8 saveProcedure(QXmlStreamWriter& xsw);

    qint8 addAction(SunnyTcsProcedureAction* action);
    qint8 deleteAction(qint32 index);
    qint32 getActionCount(){return _actionList.count();}
    SunnyTcsProcedureAction* getAction(int index){
        if(index<0||index>=_actionList.count())
            return nullptr;
        else
            return _actionList.at(index);}

    qint32 indexOfAction(SunnyTcsProcedureAction* action){return _actionList.indexOf(action);}
    QList<QString> getAllRealitiveFile();

private:
    QList<SunnyTcsProcedureAction*> _actionList;
    QString _name="Unnamed_procedure";
    QString _explain="no explain";



};

#endif // SUNNYTCSPROCEDUREACTION_H

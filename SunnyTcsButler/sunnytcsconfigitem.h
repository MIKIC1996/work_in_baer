#ifndef SUNNYTCSCONFIGITEM_H
#define SUNNYTCSCONFIGITEM_H

#include <QObject>
#include <QList>
#include <QXmlStreamReader>
#include <QDebug>
#include <QMultiMap>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

typedef struct Reload_map{
    QString itemRemarks;
    QString itemExplain;
}Rmap;

//一个item 一个标签
class SunnyTcsConfigItem : public QObject
{
    Q_OBJECT
public:
    explicit SunnyTcsConfigItem(qint8 type=0,QObject *parent = 0);

    qint8 loadItem(QXmlStreamReader& xsr,SunnyTcsConfigItem* current);
    qint8 readItem(QList<qint8>& list1,QList<SunnyTcsConfigItem*>& list2);

    qint8 loadItemByJson(SunnyTcsConfigItem* current,QJsonObject* jObj=nullptr,QJsonArray* jArr=nullptr);
    qint8 writeToJson(QJsonObject* jobj=nullptr,QJsonArray* jarr=nullptr,QList<QJsonObject*>* jobjList=nullptr,QList<QJsonArray*>* jarrList=nullptr);
    void addChild(SunnyTcsConfigItem* item){m_children.append(item);}
    qint8 deleteAllChild();
    void deleteSelf();
    void save(QXmlStreamWriter& xsw);
    qint8 saveFile(QXmlStreamWriter& xsw);
    qint8 reLoadItem(QMap<QString,Rmap>& map);

    inline qint8 getType()const{return _type;}

    QList<qint32>* getIndexForDefine(){return &m_index;}

    void defineIndexForJson(QList<qint32> index);
    void setIndex(QList<qint32> index){m_index=index;}
    qint32 getChildIndex(SunnyTcsConfigItem* child){return m_children.indexOf(child);}

    inline qint8 getValueType()const{return _valueType;}
    inline void setValueType(qint8 type){_valueType=type;}

    inline QString getJsonName(){return _jsonName;}
    inline void setJsonName(QString name){_jsonName=name;}

    inline void setJsonType(qint8 type){_jsonObjectType=type;}
    inline qint8 getJsonType()const{return _jsonObjectType;}

    inline QMap<QString,QString>* getAttributeRemarks(){return &_attributeRemark;}
    inline void setAttributeRemarks(QMap<QString,QString> map){_attributeRemark=map;}
    inline void appendAttributeRemarks(QString name,QString remarks){_attributeRemark.insert(name,remarks);}

    inline QString getItemRemarks()const{return _itemRemarks;}
    inline void setItemRemarks(QString remark){_itemRemarks=remark;}

    inline QString getExplain()const{return _explain;}
    inline void setExplain(QString explain){_explain=explain;}

    inline SunnyTcsConfigItem* getChild(qint32 index){
        if(index<0||index>=m_children.count())
            return nullptr;
        return m_children.at(index);
    }
    inline qint32 childCount(){return m_children.count();}
    inline QList<SunnyTcsConfigItem*>* getChildren(){return &m_children;}

    inline SunnyTcsConfigItem* getItemParent()const {return m_parent;}
    inline void setItemParent(SunnyTcsConfigItem* itemParent){m_parent=itemParent;}

    inline QString getName()const{return m_name;}
    inline void setName(QString name){m_name=name;}

    inline QString getValue()const{return m_value;}
    inline void setValue(QString value){m_value=value;}

    inline QList<qint32> getIndex()const{return m_index;}
    QString getIndexInfo()const;

    inline void setItemAttributes(QXmlStreamAttributes* attribute){_attributes=attribute;}
    inline QXmlStreamAttributes* getItemAttributes(){return _attributes;}

    inline bool isEndPoint()const{return m_children.isEmpty();}//是否是结束点

signals:

public slots:

private:
    //公用
    SunnyTcsConfigItem* m_parent=nullptr;
    QList<SunnyTcsConfigItem*> m_children;//子对象
    QString m_value="";
    QList<qint32> m_index;
    qint8 _type=0;//0 xml 1 json
    qint8 _valueType=0;//0 是文本 1是数字 2是bool
    QString _itemRemarks="";//标签备注
    QString _explain="";//该标签的解释与备注

    //json专属
    qint8 _jsonObjectType=0;//0 是指一个json对象，1是一个json值,但是统一用一个item来表示
    QString _jsonName="";

    //xml专属
    QString m_name;//xml标签名，json对象不一定有名字
    QXmlStreamAttributes *_attributes;//属性列表
    QMap<QString,QString> _attributeValue;//属性的键值对map
    QMap<QString,QString> _attributeRemark;//属性备注map
};

#endif // SUNNYTCSCONFIGITEM_H

#ifndef SUNNYTCSCONFIG_H
#define SUNNYTCSCONFIG_H

#include <QObject>
#include <QFile>
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QList>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <sunnytcsconfigitem.h>
#include <QMultiMap>
#include <QDateTime>

#define XML_TYPE 0x00
#define JSON_TYPE 0x01

class SunnyTcsConfig:public QObject
{
    Q_OBJECT
public:
    SunnyTcsConfig(QString path,QObject* parent =0);

    inline QString getName()const{return _name;}
    inline QString getPath()const{return _path;}
    inline qint8 getType()const{return _type;}
    inline SunnyTcsConfigItem* getContent()const{return _content;}

    inline void setFileRemarks(QString remarks){_fileRemarks=remarks;}
    inline QString getFileRemarks()const{return _fileRemarks;}
    inline QString getConfigPath()const{return _configPath;}
    inline void setConfigPath(QString path){_configPath=path;}

    inline QString getFileExplain()const{return _explain;}
    inline void setFileExplain(QString explain){_explain=explain;}

    inline void setName(QString name){_name=name;}
    inline void setPath(QString path){_path=path;}
    inline void setContent(SunnyTcsConfigItem* content){_content=content;}
    inline void setType(qint8 type){_type= type;}

    void releaseSelf();//释放数据树
    qint8 saveConfig();
    qint8 saveFile();
    qint8 load();//加载xml文件结构与属性集
    qint8 readValue();//读取xml文件标签内内容
    qint8 reload();//根据xml 和 配置文件两个文件 来恢复全部数据结构

    SunnyTcsConfigItem* getChild(QList<qint32> index);
    SunnyTcsConfigItem* getChildByInfo(QString index);

private:
    QString _path="";//读取文件路径
    QString _configPath="";//配置文件路径
    QString _name="";
    qint8 _type=0x00;//0 xml 1 json
    SunnyTcsConfigItem *_content=nullptr;

    QString _fileRemarks="";//文件备注名
    QString _explain="";//该文件的解释备注


};

#endif // SUNNYTCSCONFIG_H

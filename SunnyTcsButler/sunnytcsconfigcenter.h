#ifndef SUNNYTCSCONFIGCENTER_H
#define SUNNYTCSCONFIGCENTER_H

#include <QObject>
#include "sunnytcsconfig.h"
#include "sunnytcsconfigitem.h"
#include <QXmlStreamReader>
#include <QXmlStreamWriter>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QFile>
#include <QMap>
#include "sunnytcsprocedureaction.h"

//用来读取总配置文件（记录xml(json)文件的配置文件名与路径）
class SunnyTcsConfigCenter : public QObject
{
    Q_OBJECT
public:
    explicit SunnyTcsConfigCenter(QString path,QString procedurePath,QObject *parent = 0);
    ~SunnyTcsConfigCenter();
    qint8 readConfig();
    qint8 saveConfig();
    SunnyTcsConfig* reLoadConfig(QString path);
    qint8 addConfig(SunnyTcsConfig* con);
    bool pathCheck(QString path){return !_configMap.keys().contains(path);}//导入新xml时检查是否存在了

    inline const QMap<QString,SunnyTcsConfig*>* getConfigMap()const{return &_configMap;}
    inline const QMap<QString,SunnyTcsProcedure*>* getProcedureMap()const{return &_procedureMap;}

    inline QString getPath()const{return _path;}
    inline void setPath(QString path){_path=path;}
    inline QString getProcedurePath()const{return _procedurePath;}
    inline void setProcedurePath(QString path){_procedurePath=path;}

    inline qint8 addProcedure(SunnyTcsProcedure* pro){
        _procedureMap.insert(pro->getProcedureName(),pro);
        return 0x00;
    }
    inline qint8 removeProcedure(QString name){return _procedureMap.remove(name);}
    inline SunnyTcsProcedure* getProcedure(QString name){return _procedureMap.value(name);}
    SunnyTcsProcedure *createNewProcedure();
    inline void setTempProcedure(SunnyTcsProcedure* pro){_tempProcedure=pro;}

signals:
    void configPathMap_changed();
    void procedureMap_changed();

public slots:
    void on_configDig_setOK(SunnyTcsConfig* con);//配置文件界面完成，更新_configPathMap
    void on_procedureSave();
    void on_procedureClose();

private:
    QString _path;//原配置文件路径
    QString _procedurePath;//流程配置文件的路径
   // QMap<QString,QString> _configPathMap;//配置集 <文件路径 文件对象>
    QMap<QString,SunnyTcsConfig*> _configMap;
    SunnyTcsProcedure* _tempProcedure=nullptr;//临时编辑的流程
    //流程集 <流程名 流程对象>
    QMap<QString,SunnyTcsProcedure*> _procedureMap;

};

#endif // SUNNYTCSCONFIGCENTER_H

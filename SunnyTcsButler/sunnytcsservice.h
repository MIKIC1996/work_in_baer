#ifndef SUNNYTCSSERVICE_H
#define SUNNYTCSSERVICE_H

#include <QObject>
#include <QThread>
#include <windows.h>
#include <atlstr.h>
#include <strsafe.h>
#include <crtdbg.h>
#include <QDebug>
#include <QDateTime>


#define MODE_START 0X00
#define MODE_RESTART 0x01
#define MODE_CLOSE 0x02

#define NO_THIS_SERVICE 0X00//无该项服务
#define CANT_OPEN_MANAGER 0x01//无法打开服务管理器
#define QUERY_SERVICESTATUS_ERROR 0x02//服务状态获取错误
#define SERVICE_ALREADY_RUNNING 0x03//服务已经在运行或开启中
#define START_SERVICE_ERROR 0x04//服务启动失败
#define SERVICE_NO_ERROR 0x05//成功
#define SERVICE_OUTOF_TIME 0x06//超时
#define SERVICE_ALREADY_STOP 0x07//服务已经关闭或关闭中
#define STOP_SERVICE_ERROR 0x08//关闭服务失败

class SunnyTcsService:public QThread
{
    Q_OBJECT
public:
    SunnyTcsService(QObject* parent=0);
    inline qint8 getMode()const{return m_mode;}
    inline void setMode(qint8 mode){this->m_mode=mode;}
    inline QString getName()const{return m_name;}
    inline void setName(QString name){this->m_name=name;}

protected:
    void run();

    int startService(const char* name);
    int restartService(const char* name);
    int closeService(const char* name);

    void dealReturn(int ret);

    int startAll();
    int closeAll();
signals:
    void retSignal(int ret);
private:
    qint8 m_mode=MODE_START;
    QString m_name="";

};

#endif // SUNNYTCSSERVICE_H

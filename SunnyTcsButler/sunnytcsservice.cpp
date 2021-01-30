#include "sunnytcsservice.h"


/**************************************************
*
*
*
***************************************************/
SunnyTcsService::SunnyTcsService(QObject* parent):QThread(parent)
{

}


/**************************************************
*
*
*
***************************************************/
int SunnyTcsService::startService(const char *name)
{
    // 打开服务管理对象
    SC_HANDLE hSC = ::OpenSCManager( NULL,
        NULL, GENERIC_EXECUTE);
    if( hSC == NULL)
    {
        return CANT_OPEN_MANAGER;
    }
    // 打开服务
    char* nameData=const_cast<char*>(name);
    CString str = CString(nameData);
    USES_CONVERSION;
    LPCWSTR wszClassName = new WCHAR[str.GetLength()+1];
    wcscpy((LPTSTR)wszClassName,T2W((LPTSTR)str.GetBuffer(NULL)));
    str.ReleaseBuffer();

    SC_HANDLE hSvc = ::OpenService( hSC,wszClassName,
        SERVICE_START | SERVICE_QUERY_STATUS | SERVICE_STOP);
    if( hSvc == NULL)
    {
        ::CloseServiceHandle( hSC);
        return NO_THIS_SERVICE;
    }
    // 获得服务的状态
    SERVICE_STATUS status;
    if( ::QueryServiceStatus( hSvc, &status) == FALSE)
    {
        ::CloseServiceHandle( hSvc);
        ::CloseServiceHandle( hSC);
        return QUERY_SERVICESTATUS_ERROR;
    }
    qDebug()<<status.dwCurrentState;
    //如果处于运行或启动状态则返回
    if( status.dwCurrentState == SERVICE_RUNNING||status.dwCurrentState==SERVICE_START_PENDING)
    {

        ::CloseServiceHandle( hSvc);
        ::CloseServiceHandle( hSC);
        return SERVICE_ALREADY_RUNNING;
        // 停止服务
//        if( ::ControlService( hSvc,
//            SERVICE_CONTROL_STOP, &status) == FALSE)
//        {
//            ::CloseServiceHandle( hSvc);
//            ::CloseServiceHandle( hSC);
//            return STOP_SERVICE_ERROR;
//        }
//        // 等待服务停止
//        while( ::QueryServiceStatus( hSvc, &status) == TRUE)
//        {
//            ::Sleep( status.dwWaitHint);
//            if( status.dwCurrentState == SERVICE_STOPPED)
//            {
//                break;
//            }
//        }
    }
    // 启动服务
    qDebug()<<"start";
    if( ::StartService( hSvc, NULL, NULL) == FALSE)
    {
        qDebug()<<"START_SERVICE_ERROR";
        ::CloseServiceHandle( hSvc);
        ::CloseServiceHandle( hSC);
        return START_SERVICE_ERROR;
    }
    qDebug()<<"START_SERVICE_success";
    // 等待服务启动
    QDateTime start=QDateTime::currentDateTime();
    qDebug()<<"wait";
    while( ::QueryServiceStatus( hSvc, &status) == TRUE)
    {


        if( status.dwCurrentState == SERVICE_RUNNING)
        {
            break;
        }
        if(start.msecsTo(QDateTime::currentDateTime())>5000){//启动时间超过5秒
            qDebug()<<"timeout";
            ::CloseServiceHandle( hSvc);
            ::CloseServiceHandle( hSC);
            return SERVICE_OUTOF_TIME;
        }
        ::Sleep( status.dwWaitHint);
    }
    ::CloseServiceHandle( hSvc);
    ::CloseServiceHandle( hSC);
    return SERVICE_NO_ERROR;
}


/**************************************************
*
*
*
***************************************************/
int SunnyTcsService::restartService(const char *name)
{
    // 打开服务管理对象
    SC_HANDLE hSC = ::OpenSCManager( NULL,
        NULL, GENERIC_EXECUTE);
    if( hSC == NULL)
    {
        return CANT_OPEN_MANAGER;
    }
    // 打开服务
    char* nameData=const_cast<char*>(name);
    CString str = CString(nameData);
    USES_CONVERSION;
    LPCWSTR wszClassName = new WCHAR[str.GetLength()+1];
    wcscpy((LPTSTR)wszClassName,T2W((LPTSTR)str.GetBuffer(NULL)));
    str.ReleaseBuffer();

    SC_HANDLE hSvc = ::OpenService( hSC,wszClassName,
        SERVICE_START | SERVICE_QUERY_STATUS | SERVICE_STOP);
    if( hSvc == NULL)
    {
        ::CloseServiceHandle( hSC);
        return NO_THIS_SERVICE;
    }
    // 获得服务的状态
    SERVICE_STATUS status;
    if( ::QueryServiceStatus( hSvc, &status) == FALSE)
    {
        ::CloseServiceHandle( hSvc);
        ::CloseServiceHandle( hSC);
        return QUERY_SERVICESTATUS_ERROR;
    }
    qDebug()<<status.dwCurrentState;
    //如果处于运行或启动状态则返回
    if( status.dwCurrentState == SERVICE_RUNNING||status.dwCurrentState==SERVICE_START_PENDING)
    {

        ::CloseServiceHandle( hSvc);
        ::CloseServiceHandle( hSC);
        return SERVICE_ALREADY_RUNNING;
         //停止服务
        if( ::ControlService( hSvc,
            SERVICE_CONTROL_STOP, &status) == FALSE)
        {
            ::CloseServiceHandle( hSvc);
            ::CloseServiceHandle( hSC);
            return STOP_SERVICE_ERROR;
        }
        // 等待服务停止
        QDateTime start=QDateTime::currentDateTime();
        while( ::QueryServiceStatus( hSvc, &status) == TRUE)
        {
            ::Sleep( status.dwWaitHint);
            if( status.dwCurrentState == SERVICE_STOPPED)
            {
                break;
            }
            if(start.msecsTo(QDateTime::currentDateTime())>5000){
                ::CloseServiceHandle( hSvc);
                ::CloseServiceHandle( hSC);
                return SERVICE_OUTOF_TIME;
            }
        }
    }
    // 启动服务
    if( ::StartService( hSvc, NULL, NULL) == FALSE)
    {
        ::CloseServiceHandle( hSvc);
        ::CloseServiceHandle( hSC);
        return START_SERVICE_ERROR;
    }
    // 等待服务启动
    QDateTime start=QDateTime::currentDateTime();
    while( ::QueryServiceStatus( hSvc, &status) == TRUE)
    {

        if( status.dwCurrentState == SERVICE_RUNNING)
        {
            break;
        }
        if(start.msecsTo(QDateTime::currentDateTime())>5000){//启动时间超过十秒
            qDebug()<<"timeout";
            ::CloseServiceHandle( hSvc);
            ::CloseServiceHandle( hSC);
            return SERVICE_OUTOF_TIME;
        }
        ::Sleep( status.dwWaitHint);
    }
    ::CloseServiceHandle( hSvc);
    ::CloseServiceHandle( hSC);
    return SERVICE_NO_ERROR;
}


/**************************************************
*
*
*
***************************************************/
int SunnyTcsService::closeService(const char *name)
{
    // 打开服务管理对象
    SC_HANDLE hSC = ::OpenSCManager( NULL,
        NULL, GENERIC_EXECUTE);
    if( hSC == NULL)
    {
        return CANT_OPEN_MANAGER;
    }
    // 打开服务
    char* nameData=const_cast<char*>(name);
    CString str = CString(nameData);
    USES_CONVERSION;
    LPCWSTR wszClassName = new WCHAR[str.GetLength()+1];
    wcscpy((LPTSTR)wszClassName,T2W((LPTSTR)str.GetBuffer(NULL)));
    str.ReleaseBuffer();

    SC_HANDLE hSvc = ::OpenService( hSC,wszClassName,
        SERVICE_START | SERVICE_QUERY_STATUS | SERVICE_STOP);
    if( hSvc == NULL)
    {
        ::CloseServiceHandle( hSC);
        return NO_THIS_SERVICE;
    }
    // 获得服务的状态
    SERVICE_STATUS status;
    if( ::QueryServiceStatus( hSvc, &status) == FALSE)
    {
        ::CloseServiceHandle( hSvc);
        ::CloseServiceHandle( hSC);
        return QUERY_SERVICESTATUS_ERROR;
    }
    qDebug()<<status.dwCurrentState;
    //如果处于停止或停止中状态则返回
    if( status.dwCurrentState == SERVICE_STOPPED||status.dwCurrentState==SERVICE_STOP_PENDING)
    {
        qDebug()<<"stoping";
        ::CloseServiceHandle( hSvc);
        ::CloseServiceHandle( hSC);
        return SERVICE_ALREADY_STOP;
    }
    //关闭服务
    qDebug()<<"now stop";
    if( ControlService( hSvc,SERVICE_CONTROL_STOP, &status) == FALSE)
    {
        ::CloseServiceHandle( hSvc);
        ::CloseServiceHandle( hSC);
        qDebug()<<"STOP_SERVICE_ERROR";
        return STOP_SERVICE_ERROR;
    }
    // 等待服务停止
    qDebug()<<"wait for stop";
    QDateTime start=QDateTime::currentDateTime();
    while( ::QueryServiceStatus( hSvc, &status) == TRUE)
    {

        if( status.dwCurrentState == SERVICE_STOPPED)
        {
            break;
        }
        if(start.msecsTo(QDateTime::currentDateTime())>5000){
            qDebug()<<"timeout";
            ::CloseServiceHandle( hSvc);
            ::CloseServiceHandle( hSC);
            return SERVICE_OUTOF_TIME;
        }
        ::Sleep( status.dwWaitHint);
    }
    ::CloseServiceHandle( hSvc);
    ::CloseServiceHandle( hSC);
    qDebug()<<90909090;
    return SERVICE_NO_ERROR;
}


/**************************************************
*
#define NO_THIS_SERVICE 0X00//无该项服务
#define CANT_OPEN_MANAGER 0x01//无法打开服务管理器
#define QUERY_SERVICESTATUS_ERROR 0x02//服务状态获取错误
#define SERVICE_ALREADY_RUNNING 0x03//服务已经在运行或开启中
#define START_SERVICE_ERROR 0x04//服务启动失败
#define SERVICE_NO_ERROR 0x05//成功
#define SERVICE_OUTOF_TIME 0x06//超时
#define SERVICE_ALREADY_STOP 0x07//服务已经关闭或关闭中
#define STOP_SERVICE_ERROR 0x08//关闭服务失败
*
***************************************************/
void SunnyTcsService::dealReturn(int ret)
{
   emit retSignal(ret);
}


/**************************************************
*
*
*
***************************************************/
void SunnyTcsService::run()
{
    int ret;
    switch(m_mode){
    case MODE_START:
        ret=startService(m_name.toLocal8Bit().data());
        break;
    case MODE_CLOSE:
        ret=closeService(m_name.toLocal8Bit().data());
        break;
    case MODE_RESTART:
        ret=restartService(m_name.toLocal8Bit().data());
        break;
    }

    dealReturn(ret);
    quit();
    wait();
}

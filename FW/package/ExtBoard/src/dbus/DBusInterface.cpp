#include "DBusInterface.h"
#include <dbus-cxx.h>
#include <thread>
#include <chrono>
#include "DeamonLog.h"
#include "version.h"
#include "string"

static std::string  DbusInterface_Version()
{
#ifndef FULL_VERSION_STRING
    return "dummy";
#else
    return FULL_VERSION_STRING;
#endif
}


extern "C" void main_stop_running();

static std::shared_ptr<DBus::Dispatcher> dispatcher=nullptr;
static std::shared_ptr<DBus::Connection> con=nullptr;
static std::shared_ptr<DBus::Object> dbus_o_server=nullptr;
static std::shared_ptr<DBus::Method<std::string ()>> dbus_o_server_version=nullptr;

void DbusInterface_Init()
{
    dispatcher=DBus::StandaloneDispatcher::create();
    if(dispatcher != nullptr)
    {
        con=dispatcher->create_connection(DBus::BusType::SYSTEM);
    }

    if(con == nullptr)
    {
        LOGINFO("DBusInterface create connection failed!");
        main_stop_running();
        return;
    }

    con->bus_register();
    if(!con->is_registered())
    {
        LOGINFO("DBusInterface bus register failed!");
        main_stop_running();
        return;
    }

    LOGINFO("DBusInterface unique name:%s",con->unique_name().c_str());

    /*
        服务名称:ExtBoard.Deamon.Server
    */
    if(con->request_name( "ExtBoard.Deamon.Server", DBUSCXX_NAME_FLAG_REPLACE_EXISTING ) != DBus::RequestNameResponse::PrimaryOwner )
    {
        /*
            只能启动一个守护进程，当有其它进程时停止当前进程的运行
        */
        LOGINFO("DBusInterface Service is already started!");
        main_stop_running();
        return;
    }

    /*
        添加守护进程相关对象(server),路径为/Deamon/Server
    */
    dbus_o_server=con->create_object("/Deamon/Server", DBus::ThreadForCalling::DispatcherThread);
    if(dbus_o_server!=nullptr)
    {
        //接口名称:ExtBoard.Deamon,方法名称:Version
        dbus_o_server_version=dbus_o_server->create_method<std::string ()>("ExtBoard.Deamon", "Version", sigc::ptr_fun(DbusInterface_Version) );
    }
}

void DbusInterface_Deinit()
{

}

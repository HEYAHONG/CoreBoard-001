#include <stdint.h>
#include <stdio.h>
#include <dbus-cxx.h>
#include <iostream>
#include <string>

int main(int argc,const char *argv[])
{
    try
    {

        std::shared_ptr<DBus::Dispatcher> dispatcher = DBus::StandaloneDispatcher::create();
        if(dispatcher==nullptr)
        {
            std::cerr << "Can't create Dispatcher" << std::endl;
            return -1;
        }
        std::shared_ptr<DBus::Connection> connection = dispatcher->create_connection( DBus::BusType::SYSTEM );
        if(connection==nullptr)
        {
            std::cerr << "Can't create Connection" << std::endl;
            return -1;
        }

        {
            //获取ExtBoardD版本
            std::shared_ptr<DBus::ObjectProxy> object = connection->create_object_proxy("ExtBoard.Deamon.Server", "/Deamon/Server");
            if(object != nullptr)
            {
                DBus::MethodProxy<std::string ()>& version_proxy=*(object->create_method<std::string()>("ExtBoard.Deamon","Version"));
                std::string Version=version_proxy();
                std::cout << "ExtBoardD Version:" << Version << std::endl;
            }
        }
    }
    catch(...)
    {
        std::cerr << "Dbus Operate Error! ExtBoardD may not be running!" << std::endl;
        return -1;
    }
    return 0;
}

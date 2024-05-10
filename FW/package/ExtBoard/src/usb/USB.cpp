#include "USB.h"
#include "DeamonLog.h"
#include "vector"
#include "mutex"
#include "libserialport.h"
#include "unistd.h"
#include <fstream>

static libusb_context *ctx=NULL;
extern "C" void main_stop_running();

static std::vector<USB_Device_Info_t> usb_device_list;
static std::recursive_mutex usb_device_list_lock;

static bool usb_device_list_has_device(uint8_t bus,uint8_t address)
{
    std::lock_guard<std::recursive_mutex> lock(usb_device_list_lock);
    for(USB_Device_Info_t &dev:usb_device_list)
    {
        if(dev.bus==bus && dev.address==address)
        {
            return true;
        }
    }
    return false;
}

static USB_Device_Info_t *usb_device_list_get_device(uint8_t bus,uint8_t address)
{
    std::lock_guard<std::recursive_mutex> lock(usb_device_list_lock);
    for(USB_Device_Info_t &dev:usb_device_list)
    {
        if(dev.bus==bus && dev.address==address)
        {
            return &dev;
        }
    }
    return NULL;
}

static bool usb_device_list_device_valid(uint8_t bus,uint8_t address)
{
    std::lock_guard<std::recursive_mutex> lock(usb_device_list_lock);
    for(USB_Device_Info_t &dev:usb_device_list)
    {
        if(dev.bus==bus && dev.address==address)
        {
            if(dev.vaild)
            {
                return true;
            }
            else
            {
                return false;
            }
        }
    }
    return false;
}

static bool usb_device_list_device_set_valid(uint8_t bus,uint8_t address,bool vaild)
{
    std::lock_guard<std::recursive_mutex> lock(usb_device_list_lock);
    for(USB_Device_Info_t &dev:usb_device_list)
    {
        if(dev.bus==bus && dev.address==address)
        {
            dev.vaild=vaild;
            if(!dev.vaild)
            {
                //清空设备列表
                dev.device_map.clear();
            }
            return true;
        }
    }
    return false;
}

static void usb_device_list_add(libusb_context *ctx,libusb_device *device)
{
    USB_Device_Info_t *info=NULL;
    uint8_t bus_number=libusb_get_bus_number(device);
    uint8_t address=libusb_get_device_address(device);
    if(usb_device_list_has_device(bus_number,address))
    {
        usb_device_list_device_set_valid(bus_number,address,true);
        info=usb_device_list_get_device(bus_number,address);
    }
    else
    {
        USB_Device_Info_t new_info;
        new_info.bus=bus_number;
        new_info.address=address;
        new_info.vaild=true;
        {
            std::lock_guard<std::recursive_mutex> lock(usb_device_list_lock);
            usb_device_list.push_back(new_info);
        }
        info=usb_device_list_get_device(bus_number,address);
    }
    if(info!=NULL)
    {
        {
            ssize_t path_len=libusb_get_port_numbers(device,info->path,sizeof(info->path));
            if(path_len!=LIBUSB_ERROR_OVERFLOW && path_len<sizeof(info->path));
            {
                memset(&info->path[path_len],0,sizeof(info->path)-path_len);
            }
        }
        libusb_device_handle *device_handle=NULL;
        libusb_open(device,&device_handle);
        libusb_device_descriptor usb_device_desc= {0};
        if(LIBUSB_SUCCESS!=libusb_get_device_descriptor(device,&usb_device_desc))
        {
            return;
        }
        if(device_handle!=NULL)
        {
            {
                //读取制造商
                char buff[1024]= {0};
                libusb_get_string_descriptor_ascii(device_handle,usb_device_desc.iManufacturer,(uint8_t *)buff,sizeof(buff));
                info->manufacturer=buff;
            }

            {
                //读取产品名称
                char buff[1024]= {0};
                libusb_get_string_descriptor_ascii(device_handle,usb_device_desc.iProduct,(uint8_t *)buff,sizeof(buff));
                info->product=buff;
            }

            libusb_close(device_handle);
        }

        {
            //读取串口列表

            struct sp_port **port_list=NULL;
            if(SP_OK!=sp_list_ports(&port_list))
            {
                return ;
            }

            if(port_list!=NULL)
            {
                size_t i=0;
                struct sp_port *serial_port=NULL;
                while((serial_port=port_list[i++])!=NULL)
                {
                    if(SP_TRANSPORT_USB == sp_get_port_transport(serial_port))
                    {
                        int usb_bus=0,usb_addr=0;
                        if(SP_OK==sp_get_port_usb_bus_address(serial_port,&usb_bus,&usb_addr))
                        {
                            if(usb_bus==bus_number && usb_addr==address)
                            {
                                info->device_map["serialport"].insert(sp_get_port_name(serial_port));
                            }
                        }
                    }
                }
                sp_free_port_list(port_list);
            }
        }

        {
            //读取块设备列表
            std::filesystem::path sysfs_block_path="/sys/class/block";
            if(!std::filesystem::exists(sysfs_block_path))
            {
                sysfs_block_path="/sys/block";
            }

            if(!std::filesystem::exists(sysfs_block_path))
            {
                return;
            }

            for (const std::filesystem::directory_entry& dir_entry :std::filesystem::directory_iterator(sysfs_block_path))
            {
                if(dir_entry.is_symlink())
                {
                    std::string block_path_symlink=dir_entry.path().string();
                    std::string block_path=sysfs_block_path.string()+"/"+std::filesystem::read_symlink(block_path_symlink).string();
                    auto realpath=[](std::string path)->std::string
                    {
                        std::vector<std::string> name;
                        size_t name_count=0;
                        while(!path.empty())
                        {
                            size_t pos=path.find("/");
                            std::string dir_name;
                            if(pos==std::string::npos)
                            {
                                dir_name=path;
                                path="";
                            }
                            else
                            {
                                if(pos > 1)
                                {
                                    dir_name=path.substr(0,pos);
                                }
                                path=path.substr(pos+1);
                            }
                            if(!dir_name.empty())
                            {
                                if(dir_name==".")
                                {
                                    continue;
                                }
                                if(dir_name=="..")
                                {
                                    for(size_t i=0; i<name_count; i++)
                                    {
                                        if(!name[name_count-1-i].empty())
                                        {
                                            name[name_count-1-i]="";
                                            break;
                                        }
                                    }
                                    continue;
                                }
                                name_count++;
                                name.push_back(dir_name);
                            }
                        }
                        std::string ret;
                        for(size_t i=0; i<name.size(); i++)
                        {
                            if(name[i].empty())
                            {
                                continue;
                            }
                            ret+="/";
                            ret+=name[i];
                        }
                        if(ret.empty())
                        {
                            ret="/";
                        }
                        return ret;
                    };

                    block_path=realpath(block_path);
                    {
                        std::string temp_path=block_path;
                        auto readfile_oneline=[](std::string filepath) -> std::string
                        {
                            std::string ret;
                            std::ifstream file(filepath);
                            if(file.is_open())
                            {
                                std::getline(file,ret);
                                file.close();
                            }
                            return ret;
                        };
                        while(temp_path!="/")
                        {
                            if(std::filesystem::exists(temp_path+"/busnum") && std::filesystem::exists(temp_path+"/devnum"))
                            {
                                if(readfile_oneline(temp_path+"/busnum")==std::to_string(info->bus) && readfile_oneline(temp_path+"/devnum")==std::to_string(info->address))
                                {
                                    info->device_map["block"].insert(block_path_symlink.replace(0,sysfs_block_path.string().length(),"/dev"));
                                }
                                break;
                            }
                            temp_path+="/..";
                            temp_path=realpath(temp_path);
                        }
                    }
                }
            }


        }
    }
}

static void usb_device_list_enum(std::function<void (USB_Device_Info_t&)> On_Enum)
{
    std::lock_guard<std::recursive_mutex> lock(usb_device_list_lock);
    for(USB_Device_Info_t &dev:usb_device_list)
    {
        if(On_Enum!=NULL)
        {
            On_Enum(dev);
        }
    }
}

void USB_Enum(std::function<void (USB_Device_Info_t)> On_Enum)
{
    usb_device_list_enum([&](USB_Device_Info_t&dev) -> void
    {
        if(On_Enum!=NULL)
        {
            On_Enum(dev);
        }
    });
}

static void libusb_log(libusb_context *ctx,enum libusb_log_level level, const char *str)
{
    LOGINFO("USB(%d) :%s",static_cast<int>(level),str);
}

static int libusb_hotplug_callback(libusb_context *ctx,libusb_device *device,libusb_hotplug_event event,void *usr)
{
    uint8_t bus_number=libusb_get_bus_number(device);
    uint8_t address=libusb_get_device_address(device);
    switch(event)
    {
    case LIBUSB_HOTPLUG_EVENT_DEVICE_ARRIVED:
    {
        usb_device_list_add(ctx,device);
        LOGINFO("New USB device(bus=%d,addr=%d)",(int)bus_number,(int)address);
    }
    break;
    case LIBUSB_HOTPLUG_EVENT_DEVICE_LEFT:
    {
        usb_device_list_device_set_valid(bus_number,address,false);
        LOGINFO("Delete USB device(bus=%d,addr=%d)",(int)bus_number,(int)address);
    }
    break;
    }

    return 0;
}

void USB_Init()
{
    libusb_init(&ctx);
    if(ctx==NULL)
    {
        main_stop_running();
        LOGINFO("Init USB failed!");
        return;
    }
    libusb_set_log_cb(ctx,libusb_log,LIBUSB_LOG_CB_GLOBAL);

    if(LIBUSB_SUCCESS!=libusb_hotplug_register_callback(ctx,LIBUSB_HOTPLUG_EVENT_DEVICE_ARRIVED|LIBUSB_HOTPLUG_EVENT_DEVICE_LEFT,LIBUSB_HOTPLUG_ENUMERATE,LIBUSB_HOTPLUG_MATCH_ANY,LIBUSB_HOTPLUG_MATCH_ANY,LIBUSB_HOTPLUG_MATCH_ANY,libusb_hotplug_callback,NULL,NULL))
    {
        main_stop_running();
        LOGINFO("Init USB failed!");
        return;
    }

    if(LIBUSB_SUCCESS!=libusb_hotplug_register_callback(ctx,LIBUSB_HOTPLUG_EVENT_DEVICE_ARRIVED|LIBUSB_HOTPLUG_EVENT_DEVICE_LEFT,0,LIBUSB_HOTPLUG_MATCH_ANY,LIBUSB_HOTPLUG_MATCH_ANY,LIBUSB_HOTPLUG_MATCH_ANY,libusb_hotplug_callback,NULL,NULL))
    {
        main_stop_running();
        LOGINFO("Init USB failed!");
        return;
    }

    {
        //显示当前设备
        usb_device_list_enum([](USB_Device_Info_t &dev) -> void
        {
            std::string path_numbers_string;
            {
                for(size_t i=0; i<sizeof(dev.path); i++)
                {
                    if(dev.path[i] == 0)
                    {
                        break;
                    }
                    if(i!=0)
                    {
                        path_numbers_string+=".";
                    }
                    path_numbers_string+=std::to_string(dev.path[i]);
                }
            }
            LOGINFO("USB Device(%d.%d)",(int)dev.bus,(int)dev.address);
            if(!path_numbers_string.empty())
            {
                LOGINFO("    path=%s",path_numbers_string.c_str());
            }
            if(!dev.manufacturer.empty())
            {
                LOGINFO("    manufacturer=%s",dev.manufacturer.c_str());
            }
            if(!dev.product.empty())
            {
                LOGINFO("    product=%s",dev.product.c_str());
            }

            if(dev.device_map.find("serialport") != dev.device_map.end())
            {
                LOGINFO("    serialport:");
                std::set<std::string> devpathset=dev.device_map["serialport"];
                for(std::string devpath:devpathset)
                {
                    LOGINFO("        %s",devpath.c_str());
                }
            }

            if(dev.device_map.find("block") != dev.device_map.end())
            {
                LOGINFO("    block:");
                std::set<std::string> devpathset=dev.device_map["block"];
                for(std::string devpath:devpathset)
                {
                    LOGINFO("        %s",devpath.c_str());
                }
            }
        });
    }
}

void USB_Deinit()
{
    if(ctx!=NULL)
    {
        libusb_exit(ctx);
        ctx=NULL;
    }
}

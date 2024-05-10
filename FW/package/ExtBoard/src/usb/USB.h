#ifndef USB_H_INCLUDED
#define USB_H_INCLUDED
#include "libusb.h"
#include "stdint.h"
#include "inttypes.h"
#include "stdbool.h"
#include "stdio.h"
#include "string.h"
#include <string>
#include <functional>
#include <map>
#include <set>
#include <filesystem>

#ifdef __cplusplus

typedef struct
{
    uint8_t bus;//总线号
    uint8_t address;//设备地址
    uint8_t path[8];//设备路径
    std::string manufacturer;//厂商
    std::string product;//产品名称
    bool vaild;//是否有效，当vaild为false时设备可能已断开连接
    std::map<std::string,std::set<std::string>> device_map;//设备列表（设备对应的访问路径）,如serialport=串口设备,block=块设备
} USB_Device_Info_t;

/** \brief USB枚举
 *
 * \param On_Enum std::function<void (USB_Device_Info_t)>
 *
 */
void USB_Enum(std::function<void (USB_Device_Info_t)> On_Enum);

#endif // __cplusplus
#ifdef __cplusplus
extern "C"
{
#endif // __cplusplus

/** \brief USB初始化
 *
 *
 */
void USB_Init();


/** \brief  USB反初始化
 *
 *
 */
void USB_Deinit();

#ifdef __cplusplus
}
#endif // __cplusplus

#endif // USB_H_INCLUDED

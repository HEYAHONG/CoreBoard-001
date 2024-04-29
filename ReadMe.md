# 说明

以HLK-7688A模块为核心的核心板，HLK-7688A采用MT7688AN芯片作为核心芯片。

主要有以下特点:

- LAN 网口 * 1:可用于调试及固件烧录。
- WAN 网口 * 1:可通过以太网联网
- USB 2.0 * 1:可通过使用扩展板通过USB扩展外设。
- RTC:采用DS1307芯片，弥补MT7688AN本身不带RTC的缺陷，在某些对时间有要求的场合十分有效。
- 可通过USB Type-C连接上位机调试:采用CH340N芯片连接核心板的串口0，默认串口参数为57600 8N1。

注意:对于MT7688AN芯片原厂二次开发SDK而言，区分IOT模式与路由器模式，其本质是是否将网口1-4的引脚作为其它功能使用，在IOT模式下可使用其它功能(此时只有网口0可用)，在路由模式下，网口1-4均为网口（不可部分或全部作为其它角色使用）。若采用openwrt开发,需要在设备树中调整相应引脚功能，没有单独的模式调整。

# 固件

对于固件的烧录，通常需要通过ssh或者http访问HLK-7688A模块，其地址如下:

- openwrt.lan：新版openwrt地址，其本质是默认主机名为openwrt，.lan域名主要用于局域网。
- 192.168.1.1：breed固件或者新版openwrt默认局域网地址。
- 192.168.16.254:HLK-7688A默认固件的局域网地址。

## breed

breed为bootloader，可以供Web刷机功能(开机时按住重启键)。

其下载地址为[https://breed.hackpascal.net/](https://breed.hackpascal.net/)，文件名为[breed-mt7688-reset38.bin](https://breed.hackpascal.net/breed-mt7688-reset38.bin)。

通过ssh使用root用户登录HLK-7688A模块后，其主要步骤如下:

```bash
# 烧录
## 注意：整个过程中需要将WAN连接至internet。
## 进入tmp，将下载的文件保存在内存中
cd /tmp
## 下载breed-mt7688-reset38.bin
wget https://breed.hackpascal.net/breed-mt7688-reset38.bin
## 写入u-boot,若此步骤失败，则需要解锁u-boot。
mtd -r write breed-mt7688-reset38.bin u-boot
## 重启
reboot

# 解锁u-boot
## 注意：整个过程中需要将WAN连接至internet。
## 仅适用于新版openwrt,若烧录u-boot未报错，无需进行下列步骤。

## 更新opkg软件包
opkg update

## 安装mtd-rw模块
opkg install kmod-mtd-rw

## 加载mtd-rw模块，加载完成后u-boot变为可写。此时则可进行 写入u-boot 的操作。
insmod mtd-rw i_want_a_brick=1
```

## openwrt

HLK-7688A受openwrt官方支持,可直接通过web升级固件，通过http访问HLK-7688A模块后,可直接通过系统升级升级固件。

其下载地址为[https://downloads.openwrt.org/releases/](https://downloads.openwrt.org/releases/)。

其目录为 [系统版本]/targets/ramips/mt76x8/ ，其中系统版本是需要升级的版本，如系统版本为23.05.1则目录为23.05.1/targets/ramips/mt76x8/。

HLK-7688A的固件为名称中含有为hlk与7688a的sysupgrade.bin文件。

# 目录结构

- [HW](HW):硬件设计。
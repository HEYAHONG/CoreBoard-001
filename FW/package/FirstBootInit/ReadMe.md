#  说明 

本软件包主要提供第一次启动的脚本初始化。

本软件包不依赖其它任何软件包。

## 原理

启动过程中,当检测到/etc/FirstBootInit/NeedFirstBoot文件后,执行/etc/FirstBootInit/script/中的可执行脚本并删除/etc/FirstBootInit/NeedFirstBoot。

第二次启动不会执行任何脚本。

## 脚本说明

### 00print

打印信息,表示这是第一次启动

### 10wifi

启动WIFI AP,AP名称为CoreBoard-[Mac地址],密码为CoreBoardWifiAp。

### 10rtc

虽然openwrt本身支持rtc实时时钟，但某些芯片需要初始化一次后才会启动。如DS1307必须将相应的CH位(clock halt)清除才能启动时钟。

### 10timezone

将时区设置为UTC+8时区（北京时间）

# 使用

将需要第一次启动的脚本文件放入[./files/etc/FirstBootInit/script/](./files/etc/FirstBootInit/script/) 目录中。

注意：推荐脚本名称前两个字符为数字字符。


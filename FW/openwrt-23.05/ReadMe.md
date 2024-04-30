# 说明

基于openwrt-23.05的固件。

本固件采用make作为构建系统，支持在以下操作系统中编译(只要支持编译官方openwrt即可编译本固件)：

- Linux
- MacOS
- Windows(WSL):在Windows下仅支持在WSL中编译。

# 常用操作

## 编译

```bash
make
```

注意：整个编译过程中需要联网。

编译完成后，固件在 openwrt/bin/targets/ramips/mt76x8/ 目录中。

## Kconfig配置

对openwrt进行Kconfig配置可调整编译进固件的软件包。

```bash
make menuconfig
```


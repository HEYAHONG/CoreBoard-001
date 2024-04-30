# 说明

本目录为基于[openwrt](https://www.openwrt.org)的固件，添加了一些软件包。

注意:

1. 编译此固件，需要参考[https://openwrt.org/docs/guide-developer/start](https://openwrt.org/docs/guide-developer/start)搭建编译环境，确保能够正常编译openwrt。
2. 本目录中的固件只支持使用git下载的源代码，若使用github.com/gitee.com等平台自动打包的源代码，可能不能正常编译。
3. 本目录中的固件编译过程中全程需要联网，若网络对openwrt.org等外网的连接不稳定，需设置代理。

# 目录结构

- [openwrt-23.05](openwrt-23.05)：基于openwrt-23.05的固件。
- [package](package)：本地软件包，通常为各个固件的公共部分。


# 说明

本目录为基于[openwrt](https://www.openwrt.org)的固件，添加了一些软件包。

注意:

1. 编译此固件，需要参考[https://openwrt.org/docs/guide-developer/start](https://openwrt.org/docs/guide-developer/start)搭建编译环境，确保能够正常编译openwrt。
2. 本目录中的固件只支持使用git下载的源代码，若使用github.com/gitee.com等平台自动打包的源代码，可能不能正常编译。
3. 本目录中的固件编译过程中全程需要联网，若网络对openwrt.org等外网的连接不稳定，需设置代理。

## WSL下的编译

在WSL下的PATH环境变量可能含有空格(在Windows中PATH变量一般含有空格，如Program Files等目录)，这会影响openwrt编译。在进行编译前需要手工设置PATH变量:

```bash
export PATH=/usr/local/bin:/usr/local/sbin:/usr/bin:/usr/sbin:/bin:/sbin
```



# 代理设置

代理设置前需要手工搭建一个代理服务器，一般可使用阿里云/腾讯云在香港或境外的轻量级服务器，一般情况下可选择香港的轻量级云服务器，其它地区的服务器可能会出现网络不好（速度极低，如几K每秒）。代理搭建完成后，可获取一个代理地址，本章节的代理地址示例为[http://127.0.0.1:10809](http://127.0.0.1:10809),采用v2ray搭建,其它代理地址需要酌情修改。

## git http/https代理设置

git代理用于从https://git.openwrt.org下载源代码，一般设置如下：

```bash
#以下命令只需要执行一次，保存在~/.gitconfig中
git config --global http.proxy http://127.0.0.1:10809
git config --global https.proxy http://127.0.0.1:10809

```

## wget/curl代理设置

wget/curl代理主要用于下载源代码时使用代理，如从github.com上下载源代码。

```bash
#以下命令需要在make执行前执行,每个终端均需执行一次
export http_proxy=http://127.0.0.1:10809
export https_proxy=http://127.0.0.1:10809

```

## go模块代理

使用Go语言编写的软件包在编译过程中需要下载大量模块，使用代理可大大提高编译速度。

参见[https://goproxy.cn/](https://goproxy.cn/)



# 目录结构

- [openwrt-23.05](openwrt-23.05)：基于openwrt-23.05的固件。
- [package](package)：本地软件包，通常为各个固件的公共部分。


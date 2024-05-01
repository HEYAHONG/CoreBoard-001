

ifeq ("${Q}","")
Q=@
endif

#伪目标
.PHONY:all prepare feeds build menuconfig

#主要步骤的依赖
all:build
build:prepare
menuconfig:prepare

#openwrt源代码
openwrt/Makefile:
	${Q}git submodule update --init --recursive
	${Q}[ -f openwrt/Makefile ] || echo openwrt download failed!
	${Q}[ -f openwrt/Makefile ]

#Kconfig配置
openwrt/.config: openwrt/Makefile
	${Q}cp defconfig openwrt/.config

#feeds
feeds:openwrt/Makefile
	${Q}cp openwrt/feeds.conf.default openwrt/feeds.conf
	${Q}./local_feeds 1>> openwrt/feeds.conf 
	${Q}openwrt/scripts/feeds update -a
	${Q}openwrt/scripts/feeds install -a -f

openwrt/feeds/:feeds

#准备
GitDate		=	$(shell git show   --pretty=tformat:%as 2>/dev/null | sed -n 1p)
GitVersion	=	$(shell git rev-parse --short HEAD 2>/dev/null)

prepare: openwrt/Makefile openwrt/feeds/ openwrt/.config
	${Q}-openwrt_path_patch 2>/dev/null #若处在HEnvBox中，尝试修改源代码保存路径
	${Q}./local_patch #安装本地补丁
	${Q}# 更新版本号
	${Q}echo "GitDate=${GitDate},GitVerison=${GitVersion}"
	${Q}sed -i "s/CONFIG_VERSION_NUMBER=.*/CONFIG_VERSION_NUMBER=\"${GitDate}\"/g" openwrt/.config
	${Q}sed -i "s/CONFIG_VERSION_CODE=.*/CONFIG_VERSION_CODE=\"${GitVersion}\"/g" openwrt/.config


#构建
build:
	${Q}${MAKE} -C openwrt V=sc

#Kconfig配置
menuconfig:
	${Q}${MAKE} -C openwrt menuconfig
	${Q}cp openwrt/.config defconfig

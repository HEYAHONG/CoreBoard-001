

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
	${Q}openwrt/scripts/feeds update -a
	${Q}openwrt/scripts/feeds install -a -f

openwrt/feeds/:feeds

#准备
prepare: openwrt/Makefile openwrt/feeds/ openwrt/.config
	${Q}-openwrt_path_patch 2>/dev/null #若处在HEnvBox中，尝试修改源代码保存路径

#构建
build:
	${Q}${MAKE} -C openwrt V=sc

#Kconfig配置
menuconfig:
	${Q}${MAKE} -C openwrt menuconfig
	${Q}cp openwrt/.config defconfig

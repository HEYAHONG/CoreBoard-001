include $(TOPDIR)/rules.mk

PKG_NAME:=blackmagic
PKG_RELEASE:=1

PKG_SOURCE_URL:= https://github.com/blackmagic-debug/blackmagic.git
PKG_SOURCE_PROTO:=git
PKG_SOURCE_DATE:=2025-10-11
PKG_SOURCE_VERSION:=942817692d1b6a326c1a0a4b816a434e4d17b423
PKG_MIRROR_HASH:=09587eda6e4fa80b39f3d8c3a95869051e46336fad6aae3cb9d841981aa5ec05
ifneq (,$(wildcard ${TOPDIR}/../version_24.10))
#openwrt 24.10
PKG_MIRROR_HASH:=a66e91de2968eee4a07d6399581d441fc22de9b5f05dddf288b4bc874f5ecd7b
endif
PKG_LICENSE_FILES:=COPYING

PKG_MAINTAINER:=HEYAHONG <2229388563@qq.com>
PKG_INSTALL:=1



include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/meson.mk


define Package/blackmagic
  SECTION  := blackmaigc
  CATEGORY := CoreBoard-001
  DEPENDS  := +libstdcpp +libc +librt +libpthread +hidapi +libusb-1.0 +libftdi1 +boost
  TITLE    := In-application debugger for ARM Cortex and RISC-V processors.
endef

TARGET_CFLAGS += -I$(STAGING_DIR)/usr/include
TARGET_LDFLAGS += -L$(STAGING_DIR)/usr/lib


define Package/blackmagic/install
	$(INSTALL_DIR) $(1)/bin
	-$(CP) $(PKG_INSTALL_DIR)/usr/bin/* $(1)/bin/
	-$(CP) $(PKG_INSTALL_DIR)/usr/sbin/* $(1)/bin/
	-${CP} ${MESON_BUILD_DIR}/blackmagic $(1)/bin/
	$(INSTALL_DIR) $(1)/lib
	-$(CP) $(PKG_INSTALL_DIR)/usr/lib/*.so* $(1)/lib/
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/bin
	-$(CP) $(PKG_INSTALL_DIR)/usr/bin/* $(1)/bin/
	-$(CP) $(PKG_INSTALL_DIR)/usr/sbin/* $(1)/bin/
	$(INSTALL_DIR) $(1)/usr/include
	-$(CP) $(PKG_INSTALL_DIR)/usr/include/* $(1)/usr/include
	$(INSTALL_DIR) $(1)/usr/lib/
	-$(CP) $(PKG_INSTALL_DIR)/usr/lib/* $(1)/usr/lib
	$(INSTALL_DIR) $(1)/usr/lib/pkgconfig
	-$(CP) $(PKG_INSTALL_DIR)/usr/lib/pkgconfig/*.pc $(1)/usr/lib/pkgconfig
endef

$(eval $(call BuildPackage,blackmagic))

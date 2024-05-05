include $(TOPDIR)/rules.mk

PKG_NAME:=libsigcplusplus
PKG_RELEASE:=1

PKG_SOURCE_URL:= https://github.com/libsigcplusplus/libsigcplusplus.git
PKG_SOURCE_PROTO:=git
PKG_SOURCE_DATE:=2024-05-04
PKG_SOURCE_VERSION:=dae8f5839e447b93b13a3b00ff2ddc279b47411e
PKG_MIRROR_HASH:=9a16cb312bffbd562534977ac2fcfb6869ebfbc7367970d8e49d374340024db8
PKG_LICENSE_FILES:=COPYING

PKG_MAINTAINER:=HEYAHONG <2229388563@qq.com>
PKG_INSTALL:=1

CMAKE_OPTIONS:= 

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/libsigcplusplus
  SECTION  := libsigcplusplus
  CATEGORY := CoreBoard-001
  DEPENDS  := +libstdcpp +libc +librt +libpthread
  TITLE    := libsigc++ implements a typesafe callback system for standard C++.
endef

TARGET_CFLAGS += -I$(STAGING_DIR)/usr/include
TARGET_LDFLAGS += -L$(STAGING_DIR)/usr/lib


define Package/libsigcplusplus/install
	$(INSTALL_DIR) $(1)/bin
	-$(CP) $(PKG_INSTALL_DIR)/usr/bin/* $(1)/bin/
	-$(CP) $(PKG_INSTALL_DIR)/usr/sbin/* $(1)/bin/
	$(INSTALL_DIR) $(1)/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/*.so* $(1)/lib/
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/bin
	-$(CP) $(PKG_INSTALL_DIR)/usr/bin/* $(1)/bin/
	-$(CP) $(PKG_INSTALL_DIR)/usr/sbin/* $(1)/bin/
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) $(PKG_INSTALL_DIR)/usr/include/* $(1)/usr/include
	$(INSTALL_DIR) $(1)/usr/lib/
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/* $(1)/usr/lib
	$(INSTALL_DIR) $(1)/usr/lib/pkgconfig
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/pkgconfig/*.pc $(1)/usr/lib/pkgconfig
endef

$(eval $(call BuildPackage,libsigcplusplus))

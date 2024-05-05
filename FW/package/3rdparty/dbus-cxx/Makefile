include $(TOPDIR)/rules.mk

PKG_NAME:=dbus-cxx
PKG_RELEASE:=1

PKG_SOURCE_URL:= https://github.com/dbus-cxx/dbus-cxx.git
PKG_SOURCE_PROTO:=git
PKG_SOURCE_DATE:=2024-05-04
PKG_SOURCE_VERSION:=ca478ce28d70adffb76287a584abcabacd3ebc18
PKG_MIRROR_HASH:=c6ca630b353006103483049a5dbc2cb32bd7866a9d66998e8c858f763200b550
PKG_LICENSE_FILES:=COPYING

PKG_MAINTAINER:=HEYAHONG <2229388563@qq.com>
PKG_INSTALL:=1

CMAKE_OPTIONS:= -DENABLE_EXAMPLES=OFF -DENABLE_TOOLS=OFF -DTOOLS_BUNDLED_CPPGENERATE=OFF -DBUILD_SITE=OFF -DBUILD_TESTING=OFF  -DENABLE_GLIB_SUPPORT=OFF -DENABLE_QT_SUPPORT=OFF -DENABLE_UV_SUPPORT=OFF

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk

define Package/dbus-cxx
  SECTION  := dbus-cxx
  CATEGORY := CoreBoard-001
  DEPENDS  := +libstdcpp +libc +librt +libpthread +dbus +libdbus +libsigcplusplus +libexpat +libpopt
  TITLE    := DBus-cxx is a C++ implementation for DBus.
endef

TARGET_CFLAGS += -I$(STAGING_DIR)/usr/include
TARGET_LDFLAGS += -L$(STAGING_DIR)/usr/lib


define Package/dbus-cxx/install
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

$(eval $(call BuildPackage,dbus-cxx))

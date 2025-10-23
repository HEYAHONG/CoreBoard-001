include $(TOPDIR)/rules.mk

PKG_NAME:=dbus-cxx
PKG_RELEASE:=1

PKG_SOURCE_URL:= https://github.com/dbus-cxx/dbus-cxx.git
PKG_SOURCE_PROTO:=git
PKG_SOURCE_DATE:=2025-08-03
PKG_SOURCE_VERSION:=b705ad73bef724de0ed33f60462c70b380b6b300
PKG_MIRROR_HASH:=3363df4c674304f4ab0d90fc3f8a664759bc300591c86fe608fc2c15a9dfc986
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

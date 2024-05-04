include $(TOPDIR)/rules.mk

PKG_NAME:=libserialport
PKG_RELEASE:=1

PKG_SOURCE_URL:= https://github.com/sigrokproject/libserialport.git
PKG_SOURCE_PROTO:=git
PKG_SOURCE_DATE:=2024-05-04
PKG_SOURCE_VERSION:=fd20b0fc5a34cd7f776e4af6c763f59041de223b
PKG_MIRROR_HASH:=6cadb8022be47d56d129e7f7df5246c66f60d17c847a87405307df30e3228905
PKG_LICENSE_FILES:=COPYING

PKG_MAINTAINER:=HEYAHONG <2229388563@qq.com>
PKG_FIXUP:=libtool autoreconf
PKG_INSTALL:=1

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/autotools.mk

define Package/libserialport
  SECTION:=libserialport
  CATEGORY:=CoreBoard-001
  TITLE:=cross-platform library for accessing serial ports
endef

TARGET_CFLAGS += -I$(STAGING_DIR)/usr/include
TARGET_LDFLAGS += -L$(STAGING_DIR)/usr/lib


define Package/libserialport/install
	$(INSTALL_DIR) $(1)/lib
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/*.so* $(1)/lib/
endef

define Build/InstallDev
	$(INSTALL_DIR) $(1)/usr/include
	$(CP) $(PKG_INSTALL_DIR)/usr/include/*.h $(1)/usr/include
	$(INSTALL_DIR) $(1)/usr/lib/
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/*.so* $(1)/usr/lib
	$(INSTALL_DIR) $(1)/usr/lib/pkgconfig
	$(CP) $(PKG_INSTALL_DIR)/usr/lib/pkgconfig/*.pc $(1)/usr/lib/pkgconfig
endef

$(eval $(call BuildPackage,libserialport))

include $(TOPDIR)/rules.mk
include $(TOPDIR)/include/version.mk

PKG_NAME:=ExtBoardDeamon
PKG_RELEASE:=${VERSION_NUMBER}-${VERSION_CODE}
PKG_MAINTAINER:=HEYAHONG <2229388563@qq.com>

USE_SOURCE_DIR:=$(shell pwd)/src
CMAKE_BINARY_SUBDIR:=build-${PKG_RELEASE}
PKG_INSTALL:=1

CMAKE_OPTIONS:= -DOPENWRT=ON  -DPACKAGE_VERSION=${PKG_RELEASE}

include $(INCLUDE_DIR)/package.mk
include $(INCLUDE_DIR)/cmake.mk


define Package/ExtBoardDeamon
  SECTION:=ExtBoard
  CATEGORY:= CoreBoard-001
  DEPENDS:= +libusb-1.0 +libserialport +libstdcpp +libc +librt +libpthread +dbus-cxx +jsoncpp +kmod-usb-acm +kmod-usb-net-rndis +kmod-usb-storage +kmod-usb-storage-uas
  TITLE:= Deamon for ExtBoard
endef

define Package/ExtBoardDeamon/install
	$(INSTALL_DIR) $(1)/sbin
	$(CP) $(PKG_INSTALL_DIR)/usr/bin/* $(1)/sbin/
	$(CP) ./files/* $(1)/
endef

$(eval $(call BuildPackage,ExtBoardDeamon))


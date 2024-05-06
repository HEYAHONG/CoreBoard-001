cmake_minimum_required(VERSION 3.20)

set(PROJECTNAME ExtBoardD)
project(${PROJECTNAME} C CXX ASM)
#添加可执行文件
add_executable(${PROJECTNAME})
#设置C++标准
set_property(TARGET ${PROJECTNAME} PROPERTY CXX_STANDARD 20)

if(DEFINED PACKAGE_VERSION)
add_definitions("-DPACKAGE_VERSION=${PACKAGE_VERSION}")
endif()

option(OPENWRT "build in openwrt" OFF)
if(OPENWRT)
add_definitions("-DOPENWRT")
endif()

#添加源代码
file(GLOB  C_FILES *.h *.cpp  *.c log/*.h log/*.cpp log/*.c)
target_sources(${PROJECTNAME} PUBLIC ${C_FILES})
target_include_directories(${PROJECTNAME}  PUBLIC ./ ./log/)


#安装
INSTALL(TARGETS ${PROJECTNAME}
       RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
       LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
       ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})

include(FindPkgConfig)

#pthread库
find_package( Threads REQUIRED)
target_link_libraries( ${PROJECTNAME} ${CMAKE_THREAD_LIBS_INIT} )

#libusb-1.0库
pkg_check_modules(LIBUSB REQUIRED IMPORTED_TARGET libusb-1.0)
target_link_libraries( ${PROJECTNAME}  PkgConfig::LIBUSB)

#libserialport库
pkg_check_modules(LIBSERIALPORT REQUIRED IMPORTED_TARGET libserialport)
target_link_libraries( ${PROJECTNAME}  PkgConfig::LIBSERIALPORT)

#jsoncpp库
pkg_check_modules(JSONCPP REQUIRED IMPORTED_TARGET jsoncpp)
target_link_libraries( ${PROJECTNAME}  PkgConfig::JSONCPP)

#libpopt库
pkg_check_modules(POPT REQUIRED IMPORTED_TARGET jsoncpp)
target_link_libraries( ${PROJECTNAME}  PkgConfig::POPT)

#dbus-cxx库
pkg_check_modules(DBUSCXX REQUIRED IMPORTED_TARGET dbus-cxx-2.0)
target_link_libraries( ${PROJECTNAME}  PkgConfig::DBUSCXX)



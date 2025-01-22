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
file(GLOB  C_FILES *.h *.cpp  *.c log/*.h log/*.cpp log/*.c dbus/*.h dbus/*.cpp dbus/*.c usb/*.h usb/*.cpp usb/*.c)
target_sources(${PROJECTNAME} PUBLIC ${C_FILES})
target_include_directories(${PROJECTNAME}  PUBLIC ./ ./log/ ./dbus ./usb)


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

#HCppBox
#设定HRC文件系统目录为fs
set(HRC_FS_ROOT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/fs/)
#添加3rdparty/HCppBox
file(REAL_PATH ${CMAKE_CURRENT_SOURCE_DIR} CMAKE_CURRENT_SOURCE_DIR_REAL_PATH)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR_REAL_PATH}/../../3rdparty/HCppBox/master/  HCppBox EXCLUDE_FROM_ALL)
#启用HCppBox、HRC
hcppbox_enable(${PROJECT_NAME})
hrc_enable(${PROJECT_NAME})


#添加包含CMakeLists.txt的子目录
file(GLOB SUBDIRS *)
foreach(SUBDIR ${SUBDIRS})
	if(IS_DIRECTORY ${SUBDIR})
		if(EXISTS ${SUBDIR}/CMakeLists.txt)
			add_subdirectory(${SUBDIR})
		endif()
	endif()
endforeach()


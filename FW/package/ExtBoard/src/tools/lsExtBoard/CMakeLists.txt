
add_executable(lsExtBoard)
file(GLOB  C_FILES *.h *.cpp  *.c)
target_sources(lsExtBoard PUBLIC ${C_FILES})
target_link_libraries( lsExtBoard  PkgConfig::JSONCPP)
target_link_libraries( lsExtBoard  PkgConfig::POPT)
target_link_libraries( lsExtBoard  PkgConfig::DBUSCXX)


#安装
INSTALL(TARGETS lsExtBoard
       RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
       LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
       ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})


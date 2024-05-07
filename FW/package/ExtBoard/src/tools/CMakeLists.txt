file(GLOB SUBDIRS *)
foreach(SUBDIR ${SUBDIRS})
    if(IS_DIRECTORY ${SUBDIR})
        if(EXISTS ${SUBDIR}/CMakeLists.txt)
            add_subdirectory(${SUBDIR})
        endif()
    endif()
endforeach()


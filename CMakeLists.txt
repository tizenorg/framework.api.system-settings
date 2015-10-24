
CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
SET(fw_name "capi-system-system-settings")

PROJECT(${fw_name})

SET(CMAKE_INSTALL_PREFIX /usr)
SET(PREFIX ${CMAKE_INSTALL_PREFIX})

SET(INC_DIR include)
INCLUDE_DIRECTORIES(${INC_DIR})

SET(requires "elementary ecore ecore-x ecore-file dlog vconf appcore-efl capi-base-common glib-2.0 gobject-2.0 fontconfig libxml-2.0 eventsystem bundle capi-appfw-application")
SET(pc_requires "capi-base-common")

IF(TIZEN_WEARABLE)
    ADD_DEFINITIONS(-DTIZEN_WEARABLE)
ENDIF(TIZEN_WEARABLE)
IF(TIZEN_MOBILE)
    ADD_DEFINITIONS(-DTIZEN_MOBILE)
ENDIF(TIZEN_MOBILE)

INCLUDE(FindPkgConfig)
pkg_check_modules(${fw_name} REQUIRED ${requires})
FOREACH(flag ${${fw_name}_CFLAGS})
    SET(EXTRA_CFLAGS "${EXTRA_CFLAGS} ${flag}")
ENDFOREACH(flag)

#SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${EXTRA_CFLAGS} -fPIC -Wall -Werror")
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${EXTRA_CFLAGS} -fPIC")
SET(CMAKE_C_FLAGS_DEBUG "-O0 -g")

IF("${ARCH}" STREQUAL "arm")
    ADD_DEFINITIONS("-DTARGET")
ENDIF("${ARCH}" STREQUAL "arm")

ADD_DEFINITIONS("-DPREFIX=\"${CMAKE_INSTALL_PREFIX}\"")
ADD_DEFINITIONS("-DSLP_DEBUG")

SET(CMAKE_EXE_LINKER_FLAGS "-Wl,--as-needed -Wl,--rpath=/usr/lib")

aux_source_directory(src SOURCES)
ADD_LIBRARY(${fw_name} SHARED ${SOURCES})

TARGET_LINK_LIBRARIES(${fw_name} ${${fw_name}_LDFLAGS})

SET_TARGET_PROPERTIES(${fw_name}
     PROPERTIES
     VERSION ${FULLVER}
     SOVERSION ${MAJORVER}
     CLEAN_DIRECT_OUTPUT 1
)

# Test application - TC
#ADD_EXECUTABLE(test TC/test.c)
#TARGET_LINK_LIBRARIES(test ${fw_name})

#SET_TARGET_PROPERTIES(test PROPERTIES OUTPUT_NAME test_system_settings)
#INSTALL(TARGETS test DESTINATION /usr/local/bin)
#---------------------------------------------------------------------

# Test application - TC_gui
ADD_EXECUTABLE(test_gui TC_gui/main.c)

INCLUDE(FindPkgConfig)
pkg_check_modules(test_gui REQUIRED "elementary appcore-efl ecore-imf ecore-x ecore-x eina ecore ecore-evas ecore-input")
FOREACH(flag ${test_gui_CFLAGS})
    SET(EXTRA_CFLAGS "${EXTRA_CFLAGS} ${flag}")
ENDFOREACH(flag)

TARGET_LINK_LIBRARIES(test_gui ${fw_name})
SET_TARGET_PROPERTIES(test_gui PROPERTIES OUTPUT_NAME test_system_settings_gui)
INSTALL(TARGETS test_gui DESTINATION /usr/local/bin)
#---------------------------------------------------------------------


INSTALL(TARGETS ${fw_name} DESTINATION lib)
INSTALL(
        DIRECTORY ${INC_DIR}/ DESTINATION include/system
        FILES_MATCHING
        PATTERN "*_private.h" EXCLUDE
        PATTERN "${INC_DIR}/*.h"
        )

SET(PC_NAME ${fw_name})
SET(PC_REQUIRED ${pc_requires})
SET(PC_LDFLAGS -l${fw_name})
SET(PC_CFLAGS -I\${includedir}/system)

CONFIGURE_FILE(
    capi-system-system-settings.pc.in
    ${CMAKE_CURRENT_SOURCE_DIR}/${fw_name}.pc
    @ONLY
)
INSTALL(FILES ${CMAKE_CURRENT_SOURCE_DIR}/${fw_name}.pc DESTINATION lib/pkgconfig)

# INSTALL (TARGETS test DESTINATION bin)

IF(UNIX)

ADD_CUSTOM_TARGET (distclean @echo cleaning for source distribution)
ADD_CUSTOM_COMMAND(
        DEPENDS clean 
        COMMENT "distribution clean"
        COMMAND find
        ARGS    . 
        -not -name config.cmake -and \(
        -name tester.c -or
        -name Testing -or
        -name CMakeFiles -or
        -name cmake.depends -or
        -name cmake.check_depends -or
        -name CMakeCache.txt -or
        -name cmake.check_cache -or
        -name *.cmake -or
        -name Makefile -or
        -name core -or
        -name core.* -or
        -name gmon.out -or
        -name install_manifest.txt -or
        -name *.pc -or
        -name *~ \)
        | grep -v TC | xargs rm -rf
        TARGET  distclean
        VERBATIM
)

ENDIF(UNIX)


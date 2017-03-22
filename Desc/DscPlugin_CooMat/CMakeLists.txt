cmake_minimum_required(VERSION 2.6)

#
# проверка Unicode (UTF-8):
# 偉大和強大的俄語。
# اللغة الروسية العظمى والأقوياء.
# Η μεγάλη και πανίσχυρη ρωσική γλώσσα.
# השפה הרוסיה הגדולה והעצומה.
# 大いなるロシア語。
# 위대하고 강력한 러시아어 언어입니다.
# Wielki i potężny język rosyjski.
#

PROJECT(DscPlugin_CooMat)

set( TARGET_0 "dscplugin_coomatrix" )

if(NOT CMAKE_BUILD_TYPE)
    #set(CMAKE_BUILD_TYPE "Release")
    set(CMAKE_BUILD_TYPE "Debug")
endif()

set(PLATFORM "x32")
if("${CMAKE_SIZEOF_VOID_P}" STREQUAL "8")
    set(PLATFORM "x64")
endif()

set(BUILD_PREFIX "${CMAKE_BUILD_TYPE}_${PLATFORM}")
message("build prefix=[${BUILD_PREFIX}]")

if(UNIX)
    SET(CMAKE_CXX_FLAGS "-fPIC")
else()
	ADD_DEFINITIONS(-DDSCPLUGIN_COOMATRIX_LIBRARY)
endif()

FIND_PACKAGE( OpenCV REQUIRED )

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
find_package(Qt5Widgets REQUIRED)
##find_package(Qt5Core REQUIRED)
##find_package(Qt5Concurrent REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

##include_directories(${Qt5Widgets_INCLUDE_DIRS})
include_directories(${Qt5Core_INCLUDE_DIRS})
##include_directories(${Qt5Concurrent_INCLUDE_DIRS})
##add_definitions(${Qt5Widgets_DEFINITIONS})
##set(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
##SET(QT_USE_QTOPENGL TRUE)

SET(PRJ_SRC	src/dscplugincoomatrix.cpp
		src/lib_descriptor2sl.cpp)
SET(PRJ_HDR	include/dscplugincoomatrix_global.h
		include/dscplugincoomatrix.h
		include/dscplugininterface.h
		include/lib_descriptor2sl.h)

SET(PRJ_MOC include/dscplugincoomatrix.h)
#QT5_WRAP_CPP(MOC_HDR ${PRJ_HDR})

ADD_DEFINITIONS(-DQT_PLUGIN)
ADD_DEFINITIONS(-DQT_SHARED)
ADD_DEFINITIONS(-DQT_NO_DEBUG)

ADD_LIBRARY( ${TARGET_0} SHARED		${PRJ_SRC} ${PRJ_HDR} ${MOC_HDR})
TARGET_LINK_LIBRARIES( ${TARGET_0}	${Qt5Core_LIBRARIES} ${OpenCV_LIBS})

##get_cmake_property(_variableNames VARIABLES)
##foreach (_variableName ${_variableNames})
##   message(STATUS "${_variableName}=${${_variableName}}")
##endforeach()

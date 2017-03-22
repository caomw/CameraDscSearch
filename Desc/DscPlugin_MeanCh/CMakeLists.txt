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

PROJECT(DscPlugin_MeanCh)

set( TARGET_0 "dscplugin_meanch" )
set( TARGET_1 "dscplugin_meanch_test" )

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
	ADD_DEFINITIONS(-DDSCPLUGIN_MEANCH_LIBRARY)
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

SET(PRJ_SRC	src/dscplugin_meanch.cpp)
SET(PRJ_HDR	include/dscplugin_meanch_global.h
		include/dscplugin_meanch.h
		include/dscplugininterface.h)

SET(PRJ_MOC include/dscplugin_meanch.h)
#QT5_WRAP_CPP(MOC_HDR ${PRJ_HDR})

##TARGET_ADD_DEFINITIONS(${TARGET_0} -DQT_PLUGIN)
##TARGET_ADD_DEFINITIONS(${TARGET_0} -DQT_SHARED)
##TARGET_ADD_DEFINITIONS(${TARGET_0} -DQT_NO_DEBUG)


ADD_LIBRARY( ${TARGET_0} SHARED		${PRJ_SRC} ${PRJ_HDR} ${MOC_HDR})
SET_TARGET_PROPERTIES( ${TARGET_0} PROPERTIES DEFINITIONS -DQT_PLUGIN -DQT_SHARED -DQT_NO_DEBUG)
TARGET_LINK_LIBRARIES( ${TARGET_0}	${Qt5Core_LIBRARIES} ${OpenCV_LIBS})

set(TEST_SRC "main.cpp" ${PRJ_SRC} ${PRJ_HDR})
add_executable(${TARGET_1}		${TEST_SRC})
target_link_libraries(${TARGET_1}	${Qt5Core_LIBRARIES} ${OpenCV_LIBS})

##get_cmake_property(_variableNames VARIABLES)
##foreach (_variableName ${_variableNames})
##   message(STATUS "${_variableName}=${${_variableName}}")
##endforeach()

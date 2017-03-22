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

PROJECT(CameraDscSearch)

set( TARGET_0 "CameraDscSearch" )

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Release")
    #set(CMAKE_BUILD_TYPE "Debug")
endif()

set(PLATFORM "x32")
if("${CMAKE_SIZEOF_VOID_P}" STREQUAL "8")
    set(PLATFORM "x64")
endif()

set(BUILD_PREFIX "${CMAKE_BUILD_TYPE}_${PLATFORM}")
message("build prefix=[${BUILD_PREFIX}]")


FIND_PACKAGE( OpenCV REQUIRED )
##FIND_PACKAGE( OpenGL REQUIRED )

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
##find_package(Qt5OpenGL REQUIRED)
find_package(Qt5Concurrent REQUIRED)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${Qt5Widgets_INCLUDE_DIRS})
include_directories(${Qt5Core_INCLUDE_DIRS})
##include_directories(${Qt5OpenGL_INCLUDE_DIRS})
include_directories(${Qt5Concurrent_INCLUDE_DIRS})

add_definitions(${Qt5Widgets_DEFINITIONS})
set(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

##SET(QT_USE_QTOPENGL TRUE)

SET(PRJ_SRC	main.cpp mainwindow.cpp src/model2.cpp)
SET(PRJ_HDR	mainwindow.h include/model2.h include/dscplugininterface.h)


SET(PRJ_FORMS	mainwindow.ui )

set( LIB_QTH	"lib_qthelper"     )
set( LIB_UTIL	"lib_utils"        )


add_library( ${LIB_LUT}  STATIC "src/${LIB_QTH}.cpp"  "include/${LIB_QTH}.h" )
add_library( ${LIB_UTIL} STATIC "src/${LIB_UTIL}.cpp" "include/${LIB_UTIL}.h")

QT5_WRAP_UI(PRJ_FORMS_HDR	${PRJ_FORMS})
##QT5_ADD_RESOURCES(PRJ_RES_RCC	${PRJ_RES})


##  ${PRJ_RES_RCC}

ADD_EXECUTABLE( ${TARGET_0}_${BUILD_PREFIX}		${PRJ_SRC} ${PRJ_HDR} ${PRJ_HDR_MOC} ${PRJ_FORMS_HDR} ${PRJ_RES_RCC})
TARGET_LINK_LIBRARIES( ${TARGET_0}_${BUILD_PREFIX} ${LIB_LUT} ${LIB_UTIL} ${Qt5Widgets_LIBRARIES} ${Qt5OpenGL_LIBRARIES} ${Qt5Core_LIBRARIES} ${OpenCV_LIBS})

##get_cmake_property(_variableNames VARIABLES)
##foreach (_variableName ${_variableNames})
##   message(STATUS "${_variableName}=${${_variableName}}")
##endforeach()

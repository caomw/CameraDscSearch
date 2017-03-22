#-------------------------------------------------
#
# Project created by QtCreator 2013-06-17T11:02:14
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET      = CameraDscSearch
TEMPLATE    = app

INCLUDEPATH += include/

unix {
    # OpenCV
    INCLUDEPATH     += /home/ar/dev/opencv-2.4.6.1-release/include/opencv /home/ar/dev/opencv-2.4.6.1-release/include
    LIBS            += -L/home/ar/dev/opencv-2.4.6.1-release/lib  -lopencv_calib3d -lopencv_contrib -lopencv_core -lopencv_features2d -lopencv_flann -lopencv_gpu -lopencv_highgui -lopencv_imgproc -lopencv_legacy -lopencv_ml -lopencv_nonfree -lopencv_objdetect -lopencv_photo -lopencv_stitching -lopencv_superres -lopencv_ts -lopencv_video -lopencv_videostab
#    INCLUDEPATH     += /home/ar/dev/opencv-2.4.6.1-cuda-release/include/opencv /home/ar/dev/opencv-2.4.6.1-cuda-release/include
#    LIBS            += -L/home/ar/dev/opencv-2.4.6.1-cuda-release/lib  -lopencv_calib3d -lopencv_contrib -lopencv_core -lopencv_features2d -lopencv_flann -lopencv_gpu -lopencv_highgui -lopencv_imgproc -lopencv_legacy -lopencv_ml -lopencv_nonfree -lopencv_objdetect -lopencv_photo -lopencv_stitching -lopencv_superres -lopencv_ts -lopencv_video -lopencv_videostab
} else {
    # opencv
#    INCLUDEPATH += e:/dev/opencv/build/include/opencv e:/dev/opencv/build/include
#    LIBS        += -Le:/dev/opencv/build/x86/vc10/lib  -lopencv_core242d -lopencv_highgui242d -lopencv_imgproc242d
    INCLUDEPATH += c:/dev/opencv/build/include c:/dev/opencv/build/include/opencv
#    LIBS        += -Lc:/dev/opencv/build/x86/vc10/lib  -lopencv_core246d -lopencv_highgui246d -lopencv_imgproc246d
    LIBS        += -Lc:/dev/opencv/build/x86/vc10/lib  -lopencv_core246 -lopencv_highgui246 -lopencv_imgproc246
}

########################
SOURCES +=  main.cpp mainwindow.cpp \
    src/lib_utils.cpp \
    src/lib_qthelper.cpp \
    src/model2.cpp

HEADERS  += mainwindow.h \
    include/lib_utils.h \
    include/lib_qthelper.h \
    include/dscplugininterface.h \
    include/model2.h

FORMS    += mainwindow.ui

#-------------------------------------------------
#
# Project created by QtCreator 2017-07-05T14:23:27
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtOpencv2
TEMPLATE = app

INCLUDEPATH += /usr/local/include/opencv2
INCLUDEPATH += /usr/include/opencv
LIBS +=  -L/usr/local/lib/ \
-lopencv_core \
-lopencv_imgproc \
-lopencv_highgui \
-lopencv_ml \
-lopencv_imgcodecs \
-lopencv_video \
-lopencv_videoio \
-lopencv_features2d \
-lopencv_calib3d \
-lopencv_objdetect \
-lopencv_contrib \
-lopencv_legacy \
-lopencv_flann


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

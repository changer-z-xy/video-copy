#-------------------------------------------------
#
# Project created by QtCreator 2013-03-06T15:19:46
#
#-------------------------------------------------

QT       += core gui
QT += webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = videoCopy
TEMPLATE = app
CONFIG -= app_bundle

SOURCES += main.cpp\
    customwidget.cpp \
    customtoolbutton.cpp \
    customtoolbar.cpp \
    customtitlebar.cpp \
    customstatusbar.cpp \
    customcontentwidget.cpp \
#    arrowheadaxis.cpp \
    contentpage.cpp \
#    histogramwidget.cpp \
    mplayerwidget.cpp \
#    histogramitem.cpp
    key_frame.cpp \
    Get_Frame.cpp \
    bm_process.cpp \
    cmpthread.cpp \
    custommainwidget.cpp \
    cmpoutputwidget.cpp

HEADERS  += \
    customwidget.h \
    customtoolbutton.h \
    customtoolbar.h \
    customtitlebar.h \
    customstatusbar.h \
    customcontentwidget.h \
#    arrowheadaxis.h \
    contentpage.h \
#    histogramwidget.h \
    mplayerwidget.h \
#    histogramitem.h
    key_frame.h \
    get_frame.h \
    bm_process.h \
    abc.h \
    cmpthread.h \
    custommainwidget.h \
    cmpoutputwidget.h \
    videoCopy.h

INCLUDEPATH += C:\opencv\install\include \
				C:\opencv\install\include\opencv \
				C:\opencv\install\include\opencv2

LIBS += -LC:/opencv/install/lib \
		-llibopencv_core244d \
		-llibopencv_highgui244d \
		-llibopencv_imgproc244d

RESOURCES += \
    resources.qrc


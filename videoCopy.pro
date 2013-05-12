#-------------------------------------------------
#
# Project created by QtCreator 2013-05-12T21:24:17
#
#-------------------------------------------------

QT       += core gui
QT += webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = videoCopy
TEMPLATE = app


SOURCES += main.cpp \
    cmpoutputevent.cpp \
    cmpconsignor.cpp \
    bm_process.cpp \
    contentpage.cpp \
    cmpworker.cpp \
    cmptaskevent.cpp \
    cmppoolmanager.cpp \
    cmpoutputwidget.cpp \
    Get_Frame.cpp \
    customwidget.cpp \
    customwebpage.cpp \
    customtoolbutton.cpp \
    customtoolbar.cpp \
    customtitlebar.cpp \
    customstatusbar.cpp \
    custommainwidget.cpp \
    customcontentwidget.cpp \
    mplayerwidget.cpp \
    key_frame.cpp

HEADERS  += cmpevent.h \
    cmpconsignor.h \
    bm_process.h \
    abc.h \
    contentpage.h \
    cmpworker.h \
    cmptaskevent.h \
    cmppoolmanager.h \
    cmpoutputwidget.h \
    cmpoutputevent.h \
    get_frame.h \
    customwidget.h \
    customwebpage.h \
    customtoolbutton.h \
    customtoolbar.h \
    customtitlebar.h \
    customstatusbar.h \
    custommainwidget.h \
    customcontentwidget.h \
    videoCopy.h \
    mplayerwidget.h \
    key_frame.h

INCLUDEPATH += C:\opencv\install\include \
				C:\opencv\install\include\opencv \
				C:\opencv\install\include\opencv2

LIBS += -LC:/opencv/install/lib \
		-llibopencv_core244d \
		-llibopencv_highgui244d \
		-llibopencv_imgproc244d

RESOURCES += \
    resources.qrc

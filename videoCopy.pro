#-------------------------------------------------
#
# Project created by QtCreator 2013-03-06T15:19:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = videoCopy
TEMPLATE = app


SOURCES += main.cpp\
    customwidget.cpp \
    customtoolbutton.cpp \
    customtoolbar.cpp \
    customtitlebar.cpp \
    customstatusbar.cpp \
    customcontentwidget.cpp \
    contentpage1.cpp \
    histgramwidget.cpp

HEADERS  += \
    customwidget.h \
    customtoolbutton.h \
    customtoolbar.h \
    customtitlebar.h \
    customstatusbar.h \
    customcontentwidget.h \
    contentpage1.h \
    histgramwidget.h

INCLUDEPATH += C:\opencv\install\include \
				C:\opencv\install\include\opencv

LIBS += -LC:/opencv/install/lib \
		-llibopencv_core244d \
		-llibopencv_highgui244d \
		-llibopencv_imgproc244d

RESOURCES += \
    resources.qrc

FORMS +=

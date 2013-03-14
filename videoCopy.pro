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
        widget.cpp \
    opencvvideobox.cpp

HEADERS  += widget.h \
    opencvvideobox.h

INCLUDEPATH += C:\opencv\install\include \
				C:\opencv\install\include\opencv

LIBS += -LC:/opencv/install/lib \
		-llibopencv_core244d \
		-llibopencv_highgui244d \
		-llibopencv_imgproc244d

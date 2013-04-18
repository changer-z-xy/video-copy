#ifndef CONTENTPAGE1_H
#define CONTENTPAGE1_H

#include <QWidget>
#include <QPainter>
#include <QFileDialog>
#include <QHBoxLayout>
#include <QGridLayout>
#include <cstdlib>
#include <cstdio>
#include <QDebug>
//#include "histogramwidget.h"
//#include "histogram.h"
#include "opencvvideobox.h"

class ContentPage : public QWidget
{
    Q_OBJECT
    
public:
    ContentPage( QWidget *parent = 0 );
public slots:
    void moveToLeft( int x );
};

#endif // CONTENTPAGE1_H

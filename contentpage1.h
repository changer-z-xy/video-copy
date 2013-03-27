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
#include "histgramwidget.h"

class ContentPage1 : public QWidget
{
    Q_OBJECT
    
public:
    ContentPage1( QWidget *parent = 0 );
    ~ContentPage1();
protected:
    void paintEvent( QPaintEvent *event );
private slots:

private:
    HistgramWidget *histView;
};

#endif // CONTENTPAGE1_H

#ifndef HISTGRAM_H
#define HISTGRAM_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QList>
#include <QDebug>
#include "arrowheadaxis.h"

class Histogram : public QGraphicsView
{
    Q_OBJECT
public:
    explicit Histogram( int cntColumns,
                       double colWidth = 10,
                       QList<QGraphicsRectItem *> *cols = NULL,
                       QWidget *parent = 0 );
    void setColumns( QList<double> *colHeight,
                     QList<double> *colPos );
    void setColumn( int i, double height, double pos = -1 );
signals:
    
public slots:

private:
    QGraphicsScene *myScene;
    QList<QGraphicsRectItem *> *columns;
    int cntColumns;
    double columnWidth;
    ArrowHeadAxis *xAxis;
    ArrowHeadAxis *yAxis;
};

#endif // HISTGRAM_H

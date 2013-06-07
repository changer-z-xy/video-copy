#ifndef HISTGRAM_H
#define HISTGRAM_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QList>
#include <QDebug>
#include "arrowheadaxis.h"

class HistogramItem : public QGraphicsItem
{
    Q_OBJECT
public:
    explicit HistogramItem( int cntColumns,
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
    QGraphicsItemGroup *columns;
//    QGraphicsRectItem *
    ArrowHeadAxis *xAxis;
    ArrowHeadAxis *yAxis;
    int cntColumns;
};

#endif // HISTGRAM_H

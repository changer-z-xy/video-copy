#ifndef HistgramWidget_H
#define HistgramWidget_H

#include <QWidget>
#include <QGraphicsView>
#include <QPainter>
#include <QDebug>
#include <cstdlib>
#include <algorithm>

class HistogramWidget : public QGraphicsView
{
    Q_OBJECT
public:
    explicit HistogramWidget(QWidget *parent = 0);
    HistogramWidget( QWidget *parent, int *histogram );
    ~HistogramWidget();
protected:
    void paintEvent( QPaintEvent *event );
private:
    int *histArray;
    int *histSeg;
    int cntSegs;
    int segLength;
    int colLength;
    int spaceLength;
signals:
    
public slots:
    
};

#endif // HistgramWidget_H

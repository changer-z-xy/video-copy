#ifndef ARROWHEAD_H
#define ARROWHEAD_H

#include <QGraphicsItem>
#include <QGraphicsTextItem>
#include <QPolygonF>
#include <QLineF>
#include <QRectF>
#include <QPainter>
#include <QPainterPath>
#include <QDebug>

class ArrowHeadAxis : public QGraphicsItem
{
public:
    ArrowHeadAxis( double axisLength,
                   QVector<double> *graduationsPos = NULL );
    QRectF boundingRect() const;
    virtual void paint( QPainter *painter,
                        const QStyleOptionGraphicsItem *option,
                        QWidget *widget );
    void setGraduations( QVector<double> *graduationsPos,
                         int direction = -1 );
    void setAxisLength( double length );
    double getAxisLength();
    void setMaxValue( double value );
    double getMaxValue();
    QPainterPath shape() const;

private:
    QPolygonF *arrowHead;
    QLineF *axisLine;
    double maxValue;
    QVector<QLineF> graduations;
};

#endif // ARROWHEAD_H

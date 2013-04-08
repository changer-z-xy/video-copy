#include "arrowheadaxis.h"

ArrowHeadAxis::ArrowHeadAxis( double axisLength, QVector<double> *graduationsPos )
{
    // create axis
    axisLine = new QLineF;
    axisLine->setPoints( QPointF( 0, 0 ),
                        QPointF( axisLength, 0 ) );
    arrowHead = new QPolygonF;
    arrowHead->push_back( QPointF( axisLength, 5 ) );
    arrowHead->push_back( QPointF( axisLength, -5 ) );
    arrowHead->push_back( QPointF( axisLength + 10, 0 ) );

    // new graduationTexts
    graduationTexts = new QGraphicsItemGroup( this );

    // set graduations
    setGraduations( graduationsPos );
}

QRectF ArrowHeadAxis::boundingRect() const
{
    return QRectF( 0, 5, axisLine->length() + 10, 10 );
}

QPainterPath ArrowHeadAxis::shape() const
{
    QPainterPath myPath;
    myPath.addPolygon( *arrowHead );
    return myPath;
}

QGraphicsItemGroup * ArrowHeadAxis::getGraduationTexts()
{
    return graduationTexts;
}

void ArrowHeadAxis::paint(QPainter *painter,
                          const QStyleOptionGraphicsItem *option,
                          QWidget *widget = 0 )
{
    QBrush myBrush( QColor::fromRgb( 0, 0, 0 ) );
    painter->setBrush( myBrush );
    painter->drawLine( *axisLine );
    if ( !graduations.isEmpty() ) {
        for ( int i = 0; i < graduations.size(); ++ i )
            painter->drawLine( graduations.at( i ) );
    }
    painter->drawPolygon( *arrowHead );
}

void ArrowHeadAxis::setGraduations( QVector<double> *graduationsPos,
                                    int direction )
{
    if ( graduationsPos ) {
        if ( graduations.size() != graduationsPos->size() ) {
            graduations.resize( graduationsPos->size() );
        }
        for ( int i = 0, sz = graduationsPos->size(); i < sz; ++ i ) {
            // set graduations with height 5
            // graduations.at( i ) can not be used because it is a const function
            graduations[ i ].setLine( graduationsPos->at( i ), 0,
                                      graduationsPos->at( i ), direction * 5 );
        }
    }
}

void ArrowHeadAxis::setAxisLength( double length )
{
    axisLine->setLength( length );
    (*arrowHead)[ 0 ].setX( length );
    (*arrowHead)[ 1 ].setX( length );
    (*arrowHead)[ 2 ].setX( length + 10 );
}

double ArrowHeadAxis::getAxisLength()
{
    return axisLine->length();
}

double ArrowHeadAxis::getMaxValue()
{
    return maxValue;
}

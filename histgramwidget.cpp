#include "histgramwidget.h"

HistgramWidget::HistgramWidget( QWidget *parent, int *histgram ):
    QWidget( parent ), histArray( histgram )
{
    resize( 400, 400 );
    histSeg = new int[ 256 ];
    for ( size_t i = 0; i < 256; ++ i )
        histSeg[ i / 8 ] += histArray[ i ];

}

HistgramWidget::~HistgramWidget()
{
}

void HistgramWidget::paintEvent( QPaintEvent *event )
{
    QPainter *myPainter = new QPainter( this );
    myPainter->fillRect( rect(), Qt::white );
    myPainter->setBrush( Qt::blue );
    int highest = -1, segLength = 8;
    for ( size_t i = 0; i < 32; ++ i )
        highest = std::max( highest, histSeg[ i ] );
    for ( size_t i = 0; i < 32; ++ i )
        myPainter->drawRect( i * 8, height() - (double)histSeg[ i ] / highest * height(),
                             segLength, ( (double)histSeg[ i ] / highest ) * height() );
}

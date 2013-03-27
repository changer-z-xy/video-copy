#include "histgramwidget.h"

HistgramWidget::HistgramWidget( QWidget *parent, int *histgram = NULL ):
    QWidget( parent ), histArray( histgram )
{
    setFixedSize( 600, 400 );
    segLength = 10;
    cntSegs = 250 / segLength;
    histSeg = new int[ 250 ];
    spaceLength = 0;
    colLength = ( width() - cntSegs * spaceLength ) / cntSegs;

    if ( histgram ) {
        for ( size_t i = 0; i < 250; ++ i ) {
            histSeg[ i ] = 0;
            histSeg[ i / segLength ] += histArray[ i ];
        }
    } else {
        histgram = new int[ 250 ];
    }

}

HistgramWidget::~HistgramWidget()
{
}

void HistgramWidget::paintEvent( QPaintEvent *event )
{
    QPainter *myPainter = new QPainter( this );
    myPainter->fillRect( rect(), Qt::white );
    int highest = -1;
    for ( size_t i = 0; i < cntSegs; ++ i )
        highest = std::max( highest, histSeg[ i ] );

    // set lineargradient brush
    QLinearGradient histViewGradient( rect().topLeft(), rect().bottomRight() );
    histViewGradient.setColorAt( 0, QColor( 136, 136, 136, 150 ) );
    histViewGradient.setColorAt( 0.5, QColor( 204, 204, 204, 180 ) );
    histViewGradient.setColorAt( 1, QColor( 190, 190, 190, 200 ) );
    QBrush histViewBrush( histViewGradient );
    myPainter->setBrush( histViewBrush );
    for ( int i = 0; i < cntSegs; ++ i ) {
        int tmpY = height() - (double)histSeg[ i ] / highest * ( height() - 40 );
        int tmpH = ( (double)histSeg[ i ] / highest ) * ( height() - 40 );
        myPainter->fillRect( i * colLength + spaceLength, tmpY,
                             segLength, tmpH, histViewBrush );
        myPainter->drawText( i * colLength + spaceLength, tmpY - 20,
                             QString("%1").arg(histSeg[ i ]) );
    }
}

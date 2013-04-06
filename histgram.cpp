#include "histgram.h"

Histgram::Histgram( int cntColumns, double colWidth,
                    QList<QGraphicsRectItem *> *cols,
                    QWidget *parent )
    : cntColumns( cntColumns ),
      columnWidth( colWidth ),
      columns( cols ),
      QGraphicsView( parent )
{
    myScene = new QGraphicsScene( this );

    // add x and y axis
    QVector<double> graduationsPos;
    for ( int i = 0; i < 50; ++ i )
        graduationsPos.push_back( columnWidth * i );
    xAxis = new ArrowHeadAxis( cntColumns * columnWidth );
    xAxis->setGraduations( &graduationsPos );
    yAxis = new ArrowHeadAxis( 200 );
    yAxis->setRotation( -90 );
    myScene->addItem( xAxis );
    myScene->addItem( yAxis );

    // if columns was NULL then new QGraphicsRectItem
    if ( columns == NULL ) {
        columns = new QList<QGraphicsRectItem *>;
        for ( int i = 0; i < cntColumns; ++ i )
            columns->push_back( new QGraphicsRectItem( 0, 0, columnWidth, 0 ) );
    }
    // add columns
    for ( int i = 0; i < columns->size(); ++ i )
        myScene->addItem( columns->at( i ) );

    // set myScene as the view's scene
    setScene( myScene );
}

void Histgram::setColumns( QList<double> *colHeight,
                           QList<double> *colPos )
{
    double maxColHeight = 0, maxColPos = 0;
    // set columns' height
    if ( colHeight != NULL && colPos != NULL &&
         colHeight->size() == columns->size() &&
         colPos->size() == columns->size() ) {
        for ( int i = 0, sz = columns->size(); i < sz; ++ i ) {
            // get max colHeight and max colPos
            // so that we can decide how to display columns
            maxColHeight = std::max( colHeight->at( i ), maxColHeight );
            maxColPos = std::max( colPos->at( i ), maxColPos );
        }
        for ( int i = 0, sz = columns->size(); i < sz; ++ i ) {
            // set real position at xAxis but transformed heights
            setColumn( i, -colHeight->at( i ) / maxColHeight * yAxis->getAxisLength(),
                       colPos->at( i ) );
            columns->at( i )->setToolTip( QString( "%1" ).arg( colHeight->at( i ) ) );
        }
    }
}

void Histgram::setColumn( int i, double height, double pos )
{
    // if pos < 0, for instance -1, we just let it keep its position
    if ( pos >= 0 )
        columns->at( i )->setPos( pos, 0 );
    // set real height
    columns->at( i )->setRect( columns->at( i )->rect().x(),
                               columns->at( i )->rect().y(),
                               columns->at( i )->rect().width(),
                               height );
    // set brush
    QLinearGradient colGradient( columns->at( i )->rect().topLeft(),
                                 columns->at( i )->rect().bottomRight() );
    colGradient.setColorAt( 0, QColor( 136, 136, 136, 150 ) );
    colGradient.setColorAt( 0.5, QColor( 204, 204, 204, 180 ) );
    colGradient.setColorAt( 1, QColor( 190, 190, 190, 200 ) );
    columns->at( i )->setBrush( QBrush( colGradient ) );
}

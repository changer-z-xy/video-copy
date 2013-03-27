#include "contentpage1.h"

ContentPage1::ContentPage1(QWidget *parent)
    : QWidget(parent)
{
    int myTestArr[ 256 ];
    for ( int i = 0; i < 250; ++ i )
        myTestArr[ i ] = i;
    histView = new HistgramWidget( this, myTestArr );
    QHBoxLayout *contentLayout = new QHBoxLayout( this );
    contentLayout->addWidget( histView );
    contentLayout->setMargin( 0 );
    contentLayout->setSpacing( 0 );
}

ContentPage1::~ContentPage1()
{
}

void ContentPage1::paintEvent( QPaintEvent *event )
{
    QPainter *myPainter = new QPainter( this );
    QLinearGradient *page1Gradient = new QLinearGradient( rect().topLeft(), rect().bottomRight() );
    page1Gradient->setColorAt( 0, QColor( 100, 100, 120, 50 ) );
    page1Gradient->setColorAt( 0.5, QColor( 180, 180, 200, 100 ) );
    page1Gradient->setColorAt( 1, QColor( 170, 170, 190, 80 ) );
    myPainter->fillRect( rect(), QBrush( *page1Gradient ) );
}

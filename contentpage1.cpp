#include "contentpage1.h"

ContentPage1::ContentPage1(QWidget *parent)
    : QWidget(parent)
{
    setContentsMargins( 0, 0, 0, 0 );
    int myTestArr[ 256 ];
    histView = new HistgramWidget( this, myTestArr );
}

ContentPage1::~ContentPage1()
{
}

void ContentPage1::paintEvent( QPaintEvent *event )
{
}

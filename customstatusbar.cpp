#include "customstatusbar.h"

CustomStatusBar::CustomStatusBar(QObject *parent)
{
    setFixedHeight( STATUSBAR_HEIGHT );
}

CustomStatusBar::~CustomStatusBar()
{

}

void CustomStatusBar::paintEvent( QPaintEvent *event )
{
}

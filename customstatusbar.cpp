#include "videoCopy.h"

CustomStatusBar::CustomStatusBar(QWidget *parent) : QWidget(parent)
{
    setFixedHeight( STATUSBAR_HEIGHT );
    setMouseTracking(true);
}

CustomStatusBar::~CustomStatusBar()
{

}

void CustomStatusBar::paintEvent( QPaintEvent *event )
{
}

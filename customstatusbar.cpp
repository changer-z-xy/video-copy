#include "videoCopy.h"

CustomStatusBar::CustomStatusBar(QWidget *parent) : QWidget(parent)
{
    setMouseTracking(true);
}

CustomStatusBar::~CustomStatusBar()
{

}

void CustomStatusBar::paintEvent( QPaintEvent *event )
{
}

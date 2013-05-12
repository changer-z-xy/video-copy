#include "customstatusbar.h"

const int STATUSBAR_HEIGHT = 30;

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

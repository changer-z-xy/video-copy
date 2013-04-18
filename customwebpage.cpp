#include "customwebpage.h"

CustomWebPage::CustomWebPage(QWidget *parent) :
    QWebView(parent)
{
}

void CustomWebPage::resizeEvent(QResizeEvent *event)
{
    setFixedSize( event->size() );
    QWebView::resizeEvent( event );
}

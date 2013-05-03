#include "contentpage.h"

ContentPage::ContentPage(QWidget *parent)
    : QWidget(parent)
{

}

void ContentPage::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    int startOpacity = 50;
    int medianOpacity = 100;
    int endOpacity = 80;
    QLinearGradient mainWidgetGradient( rect().topLeft(), rect().bottomRight() );
    mainWidgetGradient.setColorAt( 0, QColor( 136, 136, 136, startOpacity ) );
    mainWidgetGradient.setColorAt( 0.5, QColor( 204, 204, 204, medianOpacity ) );
    mainWidgetGradient.setColorAt( 1, QColor( 190, 190, 190, endOpacity ) );
    QBrush mainWidgetBrush( mainWidgetGradient );
    painter.setPen( QPen( Qt::NoBrush, 1 ) );
    painter.setBrush( mainWidgetBrush );
    painter.drawRoundedRect( rect(), 5, 5 );
}

void ContentPage::moveToLeft( int x )
{
    move( x, 0 );
}

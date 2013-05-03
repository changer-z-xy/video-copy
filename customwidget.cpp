#include "customwidget.h"

CustomWidget::CustomWidget(QWidget *parent)
    : QFrame(parent)
{
    // set no system title bar
    setWindowFlags( Qt::FramelessWindowHint );
    // set mouse tracking
    setMouseTracking( true );
}

void CustomWidget::paintEvent(QPaintEvent *)
{
    QBitmap objBitmap( size() );
    QPainter *painter = new QPainter( this );
    QLinearGradient mainWidgetGradient( rect().topLeft(), rect().bottomRight() );
    mainWidgetGradient.setColorAt( 0, QColor( 0, 136, 204, 180 ) );
    mainWidgetGradient.setColorAt( 0.5, QColor( 0, 109, 204, 255 ) );
    mainWidgetGradient.setColorAt( 1, QColor( 0, 68, 205, 220 ) );
    painter->fillRect( rect(), mainWidgetGradient );
    painter->end();
    painter->begin( &objBitmap );
    painter->fillRect( rect(), Qt::white );
    painter->setBrush( QColor( 0, 0, 0 ) );
    painter->drawRoundedRect( rect(), 10, 10 );
    setMask( objBitmap );
    painter->end();
}

void CustomWidget::showMaxRestore()
{
    if ( isMaximized() ) {
        this->showNormal();
    }
    else {
        this->showMaximized();
    }
}

void CustomWidget::mousePressEvent(QMouseEvent *event)
{
    if ( event->button() == Qt::LeftButton ) {
        cursor = event->globalPos() - pos();
    }
}

void CustomWidget::mouseMoveEvent(QMouseEvent *event)
{
    if ( !isMaximized() && ( event->buttons() & Qt::LeftButton ) ) {
        move( event->globalPos() - cursor );
    }
}

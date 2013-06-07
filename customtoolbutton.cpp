#include "customtoolbutton.h"

CustomToolButton::CustomToolButton( const QString &strImage,
                                    const QString &strInfo,
                                    Qt::ToolButtonStyle style,
                                    int _pressStyle,
                                    QWidget *parent ) :
    QToolButton( parent ), strImage( strImage ), strInfo( strInfo ), pressStyle(_pressStyle)
{
    isOver = isPressed = false;
    setToolButtonStyle( style );
    setMouseTracking( true );
    if ( this->toolButtonStyle() != Qt::ToolButtonTextOnly )
        setIcon( QPixmap( strImage ) );
    if ( this->toolButtonStyle() != Qt::ToolButtonIconOnly )
        setText( strInfo );
    setStyleSheet( "CustomToolButton {"
                   "border: 0px;"
                   "}");
}

void CustomToolButton::setPressed( bool pressed )
{
    if (pressStyle == 1)
        isPressed = pressed;
    update();
}

void CustomToolButton::mousePressEvent( QMouseEvent *event )
{
    if ( event->button() == Qt::LeftButton ) {
        emit bePressed( this );
    }
    QToolButton::mousePressEvent( event );
}

void CustomToolButton::enterEvent( QEvent *event )
{
    isOver = true;
    update();
    QToolButton::enterEvent( event );
}

void CustomToolButton::leaveEvent( QEvent *event )
{
    isOver = false;
    update();
    QToolButton::leaveEvent( event );
}

void CustomToolButton::paintEvent( QPaintEvent *event )
{
    QPainter painter( this );

    int startOpacity = 0, medianOpacity = 0, endOpacity = 0;
    if ( isOver ) {
        startOpacity = 150;
        medianOpacity = 180;
        endOpacity = 200;
    } else if ( isPressed ) {
        startOpacity = 50;
        medianOpacity = 100;
        endOpacity = 80;
    }

    QLinearGradient mainWidgetGradient( rect().topLeft(), rect().bottomRight() );
    mainWidgetGradient.setColorAt( 0, QColor( 136, 136, 136, startOpacity ) );
    mainWidgetGradient.setColorAt( 0.5, QColor( 204, 204, 204, medianOpacity ) );
    mainWidgetGradient.setColorAt( 1, QColor( 190, 190, 190, endOpacity ) );
    QBrush mainWidgetBrush( mainWidgetGradient );
    painter.setPen( QPen( Qt::NoBrush, 1 ) );
    painter.setBrush( mainWidgetBrush );
    painter.drawRoundedRect( rect(), 5, 5 );
    QToolButton::paintEvent( event );
}

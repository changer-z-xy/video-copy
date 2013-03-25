#include "customtoolbutton.h"

CustomToolButton::CustomToolButton( const QString &strImage,
                            const QString &strInfo,
                            Qt::ToolButtonStyle style,
                            QWidget *parent ) :
    QToolButton( parent ), strImage( strImage ), strInfo( strInfo )
{
    setToolButtonStyle( style );
    if ( this->toolButtonStyle() != Qt::ToolButtonTextOnly )
        setIcon( QPixmap( strImage ) );
    if ( this->toolButtonStyle() != Qt::ToolButtonIconOnly )
        setText( strInfo );
    setStyleSheet( "CustomToolButton {"
                   "border: 0px"
                   "}");

}

void CustomToolButton::mousePressEvent( QMouseEvent *event )
{
    if ( event->button() == Qt::LeftButton )
        isPressed = true;
    QToolButton::mousePressEvent( event );
}

void CustomToolButton::enterEvent( QMouseEvent *event )
{
    isOver = true;
    QToolButton::enterEvent( event );
}

void CustomToolButton::leaveEvent( QMouseEvent *event )
{
    isOver = false;
    QToolButton::leaveEvent( event );
}

void CustomToolButton::mouseReleaseEvent( QMouseEvent *event )
{
    isPressed = false;
    QToolButton::mouseReleaseEvent( event );
}

void CustomToolButton::paintEvent( QPaintEvent *event )
{
    QPainter *painter = new QPainter( this );
    QPen objPen(Qt::NoBrush,1);
    painter->setPen(objPen);

    int startOpacity = 0, endOpacity = 0;
    if ( isPressed ) {
        startOpacity = 50;
        endOpacity = 100;
    } else if ( isOver ) {
        startOpacity = 150;
        endOpacity = 200;
    }

    QLinearGradient objLinear(rect().topLeft(),rect().bottomLeft());
    objLinear.setColorAt(0,QColor(150,150,150, startOpacity));
    objLinear.setColorAt(0.5,QColor(50,50,50,255));
    objLinear.setColorAt(1,QColor(100,100,100,endOpacity));
    QBrush objBrush(objLinear);
    painter->setBrush(objBrush);
    painter->drawRoundedRect(rect(),5,5);
    QToolButton::paintEvent( event );
}

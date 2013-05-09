#include "videoCopy.h"

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
        preCursorPos = event->globalPos();
        preWidgetPos = pos();
    }
}

void CustomWidget::mouseMoveEvent(QMouseEvent *event)
{
    int dir = 0;
    /*
     * 1 => left
     * 2 => right
     * 4 => top
     * 8 => bottom
     */
    if (!isMaximized()) {
        if (event->x() < 5 && event->x() > -5 ) {
            dir += 1;
        } else if (event->x() < width() + 5 && event->x() > width() - 5) {
            dir += 2;
        }
        if (event->y() < 5 && event->y() > -5) {
            dir += 4;
        } else if (event->y() < height() + 5 && event->y() > height() - 5) {
            dir += 8;
        }
        switch (dir) {
        case 1:
        case 2:
            setCursor(Qt::SizeHorCursor);
            break;
        case 4:
        case 8:
            setCursor(Qt::SizeVerCursor);
            break;
        default:
            setCursor(Qt::ArrowCursor);
        }
        if (event->buttons() & Qt::LeftButton) {
            if (dir == 0) {
                move(event->globalPos() - preCursorPos + preWidgetPos);
            } else {
                int dx = event->globalX() - preCursorPos.x();
                int dy = event->globalY() - preCursorPos.y();
                QRect tmp = geometry();
                switch (dir) {
                case 1:
                    tmp.setLeft(tmp.left() + dx);
                    break;
                case 2:
                    tmp.setRight(tmp.right() + dx);
                    break;
                case 4:
                    tmp.setTop(tmp.top() + dy);
                    break;
                case 8:
                    tmp.setBottom(tmp.bottom() + dy);
                    break;
                }
                if (tmp.width() < MinWidth || tmp.height() < MinHeight)
                    return;
                setGeometry(tmp);
            }
        }
    }
}

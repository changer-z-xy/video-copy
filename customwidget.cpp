#include "videoCopy.h"

CustomWidget::CustomWidget(QWidget *parent)
    : QFrame(parent)
{
    // set no system title bar
    setWindowFlags( Qt::FramelessWindowHint );
    setMouseTracking( true );
    dir = 0;
}

void CustomWidget::paintEvent(QPaintEvent *)
{
    QLinearGradient mainWidgetGradient( rect().topLeft(), rect().bottomRight() );
    mainWidgetGradient.setColorAt( 0, QColor( 0, 136, 204, 180 ) );
    mainWidgetGradient.setColorAt( 0.5, QColor( 0, 109, 204, 255 ) );
    mainWidgetGradient.setColorAt( 1, QColor( 0, 68, 205, 220 ) );
    QPainter painter(this);
    painter.fillRect( rect(), mainWidgetGradient );
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
        dir = calcDir(event->x(), event->y());
    }
}

void CustomWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        dir = 0;
    }
}

void CustomWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (!isMaximized()) {
        setCursorStyle(calcDir(event->x(), event->y()));
        if (event->buttons() & Qt::LeftButton) {
            if (dir == 0) {
                move(event->globalPos() - preCursorPos + preWidgetPos);
            } else {
                int dx = event->globalX() - preCursorPos.x();
                int dy = event->globalY() - preCursorPos.y();
                borderResize(event->globalPos());
            }
        }
    }
}

int CustomWidget::calcDir(int x, int y) {
    int tmp = 0;
    if (x < 5) {
        tmp += 1;
    } else if (x > width() - 5) {
        tmp += 2;
    }
    if (y < 5) {
        tmp += 4;
    } else if (y > height() - 5) {
        tmp += 8;
    }
    return tmp;
}

void CustomWidget::setCursorStyle(int _dir)
{
    switch (_dir) {
    case 1:
    case 2:
        setCursor(Qt::SizeHorCursor);
        break;
    case 4:
    case 8:
        setCursor(Qt::SizeVerCursor);
        break;
    case 1 | 4:
    case 2 | 8:
        setCursor(Qt::SizeFDiagCursor);
        break;
    case 1 | 8:
    case 2 | 4:
        setCursor(Qt::SizeBDiagCursor);
        break;
    default:
        setCursor(Qt::ArrowCursor);
    }
}

void CustomWidget::borderResize(int dx, int dy)
{
    QRect tmp = geometry();
    if (dir & 1)
        tmp.setLeft(tmp.left() + dx);
    if (dir & 2)
        tmp.setRight(tmp.right() + dx);
    if (dir & 4)
        tmp.setTop(tmp.top() + dy);
    if (dir & 8)
        tmp.setBottom(tmp.bottom() + dy);
    if (tmp.width() < minimumWidth() || tmp.height() < minimumHeight())
        return;
    setGeometry(tmp);
}

void CustomWidget::borderResize(const QPoint &curPos)
{
    QRect tmp = geometry();
    if (dir & 1)
        tmp.setLeft(curPos.x());
    if (dir & 2)
        tmp.setRight(curPos.x());
    if (dir & 4)
        tmp.setTop(curPos.y());
    if (dir & 8)
        tmp.setBottom(curPos.y());
    if (tmp.width() < minimumWidth() || tmp.height() < minimumHeight())
        return;
    setGeometry(tmp);
}

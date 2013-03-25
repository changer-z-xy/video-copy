#include "customwidget.h"
#include <QBitmap>
#include <QPainter>

CustomWidget::CustomWidget(QWidget *parent)
    : QFrame(parent)
{
    // set no system title bar
    setWindowFlags( Qt::FramelessWindowHint );

    // set myResizeFlag with 0
    myResizeFlag = 0;

    QVBoxLayout *mainLayout = new QVBoxLayout( this );
    // add myTitleBar
    myTitleBar = new CustomTitleBar( this );
    mainLayout->addWidget( myTitleBar );
    // add myToolBar
    myToolBar = new CustomToolBar( this );
    mainLayout->addWidget( myToolBar );
    // add myContentWidget
    myContentWidget = new CustomContentWidget( this );
    mainLayout->addWidget( myContentWidget );
    // add myStatusBar
    myStatusBar = new CustomStatusBar( this );
    mainLayout->addWidget( myStatusBar );
    // set mainLayout no spacing and margin
    mainLayout->setSpacing( 0 );
    mainLayout->setContentsMargins(0,0,0,0);

    setStyleSheet("CustomWidget {"
                  "border-image:url(:/img/background.jpg);"
                  "}");
    setMinimumWidth( 850 );
    setMinimumHeight( 600 );
}

CustomWidget::~CustomWidget()
{
    
}

void CustomWidget::paintEvent(QPaintEvent *)
{
    QBitmap *objBitmap = new QBitmap( size() );
    QPainter *painter = new QPainter( objBitmap );
    painter->fillRect( rect(), Qt::white );
    painter->setBrush( QColor( 0, 0, 0 ) );
    painter->drawRoundedRect( this->rect(), 10, 10 );
    setMask( *objBitmap );
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

void CustomWidget::mouseReleaseEvent( QMouseEvent *event )
{

}

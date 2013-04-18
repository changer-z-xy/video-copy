#include "customwidget.h"
#include <QBitmap>
#include <QPainter>

CustomWidget::CustomWidget(QWidget *parent)
    : QFrame(parent)
{
    // set no system title bar
    setWindowFlags( Qt::FramelessWindowHint );
    // set mouse tracking
    setMouseTracking( true );
    // set myResizeFlag with 0
    myResizeFlag = 0;

    setMinimumWidth( 850 );
    setMinimumHeight( 600 );

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
    // set mainLayout without spacing and margin
    mainLayout->setSpacing( 0 );
    mainLayout->setContentsMargins(0,0,0,0);

    connect( myToolBar, SIGNAL(showPageAt(int)),
             myContentWidget, SLOT(showPageAt(int)) );
}

CustomWidget::~CustomWidget()
{
    
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

void CustomWidget::resizeEvent( QResizeEvent *event )
{
    myContentWidget->resize( width() * myContentWidget->getCntPages(), height() - STATUSBAR_HEIGHT - TITLEBAR_HEIGHT - TOOLBAR_HEIGHT );
    QWidget::resizeEvent( event );
}

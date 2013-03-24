#include "customtitlebar.h"

CustomTitleBar::CustomTitleBar( QWidget *parent ) :
    parent( parent )
{
    icon = new QPixmap( ":/img/icon.jpg" );
    parent->setWindowTitle( "video copy detection");

    titleLabel = new QLabel( parent->windowTitle() );
    minButton = new QToolButton( this );
    QPixmap minPix = style()->standardPixmap( QStyle::SP_TitleBarMinButton );
    minButton->setIcon( minPix );
    maxButton = new QToolButton( this );
    QPixmap maxPix = style()->standardPixmap( QStyle::SP_TitleBarMaxButton );
    maxButton->setIcon( maxPix );
    closeButton = new QToolButton( this );
    QPixmap closePix = style()->standardPixmap( QStyle::SP_TitleBarCloseButton );
    closeButton->setIcon( closePix );

    QHBoxLayout *titleBarLayout = new QHBoxLayout( this );
    titleBarLayout->addWidget( titleLabel );
    titleBarLayout->addStretch();
    titleBarLayout->addWidget( minButton );
    titleBarLayout->addWidget( maxButton );
    titleBarLayout->addWidget( closeButton );
    titleBarLayout->setSpacing( 0 );
    titleBarLayout->setContentsMargins(0,0,0,0);

    connect( minButton, SIGNAL(clicked()),
             parent, SLOT(showMinimized()) );
    connect( maxButton, SIGNAL(clicked()),
             parent, SLOT(showMaxRestore()) );
    connect( closeButton, SIGNAL(clicked()),
             parent, SLOT(close()) );
}

CustomTitleBar::~CustomTitleBar()
{

}

void CustomTitleBar::mousePressEvent(QMouseEvent *event)
{
    if ( event->button() == Qt::LeftButton ) {
        cursor = mapToParent( event->globalPos() - parent->pos() );
    }
}

void CustomTitleBar::mouseMoveEvent(QMouseEvent *event)
{
    if ( !parent->isMaximized() && ( event->buttons() & Qt::LeftButton ) ) {
        parent->move( event->globalPos() - cursor );
    }
}

QToolButton *CustomTitleBar::getMinButton()
{
    return minButton;
}

QToolButton *CustomTitleBar::getMaxButton()
{
    return maxButton;
}

QToolButton *CustomTitleBar::getCloseButton()
{
    return closeButton;
}

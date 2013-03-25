#include "customtitlebar.h"

CustomTitleBar::CustomTitleBar( QWidget *parent ) :
    parent( parent )
{
    // set fixed height
    setFixedHeight( 30 );
    // set icon
    QPixmap icon( ":/img/icon.jpg" );
    iconLabel = new QLabel( this );
    iconLabel->setPixmap( icon );
    // set text title
    parent->setWindowTitle( "video copy detection");
    titleLabel = new QLabel( parent->windowTitle() );
    // set min button
    minButton = new QToolButton( this );
    QPixmap minPix = style()->standardPixmap( QStyle::SP_TitleBarMinButton );
    minButton->setIcon( minPix );
    // set max/restore button
    maxButton = new QToolButton( this );
    QPixmap maxPix = style()->standardPixmap( QStyle::SP_TitleBarMaxButton );
    maxButton->setIcon( maxPix );
    // set close button
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

void CustomTitleBar::mouseDoubleClickEvent( QMouseEvent *event )
{
    if ( event->button() == Qt::LeftButton ) {
        emit maxButton->clicked();
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

#include "customtitlebar.h"

CustomTitleBar::CustomTitleBar( QWidget *parent ) :
    parent( parent )
{
    // set fixed height
    int fixedHeight = 30;
    setFixedHeight( fixedHeight );
    setMouseTracking( true );
    // set icon
    QPixmap icon( ":/img/icon.png" );
    iconLabel = new QLabel( this );
    iconLabel->setPixmap( icon.scaled( fixedHeight, fixedHeight ) );
    // set text title
    parent->setWindowTitle( "基于内容的视频版权注册与认证系统");
    titleLabel = new QLabel( parent->windowTitle() );
    // following three button didn't show :/img/icon.png
    // because it expired after setIcon( *Pix )
    // set min button
    minButton = new CustomToolButton( ":/img/icon.png", "" );
    QPixmap minPix = style()->standardPixmap( QStyle::SP_TitleBarMinButton );
    minButton->setIcon( minPix );
    minButton->setIconSize( QSize( 50, 30 ) );
    // set max/restore button
    maxButton = new CustomToolButton( ":/img/icon.png", "" );
    QPixmap maxPix = style()->standardPixmap( QStyle::SP_TitleBarMaxButton );
    maxButton->setIconSize( QSize( 50, 30 ) );
    maxButton->setIcon( maxPix );
    // set close button
    closeButton = new CustomToolButton( ":/img/icon.png", "" );
    QPixmap closePix = style()->standardPixmap( QStyle::SP_TitleBarCloseButton );
    closeButton->setIcon( closePix );
    closeButton->setIconSize( QSize( 50, 30 ) );

    QHBoxLayout *titleBarLayout = new QHBoxLayout( this );
    titleBarLayout->addWidget( iconLabel );
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

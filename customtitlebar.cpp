#include "videoCopy.h"

CustomTitleBar::CustomTitleBar( QWidget *parent, const QString &title ) :
    parent(parent)
{
    QHBoxLayout *titleBarLayout = new QHBoxLayout( this );
    setMouseTracking( true );
    // set icon
    QPixmap icon( ":/img/icon.png" );
    iconLabel = new QLabel( this );
    iconLabel->setPixmap( icon.scaled( TITLEBAR_HEIGHT, TITLEBAR_HEIGHT ) );
    titleBarLayout->addWidget( iconLabel );
    titleLabel = new QLabel(title);
    titleBarLayout->addWidget( titleLabel );
    titleBarLayout->addStretch();
    // following three button didn't show :/img/icon.png
    // because it expired after setIcon( *Pix )
    // set min button
    minButton = new CustomToolButton(":/img/icon.png", "", Qt::ToolButtonIconOnly, 2, this);
    QPixmap minPix = style()->standardPixmap( QStyle::SP_TitleBarMinButton );
    minButton->setIcon( minPix );
    minButton->setIconSize( QSize( 50, 30 ) );
    titleBarLayout->addWidget( minButton );
    // set max/restore button
    maxButton = new CustomToolButton( ":/img/icon.png", "", Qt::ToolButtonIconOnly, 2, this);
    QPixmap maxPix = style()->standardPixmap( QStyle::SP_TitleBarMaxButton );
    maxButton->setIconSize( QSize( 50, 30 ) );
    maxButton->setIcon( maxPix );
    titleBarLayout->addWidget( maxButton );
    // set close button
    closeButton = new CustomToolButton( ":/img/icon.png", "", Qt::ToolButtonIconOnly, 2, this);
    QPixmap closePix = style()->standardPixmap( QStyle::SP_TitleBarCloseButton );
    closeButton->setIcon( closePix );
    closeButton->setIconSize( QSize( 50, 30 ) );
    titleBarLayout->addWidget( closeButton );
    titleBarLayout->setSpacing(0);
    titleBarLayout->setMargin(0);

    connect(minButton, SIGNAL(clicked()),
            this, SIGNAL(minButtonClicked()));
    connect(maxButton, SIGNAL(clicked()),
            this, SIGNAL(maxButtonClicked()));
    connect(closeButton, SIGNAL(clicked()),
            this, SIGNAL(closeButtonClicked()));
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

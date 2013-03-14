#include "widget.h"
#include "opencvvideobox.h"
#include <QPushButton>
#include <QImage>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    // new objects(widgets)
    srcVideoBox = new opencvVideoBox( this );
    targetVideoBox = new opencvVideoBox( this );
    openSrcButton = new QPushButton( tr( "open source video" ), this );
    openTargetButton = new QPushButton( tr( "open target video" ), this );
    cmpButton = new QPushButton( tr( "compare" ), this );

    // connect openXXButton.clicked() to openXXVideos()
    connect( openSrcButton, SIGNAL( clicked() ),
             this, SLOT( openSrcClicked() ) );
    connect( openTargetButton, SIGNAL( clicked() ),
             this, SLOT( openTargetClicked() ) );

    // new layouts
    QVBoxLayout *mainLayout = new QVBoxLayout( this );
    QHBoxLayout *topLayout = new QHBoxLayout( this );
    QVBoxLayout *srcLeftCol = new QVBoxLayout( this );
    QHBoxLayout *srcLeftScreen = new QHBoxLayout( this );
    QHBoxLayout *srcLeftOpenButton = new QHBoxLayout( this );
    QVBoxLayout *targetRightCol = new QVBoxLayout( this );
    QHBoxLayout *targetRightScreen = new QHBoxLayout( this );
    QHBoxLayout *targetRightOpenButton = new QHBoxLayout( this );

    // apply these layouts
    srcLeftScreen->addWidget( srcVideoBox );
    srcLeftOpenButton->addWidget( openSrcButton );
    srcLeftOpenButton->setAlignment( Qt::AlignHCenter );
    srcLeftCol->addLayout( srcLeftScreen );
    srcLeftCol->addLayout( srcLeftOpenButton );

    targetRightScreen->addWidget( targetVideoBox );
    targetRightOpenButton->addWidget( openTargetButton );
    targetRightOpenButton->setAlignment( Qt::AlignHCenter );
    targetRightCol->addLayout( targetRightScreen );
    targetRightCol->addLayout( targetRightOpenButton );

    topLayout->addLayout( srcLeftCol );
    topLayout->addLayout( targetRightCol );

    mainLayout->addLayout( topLayout );
    mainLayout->addWidget( cmpButton );

    setLayout( mainLayout );
}

Widget::~Widget()
{
    
}

bool Widget::cmpVideos()
{
    return false;
}

// these two functions should be changed
void Widget::openSrcClicked( )
{
    QString tmp = QFileDialog::getOpenFileName(
                this,
                tr( "open files" ),
                ".",
                tr( "avi files(*.avi)" ) );
    srcVideoBox->loadVideos( tmp );
}
void Widget::openTargetClicked( )
{
    QString tmp = QFileDialog::getOpenFileName(
                this,
                tr( "open files" ),
                ".",
                tr( "avi files(*.avi)" ) );
    targetVideoBox->loadVideos( tmp );
}

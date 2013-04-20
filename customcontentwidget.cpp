#include "customcontentwidget.h"

#define __PANYUFENG__

void setNoSpace( QLayout *layout )
{
    layout->setSpacing( 0 );
    layout->setMargin( 0 );
}

CustomContentWidget::CustomContentWidget(QWidget *parent) :
    QWidget(parent)
{
    resize( parent->width() * 3, parent->height() );
    ContentPage *myPage0 = new ContentPage( this );
    ContentPage *myPage1 = new ContentPage( this );
    ContentPage *myPage2 = new ContentPage( this );

    // set myPage0
    // set codes begin
    QVBoxLayout *page0Layout = new QVBoxLayout( myPage0 );
    setNoSpace( page0Layout );
    QHBoxLayout *page0TopLayout = new QHBoxLayout;
    setNoSpace( page0TopLayout );

    MPlayerWidget *srcmplayer = new MPlayerWidget( myPage0 );
    srcmplayer->setObjectName( "srcmplayer");
    QPushButton *loadSrc = new QPushButton( "loadSrc", myPage0 );
    loadSrc->resize( loadSrc->sizeHint() );
    connect( loadSrc, SIGNAL(clicked()),
             this, SLOT(setSrcFile()) );
    QPushButton *pauseSrc = new QPushButton( "pauseSrc", myPage0 );
    pauseSrc->resize( pauseSrc->sizeHint() );
    connect( pauseSrc, SIGNAL(clicked()),
             srcmplayer, SLOT(pause()) );
    QPushButton *stopSrc = new QPushButton( "stopSrc", myPage0 );
    stopSrc->resize( stopSrc->sizeHint() );
    connect( stopSrc, SIGNAL(clicked()),
             srcmplayer, SLOT(stop()) );

    QHBoxLayout *srcCtrlLayout = new QHBoxLayout;
    setNoSpace( srcCtrlLayout );
    srcCtrlLayout->addWidget( loadSrc );
    srcCtrlLayout->addWidget( pauseSrc );
    srcCtrlLayout->addWidget( stopSrc );
    srcCtrlLayout->setAlignment( Qt::AlignHCenter );

    QVBoxLayout *srcVideoLayout = new QVBoxLayout;
    srcVideoLayout->addWidget( srcmplayer );
    srcVideoLayout->addLayout( srcCtrlLayout );
    setNoSpace( srcVideoLayout );
    page0TopLayout->addLayout( srcVideoLayout );

    MPlayerWidget *targetmplayer = new MPlayerWidget( myPage0 );
    targetmplayer->setObjectName( "targetmplayer");
    QPushButton *loadTarget = new QPushButton( "loadTarget", myPage0 );
    loadTarget->resize( loadSrc->sizeHint() );
    connect( loadTarget, SIGNAL(clicked()),
             this, SLOT(setTargetFile()) );
    QPushButton *pauseTarget = new QPushButton( "pauseTarget", myPage0 );
    pauseTarget->resize( pauseTarget->sizeHint() );
    connect( pauseTarget, SIGNAL(clicked()),
             targetmplayer, SLOT(pause()) );
    QPushButton *stopTarget = new QPushButton( "stopTarget", myPage0 );
    stopTarget->resize( stopTarget->sizeHint() );
    connect( stopTarget, SIGNAL(clicked()),
             targetmplayer, SLOT(stop()) );

    QHBoxLayout *targetCtrlLayout = new QHBoxLayout;
    setNoSpace( targetCtrlLayout );
    targetCtrlLayout->addWidget( loadTarget );
    targetCtrlLayout->addWidget( pauseTarget );
    targetCtrlLayout->addWidget( stopTarget );
    targetCtrlLayout->setAlignment( Qt::AlignHCenter );

    QVBoxLayout *targetVideoLayout = new QVBoxLayout;
    targetVideoLayout->addWidget( targetmplayer );
    targetVideoLayout->addLayout( targetCtrlLayout );
    setNoSpace( targetVideoLayout );
    page0TopLayout->addLayout( targetVideoLayout );

    QPushButton *cmpVideos = new QPushButton( "cmpVideos", myPage0 );
    cmpVideos->resize( cmpVideos->sizeHint() );
    /* here connect cmpVideos' clicked() signal to the function
    ** used to compare two videos
    */
    connect( cmpVideos, SIGNAL(clicked()),
             this, SLOT(compareVideos()) );

    QHBoxLayout *page0BottomLayout = new QHBoxLayout;
    page0BottomLayout->addWidget( cmpVideos );
    page0BottomLayout->setAlignment( Qt::AlignHCenter );

    page0Layout->addLayout( page0TopLayout );
    page0Layout->addLayout( page0BottomLayout );

    myPage0->setLayout( page0Layout );
    // set codes end

    // set myPage1
    // set codes begin
    // set codes end

    // set myPage2
    // set codes begin
    QWebView *myWebPage = new QWebView( myPage2 );
    myWebPage->setObjectName( "myWebPage" );
    // set codes end

    // add my pages to myPages
    myPages.push_back( myPage0 );
    myPages.push_back( myPage1 );
    myPages.push_back( myPage2 );
    for ( int i = 0, sz = myPages.size(); i < sz; ++ i ) {
        myPages.at( i )->moveToLeft( parent->width() * i );
//        qDebug() << myPages.at( i )->x() << " " << myPages.at( i )->y();
    }
    curPageIndex = 0;
}

CustomContentWidget::~CustomContentWidget()
{
}

void CustomContentWidget::paintEvent( QPaintEvent *event )
{

}

void CustomContentWidget::showPageAt( int index )
{
    if ( index < myPages.size() && index != curPageIndex ) {
//        qDebug() << "A: " << myPages.at( curPageIndex )->x() << " " << myPages.at( curPageIndex )->y();
//        qDebug() << "B: " << myPages.at( index )->x() << " " << myPages.at( index )->y();
//        qDebug() << "C: " << this->x() << " " << this->y();
        if ( index == 2 ) {
            QWebView *tmpPage = findChild<QWebView *>( "myWebPage" );
            if ( !tmpPage->url().isValid() ) {
                QUrl url = QUrl::fromLocalFile( "E:\\myworkspace\\videoCopy-build-Desktop_Qt_5_0_1_MinGW_32bit-Debug\\debug\\百度一下，你就知道.htm" );
                if ( url.isValid() ) {
                    tmpPage->load( url );
                    qDebug() << url;
                } else {
                    qDebug() << "wrong url for qwebview to load";
                }
            }
        }
        QTimeLine *timeline = new QTimeLine( 500, this );
        timeline->setFrameRange( x(), -index * myPages.at( index )->width() );
        timeline->setCurveShape( QTimeLine::EaseInOutCurve );
        connect( timeline, SIGNAL(frameChanged(int)),
                 this, SLOT(moveToLeft(int)) );
        timeline->start();
        curPageIndex = index;
    }
}

void CustomContentWidget::resizeEvent( QResizeEvent *event )
{
    const int pageWidth = width() / myPages.size();
    moveToLeft( -curPageIndex * pageWidth );
    for ( int i = 0, sz = myPages.size(); i < sz; ++ i ) {
        myPages[ i ]->resize( pageWidth, height() );
        myPages[ i ]->moveToLeft( pageWidth * i );
//        qDebug() << myPages.at( i )->width() << " " << myPages.at( i )->height();
    }

    // some special size control on child widgets
    // set fixed size of myWebPage
    QWebView *tmpWebPage = findChild<QWebView *>( "myWebPage" );
    if ( tmpWebPage )
        tmpWebPage->setFixedSize( pageWidth, height() );
    QWidget::resizeEvent( event );
}

void CustomContentWidget::moveToLeft( int x )
{
    move( x, y() );
}

int CustomContentWidget::getCntPages()
{
    return myPages.size();
}

void CustomContentWidget::compareVideos()
{
    MPlayerWidget *srcmplayer = findChild<MPlayerWidget *>( "srcmplayer" );
    MPlayerWidget *targetmplayer = findChild<MPlayerWidget *>( "targetmplayer" );

    bool isSame = false;
#ifdef __PANYUFENG__
    Get_Frame srcVideo( "C:\\movie\\temp.avi" );
    key_frame srcKeyFrame( srcVideo, new char[256] );
    Get_Frame targetVideo("C:\\movie\\temp.avi");
    key_frame targetKeyFrame( targetVideo, new char[256] );
    isSame = cp_video( srcKeyFrame, targetKeyFrame );
#else
    copydetection histCmpVideos;
    double similarity = 0;
//    IplImage *img1 = cvLoadImage("C:\\Users\\changer_z_xy\\Desktop\\tmp\\1.jpg");
//    IplImage *img2 = cvLoadImage("C:\\Users\\changer_z_xy\\Desktop\\tmp\\2.jpg");
//    similarity = histCmpVideos.getsimilar(img1,img2);
    similarity = histCmpVideos.getsimilar( srcmplayer->getFilePath().toLocal8Bit().data(),
                                           targetmplayer->getFilePath().toLocal8Bit().data() );
    qDebug() << "similarity is: " << similarity;
    isSame = similarity < 0.8;
#endif

    if ( isSame ) {
        QMessageBox::information( this, "answer", "these two videos are same!" );
    } else {
        QMessageBox::information( this, "answer", "these two videos are not same!" );
    }
}

void CustomContentWidget::setSrcFile()
{
    MPlayerWidget *srcVideo = findChild<MPlayerWidget *>("srcmplayer");
    srcVideo->setFilePath( QFileDialog::getOpenFileName( this, "open source video", ".", tr("Avi files( *.avi )") ) );
    srcVideo->load();
}

void CustomContentWidget::setTargetFile()
{
    MPlayerWidget *targetVideo = findChild<MPlayerWidget *>("targetmplayer");
    targetVideo->setFilePath( QFileDialog::getOpenFileName( this, "open target video", ".", tr("Avi files( *.avi )") ) );
    targetVideo->load();
}

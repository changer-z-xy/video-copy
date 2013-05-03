#include "customcontentwidget.h"

#define __changer_debug__

void setNoSpace( QLayout *layout )
{
    layout->setSpacing( 0 );
    layout->setMargin( 0 );
}

CustomContentWidget::CustomContentWidget(QWidget *parent) :
    QWidget(parent)
{
    subPageWidth = parent->width();
    subPageHeight = parent->height();
    resize( subPageWidth * 3, subPageHeight );

    cmpThread = new CmpThread(this);
    outputText = new CmpOutputWidget;
    outputText->hide();
    connect(cmpThread, SIGNAL(outputNewItem()),
            outputText, SLOT(addOutput()));

    // set myPage0
    // set codes begin
    ContentPage *myPage0 = new ContentPage( this );

    QVBoxLayout *page0Layout = new QVBoxLayout( myPage0 );
    setNoSpace( page0Layout );
    QHBoxLayout *page0TopLayout = new QHBoxLayout;
//    setNoSpace( page0TopLayout );

    MPlayerWidget *srcmplayer = new MPlayerWidget( myPage0 );
    srcmplayer->setObjectName("srcmplayer");
    QPushButton *loadSrc = new QPushButton( "打开源视频", myPage0 );
    loadSrc->resize( loadSrc->sizeHint() );
    connect( loadSrc, SIGNAL(clicked()),
             this, SLOT(setSrcFile()) );
    QPushButton *pauseSrc = new QPushButton( "暂停源视频", myPage0 );
    pauseSrc->resize( pauseSrc->sizeHint() );
    connect( pauseSrc, SIGNAL(clicked()),
             srcmplayer, SLOT(pause()) );
    QPushButton *stopSrc = new QPushButton( "停止源视频", myPage0 );
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
    QPushButton *loadTarget = new QPushButton( "打开目标视频", myPage0 );
    loadTarget->resize( loadSrc->sizeHint() );
    connect( loadTarget, SIGNAL(clicked()),
             this, SLOT(setTargetFile()) );
    QPushButton *pauseTarget = new QPushButton( "暂停目标视频", myPage0 );
    pauseTarget->resize( pauseTarget->sizeHint() );
    connect( pauseTarget, SIGNAL(clicked()),
             targetmplayer, SLOT(pause()) );
    QPushButton *stopTarget = new QPushButton( "停止目标视频", myPage0 );
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


    QHBoxLayout *page0BottomLayout = new QHBoxLayout;
    QPushButton *cmpVideos = new QPushButton( "比较视频", myPage0 );
    cmpVideos->resize( cmpVideos->sizeHint() );
    connect( cmpVideos, SIGNAL(clicked()),
             this, SLOT(compareVideos()) );
    page0BottomLayout->addWidget( cmpVideos );
    QPushButton *showOutputButton = new QPushButton("打开输出窗口", myPage0);
    showOutputButton->resize(showOutputButton->sizeHint());
    connect(showOutputButton, SIGNAL(clicked()),
            this, SLOT(showOutputWidget()));
    page0BottomLayout->addWidget(showOutputButton);
    page0BottomLayout->setAlignment( Qt::AlignHCenter );

    page0Layout->addLayout( page0TopLayout );
    page0Layout->addLayout( page0BottomLayout );

    myPage0->setLayout( page0Layout );
    // set codes end

    // set myPage1
    // set codes begin
    ContentPage *myPage1 = new ContentPage( this );

    // set codes end

    // set myPage2
    // set codes begin
    ContentPage *myPage2 = new ContentPage( this );

    QWebView *myWebPage = new QWebView( myPage2 );
    myWebPage->setObjectName( "myWebPage" );
    // set codes end

    // add my pages to myPages
    myPages.push_back( myPage0 );
    myPages.push_back( myPage1 );
    myPages.push_back( myPage2 );
    for ( int i = 0, sz = myPages.size(); i < sz; ++ i ) {
        myPages.at( i )->moveToLeft( subPageWidth * i );
//        qDebug() << myPages.at( i )->x() << " " << myPages.at( i )->y();
    }
    curPageIndex = 0;
}

CustomContentWidget::~CustomContentWidget()
{
    delete outputText;
}

void CustomContentWidget::paintEvent( QPaintEvent *event )
{

}

void CustomContentWidget::showPageAt( int index )
{
    if ( index < myPages.size() && index != curPageIndex ) {
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
#ifdef __changer_debug__
    QString src = "C:\\movie\\temp1.avi";
    QString target = "C:\\movie\\temp2.avi";
#else
    qDebug() << srcmplayer->getFilePath().toLocal8Bit().data();
    QString src = srcmplayer->getFilePath();
    qDebug() << targetmplayer->getFilePath().toLocal8Bit().data();
    QString target = targetmplayer->getFilePath();
#endif
    if ( !cmpThread->isRunning() ) {
        cmpThread->setSrc( src );
        cmpThread->setTarget( target );
        cmpThread->start();
    }
}

void CustomContentWidget::setSrcFile()
{
    MPlayerWidget *srcVideo = findChild<MPlayerWidget *>("srcmplayer");
    srcVideo->setFilePath( QFileDialog::getOpenFileName( this, "打开源视频", ".", tr("Avi 视频( *.avi )") ) );
    srcVideo->load();
}

void CustomContentWidget::setTargetFile()
{
    MPlayerWidget *targetVideo = findChild<MPlayerWidget *>("targetmplayer");
    targetVideo->setFilePath( QFileDialog::getOpenFileName( this, "打开目标视频", ".", tr("Avi 视频( *.avi )") ) );
    targetVideo->load();
}

//void CustomContentWidget::showAns(bool ans)
//{
//    if ( ans ) {
//        QMessageBox::information(this,"结果","两个视频是同源的！");
//    } else {
//        QMessageBox::information(this,"结果","两个视频不是同源的！");
//    }
//}

void CustomContentWidget::showOutputWidget()
{
    outputText->show();
}

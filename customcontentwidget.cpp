#include "customcontentwidget.h"

CustomContentWidget::CustomContentWidget(QWidget *parent) :
    QWidget(parent)
{
    resize( parent->width() * 3, parent->height() );
    ContentPage *myPage0 = new ContentPage( this );
    ContentPage *myPage1 = new ContentPage( this );
    ContentPage *myPage2 = new ContentPage( this );

    // set myPage0
    // set codes begin
    MPlayerWidget *mplayer = new MPlayerWidget( myPage0 );
    QHBoxLayout *page0Layout = new QHBoxLayout( myPage0 );
    page0Layout->addWidget( mplayer );
    mplayer->setObjectName( "mplayer");
    mplayer->getMPProcess()->setObjectName( "mpprocess" );
    mplayer->setFilePath( "E:\\learn\\lecture_video\\Lec03_循环式程序样式.rmvb" );
    QPushButton *testButton = new QPushButton( myPage0 );
    connect( testButton, SIGNAL(clicked()),
             mplayer, SLOT(load()) );
    page0Layout->addWidget( testButton );
    page0Layout->setSpacing( 0 );
    page0Layout->setMargin( 0 );
    myPage0->setLayout( page0Layout );
    // set codes end

    // set myPage1
    // set codes begin
//    int cntCol = 50, colWidth = 10;
//    Histogram *histGraphicsView = new Histogram( cntCol, colWidth, NULL, this );
//    QList<double> *myColumnsHeight = new QList<double>;
//    QList<double> *myColumnsPos = new QList<double>;
//    // following is test for displaying histogram
//    // test codes begin
//    for ( int i = 0; i < cntCol; ++ i ) {
//        myColumnsHeight->push_back( i * 5 );
//        myColumnsPos->push_back( i * colWidth );
//    }
//    histGraphicsView->setColumns( myColumnsHeight, myColumnsPos );
//    // test codes end
//    QHBoxLayout *contentLayout = new QHBoxLayout( myPage1 );
//    contentLayout->addWidget( histGraphicsView );
//    contentLayout->setMargin( 0 );
//    contentLayout->setSpacing( 0 );
//    // set codes end

    // set myPage2
    // set codes begin
    QWebView *myWebPage = new QWebView( myPage2 );
    QUrl url = QUrl::fromLocalFile( "E:\\myworkspace\\videoCopy-build-Desktop_Qt_5_0_1_MinGW_32bit-Debug\\debug\\左脑设计，右脑编程 - 博客频道 - CSDN.NET.htm" );
    if ( url.isValid() ) {
        myWebPage->load( url );
        qDebug() << url;
    } else {
        qDebug() << "wrong url for qwebview to load";
    }
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

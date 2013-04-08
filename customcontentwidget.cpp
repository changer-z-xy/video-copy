#include "customcontentwidget.h"

CustomContentWidget::CustomContentWidget(QWidget *parent) :
    QWidget(parent)
{
    ContentPage *myPage0 = new ContentPage( this );
    ContentPage *myPage1 = new ContentPage( this );
    ContentPage *myPage2 = new ContentPage( this );

    // set myPage0
    // set codes begin
//    OpencvVideoBox *videoBox = new OpencvVideoBox( myPage0 );
//    QString myVideo( "E:\\learn\\lecture_video\\MIT计算机科学及编程导论.Lec01-ZQEDU.avi" );
//    videoBox->loadVideos( myVideo );
//    videoBox->resize( videoBox->sizeHint() );
    QWidget *testMplayer = new QWidget( myPage0 );
    QString mplayerPath( "mplayer/mplayer.exe" );
    QStringList mpArgs;
    mpArgs << "-wid" << QString::number(testMplayer->winId());
    mpArgs << "E:\\learn\\lecture_video\\MIT计算机科学及编程导论.Lec01-ZQEDU.avi";
    QProcess *mpProcess = new QProcess( myPage0 );
    mpProcess->start( mplayerPath, mpArgs );
    testMplayer->setFixedSize( 600, 400 );
    // set codes end

    // set myPage1
    // set codes begin
    int cntCol = 50, colWidth = 10;
    Histogram *histGraphicsView = new Histogram( cntCol, colWidth, NULL, this );
    QList<double> *myColumnsHeight = new QList<double>;
    QList<double> *myColumnsPos = new QList<double>;
    // following is test for displaying histogram
    // test codes begin
    for ( int i = 0; i < cntCol; ++ i ) {
        myColumnsHeight->push_back( i * 5 );
        myColumnsPos->push_back( i * colWidth );
    }
    histGraphicsView->setColumns( myColumnsHeight, myColumnsPos );
    // test codes end
    QHBoxLayout *contentLayout = new QHBoxLayout( myPage1 );
    contentLayout->addWidget( histGraphicsView );
    contentLayout->setMargin( 0 );
    contentLayout->setSpacing( 0 );
    // set codes end

    // set myPage2
    // set codes begin
    QWebView *webPage = new QWebView( myPage2 );
    webPage->load( QUrl("http://www.baidu.com") );
    myPage2->setFixedSize( 800, 400 );
    // set codes end

    // add my pages to myPages
    myPages.push_back( myPage0 );
    myPages.push_back( myPage1 );
    myPages.push_back( myPage2 );

    QHBoxLayout *mainLayout = new QHBoxLayout( this );
    for ( int i = 0, sz = myPages.size(); i < sz; ++ i ) {
        mainLayout->addWidget( myPages.at( i ) );
        myPages.at( i )->setVisible( false );
    }
    mainLayout->setSpacing( 0 );
    mainLayout->setContentsMargins( 0, 0, 0, 0 );
    showPageAt( 0 );
}

CustomContentWidget::~CustomContentWidget()
{

}

void CustomContentWidget::paintEvent( QPaintEvent *event )
{

}

void CustomContentWidget::showPageAt( int index )
{
    for ( int i = 0, sz = myPages.size(); i < sz; ++ i ) {
        if ( myPages[ i ]->isVisible() )
            myPages[ i ]->setVisible( false );
    }
    if ( index < myPages.size() )
        myPages[ index ]->setVisible( true );
}

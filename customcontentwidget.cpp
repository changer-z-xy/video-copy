#include "customcontentwidget.h"

CustomContentWidget::CustomContentWidget(QWidget *parent) :
    QWidget(parent)
{
    ContentPage *myPage1 = new ContentPage( this );
    // set myPage1
    int cntCol = 50, colWidth = 10;
    Histgram *histGraphicsView = new Histgram( cntCol, colWidth, NULL, this );
    QList<double> *myColumnsHeight = new QList<double>;
    QList<double> *myColumnsPos = new QList<double>;
    // following is test for displaying histgram
    for ( int i = 0; i < cntCol; ++ i ) {
        myColumnsHeight->push_back( i * 5 );
        myColumnsPos->push_back( i * colWidth );
    }
    histGraphicsView->setColumns( myColumnsHeight, myColumnsPos );
    // test code end
    QHBoxLayout *contentLayout = new QHBoxLayout( myPage1 );
    contentLayout->addWidget( histGraphicsView );
    contentLayout->setMargin( 0 );
    contentLayout->setSpacing( 0 );
    // set myPage1 end

    // add myPage1 to myPages
    myPages.push_back( myPage1 );

    QHBoxLayout *mainLayout = new QHBoxLayout( this );
    for ( int i = 0, sz = myPages.size(); i < sz; ++ i )
        mainLayout->addWidget( myPages.at( i ) );
    mainLayout->setSpacing( 0 );
    mainLayout->setContentsMargins( 0, 0, 0, 0 );
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

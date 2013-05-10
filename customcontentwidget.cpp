#include "videoCopy.h"

//#define __changer_debug__

void setNoSpace( QLayout *layout )
{
    layout->setSpacing( 0 );
    layout->setMargin( 0 );
}

CustomContentWidget::CustomContentWidget(QWidget *parent) :
    QWidget(parent)
{
    setMouseTracking(true);
    cmpThread = new CmpThread(this);
    outputText = new CmpOutputWidget(0);
    outputText->hide();
    connect(cmpThread, SIGNAL(outputNewItem()),
            outputText, SLOT(addOutput()));

    myPages = new QStackedWidget(this);
    // set myPage0
    {
    ContentPage *myPage0 = new ContentPage(this);
    srcmplayer = new MPlayerWidget(this);
    targetmplayer = new MPlayerWidget(this);
    cmpVideos = new QPushButton( "比较视频", myPage0 );
    showOutputButton = new QPushButton("打开输出窗口", myPage0);

    connect( cmpVideos, SIGNAL(clicked()),
             this, SLOT(compareVideos()) );
    connect(showOutputButton, SIGNAL(clicked()),
            this, SLOT(showOutputWidget()));

    QVBoxLayout *page0Layout = new QVBoxLayout(myPage0);
    QHBoxLayout *page0TopLayout = new QHBoxLayout;
    page0TopLayout->addWidget(srcmplayer);
    page0TopLayout->addWidget(targetmplayer);
    page0TopLayout->setMargin(0);
    QHBoxLayout *page0BottomLayout = new QHBoxLayout;
    page0BottomLayout->addWidget( cmpVideos );
    page0BottomLayout->addWidget(showOutputButton);
    page0BottomLayout->setMargin(0);
    page0BottomLayout->setAlignment( Qt::AlignHCenter );
    page0Layout->addLayout( page0TopLayout );
    page0Layout->addLayout( page0BottomLayout );
    page0Layout->setMargin(0);

    myPages->addWidget(myPage0);
    }

    // set myPage1
    {
    ContentPage *myPage1 = new ContentPage( this );
    myPages->addWidget(myPage1);
    }

    // set myPage2
    {
    ContentPage *myPage2 = new ContentPage( this );

    QWebView *myWebPage = new QWebView( myPage2 );
    myPages->addWidget(myPage2);
    }

}

CustomContentWidget::~CustomContentWidget()
{
    delete outputText;
}

void CustomContentWidget::showPageAt(int index)
{
    myPages->setCurrentIndex(index);
}

void CustomContentWidget::resizeEvent( QResizeEvent *event )
{
    myPages->resize(size());
    QWidget::resizeEvent(event);
}

void CustomContentWidget::compareVideos()
{
#ifdef __changer_debug__
    QString src = "C:\\movie\\temp1.avi";
    QString target = "C:\\movie\\temp2.avi";
#else
    qDebug() << srcmplayer->getFilePath().toLocal8Bit().data();
    QString src = srcmplayer->getFilePath();
    qDebug() << targetmplayer->getFilePath().toLocal8Bit().data();
    QString target = targetmplayer->getFilePath();
#endif
    if (!cmpThread->isRunning()) {
        cmpThread->setSrc( src );
        cmpThread->setTarget( target );
        cmpThread->start();
    }
}

void CustomContentWidget::setSrcFile()
{
    srcmplayer->setFilePath( QFileDialog::getOpenFileName( this, "打开源视频", ".", tr("Avi 视频( *.avi )") ) );
    srcmplayer->load();
}

void CustomContentWidget::setTargetFile()
{
    targetmplayer->setFilePath( QFileDialog::getOpenFileName( this, "打开目标视频", ".", tr("Avi 视频( *.avi )") ) );
    targetmplayer->load();
}

void CustomContentWidget::showOutputWidget()
{
    outputText->show();
}

void CustomContentWidget::paintEvent(QPaintEvent *)
{
}

#include "opencvvideobox.h"
#include <QMessageBox>
#include <QPixmap>
#include <QPainter>

OpencvVideoBox::OpencvVideoBox(QWidget *parent) :
    QWidget(parent)
{
    videoPath = NULL;
    videoCapture = NULL;
    videoFakeScreen = NULL;
    videoFps = 0;
    videoFrame = NULL;
    videoScreen = NULL;
    videoFakeScreen = NULL;

    // although I didn't do, but
    // maybe we shoulde set a max size of OpencvVideoBox

    // accept drag&drop
    setAcceptDrops( true );

}

void OpencvVideoBox::loadVideos( const QString &tmpVideoPath )
{
    try {
        // load the videos, throw errors
        // create video file capture
        videoCapture = cvCreateFileCapture( tmpVideoPath.toLocal8Bit().data() );

        if ( videoCapture ) {
            // get the first frame of video
            videoFrame = cvQueryFrame( videoCapture );
            // setFixedSize so that the widget can always show whole image
            this->setFixedSize( videoFrame->width, videoFrame->height );
            // if no errors, then set videoPath
            videoPath = new QString( tmpVideoPath );

            // let the videoFakeScreen->imageData point to videoScreen->bits(),
            // so that they can share pixels' data
            videoScreen = new QImage( videoFrame->width, videoFrame->height,
                                      QImage::Format_RGB888 );
            videoFakeScreen = cvCreateImageHeader( cvSize( videoFrame->width,
                                                           videoFrame->height ), 8, 3 );
            videoFakeScreen->imageData = (char *)videoScreen->bits();

            // set videoFps&interval in order to play videos at a normal speed
            // connect timeout() signal to nextframe()
            videoFps = cvGetCaptureProperty( videoCapture, CV_CAP_PROP_FPS );
            videoTimer = new QTimer( this );
            videoTimer->setInterval( (int)( 1000.0 / videoFps ) );
            connect( videoTimer, SIGNAL( timeout() ),
                     this, SLOT( nextFrame() ) );

            // here should be noted! Dose videoTimer start here good ?
            videoTimer->start();

        } else {
            throw 1;
        }
    }
    catch ( int errNum ) {
        // judge what errors occured
        switch ( errNum )
        {
        case 1:
            QMessageBox::information( this, "error", "Please choose a valid file");
            break;
        default:
            ;
        }
    }
}

void OpencvVideoBox::paintEvent( QPaintEvent *event )
{
    if ( videoPath ) { // judged by videoPath
        QPainter painter( this );
        // play videos here
        painter.drawImage( 0, 0, *videoScreen );
    }
}

void OpencvVideoBox::nextFrame()
{
    videoFrame = cvQueryFrame( videoCapture );
    refreshScreen( videoFrame );
}

void OpencvVideoBox::refreshScreen( IplImage *frame )
{
    if ( frame ) {
        if ( frame->origin == IPL_ORIGIN_TL )
            cvCopy( frame, videoFakeScreen, 0 );
        else
            cvFlip( frame, videoFakeScreen, 0 );
        cvCvtColor( videoFakeScreen, videoFakeScreen, CV_BGR2RGB );
        this->update();
    }
}

void OpencvVideoBox::dragEnterEvent( QDragEnterEvent *event )
{
    // if videoPath is NULL( the OpencvVideoBox is not playing videos)
    // then process it
    if ( event->mimeData()->hasFormat("text/uri-list") && !videoPath ) {
        event->acceptProposedAction();
    } else {
        event->ignore();
    }
}

void OpencvVideoBox::dropEvent( QDropEvent *event )
{
    QList<QUrl> urls = event->mimeData()->urls();
    if ( urls.isEmpty() )
        return ;
    QString tmpVideoPath = urls.first().toLocalFile();
    if ( tmpVideoPath.isEmpty() )
        return ;
    this->loadVideos( tmpVideoPath );
}

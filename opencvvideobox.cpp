#include "opencvvideobox.h"
#include <QMessageBox>
#include <QPixmap>
#include <QPainter>

opencvVideoBox::opencvVideoBox(QWidget *parent) :
    QWidget(parent)
{
    // let videoScreen load a.jpg for test
    this->setFixedSize( 150, 150 );
}

void opencvVideoBox::loadVideos( const QString &tmpVideoPath )
{
    try {
        // load the videos, throw errors
        videoScreen.load( tmpVideoPath );
        this->resize( videoScreen.size() );
    }
    catch ( int errNum ) {
        // judge what errors occured
        switch ( errNum )
        {
            default:
                ;
        }
    }
    // if no errors, then set videoPath
    videoPath = tmpVideoPath;
}

void opencvVideoBox::paintEvent( QPaintEvent *event )
{
    QPainter painter( this );
    // play videos here
    painter.drawImage( 0, 0, videoScreen );
}

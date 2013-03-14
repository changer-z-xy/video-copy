#ifndef OPENCVVIDEO_H
#define OPENCVVIDEO_H

#include <QWidget>
#include <QTimer>
#include <QImage>
#include <QString>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include "cv.h"
#include "highgui.h"

class opencvVideoBox : public QWidget
{
    Q_OBJECT
public:
    explicit opencvVideoBox(QWidget *parent = 0);
    void loadVideos( const QString &tmpVideoPath );
    void paintEvent( QPaintEvent *event );

protected:
    void dragEnterEvent( QDragEnterEvent *event );
    void dropEvent( QDropEvent *event );

private slots:
    void nextFrame( );

private:
    void refreshScreen( IplImage *frame );
    QString *videoPath;
    QImage *videoScreen;
    QTimer *videoTimer;
    IplImage *videoFrame;
    IplImage *videoFakeScreen;
    CvCapture *videoCapture;
    int videoFps;
};

#endif // OPENCVVIDEO_H

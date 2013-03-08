#ifndef OPENCVVIDEO_H
#define OPENCVVIDEO_H

#include <QWidget>

class opencvVideoBox : public QWidget
{
    Q_OBJECT
public:
    explicit opencvVideoBox(QWidget *parent = 0);
    void loadVideos( const QString &tmpVideoPath );
    void paintEvent( QPaintEvent *event );

signals:
    
public slots:

private:
    QString videoPath;
    QImage videoScreen;
};

#endif // OPENCVVIDEO_H

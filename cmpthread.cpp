#include "videoCopy.h"

#define __PANYUFENG__

QMutex outputMutex;
QWaitCondition outputNotEmpty;
QQueue<QString> outputQueue;

CmpThread::CmpThread( QObject *parent ) :
     QThread(parent)
{
}

void CmpThread::run()
{
    bool isSame = true;
#ifdef __PANYUFENG__
    Get_Frame srcVideo( src.toLocal8Bit().data() );
    if ( !srcVideo.cap ) {
        outputAdd("capture failed");
        return ;
    }
    outputAdd(QString("srcVideo.num_frame is: %1").arg(srcVideo.num_frame));
    key_frame srcKeyFrame( srcVideo, this, "" );
    Get_Frame targetVideo( target.toLocal8Bit().data() );
    if ( !targetVideo.cap ) {
        outputAdd("capture failed");
        return ;
    }
    outputAdd(QString("targetVideo.num_frame is: %1").arg(targetVideo.num_frame));
    key_frame targetKeyFrame( targetVideo, this, "" );
    isSame = srcKeyFrame.cp_video(targetKeyFrame);
    outputAdd(QString("两视频是: %1").arg(isSame ? "相同的" : "不同的"));
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
    emit compareEnd(isSame);
}

void CmpThread::setSrc( QString _src )
{
    src = _src;
}

void CmpThread::setTarget( QString _target )
{
    target = _target;
}

void CmpThread::outputAdd(const QString &text)
{
    outputMutex.lock();
    outputQueue.enqueue(text);
    outputNotEmpty.wakeOne();
    outputMutex.unlock();
    emit outputNewItem();
}

void CmpThread::outputClear()
{
    outputMutex.lock();
    while (!outputQueue.empty()) {
        outputQueue.dequeue();
    }
    outputMutex.unlock();
    emit outputCleared();
}

#include "cmpworker.h"

int CmpWorker::count = 0;

CmpWorker::CmpWorker(CmpPoolManager *_pm, QObject *parent)
    : QObject(parent)
{
    pm = _pm;
    no = count++;
    taskState = 0;
}

bool CmpWorker::cmpTwoFiles(const QString &fa, const QString &fb)
{
    bool ans = false;
#ifdef __COLOR_HISTOGRAM__
    Get_Frame srcVideo( fa.toLocal8Bit().data() );
    if ( !srcVideo.cap ) {
        output("capture failed");
        return false;
    }
    output(QString("srcVideo.num_frame is: %1").arg(srcVideo.num_frame));
    key_frame srcKeyFrame( srcVideo, this, fa );
    Get_Frame targetVideo( fb.toLocal8Bit().data() );
    if ( !targetVideo.cap ) {
        if (enableOutput)
            output("capture failed");
        return false;
    }
    output(QString("targetVideo.num_frame is: %1").arg(targetVideo.num_frame));
    key_frame targetKeyFrame( targetVideo, this, fb );
    ans = srcKeyFrame.cp_video(targetKeyFrame);
    output(QString("两视频是: %1").arg(ans ? "同源的" : "不同源的"));
#endif
    return ans;
}

void CmpWorker::output(const QString &text)
{
    if (!enableOutput)
        return;
    CmpOutputEvent *oe = new CmpOutputEvent();
    oe->setContent(text);
    oe->setTaskNo(taskNo);
    QApplication::postEvent((QObject*)consignor, oe);
}

int CmpWorker::getNo()
{
    return no;
}

int CmpWorker::getCount()
{
    return count;
}

int CmpWorker::getTaskState()
{
    return taskState;
}

bool CmpWorker::event(QEvent *e)
{
    if (e->type() == CmpTaskEventType) {
        CmpTaskEvent *tmp = static_cast<CmpTaskEvent *>(e);
        processTaskEvent(tmp);
        return true;
    }
    return QObject::event(e);
}

void CmpWorker::processTaskEvent(CmpTaskEvent *event)
{
    taskState = 1;
    consignor = event->getConsignor();
    enableOutput = event->getEnableOutput();
    taskNo = event->getTaskNo();
    bool ans = cmpTwoFiles(event->getFa(), event->getFb());
    CmpTaskEvent *tmp = new CmpTaskEvent(*event);
    tmp->setAns(ans);
    QApplication::postEvent((QObject*)(tmp->getConsignor()), tmp);
    taskState = 0;
}

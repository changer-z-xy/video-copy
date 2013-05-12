#include "cmpconsignor.h"

CmpConsignor::CmpConsignor(CmpPoolManager *_pm, QObject *parent)
    : pm(_pm), QObject(parent)
{
}

void CmpConsignor::addTask(const QString &fa,
                           const QString &fb,
                           bool enableOutput,
                           int taskNo)
{
    qDebug() << "CmpConsignor::addTask";
    CmpTaskEvent *te = new CmpTaskEvent();
    te->setFiles(fa, fb);
    te->setConsignor(this);
    te->setTaskNo(taskNo);
    te->setEnableOutput(enableOutput);
    te->setAns(-1);
    QApplication::postEvent((QObject*)(pm), te);
}

QQueue<QString> &CmpConsignor::getOq()
{
    return oq;
}

bool CmpConsignor::event(QEvent *e)
{
    qDebug() << "CmpConsignor::event";
    if (e->type() == CmpOutputEventType) {
        qDebug() << "e->type() == CmpOutputEventType";
        CmpOutputEvent *tmp = static_cast<CmpOutputEvent *>(e);
        processOutputEvent(tmp);
        return true;
    }
    if (e->type() == CmpTaskEventType) {
        qDebug() << "e->type() == CmpTaskEventType";
        CmpTaskEvent *tmp = static_cast<CmpTaskEvent *>(e);
        processTaskEvent(tmp);
        return true;
    }
    return QObject::event(e);
}

void CmpConsignor::processOutputEvent(CmpOutputEvent *event)
{
    CmpOutputEvent *tmp = new CmpOutputEvent(*event);
    oq.push_back(tmp->getContent());
    emit oqNotEmpty();
    event->accept();
}

void CmpConsignor::processTaskEvent(CmpTaskEvent *event)
{
    qDebug() << "CmpConsignor::processTaskEvent";
    bool ans = (event->getAns() == 1);
    qDebug() << ans;
    emit cmpEnd(event->getTaskNo(), ans);
    event->accept();
}

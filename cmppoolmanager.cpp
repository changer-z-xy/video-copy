#include "cmppoolmanager.h"

CmpPoolManager::CmpPoolManager(int ps, QObject *parent) :
    QObject(parent), poolSize(ps)
{
    pool.resize(poolSize);
    workers.resize(poolSize);
    for (int i = 0; i < poolSize; ++i) {
        pool[i] = new QThread();
        workers[i] = new CmpWorker(this);
        workers[i]->moveToThread(pool[i]);
        pool[i]->start();
        fq.push_back(workers[i]);
    }
}

CmpWorker * CmpPoolManager::getFreeWorker()
{
    if (fq.isEmpty())
        return NULL;
    return fq.dequeue();
}

bool CmpPoolManager::event(QEvent *e)
{
    qDebug() << "CmpPoolManager::event";
    if (e->type() == CmpTaskEventType) {
        qDebug() << "e->type() == CmpTaskEventType";
        CmpTaskEvent *te = static_cast<CmpTaskEvent *>(e);
        if (te->getAns() == -1) {
            qDebug() << "te->getAns() == -1";
            processCmpTask(te);
        } else {
            qDebug() << "else";
            reportCmpTask(te);
        }
        return true;
    }
    return QObject::event(e);
}

void CmpPoolManager::processCmpTask(CmpTaskEvent *event)
{
    qDebug() << "CmpPoolManager::processCmpTask";
    CmpTaskEvent *tmp = new CmpTaskEvent(*event);
    tq.enqueue(tmp);
    checkfree();
    event->accept();
}

void CmpPoolManager::reportCmpTask(CmpTaskEvent *event)
{
    CmpTaskEvent *tmp = new CmpTaskEvent(*event);
    QApplication::postEvent((QObject*)(tmp->getConsignor()), tmp);
    checkfree();
    event->accept();
}

void CmpPoolManager::checkfree()
{
    qDebug() << "checkfree";
    CmpWorker *worker = getFreeWorker();
    if (worker != NULL) {
        qDebug() << "worker != NULL";
        if (!tq.isEmpty()) {
            qDebug() << "!tq.isEmpty()";
            CmpTaskEvent *tmp = tq.dequeue();
            tmp->setWorker(worker);
            QApplication::postEvent((QObject*)worker, tmp);
        }
    }
}

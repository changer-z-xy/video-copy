#ifndef CMPPOOLMANAGER_H
#define CMPPOOLMANAGER_H

#include <QObject>
#include <QMutex>
#include <QWaitCondition>
#include <QQueue>
#include <QDebug>

#include "cmpworker.h"
#include "cmptaskevent.h"

class CmpConsignor;

class CmpPoolManager : public QObject
{
    Q_OBJECT
public:
    explicit CmpPoolManager(int ps, QObject *parent = 0);
    CmpWorker *getFreeWorker();
protected:
    bool event(QEvent *e);
    void processCmpTask(CmpTaskEvent *event);
    void reportCmpTask(CmpTaskEvent *event);
    void checkfree();
private:
    int poolSize;
    QQueue<CmpWorker *> fq;
    QQueue<CmpTaskEvent *> tq;
    QVector<CmpWorker *> workers;
    QVector<QThread *> pool;
};

#endif // CMPPOOLMANAGER_H

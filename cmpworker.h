#ifndef CMPWORKER_H
#define CMPWORKER_H

#include <QApplication>
#include <QDebug>
#include <QString>

#include "abc.h"
#include "cmpevent.h"

#define __COLOR_HISTOGRAM__

class CmpPoolManager;
class CmpConsignor;

class CmpWorker : public QObject
{
    Q_OBJECT
public:
    explicit CmpWorker(CmpPoolManager *_pm, QObject *parent = 0);
    int getNo();
    int getCount();
    int getTaskState();
    void output(const QString &text);
    bool cmpTwoFiles(const QString &fa, const QString &fb);
private:
    int no;
    static int count;
    /* 0: initial state( is free )
     * 1: is busy
     */
    int taskState;
    int taskNo;
    bool enableOutput;
    CmpPoolManager *pm;
    CmpConsignor *consignor;
signals:
    void cmpTwoFilesEnd(bool ans);
protected:
    bool event(QEvent *event);
    void processTaskEvent(CmpTaskEvent *event);
};

#endif // CMPWORKER_H

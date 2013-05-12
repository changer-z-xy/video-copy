#ifndef CMPCONSIGNOR_H
#define CMPCONSIGNOR_H

#include <QApplication>
#include <QObject>
#include <QQueue>
#include <QDebug>

#include "cmpevent.h"

class CmpPoolManager;

class CmpConsignor : public QObject
{
    Q_OBJECT
public:
    explicit CmpConsignor(CmpPoolManager *_pm, QObject *parent = 0);
    QQueue<QString> &getOq();
protected:
    bool event(QEvent *event);
    void processOutputEvent(CmpOutputEvent *event);
    void processTaskEvent(CmpTaskEvent *event);
private:
    CmpPoolManager *pm;
    QQueue<QString> oq;
signals:
    void cmpEnd(int taskNo, bool ans);
    void oqNotEmpty();
public slots:
    void addTask(const QString &fa,
                 const QString &fb,
                 bool enableOutput,
                 int taskNo);
};

#endif // CMPCONSIGNOR_H

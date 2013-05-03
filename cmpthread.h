#ifndef CMPTHREAD_H
#define CMPTHREAD_H

#include <QThread>
#include <QDebug>
#include <QString>
#include <QQueue>
#include "abc.h"

class CmpThread : public QThread
{
    Q_OBJECT
public:
    explicit CmpThread( QObject *parent = 0);
    void setSrc( QString _src );
    void setTarget( QString _target );
    void outputAdd(const QString &text);
    void outputClear();
private:
    QString src;
    QString target;
signals:
    void compareEnd(bool ans);
    void outputNewItem();
    void outputCleared();
protected:
    void run();
};

#endif // CMPTHREAD_H

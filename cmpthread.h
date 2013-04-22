#ifndef CMPTHREAD_H
#define CMPTHREAD_H

#include <QThread>

class CmpThread : public QThread
{
    Q_OBJECT
public:
    explicit CmpThread(QObject *parent = 0, QString srcFilePath, QString targetFilePath);
private:
    void run();
signals:
    
public slots:
    
};

#endif // CMPTHREAD_H

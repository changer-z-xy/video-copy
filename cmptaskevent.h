#ifndef CMPTASKEVENT_H
#define CMPTASKEVENT_H

#include <QEvent>
#include <QString>

class CmpConsignor;
class CmpWorker;

extern const QEvent::Type CmpTaskEventType;

class CmpTaskEvent : public QEvent
{
public:
    CmpTaskEvent();
    const QString& getFa();
    const QString& getFb();
    int getAns();
    int getTaskNo();
    bool getEnableOutput();
    CmpConsignor *getConsignor();
    CmpWorker *getWorker();
    void setFiles(const QString& _fa,
                  const QString& _fb);
    void setAns(int _ans);
    void setTaskNo(int no);
    void setEnableOutput(bool eo);
    void setConsignor(CmpConsignor *_consignor);
    void setWorker(CmpWorker *_worker);
private:
    QString fa;
    QString fb;
    /* ans == -1: not compeleted
     * ans == 0 : false
     * ans == 1 : true
     */
    int ans;
    int taskNo;
    bool enableOutput;
    CmpConsignor *consignor;
    CmpWorker *worker;
};

#endif // CMPTASKEVENT_H

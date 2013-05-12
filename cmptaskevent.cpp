#include "cmptaskevent.h"

const QEvent::Type CmpTaskEventType = QEvent::User;

CmpTaskEvent::CmpTaskEvent()
    : QEvent(CmpTaskEventType)
{

}

void CmpTaskEvent::setAns(int _ans)
{
    ans = _ans;
}

void CmpTaskEvent::setTaskNo(int no)
{
    taskNo = no;
}

void CmpTaskEvent::setEnableOutput(bool eo)
{
    enableOutput = eo;
}

void CmpTaskEvent::setFiles(const QString &_fa, const QString &_fb)
{
    fa = _fa;
    fb = _fb;
}

void CmpTaskEvent::setConsignor(CmpConsignor *_consignor)
{
    consignor = _consignor;
}

void CmpTaskEvent::setWorker(CmpWorker *_worker)
{
    worker = _worker;
}

const QString& CmpTaskEvent::getFa()
{
    return fa;
}

const QString& CmpTaskEvent::getFb()
{
    return fb;
}

int CmpTaskEvent::getAns()
{
    return ans;
}

int CmpTaskEvent::getTaskNo()
{
    return taskNo;
}

bool CmpTaskEvent::getEnableOutput()
{
    return enableOutput;
}

CmpConsignor *CmpTaskEvent::getConsignor()
{
    return consignor;
}

CmpWorker *CmpTaskEvent::getWorker()
{
    return worker;
}

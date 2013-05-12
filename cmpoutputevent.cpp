#include "cmpoutputevent.h"

const QEvent::Type CmpOutputEventType = QEvent::Type(QEvent::User + 1);

CmpOutputEvent::CmpOutputEvent()
    : QEvent(CmpOutputEventType)
{

}

void CmpOutputEvent::setContent(const QString& _content)
{
    content = _content;
}

const QString& CmpOutputEvent::getContent()
{
    return content;
}

int CmpOutputEvent::getTaskNo()
{
    return taskNo;
}

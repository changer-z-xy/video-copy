#ifndef CMPOUTPUTEVENT_H
#define CMPOUTPUTEVENT_H

#include <QEvent>
#include <QString>

extern const QEvent::Type CmpOutputEventType;

class CmpOutputEvent : public QEvent
{
public:
    CmpOutputEvent();
    const QString &getContent();
    void setContent(const QString& _content);
    void setTaskNo(int no);
    int getTaskNo();
private:
    int taskNo;
    QString content;
};

#endif // CMPOUTPUTEVENT_H

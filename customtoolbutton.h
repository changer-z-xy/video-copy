#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H

#include <QToolButton>

class CustomToolButton : public QToolButton
{
    Q_OBJECT
private:
    QString strImage;
    QString strInfo;
public:
    explicit CustomToolButton( const QString &strImage,
                           const QString &strInfo,
                           Qt::ToolButtonStyle style = Qt::ToolButtonIconOnly,
                           QWidget *parent = 0 );
signals:
    
};

#endif // CUSTOMBUTTON_H

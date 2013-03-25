#ifndef CUSTOMBUTTON_H
#define CUSTOMBUTTON_H

#include <QToolButton>
#include <QPainter>
#include <QMouseEvent>

class CustomToolButton : public QToolButton
{
    Q_OBJECT
private:
    QString strImage;
    QString strInfo;
    bool isPressed;
    bool isOver;
public:
    explicit CustomToolButton( const QString &strImage,
                           const QString &strInfo,
                           Qt::ToolButtonStyle style = Qt::ToolButtonIconOnly,
                           QWidget *parent = 0 );
signals:
protected:
    void paintEvent( QPaintEvent *event );
    void mousePressEvent( QMouseEvent *event );
    void enterEvent( QMouseEvent *event );
    void leaveEvent( QMouseEvent *event );
    void mouseReleaseEvent( QMouseEvent *event );
    
};

#endif // CUSTOMBUTTON_H

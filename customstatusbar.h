#ifndef CUSTOMSTATUSBAR_H
#define CUSTOMSTATUSBAR_H

#include <QStatusBar>
#include <QPainter>

extern const int STATUSBAR_HEIGHT;

class CustomStatusBar : public QWidget
{
    Q_OBJECT
public:
    explicit CustomStatusBar(QWidget *parent = 0);
    ~CustomStatusBar();
signals:
    
public slots:

protected:
    void paintEvent( QPaintEvent *event );
    
};

#endif // CUSTOMSTATUSBAR_H

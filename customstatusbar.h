#ifndef CUSTOMSTATUSBAR_H
#define CUSTOMSTATUSBAR_H

#include <QStatusBar>
#include <QPainter>

const int STATUSBAR_HEIGHT = 30;

class CustomStatusBar : public QWidget
{
    Q_OBJECT
public:
    explicit CustomStatusBar(QWidget *parent = 0) : QWidget(parent);
    ~CustomStatusBar();
signals:
    
public slots:

protected:
    void paintEvent( QPaintEvent *event );
    
};

#endif // CUSTOMSTATUSBAR_H

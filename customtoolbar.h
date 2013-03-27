#ifndef CUSTOMTOOLBAR_H
#define CUSTOMTOOLBAR_H

#include <QToolBar>
#include <QHBoxLayout>
#include <QPainter>
#include "customtoolbutton.h"

class CustomToolBar : public QWidget
{
    Q_OBJECT
private:
    QList<CustomToolButton*> listCustomButton;
public:
    explicit CustomToolBar(QWidget *parent = 0);
    ~CustomToolBar();
signals:
    
public slots:
    
protected:
    void paintEvent( QPaintEvent *event );
};

#endif // CUSTOMTOOLBAR_H

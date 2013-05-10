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
signals:
    void showPageAt( int index );
public slots:
    void childPressed( CustomToolButton *child );
};

#endif // CUSTOMTOOLBAR_H

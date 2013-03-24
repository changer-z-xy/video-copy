#ifndef CUSTOMTOOLBAR_H
#define CUSTOMTOOLBAR_H

#include <QToolBar>
#include <QHBoxLayout>
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
    
};

#endif // CUSTOMTOOLBAR_H

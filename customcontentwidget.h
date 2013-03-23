#ifndef CUSTOMCONTENTWIDGET_H
#define CUSTOMCONTENTWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPainter>
#include "contentpage1.h"

class CustomContentWidget : public QWidget
{
    Q_OBJECT
private:
    QPixmap *myPix;
    ContentPage1 *myPage1;
public:
    explicit CustomContentWidget(QWidget *parent = 0);
    ~CustomContentWidget();
protected:
    void paintEvent(QPaintEvent *evemt);
signals:
    
public slots:
    
};

#endif // CUSTOMCONTENTWIDGET_H

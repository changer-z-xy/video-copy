#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QPushButton>
#include "opencvvideobox.h"

class Widget : public QWidget
{
    Q_OBJECT
    
public:
    Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    bool cmpVideos( );
    void openSrcClicked();
    void openTargetClicked();

private:
    QPushButton *cmpButton;
    QPushButton *openSrcButton;
    QPushButton *openTargetButton;
    opencvVideoBox *srcVideoBox;
    opencvVideoBox *targetVideoBox;
};

#endif // WIDGET_H

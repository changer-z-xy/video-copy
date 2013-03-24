#ifndef CONTENTPAGE1_H
#define CONTENTPAGE1_H

#include <QWidget>
#include <QPushButton>
#include "opencvvideobox.h"

class ContentPage1 : public QWidget
{
    Q_OBJECT
    
public:
    ContentPage1(QWidget *parent = 0);
    ~ContentPage1();

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

#endif // CONTENTPAGE1_H

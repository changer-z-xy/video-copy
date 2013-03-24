#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QToolBar>
#include <QStatusBar>
#include "customtitlebar.h"
#include "customtoolbar.h"
#include "customcontentwidget.h"
#include "customstatusbar.h"

class CustomWidget : public QFrame
{
    Q_OBJECT
private:
    CustomTitleBar *myTitleBar;
    CustomToolBar *myToolBar;
    CustomContentWidget *myContentWidget;
    CustomStatusBar *myStatusBar;
public:
    CustomWidget(QWidget *parent = 0);
    ~CustomWidget();
protected:
    void paintEvent(QPaintEvent *);
//    void mouseReleaseEvent(QMouseEvent *event);
//    void mouseMoveEvent(QMouseEvent *event);
//    void mousePressEvent(QMouseEvent *event);
public slots:
    void showMaxRestore();
};

#endif // CUSTOMWIDGET_H

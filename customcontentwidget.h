#ifndef CUSTOMCONTENTWIDGET_H
#define CUSTOMCONTENTWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QProcess>
#include <QTimeLine>
#include <QtWebKitWidgets/QWebView>
#include <QMessageBox>
#include <QPushButton>
#include "contentpage.h"
#include "mplayerwidget.h"
#include "customwebpage.h"
#include "abc.h"
#include "copydetection.h"
#include "cmpthread.h"
#include "cmpoutputwidget.h"

class CustomWidget;

class CustomContentWidget : public QWidget
{
    Q_OBJECT
private:
    QVector<ContentPage *> myPages;
    int curPageIndex;
    int subPageWidth;
    int subPageHeight;
    CmpThread *cmpThread;
    CmpOutputWidget *outputText;
    MPlayerWidget *srcmplayer;
    CustomToolButton *loadSrc;
    CustomToolButton *pauseSrc;
    CustomToolButton *stopSrc;
    MPlayerWidget *targetmplayer;
    CustomToolButton *loadTarget;
    CustomToolButton *pauseTarget;
    CustomToolButton *stopTarget;
    QPushButton *cmpVideos;
    QPushButton *showOutputButton;
public:
    explicit CustomContentWidget(QWidget *parent = 0);
    ~CustomContentWidget();
    int getCntPages();
public slots:
    void showPageAt( int index );
    void moveToLeft( int x );
    void setSrcFile();
    void setTargetFile();
    void compareVideos();
//    void showAns(bool);
    void showOutputWidget();
protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent( QResizeEvent *event );
};

#endif // CUSTOMCONTENTWIDGET_H

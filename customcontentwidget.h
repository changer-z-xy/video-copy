#ifndef CUSTOMCONTENTWIDGET_H
#define CUSTOMCONTENTWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QProcess>
#include <QTimeLine>
#include <QtWebKitWidgets/QWebView>
#include <QMessageBox>
#include <QPushButton>
#include <QStackedWidget>
#include <QFileDialog>
#include "contentpage.h"
#include "mplayerwidget.h"
#include "customwebpage.h"
#include "abc.h"
#include "copydetection.h"
#include "cmpthread.h"
#include "cmpoutputwidget.h"

class CustomContentWidget : public QWidget
{
    Q_OBJECT
private:
    QStackedWidget *myPages;
    int curPageIndex;
    int subPageWidth;
    int subPageHeight;
    CmpThread *cmpThread;
    CmpOutputWidget *outputText;
    MPlayerWidget *srcmplayer;
    MPlayerWidget *targetmplayer;
    QPushButton *cmpVideos;
    QPushButton *showOutputButton;
public:
    explicit CustomContentWidget(QWidget *parent = 0);
    ~CustomContentWidget();
    int getCntPages();
public slots:
    void showPageAt( int index );
    void setSrcFile();
    void setTargetFile();
    void compareVideos();
    void showOutputWidget();
protected:
    void resizeEvent( QResizeEvent *event );
    void paintEvent(QPaintEvent *);
};

#endif // CUSTOMCONTENTWIDGET_H

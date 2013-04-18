#ifndef CUSTOMCONTENTWIDGET_H
#define CUSTOMCONTENTWIDGET_H

#include <QWidget>
#include <QPainter>
#include <QProcess>
#include <QTimeLine>
#include <QtWebKitWidgets/QWebView>
#include <QPushButton>
#include "contentpage.h"
#include "mplayerwidget.h"
#include "customwebpage.h"

class CustomContentWidget : public QWidget
{
    Q_OBJECT
private:
    QVector<ContentPage *> myPages;
    int curPageIndex;
public:
    explicit CustomContentWidget(QWidget *parent = 0);
    ~CustomContentWidget();
    int getCntPages();
public slots:
    void showPageAt( int index );
    void moveToLeft( int x );
protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent( QResizeEvent *event );
};

#endif // CUSTOMCONTENTWIDGET_H

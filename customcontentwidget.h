#ifndef CUSTOMCONTENTWIDGET_H
#define CUSTOMCONTENTWIDGET_H

#include <QWidget>
#include <QPixmap>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPainter>
#include <QProcess>
#include <QtWebKitWidgets/QWebView>
#include "contentpage.h"

class CustomContentWidget : public QWidget
{
    Q_OBJECT
private:
    QVector<ContentPage *> myPages;
public:
    explicit CustomContentWidget(QWidget *parent = 0);
    ~CustomContentWidget();
public slots:
    void showPageAt( int index );
protected:
    void paintEvent(QPaintEvent *event);
};

#endif // CUSTOMCONTENTWIDGET_H

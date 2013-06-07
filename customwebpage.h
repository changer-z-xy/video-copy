#ifndef CUSTOMWEBPAGE_H
#define CUSTOMWEBPAGE_H

#include <QWebView>
#include <QThread>
#include <QResizeEvent>
#include <QHBoxLayout>

class CustomWebPage : public QWidget
{
    Q_OBJECT
public:
    explicit CustomWebPage(QWidget *parent = 0);
protected:

signals:
    
public slots:
private:
    QWebView *webview;
};

#endif // CUSTOMWEBPAGE_H

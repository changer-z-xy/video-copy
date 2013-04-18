#ifndef CUSTOMWEBPAGE_H
#define CUSTOMWEBPAGE_H

#include <QWebView>
#include <QResizeEvent>

class CustomWebPage : public QWebView
{
    Q_OBJECT
public:
    explicit CustomWebPage(QWidget *parent = 0);
protected:
    void resizeEvent( QResizeEvent *event );
signals:
    
public slots:

};

#endif // CUSTOMWEBPAGE_H

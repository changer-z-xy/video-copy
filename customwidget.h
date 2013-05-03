#ifndef CUSTOMWIDGET_H
#define CUSTOMWIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QDebug>
#include <QLinearGradient>
#include <QFrame>
#include <QBitmap>
#include <QPainter>
#include <QMouseEvent>

class CustomWidget : public QFrame
{
    Q_OBJECT
private:
    QPoint cursor;
public:
    CustomWidget(QWidget *parent = 0);
protected:
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent( QMouseEvent *event );
    void mousePressEvent( QMouseEvent *event );
public slots:
    void showMaxRestore();
};

#endif // CUSTOMWIDGET_H

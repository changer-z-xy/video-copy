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

const int MinWidth = 850;
const int MinHeight = 600;

class CustomWidget : public QFrame
{
    Q_OBJECT
private:
    QPoint preCursorPos;
    QPoint preWidgetPos;
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

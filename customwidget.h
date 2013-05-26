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
#include <QPaintEvent>

class CustomWidget : public QFrame
{
    Q_OBJECT
private:
    QPoint preCursorPos;
    QPoint preWidgetPos;
    int dir;
public:
    CustomWidget(QWidget *parent = 0);
    void setCursorStyle(int _dir);
    void borderResize(int dx, int dy);
    void borderResize(const QPoint &curPos);
    int calcDir(int x, int y);
protected:
    void paintEvent(QPaintEvent *event);
    void mouseMoveEvent( QMouseEvent *event );
    void mousePressEvent( QMouseEvent *event );
    void mouseReleaseEvent(QMouseEvent *event);
public slots:
    void showMaxRestore();
};

#endif // CUSTOMWIDGET_H

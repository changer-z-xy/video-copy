#ifndef HistgramWidget_H
#define HistgramWidget_H

#include <QWidget>
#include <QPainter>
#include <QDebug>
#include <cstdlib>
#include <algorithm>

class HistgramWidget : public QWidget
{
    Q_OBJECT
public:
    explicit HistgramWidget(QWidget *parent = 0);
    HistgramWidget( QWidget *parent, int *histgram );
    ~HistgramWidget();
protected:
    void paintEvent( QPaintEvent *event );
private:
    int *histArray;
    int *histSeg;
signals:
    
public slots:
    
};

#endif // HistgramWidget_H

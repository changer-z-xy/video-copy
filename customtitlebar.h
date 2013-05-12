#ifndef MYTITLEBAR_H
#define MYTITLEBAR_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QDebug>
#include <QMessageBox>
#include <QToolButton>
#include <QPixmap>
#include <QStyle>
#include <QCoreApplication>

#include "customtoolbutton.h"

extern const int TITLEBAR_HEIGHT;

class CustomTitleBar : public QWidget
{
    Q_OBJECT
private:
    QWidget *parent;
    QLabel *iconLabel;
    QLabel *titleLabel;
    CustomToolButton *minButton;
    CustomToolButton *maxButton;
    CustomToolButton *closeButton;

public:
    explicit CustomTitleBar(QWidget *parent, const QString &title);
    ~CustomTitleBar();
signals:
    void closeButtonClicked();
    void minButtonClicked();
    void maxButtonClicked();
public slots:
    
protected:
    void mouseDoubleClickEvent( QMouseEvent * );
};

#endif // MYTITLEBAR_H

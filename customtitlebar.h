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
#include <QStyle>

class CustomTitleBar : public QWidget
{
    Q_OBJECT
private:
    QWidget *parent;
    QLabel *iconLabel;
    QLabel *titleLabel;
    QToolButton *minButton;
    QToolButton *maxButton;
    QToolButton *closeButton;

public:
    explicit CustomTitleBar(QWidget *parent);
    QToolButton *getMinButton();
    QToolButton *getMaxButton();
    QToolButton *getCloseButton();
    ~CustomTitleBar();
signals:
    
public slots:
    
protected:
    void mouseDoubleClickEvent( QMouseEvent * );
};

#endif // MYTITLEBAR_H

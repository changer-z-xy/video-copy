#ifndef CUSTOMTREEWIDGET_H
#define CUSTOMTREEWIDGET_H

#include <QTreeWidget>
#include <QString>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>

#include "cmppoolmanager.h"
#include "cmpconsignor.h"

class CustomTreeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CustomTreeWidget(CmpPoolManager *_pm, QWidget *parent = 0);

signals:
    
public slots:
    void insertItem();
    void deleteItem();
    void compareItems();
    void showAns(int _taskNo, bool _ans);
private:
    QTreeWidget *tw;
    QPushButton *btnAdd;
    QPushButton *btnRemove;
    QPushButton *btnCompare;
    CmpPoolManager *pm;
    CmpConsignor *consignor;
    int count;
};

#endif // CUSTOMTREEWIDGET_H

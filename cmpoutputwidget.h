#ifndef CMPOUTPUTWIDGET_H
#define CMPOUTPUTWIDGET_H

#include <QTextEdit>
#include <QPushButton>
#include <QQueue>

#include "abc.h"

#include "customwidget.h"
#include "customtitlebar.h"
#include "cmpconsignor.h"

class CmpOutputWidget : public CustomWidget
{
    Q_OBJECT
private:
    CustomTitleBar *myTitleBar;
    QTextEdit *outputTextArea;
    QPushButton *hideButton;
    QPushButton *clearButton;
    CmpConsignor *consignor;
public:
    CmpOutputWidget(CmpConsignor *_consignor, QWidget *parent = 0);
public slots:
    void addOutput();
    void clearOutput();
};

#endif // CMPOUTPUTWIDGET_H

#ifndef CMPOUTPUTWIDGET_H
#define CMPOUTPUTWIDGET_H

#include "customwidget.h"
#include "customtitlebar.h"
#include "abc.h"
#include <QTextEdit>
#include <QPushButton>
#include <QQueue>

class CmpOutputWidget : public CustomWidget
{
    Q_OBJECT
private:
    CustomTitleBar *myTitleBar;
    QTextEdit *outputTextArea;
    QPushButton *hideButton;
public:
    CmpOutputWidget(QWidget *parent = 0);
public slots:
    void addOutput();
    void clear();
};

#endif // CMPOUTPUTWIDGET_H

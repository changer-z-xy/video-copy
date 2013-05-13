#include "cmpoutputwidget.h"

CmpOutputWidget::CmpOutputWidget(CmpConsignor *_consignor, QWidget *parent)
    : CustomWidget(parent)
{
    consignor = _consignor;

    outputTextArea = new QTextEdit();
    myTitleBar = new CustomTitleBar(this, "视频比较输出");
    hideButton = new QPushButton("关闭");
    clearButton = new QPushButton("清空");

    QVBoxLayout *mainLayout = new QVBoxLayout( this );
    mainLayout->addWidget(myTitleBar);
    mainLayout->addWidget(outputTextArea);
    QHBoxLayout *btnLayout = new QHBoxLayout;
    btnLayout->addWidget(clearButton);
    btnLayout->addWidget(hideButton);
    btnLayout->setAlignment(Qt::AlignHCenter);
    btnLayout->setMargin(0);
    mainLayout->addLayout(btnLayout);
    mainLayout->setMargin(0);

    connect(hideButton, SIGNAL(clicked()),
            this, SLOT(hide()));
    connect(clearButton, SIGNAL(clicked()),
            this, SLOT(clearOutput()));
    connect(myTitleBar, SIGNAL(closeButtonClicked()),
            this, SLOT(hide()));
    connect(myTitleBar, SIGNAL(minButtonClicked()),
            this, SLOT(showMinimized()));
    connect(myTitleBar, SIGNAL(maxButtonClicked()),
            this, SLOT(showMaxRestore()));
    connect(consignor, SIGNAL(oqItemAdded()),
            this, SLOT(addOutput()));
}

void CmpOutputWidget::addOutput()
{
    if (!consignor->getOq().isEmpty()) {
        QString tmp = consignor->getOq().dequeue();
        outputTextArea->append(tmp);
    }
}

void CmpOutputWidget::clearOutput()
{
    outputTextArea->clear();
}

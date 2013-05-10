#include "videoCopy.h"

CmpOutputWidget::CmpOutputWidget(QWidget *parent) :
    CustomWidget(parent)
{
    outputTextArea = new QTextEdit();
    myTitleBar = new CustomTitleBar(this, "视频比较输出");
    hideButton = new QPushButton("关闭");

    QVBoxLayout *mainLayout = new QVBoxLayout( this );
    mainLayout->setAlignment(Qt::AlignHCenter);
    mainLayout->addWidget(myTitleBar);
    mainLayout->addWidget(outputTextArea);
    mainLayout->addWidget(hideButton);
    mainLayout->setSpacing(0);
    mainLayout->setMargin(0);

    connect(hideButton, SIGNAL(clicked()),
            this, SLOT(hide()));
    connect(myTitleBar, SIGNAL(closeButtonClicked()),
            this, SLOT(hide()));
    connect(myTitleBar, SIGNAL(minButtonClicked()),
            this, SLOT(showMinimized()));
    connect(myTitleBar, SIGNAL(maxButtonClicked()),
            this, SLOT(showMaxRestore()));
}

void CmpOutputWidget::addOutput()
{
    outputMutex.lock();
    if (outputQueue.empty())
        outputNotEmpty.wait(&outputMutex);
    outputTextArea->append(outputQueue.dequeue());
    outputMutex.unlock();
}

void CmpOutputWidget::clear()
{
    outputTextArea->clear();
}

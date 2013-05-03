#include "cmpoutputwidget.h"

CmpOutputWidget::CmpOutputWidget(QWidget *parent) :
    CustomWidget(parent)
{
    QVBoxLayout *mainLayout = new QVBoxLayout( this );
    mainLayout->setAlignment(Qt::AlignHCenter);
    // add myTitleBar
    myTitleBar = new CustomTitleBar(this, "视频比较输出");
    mainLayout->addWidget(myTitleBar);
    // add outputText
    outputTextArea = new QTextEdit();
    mainLayout->addWidget(outputTextArea);
    // add hideButton
    hideButton = new QPushButton("关闭");
    hideButton->resize(hideButton->sizeHint());
    mainLayout->addWidget(hideButton);
    connect(hideButton, SIGNAL(clicked()),
            this, SLOT(hide()));
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

#include "customwebpage.h"

CustomWebPage::CustomWebPage(QWidget *parent) :
    QWidget(parent)
{
    webview = new QWebView(this);
    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(webview);
}

#include "custommainwidget.h"

const int MinWidth = 850;
const int MinHeight = 600;

CustomMainWidget::CustomMainWidget(QWidget *parent) :
    CustomWidget(parent)
{
    setMinimumWidth( MinWidth );
    setMinimumHeight( MinHeight );
    setMouseTracking(true);

    QVBoxLayout *mainWidgetLayout = new QVBoxLayout(this);
    myTitleBar = new CustomTitleBar(this, "基于视频内容拷贝检测的认证系统");
    myTitleBar->setFixedHeight(TITLEBAR_HEIGHT);
    mainWidgetLayout->addWidget(myTitleBar);
    myToolBar = new CustomToolBar(this);
    myToolBar->setFixedHeight(TOOLBAR_HEIGHT);
    mainWidgetLayout->addWidget(myToolBar);
    myContentWidget = new CustomContentWidget(this);
    mainWidgetLayout->addWidget(myContentWidget);
    myStatusBar = new CustomStatusBar(this);
    myStatusBar->setFixedHeight(STATUSBAR_HEIGHT);
    myStatusBar->resize(width(), STATUSBAR_HEIGHT);
    mainWidgetLayout->addWidget(myStatusBar);
    mainWidgetLayout->setSpacing(0);
    mainWidgetLayout->setMargin(1);

    connect(myToolBar, SIGNAL(showPageAt(int)),
            myContentWidget, SLOT(showPageAt(int)));
    connect(myTitleBar, SIGNAL(closeButtonClicked()),
            QApplication::instance(), SLOT(quit()));
    connect(myTitleBar, SIGNAL(minButtonClicked()),
            this, SLOT(showMinimized()));
    connect(myTitleBar, SIGNAL(maxButtonClicked()),
            this, SLOT(showMaxRestore()));
}

void CustomMainWidget::resizeEvent(QResizeEvent *event)
{
    QWidget::resizeEvent( event );
}

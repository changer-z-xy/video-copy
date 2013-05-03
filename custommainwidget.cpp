#include "custommainwidget.h"

CustomMainWidget::CustomMainWidget(QWidget *parent) :
    CustomWidget(parent)
{
    setMinimumWidth( 850 );
    setMinimumHeight( 600 );

    QVBoxLayout *mainLayout = new QVBoxLayout( this );
    // add myTitleBar
    myTitleBar = new CustomTitleBar(this, "基于内容的视频版权注册认证系统");
    mainLayout->addWidget( myTitleBar );
    // add myToolBar
    myToolBar = new CustomToolBar( this );
    mainLayout->addWidget( myToolBar );
    // add myContentWidget
    myContentWidget = new CustomContentWidget( this );
    mainLayout->addWidget( myContentWidget );
    // add myStatusBar
    myStatusBar = new CustomStatusBar( this );
    mainLayout->addWidget( myStatusBar );
    // set mainLayout without spacing and margin
    mainLayout->setSpacing( 0 );
    mainLayout->setContentsMargins(0,0,0,0);

    connect( myToolBar, SIGNAL(showPageAt(int)),
             myContentWidget, SLOT(showPageAt(int)) );
}

void CustomMainWidget::resizeEvent(QResizeEvent *event)
{
    myContentWidget->resize( width() * myContentWidget->getCntPages(),
                             height() - STATUSBAR_HEIGHT - TITLEBAR_HEIGHT - TOOLBAR_HEIGHT );
    QWidget::resizeEvent( event );
}

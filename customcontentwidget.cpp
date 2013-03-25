#include "customcontentwidget.h"

CustomContentWidget::CustomContentWidget(QWidget *parent) :
    QWidget(parent)
{
    myPage1 = new ContentPage1( this );
    QHBoxLayout *mainLayout = new QHBoxLayout( this );
    mainLayout->addWidget( myPage1 );
    mainLayout->setSpacing( 0 );
    mainLayout->setContentsMargins( 0, 0, 0, 0 );
}

CustomContentWidget::~CustomContentWidget()
{

}

void CustomContentWidget::paintEvent(QPaintEvent *evemt)
{
}

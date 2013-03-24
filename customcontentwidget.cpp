#include "customcontentwidget.h"

CustomContentWidget::CustomContentWidget(QWidget *parent) :
    QWidget(parent)
{
    myPage1 = new ContentPage1( this );
    QHBoxLayout *mainLayout = new QHBoxLayout( this );
    mainLayout->addWidget( myPage1 );
}

CustomContentWidget::~CustomContentWidget()
{

}

void CustomContentWidget::paintEvent(QPaintEvent *evemt)
{
    QPainter *painter = new QPainter;
    painter->fillRect( rect(), Qt::yellow );
}

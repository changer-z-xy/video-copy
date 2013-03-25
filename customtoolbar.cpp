#include "customtoolbar.h"

CustomToolBar::CustomToolBar(QWidget *parent)
    : QWidget( parent )
{
    setFixedHeight( 80 );
    QHBoxLayout *toolBarLayout = new QHBoxLayout( this );
    QList<QString> strList;
    strList << "test1" << "test2" << "test3" << "test4";
    for ( int i = 0; i < 4; ++ i ) {
        QString strImage = QString(":/img/%1.png").arg( i + 1 );
        listCustomButton.append( new CustomToolButton( strImage,
                                                   strList.at( i ),
                                                   Qt::ToolButtonTextUnderIcon,
                                                   this ) );
        toolBarLayout->addWidget( listCustomButton.at( i ) );
    }
    toolBarLayout->addStretch();
    setContentsMargins( 0, 0, 0, 0 );
}

CustomToolBar::~CustomToolBar()
{
}

void CustomToolBar::paintEvent(QPaintEvent *event)
{
}

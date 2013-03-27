#include "customtoolbar.h"

CustomToolBar::CustomToolBar(QWidget *parent)
    : QWidget( parent )
{
    QHBoxLayout *toolBarLayout = new QHBoxLayout( this );
    setFixedHeight( 100 );
    setMouseTracking( true );
    QList<QString> strList;
    strList << "视频比较" << "直方图查看" << "上传视频" << "浏览网络" << "帮助";
    for ( int i = 0, sz = strList.size(); i < sz; ++ i ) {
        QString strImage = QString(":/img/%1.png").arg( i + 1 );
        listCustomButton.append( new CustomToolButton( strImage,
                                                   strList.at( i ),
                                                   Qt::ToolButtonTextUnderIcon,
                                                   this ) );
        toolBarLayout->addWidget( listCustomButton.at( i ) );
        listCustomButton.at( i )->setIconSize( QSize( 60, 60 ) );
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

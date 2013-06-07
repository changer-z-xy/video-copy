#include "customtoolbar.h"

const int TOOLBAR_HEIGHT = 100;

CustomToolBar::CustomToolBar(QWidget *parent)
    : QWidget( parent )
{
    QHBoxLayout *toolBarLayout = new QHBoxLayout( this );
    setMouseTracking( true );
    QList<QString> strList;
    strList << "视频比较" << "直方图查看" << "上传视频" << "多视频比较" << "帮助";
    for ( int i = 0, sz = strList.size(); i < sz; ++ i ) {
        QString strImage = QString(":/img/%1.png").arg( i + 1 );
        listCustomButton.append( new CustomToolButton( strImage,
                                                       strList.at( i ),
                                                       Qt::ToolButtonTextUnderIcon,
                                                       1,
                                                       this ) );
        toolBarLayout->addWidget( listCustomButton.at( i ) );
        listCustomButton.at( i )->setIconSize( QSize( 60, 60 ) );
        connect( listCustomButton.at( i ), SIGNAL(bePressed(CustomToolButton*)),
                 this, SLOT(childPressed(CustomToolButton*)) );
    }
    toolBarLayout->addStretch();
}

void CustomToolBar::childPressed( CustomToolButton *child )
{
    int index = -1;
    for ( int i = 0, sz = listCustomButton.size(); i < sz; ++ i ) {
        if ( listCustomButton.at( i ) != child )
            listCustomButton[ i ]->setPressed( false );
        else
            index = i;
    }
    child->setPressed( true );
    if ( index != -1 )
        emit showPageAt( index );
}

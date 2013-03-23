#include "customtoolbutton.h"

CustomToolButton::CustomToolButton( const QString &strImage,
                            const QString &strInfo,
                            Qt::ToolButtonStyle style,
                            QWidget *parent ) :
    strImage( strImage ), strInfo( strInfo ), QToolButton( parent )
{
    setToolButtonStyle( style );
    if ( this->toolButtonStyle() != Qt::ToolButtonTextOnly )
        setIcon( QPixmap( strImage ) );
    if ( this->toolButtonStyle() != Qt::ToolButtonIconOnly )
        setText( strInfo );

}

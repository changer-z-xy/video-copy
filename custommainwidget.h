#ifndef CUSTOMMAINWIDGET_H
#define CUSTOMMAINWIDGET_H

#include "customwidget.h"
#include "customtitlebar.h"
#include "customtoolbar.h"
#include "customcontentwidget.h"
#include "customstatusbar.h"

class CustomMainWidget : public CustomWidget
{
private:
    CustomTitleBar *myTitleBar;
    CustomToolBar *myToolBar;
    CustomContentWidget *myContentWidget;
    CustomStatusBar *myStatusBar;
protected:
    void resizeEvent( QResizeEvent *event );
public:
    CustomMainWidget(QWidget *parent = 0);
};

#endif // CUSTOMMAINWIDGET_H

#include "contentpage.h"

ContentPage::ContentPage(QWidget *parent)
    : QWidget(parent)
{

}

void ContentPage::moveToLeft( int x )
{
    move( x, 0 );
}

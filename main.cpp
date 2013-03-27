#include "customwidget.h"
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CustomWidget w;
    w.show();
    
    return a.exec();
}

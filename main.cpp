#include "custommainwidget.h"
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CustomMainWidget w;
    w.show();
    
    return a.exec();
}

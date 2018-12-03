#include "abmainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ABMainWindow w;
    if(!w.init())
    {
        printf("ABMainWindow init error!\n");
        return 1;
    }
    w.show();

    return a.exec();
}

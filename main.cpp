#include "T12306.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    T12306 w;
    w.show();

    return a.exec();
}

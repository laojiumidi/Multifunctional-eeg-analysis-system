#include <QApplication>
#include <QProcess>

#include "topwin.h"
#include "classwin.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    topwin top;
    top.show();
//    classwin classw;
//    classw.show();

    return a.exec();
}

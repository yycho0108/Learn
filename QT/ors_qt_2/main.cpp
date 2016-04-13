#include "ors_qt_2.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ors_qt_2 w;
    w.show();

    return a.exec();
}

#include "ors_qt.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ors_qt w;
    w.show();

    return a.exec();
}

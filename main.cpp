#include "FileCopy.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    FileCopy w;
    w.show();
    return a.exec();
}

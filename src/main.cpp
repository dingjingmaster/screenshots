#include "screenshots.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Screenshots w;
    w.show();
    return a.exec();
}

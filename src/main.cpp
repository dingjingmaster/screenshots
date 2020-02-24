#include "screenwidget.h"

#include <QApplication>


int main (int argc, char* argv[])
{
    QApplication app(argc, argv);

    ScreenWidget::Instance()->showFullScreen();

    return app.exec();
}

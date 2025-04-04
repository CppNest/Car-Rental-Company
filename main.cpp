#include "menuwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MenuWindow menuWindow;
    menuWindow.showFullScreen();

    return a.exec();
}

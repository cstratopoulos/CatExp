#include "catwindow.hpp"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CatWindow w;
    w.show();

    return a.exec();
}

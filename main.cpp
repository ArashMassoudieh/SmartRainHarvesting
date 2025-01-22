#include "smartrainharvest.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SmartRainHarvest w;
    w.show();
    return a.exec();
}

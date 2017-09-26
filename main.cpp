#include "mainwindow.h"
#include <QApplication>
#include <QFile>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

   // QFile settings("settings.json");
   // if(!settings.open(QIODevice::WriteOnly))
  //  {
   //     qWarning ("Couldn't open or create file.");
   // }
   // settings.close();

    return a.exec();
}

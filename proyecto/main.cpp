#include "widget.h"
#include <QTextStream>
#include <QCoreApplication>
#include <QSerialPort>
#include <QThread>
#include <QApplication>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Widget w;  // Tu ventana principal
    w.show();


    return a.exec();

}
















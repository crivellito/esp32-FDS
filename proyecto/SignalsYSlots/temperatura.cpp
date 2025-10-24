#include "temperatura.h"

Temperatura::Temperatura(QObject *parent)
    : QObject{parent}
{}



void Temperatura::seTemp(int temp){

    temperatura = temp;
    qDebug() <<"La temperatura actual es: "<<temp<< Qt::endl;

    if(temp<50){
        emit signalAltaTemp(temp);
    }
}

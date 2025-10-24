#include "alarma.h"

Alarma::Alarma(QWidget *parent)
    : QWidget{parent}
{}

void Alarma::SlotAlarmaTemp(int temp){

    qDebug()<<"ALARMA, ALTA TEMPERATURA!!! TEMPERATURA DE  "<< temp <<"°C"<< Qt::endl;
}

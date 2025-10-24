#include "widget.h"
#include "ui_widget.h"
#include <QSerialPort>
#include <QThread>
#include <QCoreApplication>
#include <QTextStream>
#include <QTimer>
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    //configuracion de la interfaz

    ui->setupUi(this);

    ui->btnAlarmaGas->setCheckable(true);
    ui->Temp->setReadOnly(true);

    QTextStream out(stdout);

    serialPort.setPortName("COM5");                                                //aqui va el puerto del arduino que se va a usar
    serialPort.setBaudRate(QSerialPort::Baud115200);
    serialPort.setDataBits(QSerialPort::Data8);
    serialPort.setParity(QSerialPort::NoParity);
    serialPort.setStopBits(QSerialPort::OneStop);
    serialPort.setFlowControl(QSerialPort::NoFlowControl);

    if(!serialPort.open(QIODevice::ReadWrite)){         // intenta abrir el puerto serie, se abre para lectura y escritura
        out <<"No se pudo abrir el puerto serie" << Qt::endl;
        return ;
    }

     connect(&serialPort, &QSerialPort::readyRead, this, &Widget::leerSensor);

    out << "Puerto serie abierto correctamente" << Qt::endl;

    //Espera a que haya datos disponibles para leer
    if(serialPort.waitForReadyRead(5000)){  //Espera hasta 3 segundos hasta que ingrese el dato
        QString receivedData = serialPort.readLine();

        out <<"Datos recibidos: " << receivedData << Qt::endl;
    } else {
        out << "No se recibio datos a tiempo" << Qt::endl;
    }

}

Widget::~Widget()
{
    delete ui;
}

/*
void Widget::leerSensor()
{
    // Simulación de sensor sin esp32
    static bool estadoSimulado = false;
    estadoSimulado = !estadoSimulado;
    bool sensorDetecta = estadoSimulado;

    temperatura = sensorDetecta ? 55.0 : 22.0; // ejemplo
    ui->Temp->setText(QString::number(temperatura, 'f', 2));

    actualizarBotonAlarmaGas(sensorDetecta);
    actualizarBotonAlarmaMedia(sensorDetecta);
    actualizarBotonAlarmaAlta(sensorDetecta);
    actualizarBotonAlarmaBaja(sensorDetecta);
}
*/

void Widget::leerSensor() {
    while (serialPort.canReadLine()) {
        QByteArray line = serialPort.readLine().trimmed();
        QString strLine = QString::fromUtf8(line);
        QStringList parts = strLine.split('~');

        if (parts.size() >= 3) {
            bool gasDetectado = (parts[1].toLower() == "true");
            bool ok;
            float temperatura = parts[2].toFloat(&ok);
            if (!ok) temperatura = 0;

            ui->Temp->setText(QString::number(temperatura, 'f', 2));
            actualizarBotonAlarmaGas(gasDetectado);
            actualizarBotonAlarmaMedia(gasDetectado || temperatura > 40.0);
            actualizarBotonAlarmaBaja(!gasDetectado && temperatura < 40.0);
            actualizarBotonAlarmaAlta(gasDetectado && temperatura > 40.0);
        }
    }
}


void Widget::on_btnAlarmaGas_toggled(bool checked)
{
    actualizarBotonAlarmaGas(checked);
    actualizarBotonAlarmaMedia(checked);
    actualizarBotonAlarmaAlta(checked);
    actualizarBotonAlarmaBaja(checked);
}
void Widget::actualizarBotonAlarmaGas(bool estado)
{

    if (estado) {
        // LED encendido (amarillo)
        ui->btnAlarmaGas->setStyleSheet(
            "QToolButton#btnAlarmaGas {"
            "background-color: #FFFF00;"
            "border-radius: 12px;"
            "border: 1px solid #C0C0C0;"
            "min-width: 24px;"
            "min-height: 24px;"
            "max-width: 24px;"
            "max-height: 24px;"
            "}"
            );
    } else {
        // LED apagado
        ui->btnAlarmaGas->setStyleSheet(
            "QToolButton#btnAlarmaGas {"
            "background-color: #2e2e2e;"
            "border-radius: 12px;"
            "border: 1px solid #C0C0C0;"
            "min-width: 24px;"
            "min-height: 24px;"
            "max-width: 24px;"
            "max-height: 24px;"
            "}"
            );
    }
}

void Widget::actualizarBotonAlarmaMedia(bool estado)
{
    if (estado) {
        // LED encendido (naranja)
        ui->btnNivelMedio->setStyleSheet(
            "QToolButton#btnNivelMedio {"
            "background-color: orange;"
            "border-radius: 24px;"
            "border: 1px solid #C0C0C0;"
            "min-width: 48px;"
            "min-height: 48px;"
            "max-width: 48px;"
            "max-height: 48px;"
            "}"
            );
    } else {
        // LED apagado
        ui->btnNivelMedio->setStyleSheet(
            "QToolButton#btnNivelMedio {"
            "background-color: #2e2e2e;"
            "border-radius: 24px;"
            "border: 1px solid #C0C0C0;"
            "min-width: 48px;"
            "min-height: 48px;"
            "max-width: 48px;"
            "max-height: 48px;"
            "}"
            );
    }
}

void Widget::actualizarBotonAlarmaBaja(bool estado)
{
    if (estado) {
        // LED encendido (verde)
        ui->btnNivelBajo->setStyleSheet(
            "QToolButton#btnNivelBajo {"
            "background-color: #90EE90;"
            "border-radius: 24px;"
            "border: 1px solid #C0C0C0;"
            "min-width: 48px;"
            "min-height: 48px;"
            "max-width: 48px;"
            "max-height: 48px;"
            "}"
            );
    } else {
        // LED apagado
        ui->btnNivelBajo->setStyleSheet(
            "QToolButton#btnNivelBajo {"
            "background-color: #2e2e2e;"
            "border-radius: 24px;"
            "border: 1px solid #C0C0C0;"
            "min-width: 48px;"
            "min-height: 48px;"
            "max-width: 48px;"
            "max-height: 48px;"
            "}"
            );
    }
}

void Widget::actualizarBotonAlarmaAlta(bool estado)
{
    if (estado) {
        // LED encendido (rojo)
        ui->btnNivelAlto->setStyleSheet(
            "QToolButton#btnNivelAlto {"
            "background-color: red;"
            "border-radius: 24px;"
            "border: 1px solid #C0C0C0;"
            "min-width: 48px;"
            "min-height: 48px;"
            "max-width: 48px;"
            "max-height: 48px;"
            "}"
            );
    } else {
        // LED apagado
        ui->btnNivelAlto->setStyleSheet(
            "QToolButton#btnNivelAlto {"
            "background-color: #2e2e2e;"
            "border-radius: 24px;"
            "border: 1px solid #C0C0C0;"
            "min-width: 48px;"
            "min-height: 48px;"
            "max-width: 48px;"
            "max-height: 48px;"
            "}"
            );
    }
}

void Widget::on_pushButton_2_clicked()
{
    QApplication::quit();
}

void Widget::on_NombreWifi_cursorPositionChanged(int arg1, int arg2)
{
    Q_UNUSED(arg1);
    Q_UNUSED(arg2);
}


void Widget::on_ContraseniaWifi_cursorPositionChanged(int arg1, int arg2)
{
    Q_UNUSED(arg1);
    Q_UNUSED(arg2);
}


void Widget::on_pushButton_3_clicked()
{
    QString ssid = ui->NombreWifi->text().trimmed();
    QString password = ui->ContraseniaWifi->text().trimmed();

    if (ssid.isEmpty() || password.isEmpty()) {
        qDebug() << "SSID o contraseña vacíos";
        return;
    }

    QString mensaje = "E~0~" + ssid + "\n";

    if (serialPort.isOpen()){
        serialPort.write(mensaje.toUtf8());
        serialPort.flush();
        qDebug() << "Enviado al ESP32:" << mensaje;
    } else {
        qDebug() << "Puerto serie no disponible";
    }

    mensaje = "E~1~" + password + "\n";

    if (serialPort.isOpen()){
        serialPort.write(mensaje.toUtf8());
        serialPort.flush();
        qDebug() << "Enviado al ESP32:" << mensaje;
    } else {
        qDebug() << "Puerto serie no disponible";
    }

}


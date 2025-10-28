#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSerialPort>

QT_BEGIN_NAMESPACE
namespace Ui {class Widget;}


QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_pushButton_2_clicked();
    void leerSensor();
    void on_btnAlarmaGas_toggled(bool checked);

    void on_NombreWifi_cursorPositionChanged(int arg1, int arg2);

    void on_ContraseniaWifi_cursorPositionChanged(int arg1, int arg2);

    void on_pushButton_3_clicked();

    void on_PuertoSerie_cursorPositionChanged(int arg1, int arg2);

private:
    Ui::Widget *ui;
    QSerialPort serialPort;
    float temperatura = 0.0;
    void actualizarBotonAlarmaGas(bool estado);
    void actualizarBotonAlarmaMedia(bool estado);
    void actualizarBotonAlarmaBaja(bool estado);
    void actualizarBotonAlarmaAlta(bool estado);

};
#endif // WIDGET_H

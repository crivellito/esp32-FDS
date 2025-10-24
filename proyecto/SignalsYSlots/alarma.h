#ifndef ALARMA_H
#define ALARMA_H

#include <QWidget>

class Alarma : public QWidget
{
    Q_OBJECT
public:
    explicit Alarma(QWidget *parent = nullptr);

public slots:
    void SlotAlarmaTemp(int temp);

signals:
};

#endif // ALARMA_H

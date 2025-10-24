#ifndef TEMPERATURA_H
#define TEMPERATURA_H

#include <QObject>

class Temperatura : public QObject
{
    Q_OBJECT
public:
    explicit Temperatura(QObject *parent = nullptr);
    void seTemp(int temp);


private:
    int temperatura;

signals:
    void signalAltaTemp(int temp);
};

#endif // TEMPERATURA_H

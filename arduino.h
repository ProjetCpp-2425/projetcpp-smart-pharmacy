#ifndef ARDUINO_H
#define ARDUINO_H
#include <QObject>
#include <QByteArray>
#include <QSerialPort>
#include <QSerialPortInfo>



class arduino:public QObject
{
    Q_OBJECT

public:
    explicit arduino(QObject *parent = nullptr);

    arduino();
    bool connect_arduino();
    int close_arduino();

signals:
    void dataReceived(QByteArray &data);  // Signal émis lorsqu'une donnée est reçue

private:
    arduino *Arduino;
    QSerialPort *serial;// Objet de communication série

    static const quint16 arduino_uno_vendor_id=9025;
    static const quint16 arduino_uno_producy_id=67;

    QString arduino_port_name;
    bool arduino_is_available;
    QByteArray data;




private slots:
    void readData();  // Pour lire les données reçues
};



#endif // ARDUINO_H

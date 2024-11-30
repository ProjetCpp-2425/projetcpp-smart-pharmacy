#include <QByteArray>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QDebug>
#include "arduino.h"


arduino::arduino(QObject *parent) : QObject(parent), serial(nullptr)
{
}

bool arduino::connect_arduino()
{
    QStringList availablePorts;
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        availablePorts.append(info.portName());
    }
    qDebug() << "Ports disponibles : " << availablePorts;

    serial = new QSerialPort(this);
    if (!serial) {
        qDebug() << "Erreur : Impossible de créer l'objet QSerialPort.";
        return false;
    }

    serial->setPortName("COM3");
    serial->setBaudRate(QSerialPort::Baud9600);
    serial->setDataBits(QSerialPort::Data8);
    serial->setParity(QSerialPort::NoParity);
    serial->setStopBits(QSerialPort::OneStop);
    serial->setFlowControl(QSerialPort::NoFlowControl);

    if (serial->open(QIODevice::ReadWrite)) {
        connect(serial, &QSerialPort::readyRead, this, &arduino::readData);
        qDebug() << "Connexion à Arduino réussie.";
        return true;
    }
    else
    {
        qDebug() << "Erreur de connexion à Arduino :" << serial->errorString();
        return false;
    }
}

int arduino::close_arduino()
{
    if(serial->isOpen()) {
        serial->close();
        return 0;
    }
    return 1;
}

void arduino::readData()
{
    qDebug() << "Lecture des données depuis Arduino.";
    while (serial->canReadLine()) {  // Vérifie si une ligne complète est disponible
        QByteArray data = serial->readLine().trimmed();
        QString message = QString::fromUtf8(data);  // Conversion de QByteArray en QString pour l'affichage
        qDebug() << "Données brutes : " << message;  // Affiche les données dans la console
        emit dataReceived(data);  // Émet le signal avec QByteArray
    }
}

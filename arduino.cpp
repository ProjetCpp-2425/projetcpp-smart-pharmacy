#include "arduino.h"
#include "qthread.h"
Arduino::Arduino()
{
    data="";
    arduino_port_name="";
    arduino_is_available=false;
    serial=new QSerialPort;
}

QString Arduino::getarduino_port_name()
{
    return arduino_port_name;
}

QSerialPort *Arduino::getserial()
{
   return serial;
}
int Arduino::connect_arduino()
{   // recherche du port sur lequel la carte arduino identifée par  arduino_uno_vendor_id
    // est connectée
    foreach (const QSerialPortInfo &serial_port_info, QSerialPortInfo::availablePorts()){
           if(serial_port_info.hasVendorIdentifier() && serial_port_info.hasProductIdentifier()){
               if(serial_port_info.vendorIdentifier() == arduino_uno_vendor_id && serial_port_info.productIdentifier()
                       == arduino_uno_producy_id) {
                   arduino_is_available = true;
                   arduino_port_name=serial_port_info.portName();
               } } }
        qDebug() << "arduino_port_name is :" << arduino_port_name;
        if(arduino_is_available){ // configuration de la communication ( débit...)
            serial->setPortName(arduino_port_name);
            if(serial->open(QSerialPort::ReadWrite)){
                serial->setBaudRate(QSerialPort::Baud9600); // débit : 9600 bits/s
                serial->setDataBits(QSerialPort::Data8); //Longueur des données : 8 bits,
                serial->setParity(QSerialPort::NoParity); //1 bit de parité optionnel
                serial->setStopBits(QSerialPort::OneStop); //Nombre de bits de stop : 1
                serial->setFlowControl(QSerialPort::NoFlowControl);
                return 0;
            }
            return 1;
        }
        return -1;
}


int Arduino::connect_arduino(const QString &portName)
{
    if (serial->isOpen()) {
        serial->close();
        serial->setBaudRate(QSerialPort::Baud9600);
        QThread::msleep(1000);
    }

    arduino_port_name = portName;
    serial->setPortName(arduino_port_name);

    if (serial->open(QSerialPort::ReadWrite)) {
        serial->setBaudRate(QSerialPort::Baud9600);
        serial->setDataBits(QSerialPort::Data8);
        serial->setParity(QSerialPort::NoParity);
        serial->setStopBits(QSerialPort::OneStop);
        serial->setFlowControl(QSerialPort::NoFlowControl);

        QThread::msleep(1000);

        return 0;
    } else {
        qDebug() << "Failed to open serial port:" << serial->errorString();
        return 1;
    }
}


int Arduino::close_arduino()

{

    if(serial->isOpen()){
            serial->close();
            return 0;
        }
    return 1;


}

QByteArray Arduino::read_from_arduino()
{
    if (serial->isOpen() && serial->bytesAvailable() > 0) {
        return serial->readAll(); // Return immediately available data
    }
    return QByteArray(); // Return an empty array if no data
}


/*QByteArray Arduino::read_from_arduino()
{
    QByteArray data="";
    int i=0;
    while (true) {
        if (serial->waitForReadyRead(500)) {
            data +=serial->readAll(); // Retrieve the received data
             // Exit the loop once data is received
        }
        if (i>10) {
            break;

       }
        i++;
        // You can add additional logic or sleep here if needed
    }

    return data;
}*/
/*QByteArray Arduino::read_from_arduino()
{
    if (serial->waitForReadyRead(100)) {
        data = serial->readAll(); // Retrieve the received data
    }
    return data;
}*/


int Arduino::write_to_arduino( QByteArray d)

{

    if(serial->isWritable()){
        serial->write(d);
        return 1;// envoyer des donnés vers Arduino
    }else{
        qDebug() << "Couldn't write to serial!";
        return 0;
    }


}

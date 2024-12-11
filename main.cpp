#include "mainwindow.h"
#include <QMessageBox>
#include "connection.h"
#include <QApplication>
#include "arduino.h"

Arduino arduino;

int main(int argc, char *argv[])
{
    Connection c;
    bool test=c.createconnect();

    QApplication a(argc, argv);
    MainWindow w;

    int result = arduino.connect_arduino(); // Attempt to connect to Arduino

    if (result == 0) {
        qDebug() << "Connected to Arduino on port:" << arduino.getarduino_port_name();
        arduino.is_connected = 1;
    } else if (result == 1) {
        qDebug() << "Failed to open the serial port.";
        arduino.close_arduino();
        arduino.is_connected = 0;
    } else {
        qDebug() << "Arduino not found.";
        arduino.close_arduino();
        arduino.is_connected = 0;
    }





    if(test)
    {

       QMessageBox::information(nullptr,QObject::tr("database is open"),
                                QObject::tr("connection successful \n"
                                            "Click Cancel to exit"),QMessageBox::Cancel);
     }
    else{
        QMessageBox::critical(nullptr,QObject::tr("database is not open"),
                                 QObject::tr("connection failed \n"
                                                 "Click Cancel to exit"),QMessageBox::Cancel);
        return  0;
    }

    w.show();
    return a.exec();
}

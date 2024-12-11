#include "Arduino.h"
#include <QApplication>
#include <QStyle>
#include <QSystemTrayIcon>

Arduino::Arduino() {
    // Configure the serial port
    serial.setPortName("COM3");  // Replace with your actual COM port
    serial.setBaudRate(QSerialPort::Baud9600);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);
    serial.setFlowControl(QSerialPort::NoFlowControl);

    // Connect the serial readyRead signal to the slot
    QObject::connect(&serial, &QSerialPort::readyRead, [this]() {
        readSerialData();
    });
}

bool Arduino::initializeDatabaseConnection() {
    return dbConnection.createconnect(); // Connect to the database
}

void Arduino::openSerialPort() {
    if (serial.open(QIODevice::ReadWrite)) {
        qDebug() << "Serial port opened.";
    } else {
        qDebug() << "Error opening serial port: " << serial.errorString();
    }
}

void Arduino::readSerialData() {
    if (serial.canReadLine()) {
        QByteArray data = serial.readLine();
        QString code = QString::fromUtf8(data).trimmed();

        qDebug() << "Received code: " << code;
        handleReceivedCode(code);  // Process the code
    }
}

void Arduino::handleReceivedCode(const QString &code) {
    QString employeeName = dbConnection.checkCodeInDatabase(code);
    QString message;

    if (employeeName.startsWith("Error")) {
        serial.write("Error: Code not found\n");
        message = "Invalid Code: Access Denied";
    } else {
        if (code == "1001") {
            serial.write((employeeName + ": Access Granted\n").toUtf8());
            message = QString("Code: %1\nEmployee: %2\nAccess Granted").arg(code).arg(employeeName);
        } else {
            serial.write((employeeName + ": Access Denied\n").toUtf8());
            message = QString("Code: %1\nEmployee: %2\nAccess Denied").arg(code).arg(employeeName);
        }
    }

    showNotification(message);  // Display the system notification
}

void Arduino::showNotification(const QString &message) {
    // Check if the system tray icon is supported
    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        qDebug() << "System tray not available.";
        return;
    }

    QSystemTrayIcon *trayIcon = new QSystemTrayIcon();
    trayIcon->setIcon(QApplication::style()->standardIcon(QStyle::SP_MessageBoxInformation));
    trayIcon->setVisible(true);

    trayIcon->showMessage("Code Verification", message, QSystemTrayIcon::Information, 5000);
}

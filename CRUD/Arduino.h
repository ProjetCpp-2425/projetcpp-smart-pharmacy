#ifndef ARDUINO_H
#define ARDUINO_H

#include <QSerialPort>
#include <QString>
#include "connection.h"
#include <QSystemTrayIcon>

class Arduino {
public:
    Arduino();                       // Constructor
    void openSerialPort();           // Opens the serial port
    void readSerialData();           // Reads data from the serial port
    bool initializeDatabaseConnection(); // Initialize the database connection

private:
    QSerialPort serial;
    Connection dbConnection;         // Database connection remains private
    void handleReceivedCode(const QString &code); // Processes the received code
    void showNotification(const QString &message); // Helper function for notifications
};

#endif // ARDUINO_H

#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "Arduino.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;

    // Create Arduino object
    Arduino arduino;

    // Initialize the database connection
    if (arduino.initializeDatabaseConnection()) {
        qDebug() << "Database connection successful.";

        // Show the main window
        w.show();

        // Optionally show system tray notification for low stock (existing function in MainWindow)
        w.showNotification();

        // Open serial port and start reading
        arduino.openSerialPort();

    } else {
        // Handle database connection failure
        qDebug() << "Database connection failed.";
        QMessageBox::critical(nullptr, QObject::tr("Database Connection Error"),
                              QObject::tr("Failed to connect to the database.\n"
                                          "Please check the connection settings and try again."),
                              QMessageBox::Cancel);
        return -1;  // Exit the application if the connection fails
    }

    return a.exec();
}

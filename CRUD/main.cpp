#include "mainwindow.h"
#include <QApplication>
#include <QMessageBox>
#include "connection.h"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;  // Create MainWindow object
    Connection c;

    qDebug() << "Attempting to establish a database connection...";
    bool test = c.createconnect();  // Try to create the connection

    if (test)
    {
        // Database connection was successful
        w.show();  // Show MainWindow

        qDebug() << "Connection successful.";

        // Show a message box indicating successful connection
        QMessageBox::information(nullptr, QObject::tr("Database is open"),
                    QObject::tr("Connection successful.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);

        // Debugging to check if showNotification is being called
        qDebug() << "Calling showNotification...";
        w.showNotification();  // Call showNotification to display the products in shortage (<= 20 in quantity)

    }
    else
    {
        // Connection failed
        qDebug() << "Connection failed.";
        QMessageBox::critical(nullptr, QObject::tr("Database is not open"),
                    QObject::tr("Connection failed.\n"
                                "Click Cancel to exit."), QMessageBox::Cancel);
    }

    return a.exec();
}

#include <QApplication>
#include "mainwindow.h"
#include "connection.h"
#include "prescription.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    Connection c;

    // Establish the database connection
    if (!c.createconnect()) {
        qDebug() << "La connexion a échoué\n";
        return -1;
    }
    MainWindow mainWindow;
    mainWindow.show();

    return app.exec();
}

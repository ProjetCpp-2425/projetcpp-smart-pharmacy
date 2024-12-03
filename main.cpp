#include "mainwindow.h"
#include <QApplication>
#include "connection.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Connection c;
    bool test = c.createconnection();

    MainWindow w;

    if (test) {
        w.show();
    } else {
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                              QObject::tr("Connection failed.\nClick Cancel to exit."),
                              QMessageBox::Cancel);
    }

    return a.exec();
}

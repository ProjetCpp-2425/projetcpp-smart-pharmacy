#include "mainwindow.h"
#include "connexion.h"
#include "employeeui.h"
#include "login.h"
#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    login l;

    MainWindow w;
    employeeUI eUI;
    connexion c;
    bool test =c.createconnect();
    if(test)
    {
      //  w.show();
        l.exec();
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                              QObject::tr("connexion failed.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);

    return a.exec();
}

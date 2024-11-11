#include "mainwindow.h"
#include "connexion.h"
#include "employeeui.h"

#include <QApplication>
#include <QMessageBox>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;
    employeeUI eUI;
    connexion c;
    bool test =c.createconnect();
    if(test)
    {
      //  w.show();
        eUI.exec();
    }
    else
        QMessageBox::critical(nullptr, QObject::tr("database is not open"),
                              QObject::tr("connexion failed.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);

    return a.exec();
}

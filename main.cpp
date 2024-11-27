#include "gestioncommande.h"
#include <QMessageBox>
#include "connection.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    Connection c;
    bool test=c.createconnect();

    QApplication a(argc, argv);
    GestionCommande w;


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

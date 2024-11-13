#include "connection.h"
#include <QSqlQuery>
#include <QSqlError>

Connection::Connection()
{
    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("source2a32");//inserer le nom de la source de données
    db.setUserName("aouadi");//inserer nom de l'utilisateur
    db.setPassword("0000");//inserer mot de passe de cet utilisateur

}

bool Connection::createconnect()
{
    bool test =false;
    if (db.open())
    {
        test=true;
        qDebug()<<"Connexion reussie a la base de donne.";
    }
    else{
        qDebug()<<"Errueur de connexion"<<db.lastError().text();
    }
    return test;
}

void Connection::closeConnection()
    {
        if (db.isOpen())
        {
            db.close();
            qDebug()<<"Connexion fermee";
        }
        else
        {
            qDebug()<< "La connexion est deja fermee ou na pas ete ouverte ";
        }
    }


int Connection:: get_size()
{
        QSqlQuery query;
        query.prepare("SELECT COUNT(*) FROM prescription");

        if (!query.exec()) {
            qDebug() << "Error executing count query:" << query.lastError().text();
            return -1;
        }

        int rowCount = 0;
        if (query.next()) {
            rowCount = query.value(0).toInt();
        }

        return rowCount;


}

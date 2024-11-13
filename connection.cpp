#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{
db = QSqlDatabase::addDatabase("ODBC");
bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("source2a32");//inserer le nom de la source de données
db.setUserName("Projectcpp2a32");//inserer nom de l'utilisateur
db.setPassword("mp2a32");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;


    return  test;
}
void Connection::closeConnection(){db.close();}

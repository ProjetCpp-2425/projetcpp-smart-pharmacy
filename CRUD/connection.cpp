#include "connection.h"

Connection::Connection()
{

}

bool Connection::createconnect()
{bool test=false;
QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
db.setDatabaseName("source2a32");//inserer le nom de la source de données
db.setUserName("projetcpp2a32");//inserer nom de l'utilisateur
db.setPassword("mp2a32");//inserer mot de passe de cet utilisateur

if (db.open())
test=true;





    return  test;
}
void Connection::closeConnect (){db.close();}

QString Connection::checkCodeInDatabase(const QString &code) {
    QSqlQuery query;
    query.prepare("SELECT NOM FROM \"PROJETCPP2A32\".\"EMPLOYÉS\" WHERE MPD = :code");
    query.bindValue(":code", code);

    if (query.exec()) {
        if (query.next()) {
            // Code exists in the database, return the employee name
            return query.value("NOM").toString();
        } else {
            // Code does not exist in the database
            return "Unknown";
        }
    } else {
        // Query execution failed
        return "Error executing query";
    }
}



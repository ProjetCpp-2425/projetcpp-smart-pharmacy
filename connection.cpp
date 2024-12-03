#include "connection.h"

    Connection::Connection(){}

    bool Connection::createconnection()
    {
    test = false;
    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName(""); // Insérer le nom de la source de données ODBC
    db.setUserName(""); // Insérer le nom de l'utilisateur
    db.setPassword(""); // Insérer le mot de passe de cet utilisateur

    if (db.open()) test = true;

    return test;
    }

    void Connection::closeConnection()
    {
    db.close();
    }

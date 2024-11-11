#include "connexion.h"

connexion::connexion()
{

}

bool connexion::createconnect()
{
    bool test=false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("projetQT");
    db.setUserName("projetQT");//inserer nom de l'utilisateur
    db.setPassword("test123");//inserer mot de passe de cet utilisateur

    if (db.open())
        test=true;

    return  test;
}

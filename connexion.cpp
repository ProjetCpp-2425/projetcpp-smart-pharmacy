#include "connexion.h"

connexion::connexion()
{

}

bool connexion::createconnect()
{
    bool test=false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("Source_Projet2a32");
    db.setUserName("projetcpp2a32");//inserer nom de l'utilisateur
    db.setPassword("mp2a32");//inserer mot de passe de cet utilisateur

    if (db.open())
        test=true;

    return  test;
}

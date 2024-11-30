#ifndef FOURNISSEURS_H
#define FOURNISSEURS_H

#include<QString>
#include<QSqlQuery>
#include<QSqlQueryModel>

class fournisseurs
{
    int codef,numerof;
    QString nomf, email,rs;
    QString produit;

public:
    //constr
    fournisseurs();
    fournisseurs(int,int,QString,QString,QString,QString);

    //get
    QString getprd();
    QString getnomf();
    QString getmail();
    QString getrs();
    int getcodef();
    int getnumf();

    //set
    void setnomf(QString nomf);
    void setmail(QString email);
    void setrs(QString rs);
    void setcodef(int codef);
    void setnumerof(int numerof);
    void setproduit(QString produit);

    //crud
    bool ajouterfour();
    QSqlQueryModel * afficherfour();
    bool suppfour(int);
    bool modifier(int codef, int numerof,  QString nomf,  QString email,  QString rs, QString produit);


    //metiers




};

#endif // FOURNISSEURS_H

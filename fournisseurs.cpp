#include "fournisseurs.h"
#include "qitemselectionmodel.h"
#include "mainwindow.h"
#include <QSqlError>
#include "ui_mainwindow.h"
#include <QTableView>
#include <QSqlQuery>
#include <QMessageBox>
#include <QString>
#include <QDebug>
#include <QVariant>
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>

fournisseurs::fournisseurs()
{

}

fournisseurs::fournisseurs(int codef,int numerof, QString nomf, QString email, QString rs,QString produit)
{
    this->codef=codef;
    this->numerof=numerof;
    this->nomf=nomf;
    this->rs=rs;
    this->email=email;
    this->produit=produit;

}

//gett
int fournisseurs::getcodef()
{
    return codef;
}
QString fournisseurs::getnomf()
{
    return nomf;
}
QString fournisseurs::getmail()
{
    return email;
}
int fournisseurs::getnumf()
{
    return numerof;
}
QString fournisseurs::getrs()
{
    return rs;
}
QString fournisseurs::getprd()
{
    return produit;
}


//sett
void fournisseurs::setcodef(int codef)
{
    codef=codef;
}

void fournisseurs::setnumerof(int numerof)
{
    numerof=numerof;
}

void fournisseurs::setnomf(QString nomf)
{
    nomf = nomf;
}

void fournisseurs::setrs(QString rs)
{
    rs = rs;
}

void fournisseurs::setmail(QString email)
{
    email=email;
}

void fournisseurs::setproduit(QString produit)
{
    produit=produit;
}

QSqlQueryModel * fournisseurs::afficherfour()
{
    QSqlQueryModel * model = new QSqlQueryModel();
    model->setQuery("select * from fournisseurs");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("CODE"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("EMAIL"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("NUMERO"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("RAISONSOCIALE"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("PRODUIT"));

    return model;
}




bool fournisseurs::suppfour(int codef)
{
    QSqlQuery query;
    QString res=QString::number(codef);

    query.prepare("Delete from fournisseurs where codef=codef");
    query.bindValue(":codef",res);

    return query.exec(); //envoie la requete à l'execu
}






 bool fournisseurs::ajouterfour()
 {
     QSqlQuery query;
     QString res = QString::number(codef);
     QString res1= QString::number(numerof);

     query.prepare("insert into fournisseurs(codef,nomf,email,numerof,rs,produit)""values(:codef, :nomf, :email, :numerof, :rs,:produit)");

     //affect
     query.bindValue(":codef",codef);
     query.bindValue(":nomf",nomf);
     query.bindValue(":email",email);
     query.bindValue(":numerof",numerof);
     query.bindValue(":rs",rs);
     query.bindValue(":produit",produit);

     return query.exec();
}

 bool fournisseurs::modifier(int codef, int numerof,  QString nomf,  QString email,  QString rs, QString produit)
{
     QSqlQuery query;
         query.prepare("UPDATE fournisseurs SET nomf = :nomf, email = :email, rs = :rs, produit = :produit, numerof = :numerof WHERE codef = :codef");
         query.bindValue(":nomf", nomf);
         query.bindValue(":email", email);
         query.bindValue(":rs", rs);
         query.bindValue(":produit", produit);
         query.bindValue(":numerof", numerof);
         query.bindValue(":codef", codef);

         return query.exec();
 }





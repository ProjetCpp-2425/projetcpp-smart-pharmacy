#ifndef COMMANDE_H
#define COMMANDE_H

#include <QString>
#include <QDateTime>
#include <QSqlQueryModel>
#include <QObject>
#include <QSqlQuery>
class Commande
{
public:
    // ructors
    Commande();
    Commande( int codeCommande,QString &adresse,  QDateTime &dateCommande,  QString &statusCommande,
                        QString &remarque, int codef, int cin, int produit);


    int getCodeCommande() ;
    QString getAdresse() ;
    QDateTime getDateCommande() ;
    QString getStatusCommande() ;
    QString getRemarque() ;
    int getCodef() ;
    int getCin() ;
    int getProduit() ;


    void setAdresse( QString &adresse);
    void setDateCommande( QDateTime &dateCommande);
    void setStatusCommande( QString &statusCommande);
    void setRemarque( QString &remarque);
    void setCodef(int codef);
    void setCin(int cin);
    void setProduit(int produit);

    QSqlQueryModel* afficher();
    QSqlQueryModel* afficherTri(QString &trierSelon , QString &OrdreTri);

    bool supprimer(int code);
    Commande trouver(int code);
    QSqlQueryModel* rechercher(QString critere);



private:
    int codecommande;
    QString adresse;
    QDateTime dateCommande;
    QString statusCommande;
    QString remarque;
    int codef;
    int cin;
    int produit;
};

#endif // COMMANDE_H

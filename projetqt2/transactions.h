#ifndef TRANSACTIONS_H
#define TRANSACTIONS_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class Transactions
{
    int numero;
    QString dateHeure;
    QString mode;
    QString status;
    double montant;

public:
    // Constructeurs
    Transactions();
    Transactions(int, QString, QString, QString, double);

    // Getters
    int getNumero() { return numero; }
    QString getDateHeure() { return dateHeure; }
    QString getMode() { return mode; }
    QString getStatus() { return status; }
    double getMontant() { return montant; }

    // Setters
    void setNumero(int n) { numero = n; }
    void setDateHeure(QString d) { dateHeure = d; }
    void setMode(QString m) { mode = m; }
    void setStatus(QString s) { status = s; }
    void setMontant(double m) { montant = m; }

    // Fonctionnalités de base
    bool ajouter();
    QSqlQueryModel* afficher();
    bool supprimer(int);
    QSqlQueryModel* trier(QString critere); // Trier les transactions par critère
    QSqlQueryModel* rechercher(QString valeur); // Recherche selon un critère
    double calculerTotal(); // Calculer le total des montants
    int compterTransactions(QString status); // Compter les transactions vérifiées ou non
    QSqlQuery transactionMaxMontant(); // Trouver la transaction avec le montant maximum
    QSqlQuery transactionMinDate(); // Trouver la transaction la plus ancienne

};

#endif // TRANSACTIONS_H

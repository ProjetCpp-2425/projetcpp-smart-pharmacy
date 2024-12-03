#include "transactions.h"
#include <QSqlQuery>
#include <QVariant>

Transactions::Transactions() : numero(0), montant(0.0) {}

Transactions::Transactions(int num, QString date, QString modeTrans, QString stat, double montantTrans)
    : numero(num), dateHeure(date), mode(modeTrans), status(stat), montant(montantTrans) {}

bool Transactions::ajouter()
{
    QSqlQuery query;
    query.prepare("INSERT INTO transactions (numero, dateHeure, mode, status, montant) "
                  "VALUES (:numero, :dateHeure, :mode, :status, :montant)");
    query.bindValue(":numero", numero);
    query.bindValue(":dateHeure", dateHeure);
    query.bindValue(":mode", mode);
    query.bindValue(":status", status);
    query.bindValue(":montant", montant);
    return query.exec();
}

QSqlQueryModel* Transactions::afficher()
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM transactions");
    return model;
}

bool Transactions::supprimer(int num)
{
    QSqlQuery query;
    query.prepare("DELETE FROM transactions WHERE numero = :numero");
    query.bindValue(":numero", num);
    return query.exec();
}

QSqlQueryModel* Transactions::trier(QString)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM transactions ORDER BY numero ASC"); // Tri par numéro uniquement
    return model;
}

QSqlQueryModel* Transactions::rechercher(QString valeur)
{
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT * FROM transactions WHERE CAST(numero AS TEXT) LIKE '%" + valeur + "%'");
    return model;

    double Transactions::calculerTotal()
    {
        QSqlQuery query;
        query.prepare("SELECT SUM(montant) FROM transactions");
        if (query.exec() && query.next()) {
            return query.value(0).toDouble(); // Retourne le total des montants
        }
        return 0.0;
    }

    int Transactions::compterTransactions(QString status)
    {
        QSqlQuery query;
        query.prepare("SELECT COUNT(*) FROM transactions WHERE status = :status");
        query.bindValue(":status", status);
        if (query.exec() && query.next()) {
            return query.value(0).toInt(); // Retourne le nombre de transactions avec le statut donné
        }
        return 0;
    }

    QSqlQuery Transactions::transactionMaxMontant()
    {
        QSqlQuery query;
        query.prepare("SELECT * FROM transactions WHERE montant = (SELECT MAX(montant) FROM transactions)");
        query.exec(); // Retourne la transaction avec le montant maximum
        return query;
    }

    QSqlQuery Transactions::transactionMinDate()
    {
        QSqlQuery query;
        query.prepare("SELECT * FROM transactions WHERE dateHeure = (SELECT MIN(dateHeure) FROM transactions)");
        query.exec(); // Retourne la transaction la plus ancienne
        return query;
    }
}

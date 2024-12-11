#include "stock.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

// Constructor Implementations
Stock::Stock() : id(0), quantite(0), prixAchat(0.0), prixVente(0.0) {}

Stock::Stock(int id, const QString &nomProduit, const QString &categorie, int quantite, const QDate &dateExp, float prixAchat, float prixVente)
    : id(id), nomProduit(nomProduit), categorie(categorie), quantite(quantite), dateExp(dateExp), prixAchat(prixAchat), prixVente(prixVente) {}

bool Stock::ajouter() {
    qDebug()<< "IN AJOUT\n";
    // Check if the required fields are not empty or invalid before attempting insertion
    if (nomProduit.isEmpty() || categorie.isEmpty() || quantite <= 0 || prixAchat <= 0 || prixVente <= 0) {
        qDebug() << "Input validation failed. Please check the fields.";
        return false;  // Return false if validation fails
    }

    // Prepare SQL query to insert a new record into the 'stock' table
    QSqlQuery query;
    query.prepare("INSERT INTO stock (id, nom_produit, categorie, quantite, date_exp, prix_achat, prix_vente) "
                  "VALUES (:id, :nom_produit, :categorie, :quantite, :date_exp, :prix_achat, :prix_vente)");
    qDebug()<< "sql querey prepared \n ";
    query.bindValue(":id", id);
    query.bindValue(":nom_produit", nomProduit);
    query.bindValue(":categorie", categorie);
    query.bindValue(":quantite", quantite);
    query.bindValue(":date_exp", dateExp.toString("dd-MMM-yy").toUpper());
    query.bindValue(":prix_achat", prixAchat);
    query.bindValue(":prix_vente", prixVente);

    // Execute the query and check for errors
    if (!query.exec()) {
        qDebug() << "Error adding product to stock:" << query.lastError().text();
        return false;  // Return false if query execution fails
    }

    // Return true if the product was added successfully
    return true;
}


bool Stock::modifier() {
    QSqlQuery query;
    query.prepare("UPDATE stock SET nom_produit = :nom_produit, categorie = :categorie, quantite = :quantite, "
                  "date_exp = :date_exp, prix_achat = :prix_achat, prix_vente = :prix_vente WHERE id = :id");
    query.bindValue(":id", id);
    query.bindValue(":nom_produit", nomProduit);
    query.bindValue(":categorie", categorie);
    query.bindValue(":quantite", quantite);
    query.bindValue(":date_exp", dateExp);
    query.bindValue(":prix_achat", prixAchat);
    query.bindValue(":prix_vente", prixVente);

    if (!query.exec()) {
        qDebug() << "Update Error:" << query.lastError().text();
        return false;
    }
    return true;
}

bool Stock::supprimer(int id) {
    QSqlQuery query;

    // Prepare the DELETE SQL statement
    query.prepare("DELETE FROM stock WHERE id = :id");
    query.bindValue(":id", id);

    // Execute the query and return the result
    if (query.exec()) {
        return true;
    } else {
        qDebug() << "Error deleting stock item:" << query.lastError().text();
        return false;
    }
}

QSqlQueryModel* Stock::afficher() {
    QSqlQueryModel* model = new QSqlQueryModel();
    model->setQuery("SELECT id, nom_produit, categorie, quantite, date_exp, prix_achat, prix_vente FROM stock");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Product Name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Category"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Quantity"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Expiration Date"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Purchase Price"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Selling Price"));
    return model;
}

QSqlQueryModel* Stock::recherche(const QString &criterion, const QVariant &value) {
    QSqlQuery query;
    QSqlQueryModel* model = new QSqlQueryModel();

    QString sqlQuery;
    if (criterion == "id") {
        sqlQuery = "SELECT * FROM stock WHERE id = :value";
        query.prepare(sqlQuery);
        query.bindValue(":value", value.toInt());
    } else if (criterion == "nom_produit") {
        sqlQuery = "SELECT * FROM stock WHERE LOWER(nom_produit) LIKE :value";
        query.prepare(sqlQuery);
        query.bindValue(":value", "%" + value.toString().toLower() + "%");
    } else if (criterion == "categorie") {
        sqlQuery = "SELECT * FROM stock WHERE LOWER(categorie) LIKE :value";
        query.prepare(sqlQuery);
        query.bindValue(":value", "%" + value.toString().toLower() + "%");
    } else {
        delete model;
        return nullptr;
    }

    if (query.exec()) {
        model->setQuery(query);
    } else {
        qDebug() << "Search query failed:" << query.lastError().text();
        delete model;
        return nullptr;
    }

    return model;
}

QSqlQueryModel* Stock::trierParCategorie(const QString& category) {
        QSqlQueryModel* model = new QSqlQueryModel();
        QSqlQuery query;

        // Debugging log to check the category value
        qDebug() << "Filtering by category: " << category;

        // Prepare the query
        query.prepare("SELECT * FROM stock WHERE TRIM(categorie) = :category ORDER BY id ASC");
        query.bindValue(":category", category);

        // Execute the query
        if (!query.exec()) {
            qDebug() << "Error executing query:" << query.lastError().text();
            return model;
        }

        model->setQuery(query);
        return model;
    }


QSqlQueryModel* Stock::trierParQuantite(bool ascending) {
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;
    QString order = ascending ? "ASC" : "DESC";
    query.prepare("SELECT * FROM stock ORDER BY quantite " + order);
    query.exec();
    model->setQuery(query);
    return model;
}


QSqlQueryModel* Stock::trierParExpiration() {
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;

    // Use the correct column name "DATE_EXP" instead of "date_expiration"
    query.prepare("SELECT * FROM stock ORDER BY DATE_EXP ASC");

    // Check if the query was executed successfully
    if (query.exec()) {
        model->setQuery(query);
    } else {
        qDebug() << "Query execution failed: " << query.lastError().text();
    }

    return model;
}


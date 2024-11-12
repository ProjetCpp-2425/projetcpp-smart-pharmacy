#include "stock.h"
#include <QDebug>

#include <QSqlError>
#include <QSqlQuery>
#include <QMessageBox>

#include <QSqlQueryModel>



Stock::Stock() : id(0), quantite(0), prixAchat(0.0), prixVente(0.0) {}

// Constructor with parameters
Stock::Stock(int id, const QString &nomProduit, const QString &categorie, int quantite, const QDate &dateExp, float prixAchat, float prixVente)
    : id(id), nomProduit(nomProduit), categorie(categorie), quantite(quantite), dateExp(dateExp), prixAchat(prixAchat), prixVente(prixVente) {}


bool Stock::ajouter() {
    // Create a QSqlQuery object to execute SQL statements
    QSqlQuery query;

    // Prepare the SQL INSERT statement
    query.prepare("INSERT INTO stock (id, nom_produit, categorie, quantite, date_exp, prix_achat, prix_vente) "
                  "VALUES (:id, :nom_produit, :categorie, :quantite, :date_exp, :prix_achat, :prix_vente)");

    // Bind values to placeholders
    query.bindValue(":id", id);
    query.bindValue(":nom_produit", nomProduit);
    query.bindValue(":categorie", categorie);
    query.bindValue(":quantite", quantite);
    query.bindValue(":date_exp", dateExp);
    query.bindValue(":prix_achat", prixAchat);
    query.bindValue(":prix_vente", prixVente);

    // Execute the query
    if (query.exec()) {
        return true;  // Successful insertion
    } else {
        qDebug() << "Error adding stock item:" << query.lastError().text();
        return false;  // Insertion failed
    }
}
bool Stock::modifier() {
    // First, check if the ID exists in the database
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM stock WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Error checking stock ID:" << query.lastError().text();
        return false;
    }

    // Move to the first record to get the count
    query.next();
    int count = query.value(0).toInt();

    // If count is zero, the ID does not exist
    if (count == 0) {
        return false;
    }

    // If ID exists, perform the update
    query.prepare("UPDATE stock SET nom_produit = :nom_produit, categorie = :categorie, quantite = :quantite, "
                  "date_exp = :date_exp, prix_achat = :prix_achat, prix_vente = :prix_vente WHERE id = :id");

    // Bind values
    query.bindValue(":id", id);
    query.bindValue(":nom_produit", nomProduit);
    query.bindValue(":categorie", categorie);
    query.bindValue(":quantite", quantite);
    query.bindValue(":date_exp", dateExp);
    query.bindValue(":prix_achat", prixAchat);
    query.bindValue(":prix_vente", prixVente);

    // Execute the update
    if (query.exec()) {
        return true;  // Successfully updated
    } else {
        qDebug() << "Error updating stock item:" << query.lastError().text();
        return false;  // Update failed
    }
}



QSqlQueryModel* Stock::afficher() {
    QSqlQueryModel* model = new QSqlQueryModel();

    // Set up the SQL query to select all columns from the stock table
    model->setQuery("SELECT id, nom_produit, categorie, quantite, date_exp, prix_achat, prix_vente FROM stock");

    // Set column headers (optional but recommended for clarity in the UI)
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Product Name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Category"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Quantity"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Expiration Date"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Purchase Price"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Selling Price"));

    return model;
}
bool Stock::supprimer(int id) {
    // Check if the ID exists
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM stock WHERE id = :id");
    query.bindValue(":id", id);

    if (!query.exec()) {
        qDebug() << "Error checking stock ID:" << query.lastError().text();
        return false;
    }

    query.next();
    int count = query.value(0).toInt();

    // If count is zero, the ID does not exist
    if (count == 0) {
        return false;
    }

    // Delete the record with the specified ID
    query.prepare("DELETE FROM stock WHERE id = :id");
    query.bindValue(":id", id);

    if (query.exec()) {
        return true;  // Successfully deleted
    } else {
        qDebug() << "Error deleting stock item:" << query.lastError().text();
        return false;  // Deletion failed
    }
}


QSqlQueryModel* Stock::recherche(const QString& critere, const QVariant& valeur) {
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;

    // Set up the query based on the criterion (ID or product name)
    if (critere == "id") {
        query.prepare("SELECT id, nom_produit, categorie, quantite, date_exp, prix_achat, prix_vente FROM stock WHERE id = :valeur");
        query.bindValue(":valeur", valeur.toInt());
    } else if (critere == "nom_produit") {
        query.prepare("SELECT id, nom_produit, categorie, quantite, date_exp, prix_achat, prix_vente FROM stock WHERE nom_produit LIKE :valeur");
        query.bindValue(":valeur", "%" + valeur.toString() + "%");
    }

    // Execute the query
    if (!query.exec()) {
        qDebug() << "Error executing search query:" << query.lastError().text();
        delete model;
        return nullptr;  // Return nullptr on error
    }

    // Set the model with the results
    model->setQuery(query);

    // Optional: Set column headers for clarity
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Product Name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Category"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Quantity"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Expiration Date"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Purchase Price"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Selling Price"));

    return model;
}

QSqlQueryModel* Stock::trier(const QString& critere) {
    QSqlQueryModel* model = new QSqlQueryModel();
    QSqlQuery query;

    // Set up the query based on the sorting criterion
    if (critere == "trier_par_date_expiration") {
        query.prepare("SELECT id, nom_produit, categorie, quantite, date_exp, prix_achat, prix_vente FROM stock ORDER BY date_exp ASC");
    } else if (critere == "trier_par_quantite") {
        query.prepare("SELECT id, nom_produit, categorie, quantite, date_exp, prix_achat, prix_vente FROM stock ORDER BY quantite DESC");
    }

    // Execute the query
    if (!query.exec()) {
        qDebug() << "Error executing sort query:" << query.lastError().text();
        delete model;
        return nullptr;
    }

    // Set the model with the sorted results
    model->setQuery(query);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Product Name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Category"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Quantity"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Expiration Date"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Purchase Price"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Selling Price"));

    return model;
}

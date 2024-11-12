#ifndef STOCK_H
#define STOCK_H


#include <QString>
#include <QDate>
#include <QSpinBox>
#include <QSqlQueryModel>


class Stock {
public:
    // Constructors
    Stock();
    Stock(int id, const QString &nomProduit, const QString &categorie, int quantite, const QDate &dateExp, float prixAchat, float prixVente);

    bool ajouter();
    // This will perform the addition
    bool modifier();  // This will handle the update logic
    QSqlQueryModel* afficher();
    bool supprimer(int id);
    QSqlQueryModel* recherche(const QString& critere, const QVariant& valeur);  // Search function based on criteria
     QSqlQueryModel* trier(const QString& critere);

    // Getters
    int getId() const;
    QString getNomProduit() const;
    QString getCategorie() const;
    int getQuantite() const;
    QDate getDateExp() const;
    float getPrixAchat() const;
    float getPrixVente() const;

    // Setters
    void setId(int id);
    void setNomProduit(const QString &nomProduit);
    void setCategorie(const QString &categorie);
    void setQuantite(int quantite);
    void setDateExp(const QDate &dateExp);
    void setPrixAchat(float prixAchat);
    void setPrixVente(float prixVente);

private:
    int id;
    QString nomProduit;
    QString categorie;
    int quantite;  // This will be linked to a QSpinBox in the UI
    QDate dateExp;
    float prixAchat;
    float prixVente;
};




#endif // STOCK_H

#include "commande.h"


Commande::Commande() {
    this->codecommande =0;
}


Commande::Commande( int codeCommande,QString &adresse,  QDateTime &dateCommande,  QString &statusCommande,
                    QString &remarque, int codef, int cin, int produit)
    : codecommande(codeCommande),adresse(adresse), dateCommande(dateCommande), statusCommande(statusCommande),
      remarque(remarque), codef(codef), cin(cin), produit(produit) {}


QString Commande::getAdresse()  { return adresse; }
QDateTime Commande::getDateCommande()  { return dateCommande; }
QString Commande::getStatusCommande()  { return statusCommande; }
QString Commande::getRemarque()  { return remarque; }
int Commande::getCodef()  { return codef; }
int Commande::getCodeCommande()  { return codecommande; }
int Commande::getCin()  { return cin; }
int Commande::getProduit()  { return produit; }


void Commande::setAdresse( QString &adresse) { this->adresse = adresse; }
void Commande::setDateCommande( QDateTime &dateCommande) { this->dateCommande = dateCommande; }
void Commande::setStatusCommande( QString &statusCommande) { this->statusCommande = statusCommande; }
void Commande::setRemarque( QString &remarque) { this->remarque = remarque; }
void Commande::setCodef(int codef) { this->codef = codef; }
void Commande::setCin(int cin) { this->cin = cin; }
void Commande::setProduit(int produit) { this->produit = produit; }


QSqlQueryModel* Commande::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(R"(
            SELECT code_commande, adresse, date_commande, status_commande, remarque, codef,TO_CHAR(cin) AS cin, produit
            FROM COMMANDES
        )");

    // Set headers for each column
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Code Commande"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date Commande"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Status Commande"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Remarque"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("CodeF"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Produit"));

    return model;
}

bool Commande::supprimer(int code)
{
    QSqlQuery query;
    query.prepare("DELETE FROM COMMANDES WHERE code_commande = :codeasupprimer");
    query.bindValue(":codeasupprimer", code);


    if (query.exec()) {
        return query.numRowsAffected() > 0;

    } else {

        return false;
    }
}


Commande Commande::trouver(int code)
{
    QSqlQuery query;
    query.prepare("SELECT code_commande, adresse, date_commande, status_commande, remarque, codef, cin, produit "
                  "FROM COMMANDES WHERE code_commande = :code");
    query.bindValue(":code", code);

    if (!query.exec() || !query.next()) {
        return Commande();
    }


    int codeCommande = query.value("code_commande").toInt();
    QString adresse = query.value("adresse").toString();
    QDateTime dateCommande = query.value("date_commande").toDateTime();
    QString statusCommande = query.value("status_commande").toString();
    QString remarque = query.value("remarque").toString();
    int codef = query.value("codef").toInt();
    int cin = query.value("cin").toInt();
    int produit = query.value("produit").toInt();


    Commande tmp(codeCommande,adresse,dateCommande,statusCommande, remarque, codef, cin, produit);
    return tmp;
}

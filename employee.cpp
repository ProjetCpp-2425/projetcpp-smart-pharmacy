#include "employee.h"
#include <QMessageBox>
#include <QSqlError>

employee::employee() {
    nom ="";
    date_n = QDate();
    adresse ="";
    numtel = 0 ;
    email = "";
    cin = 0;
    date_e = QDate();
    horaire_debut = QTime();
    horaire_fin = QTime();
    conge = 0;
    absences = 0;
    salaire = 0.0;
    prime = 0.0 ;
    mdp = "";
}

employee::employee(QString Nom, QDate DateN, QString Adresse, int NumTel, QString Email, int Cin,
                 QDate DateE, QTime HoraireDebut, QTime HoraireFin, int Conge, int Absences,
                 float Salaire, float Prime, QString Mdp) {

    nom = Nom;
    date_n = DateN;
    adresse = Adresse;
    numtel = NumTel;
    email = Email;
    cin = Cin;
    date_e = DateE;
    horaire_debut = HoraireDebut;
    horaire_fin = HoraireFin;
    conge = Conge;
    absences = Absences;
    salaire = Salaire;
    prime = Prime;
    mdp = Mdp;
}

// Getters

QString employee::getNom() {
    return nom;
}

QDate employee::getDateN() {
    return date_n;
}

QString employee::getAdresse() {
    return adresse;
}

int employee::getNumTel() {
    return numtel;
}

QString employee::getEmail() {
    return email;
}

int employee::getCin() {
    return cin;
}

QDate employee::getDateE() {
    return date_e;
}

QTime employee::getHoraireDebut() {
    return horaire_debut;
}

QTime employee::getHoraireFin() {
    return horaire_fin;
}

int employee::getConge() {
    return conge;
}

int employee::getAbsences() {
    return absences;
}

float employee::getSalaire() {
    return salaire;
}

float employee::getPrime() {
    return prime;
}

QString employee::getMdp() {
    return mdp;
}

// Setters

void employee::setNom(QString Nom) {
    nom = Nom;
}

void employee::setDateN(QDate DateN) {
    date_n = DateN;
}

void employee::setAdresse(QString Adresse) {
    adresse = Adresse;
}

void employee::setNumTel(int NumTel) {
    numtel = NumTel;
}

void employee::setEmail(QString Email) {
    email = Email;
}

void employee::setCin(int Cin) {
    cin = Cin;
}

void employee::setDateE(QDate DateE) {
    date_e = DateE;
}

void employee::setHoraireDebut(QTime HoraireDebut) {
    horaire_debut = HoraireDebut;
}

void employee::setHoraireFin(QTime HoraireFin) {
    horaire_fin = HoraireFin;
}

void employee::setConge(int Conge) {
    conge = Conge;
}

void employee::setAbsences(int Absences) {
    absences = Absences;
}

void employee::setSalaire(float Salaire) {
    salaire = Salaire;
}

void employee::setPrime(float Prime) {
    prime = Prime;
}

void employee::setMdp(QString Mdp) {
    mdp = Mdp;
}

// CRUD
// Create :

bool employee::Ajouter()
{
    if (nom.isEmpty()) {
        QMessageBox::warning(nullptr, "Erreur de saisie", "Le nom ne peut pas être vide.");
        return false;
    }

    if (adresse.isEmpty()) {
        QMessageBox::warning(nullptr, "Erreur de saisie", "L'adresse ne peut pas être vide.");
        return false;
    }

    if (QString::number(numtel).length() != 8) {
        QMessageBox::warning(nullptr, "Erreur de saisie", "Le numéro de téléphone doit comporter 8 chiffres.");
        return false;
    }

    if (email.isEmpty() || !email.contains("@") || !email.contains(".")) {
        QMessageBox::warning(nullptr, "Erreur de saisie", "L'email doit être valide et contenir un '@'.");
        return false;
    }

    if (QString::number(cin).length() != 5) {
        QMessageBox::warning(nullptr, "Erreur de saisie", "Le CIN doit comporter 5 chiffres.");
        return false;
    }

    if (salaire <= 0) {
        QMessageBox::warning(nullptr, "Erreur de saisie", "Le salaire doit être un nombre positif.");
        return false;
    }

    if (mdp.isEmpty()) {
        QMessageBox::warning(nullptr, "Erreur de saisie", "Le mot de passe ne peut pas être vide.");
        return false;
    }

    QSqlQuery query;

    query.prepare("INSERT INTO employee (nom, date_n, adresse, numtel, email, cin, date_e, "
                  "horaire_debut, horaire_fin, conge, absences, salaire, prime, mdp) "
                  "VALUES (:nom, :date_n, :adresse, :numtel, :email, :cin, :date_e, "
                  ":horaire_debut, :horaire_fin, :conge, :absences, :salaire, :prime, :mdp)");

    query.bindValue(":nom", nom);
    query.bindValue(":date_n", date_n);
    query.bindValue(":adresse", adresse);
    query.bindValue(":numtel", numtel);
    query.bindValue(":email", email);
    query.bindValue(":cin", cin);
    query.bindValue(":date_e", date_e);
    query.bindValue(":horaire_debut", horaire_debut);  // Correction ici
    query.bindValue(":horaire_fin", horaire_fin);  // Correction ici
    query.bindValue(":conge", conge);
    query.bindValue(":absences", absences);  // Correction ici
    query.bindValue(":salaire", salaire);
    query.bindValue(":prime", prime);
    query.bindValue(":mdp", mdp);

    return query.exec();
}

// Afficher

QSqlQueryModel* employee::afficher()
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT nom, "
                    "TO_CHAR(date_n, 'DD-MM-YYYY') AS date_n, "
                    "adresse, "
                    "TO_CHAR(numtel) AS numtel, "
                    "TO_CHAR(email) AS email, "
                    "TO_CHAR(cin) AS cin, "
                    "TO_CHAR(date_e, 'DD-MM-YYYY') AS date_e, "
                    "TO_CHAR(horaire_debut, 'HH24:MI') AS horaire_debut, "
                    "TO_CHAR(horaire_fin, 'HH24:MI') AS horaire_fin, "
                    "conge, absences, "
                    "TO_CHAR(salaire, 'FM99999999.00') AS salaire, "
                    "TO_CHAR(prime, 'FM99999999.00') AS prime, "
                    "mdp "
                    "FROM employee");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Date Naissance"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Numéro Téléphone"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Date Entrée"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Horaire Début"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Horaire Fin"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("Congé"));
    model->setHeaderData(10, Qt::Horizontal, QObject::tr("Absences"));
    model->setHeaderData(11, Qt::Horizontal, QObject::tr("Salaire"));
    model->setHeaderData(12, Qt::Horizontal, QObject::tr("Prime"));
    model->setHeaderData(13, Qt::Horizontal, QObject::tr("Mot de passe"));

    return model;
}

// Modifier

bool employee::modifier()
{
    if (nom.isEmpty()) {
        QMessageBox::warning(nullptr, "Erreur de saisie", "Le nom ne peut pas être vide.");
        return false;
    }

    if (adresse.isEmpty()) {
        QMessageBox::warning(nullptr, "Erreur de saisie", "L'adresse ne peut pas être vide.");
        return false;
    }

    if (QString::number(numtel).length() != 8) {
        QMessageBox::warning(nullptr, "Erreur de saisie", "Le numéro de téléphone doit comporter 8 chiffres.");
        return false;
    }

    if (email.isEmpty() || !email.contains("@")) {
        QMessageBox::warning(nullptr, "Erreur de saisie", "L'email doit être valide et contenir un '@'.");
        return false;
    }

    if (QString::number(cin).length() != 5) {
        QMessageBox::warning(nullptr, "Erreur de saisie", "Le CIN doit comporter 5 chiffres.");
        return false;
    }

    if (salaire <= 0) {
        QMessageBox::warning(nullptr, "Erreur de saisie", "Le salaire doit être un nombre positif.");
        return false;
    }

    if (mdp.isEmpty()) {
        QMessageBox::warning(nullptr, "Erreur de saisie", "Le mot de passe ne peut pas être vide.");
        return false;
    }

    QSqlQuery query;

    query.prepare("UPDATE employee SET nom = :nom, date_n = :date_n, adresse = :adresse, numtel = :numtel, "
                  "email = :email, date_e = :date_e, horaire_debut = :horaire_debut, "
                  "horaire_fin = :horaire_fin, conge = :conge, absences = :absences, salaire = :salaire, "
                  "prime = :prime, mdp = :mdp WHERE cin = :cin");

    query.bindValue(":nom", nom);
    query.bindValue(":date_n", date_n);
    query.bindValue(":adresse", adresse);
    query.bindValue(":numtel", numtel);
    query.bindValue(":email", email);
    query.bindValue(":date_e", date_e);
    query.bindValue(":horaire_debut", horaire_debut);
    query.bindValue(":horaire_fin", horaire_fin);
    query.bindValue(":conge", conge);
    query.bindValue(":absences", absences);
    query.bindValue(":salaire", salaire);
    query.bindValue(":prime", prime);
    query.bindValue(":mdp", mdp);

    query.bindValue(":cin", cin);

    return query.exec();
}


// Supprimer

bool employee::Supprimer(int cin)
{
    QSqlQuery query;
    query.prepare("DELETE FROM employee WHERE cin = :cin");
    query.bindValue(":cin", cin);
    return query.exec();
}

//reset

bool employee::reset()
{
    QSqlQuery query;
    query.prepare("delete employee");
    return query.exec();
}

// ## Recherche ## //

QSqlQueryModel *employee::afficher_cin(QString ch)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT nom, "
                    "TO_CHAR(date_n, 'DD-MM-YYYY') AS date_n, "
                    "adresse, "
                    "TO_CHAR(numtel) AS numtel, "
                    "TO_CHAR(email) AS email, "
                    "TO_CHAR(cin) AS cin, "
                    "TO_CHAR(date_e, 'DD-MM-YYYY') AS date_e, "
                    "TO_CHAR(horaire_debut, 'HH24:MI') AS horaire_debut, "
                    "TO_CHAR(horaire_fin, 'HH24:MI') AS horaire_fin, "
                    "conge, absences, "
                    "TO_CHAR(salaire, 'FM99999999.00') AS salaire, "
                    "TO_CHAR(prime, 'FM99999999.00') AS prime, "
                    "mdp "
                    "FROM employee where cin = '"+ch+"'");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Date Naissance"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Numéro Téléphone"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Date Entrée"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Horaire Début"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Horaire Fin"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("Congé"));
    model->setHeaderData(10, Qt::Horizontal, QObject::tr("Absences"));
    model->setHeaderData(11, Qt::Horizontal, QObject::tr("Salaire"));
    model->setHeaderData(12, Qt::Horizontal, QObject::tr("Prime"));
    model->setHeaderData(13, Qt::Horizontal, QObject::tr("Mot de passe"));

    return model;
}
QSqlQueryModel *employee::afficher_nom(QString ch)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT nom, "
                    "TO_CHAR(date_n, 'DD-MM-YYYY') AS date_n, "
                    "adresse, "
                    "TO_CHAR(numtel) AS numtel, "
                    "TO_CHAR(email) AS email, "
                    "TO_CHAR(cin) AS cin, "
                    "TO_CHAR(date_e, 'DD-MM-YYYY') AS date_e, "
                    "TO_CHAR(horaire_debut, 'HH24:MI') AS horaire_debut, "
                    "TO_CHAR(horaire_fin, 'HH24:MI') AS horaire_fin, "
                    "conge, absences, "
                    "TO_CHAR(salaire, 'FM99999999.00') AS salaire, "
                    "TO_CHAR(prime, 'FM99999999.00') AS prime, "
                    "mdp "
                    "FROM employee where nom = '"+ch+"'");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Date Naissance"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Numéro Téléphone"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Date Entrée"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Horaire Début"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Horaire Fin"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("Congé"));
    model->setHeaderData(10, Qt::Horizontal, QObject::tr("Absences"));
    model->setHeaderData(11, Qt::Horizontal, QObject::tr("Salaire"));
    model->setHeaderData(12, Qt::Horizontal, QObject::tr("Prime"));
    model->setHeaderData(13, Qt::Horizontal, QObject::tr("Mot de passe"));

    return model;
}
QSqlQueryModel *employee::afficher_salaire(QString ch)
{
    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery("SELECT nom, "
                    "TO_CHAR(date_n, 'DD-MM-YYYY') AS date_n, "
                    "adresse, "
                    "TO_CHAR(numtel) AS numtel, "
                    "TO_CHAR(email) AS email, "
                    "TO_CHAR(cin) AS cin, "
                    "TO_CHAR(date_e, 'DD-MM-YYYY') AS date_e, "
                    "TO_CHAR(horaire_debut, 'HH24:MI') AS horaire_debut, "
                    "TO_CHAR(horaire_fin, 'HH24:MI') AS horaire_fin, "
                    "conge, absences, "
                    "TO_CHAR(salaire, 'FM99999999.00') AS salaire, "
                    "TO_CHAR(prime, 'FM99999999.00') AS prime, "
                    "mdp "
                    "FROM employee where salaire = '"+ch+"'");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Nom"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Date Naissance"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Numéro Téléphone"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Date Entrée"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Horaire Début"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Horaire Fin"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("Congé"));
    model->setHeaderData(10, Qt::Horizontal, QObject::tr("Absences"));
    model->setHeaderData(11, Qt::Horizontal, QObject::tr("Salaire"));
    model->setHeaderData(12, Qt::Horizontal, QObject::tr("Prime"));
    model->setHeaderData(13, Qt::Horizontal, QObject::tr("Mot de passe"));

    return model;
}


// ## Tri ## //

QSqlQueryModel *employee:: afficher_choix(QString choix)
{
    QSqlQueryModel * model =new QSqlQueryModel();

    if(choix=="salaire croissants")
    {
        model->setQuery("SELECT nom, "
                        "TO_CHAR(date_n, 'DD-MM-YYYY') AS date_n, "
                        "adresse, "
                        "TO_CHAR(numtel) AS numtel, "
                        "TO_CHAR(email) AS email, "
                        "TO_CHAR(cin) AS cin, "
                        "TO_CHAR(date_e, 'DD-MM-YYYY') AS date_e, "
                        "TO_CHAR(horaire_debut, 'HH24:MI') AS horaire_debut, "
                        "TO_CHAR(horaire_fin, 'HH24:MI') AS horaire_fin, "
                        "conge, absences, "
                        "TO_CHAR(salaire, 'FM99999999.00') AS salaire, "
                        "TO_CHAR(prime, 'FM99999999.00') AS prime, "
                        "mdp "
                        "FROM employee ORDER BY salaire ASC");

        model->setHeaderData(0, Qt::Horizontal, QObject::tr("Nom"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Date Naissance"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Adresse"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Numéro Téléphone"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Email"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("CIN"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("Date Entrée"));
        model->setHeaderData(7, Qt::Horizontal, QObject::tr("Horaire Début"));
        model->setHeaderData(8, Qt::Horizontal, QObject::tr("Horaire Fin"));
        model->setHeaderData(9, Qt::Horizontal, QObject::tr("Congé"));
        model->setHeaderData(10, Qt::Horizontal, QObject::tr("Absences"));
        model->setHeaderData(11, Qt::Horizontal, QObject::tr("Salaire"));
        model->setHeaderData(12, Qt::Horizontal, QObject::tr("Prime"));
        model->setHeaderData(13, Qt::Horizontal, QObject::tr("Mot de passe"));
    }
    else if(choix=="salaire decroissants")
    {
        model->setQuery("SELECT nom, "
                        "TO_CHAR(date_n, 'DD-MM-YYYY') AS date_n, "
                        "adresse, "
                        "TO_CHAR(numtel) AS numtel, "
                        "TO_CHAR(email) AS email, "
                        "TO_CHAR(cin) AS cin, "
                        "TO_CHAR(date_e, 'DD-MM-YYYY') AS date_e, "
                        "TO_CHAR(horaire_debut, 'HH24:MI') AS horaire_debut, "
                        "TO_CHAR(horaire_fin, 'HH24:MI') AS horaire_fin, "
                        "conge, absences, "
                        "TO_CHAR(salaire, 'FM99999999.00') AS salaire, "
                        "TO_CHAR(prime, 'FM99999999.00') AS prime, "
                        "mdp "
                        "FROM employee ORDER BY salaire DESC");

        model->setHeaderData(0, Qt::Horizontal, QObject::tr("Nom"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Date Naissance"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Adresse"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Numéro Téléphone"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Email"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("CIN"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("Date Entrée"));
        model->setHeaderData(7, Qt::Horizontal, QObject::tr("Horaire Début"));
        model->setHeaderData(8, Qt::Horizontal, QObject::tr("Horaire Fin"));
        model->setHeaderData(9, Qt::Horizontal, QObject::tr("Congé"));
        model->setHeaderData(10, Qt::Horizontal, QObject::tr("Absences"));
        model->setHeaderData(11, Qt::Horizontal, QObject::tr("Salaire"));
        model->setHeaderData(12, Qt::Horizontal, QObject::tr("Prime"));
        model->setHeaderData(13, Qt::Horizontal, QObject::tr("Mot de passe"));
    }
    else if(choix=="nom decroissants")
    {
        model->setQuery("SELECT nom, "
                        "TO_CHAR(date_n, 'DD-MM-YYYY') AS date_n, "
                        "adresse, "
                        "TO_CHAR(numtel) AS numtel, "
                        "TO_CHAR(email) AS email, "
                        "TO_CHAR(cin) AS cin, "
                        "TO_CHAR(date_e, 'DD-MM-YYYY') AS date_e, "
                        "TO_CHAR(horaire_debut, 'HH24:MI') AS horaire_debut, "
                        "TO_CHAR(horaire_fin, 'HH24:MI') AS horaire_fin, "
                        "conge, absences, "
                        "TO_CHAR(salaire, 'FM99999999.00') AS salaire, "
                        "TO_CHAR(prime, 'FM99999999.00') AS prime, "
                        "mdp "
                        "FROM employee ORDER BY nom DESC");

        model->setHeaderData(0, Qt::Horizontal, QObject::tr("Nom"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Date Naissance"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Adresse"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Numéro Téléphone"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Email"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("CIN"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("Date Entrée"));
        model->setHeaderData(7, Qt::Horizontal, QObject::tr("Horaire Début"));
        model->setHeaderData(8, Qt::Horizontal, QObject::tr("Horaire Fin"));
        model->setHeaderData(9, Qt::Horizontal, QObject::tr("Congé"));
        model->setHeaderData(10, Qt::Horizontal, QObject::tr("Absences"));
        model->setHeaderData(11, Qt::Horizontal, QObject::tr("Salaire"));
        model->setHeaderData(12, Qt::Horizontal, QObject::tr("Prime"));
        model->setHeaderData(13, Qt::Horizontal, QObject::tr("Mot de passe"));
    }
    else if(choix=="nom croissants")
    {
        model->setQuery("SELECT nom, "
                        "TO_CHAR(date_n, 'DD-MM-YYYY') AS date_n, "
                        "adresse, "
                        "TO_CHAR(numtel) AS numtel, "
                        "TO_CHAR(email) AS email, "
                        "TO_CHAR(cin) AS cin, "
                        "TO_CHAR(date_e, 'DD-MM-YYYY') AS date_e, "
                        "TO_CHAR(horaire_debut, 'HH24:MI') AS horaire_debut, "
                        "TO_CHAR(horaire_fin, 'HH24:MI') AS horaire_fin, "
                        "conge, absences, "
                        "TO_CHAR(salaire, 'FM99999999.00') AS salaire, "
                        "TO_CHAR(prime, 'FM99999999.00') AS prime, "
                        "mdp "
                        "FROM employee ORDER BY nom ASC");

        model->setHeaderData(0, Qt::Horizontal, QObject::tr("Nom"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Date Naissance"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Adresse"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Numéro Téléphone"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Email"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("CIN"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("Date Entrée"));
        model->setHeaderData(7, Qt::Horizontal, QObject::tr("Horaire Début"));
        model->setHeaderData(8, Qt::Horizontal, QObject::tr("Horaire Fin"));
        model->setHeaderData(9, Qt::Horizontal, QObject::tr("Congé"));
        model->setHeaderData(10, Qt::Horizontal, QObject::tr("Absences"));
        model->setHeaderData(11, Qt::Horizontal, QObject::tr("Salaire"));
        model->setHeaderData(12, Qt::Horizontal, QObject::tr("Prime"));
        model->setHeaderData(13, Qt::Horizontal, QObject::tr("Mot de passe"));

    }
    else if(choix=="conge decroissants")
    {
        model->setQuery("SELECT nom, "
                        "TO_CHAR(date_n, 'DD-MM-YYYY') AS date_n, "
                        "adresse, "
                        "TO_CHAR(numtel) AS numtel, "
                        "TO_CHAR(email) AS email, "
                        "TO_CHAR(cin) AS cin, "
                        "TO_CHAR(date_e, 'DD-MM-YYYY') AS date_e, "
                        "TO_CHAR(horaire_debut, 'HH24:MI') AS horaire_debut, "
                        "TO_CHAR(horaire_fin, 'HH24:MI') AS horaire_fin, "
                        "conge, absences, "
                        "TO_CHAR(salaire, 'FM99999999.00') AS salaire, "
                        "TO_CHAR(prime, 'FM99999999.00') AS prime, "
                        "mdp "
                        "FROM employee ORDER BY conge DESC");

        model->setHeaderData(0, Qt::Horizontal, QObject::tr("Nom"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Date Naissance"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Adresse"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Numéro Téléphone"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Email"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("CIN"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("Date Entrée"));
        model->setHeaderData(7, Qt::Horizontal, QObject::tr("Horaire Début"));
        model->setHeaderData(8, Qt::Horizontal, QObject::tr("Horaire Fin"));
        model->setHeaderData(9, Qt::Horizontal, QObject::tr("Congé"));
        model->setHeaderData(10, Qt::Horizontal, QObject::tr("Absences"));
        model->setHeaderData(11, Qt::Horizontal, QObject::tr("Salaire"));
        model->setHeaderData(12, Qt::Horizontal, QObject::tr("Prime"));
        model->setHeaderData(13, Qt::Horizontal, QObject::tr("Mot de passe"));
    }
    else if(choix=="conge croissants")
    {
        model->setQuery("SELECT nom, "
                        "TO_CHAR(date_n, 'DD-MM-YYYY') AS date_n, "
                        "adresse, "
                        "TO_CHAR(numtel) AS numtel, "
                        "TO_CHAR(email) AS email, "
                        "TO_CHAR(cin) AS cin, "
                        "TO_CHAR(date_e, 'DD-MM-YYYY') AS date_e, "
                        "TO_CHAR(horaire_debut, 'HH24:MI') AS horaire_debut, "
                        "TO_CHAR(horaire_fin, 'HH24:MI') AS horaire_fin, "
                        "conge, absences, "
                        "TO_CHAR(salaire, 'FM99999999.00') AS salaire, "
                        "TO_CHAR(prime, 'FM99999999.00') AS prime, "
                        "mdp "
                        "FROM employee ORDER BY conge ASC");

        model->setHeaderData(0, Qt::Horizontal, QObject::tr("Nom"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Date Naissance"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Adresse"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Numéro Téléphone"));
        model->setHeaderData(4, Qt::Horizontal, QObject::tr("Email"));
        model->setHeaderData(5, Qt::Horizontal, QObject::tr("CIN"));
        model->setHeaderData(6, Qt::Horizontal, QObject::tr("Date Entrée"));
        model->setHeaderData(7, Qt::Horizontal, QObject::tr("Horaire Début"));
        model->setHeaderData(8, Qt::Horizontal, QObject::tr("Horaire Fin"));
        model->setHeaderData(9, Qt::Horizontal, QObject::tr("Congé"));
        model->setHeaderData(10, Qt::Horizontal, QObject::tr("Absences"));
        model->setHeaderData(11, Qt::Horizontal, QObject::tr("Salaire"));
        model->setHeaderData(12, Qt::Horizontal, QObject::tr("Prime"));
        model->setHeaderData(13, Qt::Horizontal, QObject::tr("Mot de passe"));

    }
    return model ;
}

// ## Statistique ## //

int employee::statistique1(){
    int count = 0;

    QSqlQuery requete("SELECT * FROM employee WHERE salaire < 500");

    while(requete.next()) {
        count++;
    }

    return count;
}


int employee::statistique2(){
    int count = 0;

    QSqlQuery requete("SELECT * FROM employee WHERE salaire > 500");

    while(requete.next()) {
        count++;
    }

    return count;
}


// PDF
employee* employee::reademploye(int val)
{
    QSqlQuery query;
    query.prepare("SELECT cin, nom, TO_CHAR(date_n, 'DD-MM-YYYY') AS date_n, "
                  "TO_CHAR(date_e, 'DD-MM-YYYY') AS date_e, "
                  "adresse, numtel, email, mdp, "
                  "TO_CHAR(horaire_debut, 'HH24:MI:SS') AS horaire_debut, "
                  "TO_CHAR(horaire_fin, 'HH24:MI:SS') AS horaire_fin, "
                  "conge, absences, salaire, prime "
                  "FROM employee WHERE cin = :val");

    query.bindValue(":val", val);

    if (query.exec())
    {
        while (query.next())
        {
            setCin(query.value(0).toInt());
            setNom(query.value(1).toString());
            QDate dateN = QDate::fromString(query.value(2).toString(), "dd-MM-yyyy");
            QDate dateE = QDate::fromString(query.value(3).toString(), "dd-MM-yyyy");
            setDateN(dateN);
            setDateE(dateE);
            setAdresse(query.value(4).toString());
            setNumTel(query.value(5).toInt());
            setEmail(query.value(6).toString());
            setMdp(query.value(7).toString());
            QTime horaireDebut = QTime::fromString(query.value(8).toString(), "HH:mm:ss");
            QTime horaireFin = QTime::fromString(query.value(9).toString(), "HH:mm:ss");
            setHoraireDebut(horaireDebut);
            setHoraireFin(horaireFin);
            setConge(query.value(10).toInt());
            setAbsences(query.value(11).toInt());
            setSalaire(query.value(12).toFloat());
            setPrime(query.value(13).toFloat());
        }
    }
    return this;
}
bool employee::isMdpCorrect(int cinn, const QString& mdp) {
    QSqlQuery query;
    query.prepare("SELECT mdp FROM EMPLOYEE WHERE CIN = :cin");
    query.bindValue(":cin", cinn);

    if (query.exec()) {
        if (query.next()) {
            QString dbMdp = query.value(0).toString();
            return dbMdp == mdp;
        }
    } else {
        qDebug() << "Erreur SQL dans isPasswordCorrect:" << query.lastError().text();
    }

    return false;
}
bool employee::doesCINExist(int cinn) {
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM EMPLOYEE WHERE CIN = :cin");  // Assurez-vous que la colonne s'appelle bien CIN
    query.bindValue(":cin", cinn);

    if (query.exec()) {
        if (query.next()) {
            int count = query.value(0).toInt();
            return count > 0; // Retourne true si le CIN existe
        }
    } else {
        qDebug() << "Erreur SQL dans doesCINExist:" << query.lastError().text();
    }

    return false;
}



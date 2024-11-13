#ifndef PRESCRIPTION_H
#define PRESCRIPTION_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <iostream>
#include <QDate>
#include <QFile>

using namespace std;

class Prescription {
    int ID_prescription;
    QDate Date_prescription;
    QString Nom_patient;
    QString Nom_medecin;
    QString Medicament;
    QString Statut_prescription;
    int Duree_traitement;
    QString Dosage;
    int Frequence;
    QString Note;

public:
    //constructeur
    Prescription(int id, QDate datePrescrip, QString nomPatient, QString nomMedecin,
                 QString medicament, QString statutPrescrip,
                 int dureeTraitement, QString dosage, int frequence, QString note);
    Prescription(){return ;}

    //getters
    int getID_Prescription(){return this->ID_prescription;}
    QDate getDate_Prescription(){return this->Date_prescription;}
    QString getNom_Patient(){return this->Nom_patient;}
    QString getNom_Medecin(){return this->Nom_medecin;}
    QString getMedicament(){return this->Medicament;}
    QString getStatut(){return this->Statut_prescription;}
    int getDuree_traitement(){return this->Duree_traitement;}
    QString getDosage(){return this->Dosage;}
    int getFrequence(){return this->Frequence;}
    QString getNote(){return this->Note;}


    //setters
    void setID(int id){this->ID_prescription=id;}
    void setDate_Prescription(QDate date_prescription){this->Date_prescription=date_prescription;}
    void setNom_Patient(QString nom){this->Nom_patient=nom;}
    void setNom_Medecin (QString nom){this->Nom_medecin= nom;}
    void setMedicament (QString medicament){this->Medicament=medicament;}
    void setStatut(QString statut){this->Statut_prescription=statut;}
    void setDuree_traitement(int duree){this->Duree_traitement=duree;}
    void setDosage(QString dosage){this->Dosage=dosage;}
    void setFrequence (int frequence){this->Frequence=frequence;}
    void setNote(QString note){this->Note=note;}





static QSqlQueryModel * afficher();
static bool ajouter (Prescription pres);
static bool supprimer(int id);
static bool modifier ();
static QSqlQueryModel* trier_nom();
static bool genereText();





};

#endif // PRESCRIPTION_H

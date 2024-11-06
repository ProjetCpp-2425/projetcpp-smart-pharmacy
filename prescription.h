#ifndef PRESCRIPTION_H
#define PRESCRIPTION_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <iostream>
#include <QDate>

using namespace std;

class Prescription {
    int ID_prescription;
    QDate Date_prescription;
    QString Nom_patient;
    QString Nom_medecin;
    QString Medicament;
    QDate Date_Creation;
    QString Statut_prescription;
    QString Duree_traitement;
    QString Dosage;
    QString Frequence;
    QString Note;

public:
    //constructeur
    Prescription(int id, QDate datePrescrip, QString nomPatient, QString nomMedecin,
                 QString medicament, QDate dateCreation, QString statutPrescrip,
                 QString dureeTraitement, QString dosage, QString frequence, QString note);
    Prescription(){return ;}

    //getters
    int getID_Prescription(){return this->ID_prescription;}
    QDate getDate_Prescription(){return this->Date_prescription;}
    QString getNom_Patient(){return this->Nom_patient;}
    QString getNom_Medecin(){return this->Nom_medecin;}
    QString getMedicament(){return this->Medicament;}
    QDate getDate_Creation(){return this->Date_Creation;}
    QString getStatut(){return this->Statut_prescription;}
    QString getDuree_traitement(){return this->Duree_traitement;}
    QString getDosage(){return this->Dosage;}
    QString getFrequence(){return this->Frequence;}
    QString getNote(){return this->Note;}


    //setters
    void setID(int id){this->ID_prescription=id;}
    void setDate_Prescription(QDate date_prescription){this->Date_Creation=date_prescription;}
    void setNom_Patient(QString nom){this->Nom_patient=nom;}
    void setNom_Medecin (QString nom){this->Nom_medecin= nom;}
    void setMedicament (QString medicament){this->Medicament=medicament;}
    void setDate_Creation(QDate date_creation){this->Date_Creation=date_creation;}
    void setStatut(QString statut){this->Statut_prescription=statut;}
    void setDuree_traitement(QString duree){this->Duree_traitement=duree;}
    void setDosage(QString dosage){this->Dosage=dosage;}
    void setFrequence (QString frequence){this->Frequence=frequence;}
    void setNote(QString note){this->Note=note;}





 QSqlQueryModel * affiche(int id);
static bool supprimer(int id);
static bool modifier (int ID,QString champ,QString nouvelle_valeure);


};

#endif // PRESCRIPTION_H

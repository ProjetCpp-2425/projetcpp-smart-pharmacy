#ifndef PRESCRIPTION_H
#define PRESCRIPTION_H

#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

#include <iostream>
#include <string.h>

using namespace std;

class Prescription{
    int ID_prescription;
       string Date_prescription;
       string Nom_patient;
       string Nom_medecin;
       string Medicament;
       string Date_Creation;
       string Statut_prescription;
       int Duree_traitement;
       int Dosage;
       int Frequence;
       string Note;

   public:
       Prescription(int id, string datePrescrip,string nomPatient, string nomMedecin,string medicament, string dateCreation,string statutPrescrip, int dureeTraitement,int dosage, int frequence, string note);

       int getIDPrescription();
       string getDatePrescription();
       string getNomPatient();
       string getNomMedecin();
       string getMedicament();
       string getDateCreation();
       string getStatutPrescription();
       int getDureeTraitement();
       int getDosage();
       int getFrequence();
       string getNote();

       void setDatePrescription(string datePrescrip);
       void setNomPatient(string nomPatient);
       void setNomMedecin(string nomMedecin);
       void setMedicament(string medicament);
       void setDateCreation(string dateCreation);
       void setStatutPrescription(string statutPrescrip);
       void setDureeTraitement(int dureeTraitement);
       void setDosage(int dosage);
       void setFrequence(int frequence);
       void setNote(string note);

       void afficherDetails();
};


#endif // PRESCRIPTION_H

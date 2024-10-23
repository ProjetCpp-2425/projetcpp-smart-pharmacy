#include "Prescription.h"
#include <string>

using namespace std;

Prescription::Prescription(int id, const string &datePrescrip,
                           const string &nomPatient, const string &nomMedecin,
                           const string &medicament, const string &dateCreation,
                           const string &statutPrescrip, int dureeTraitement,
                           int dosage, int frequence, const string &note) {
    ID_prescription = id;
    Date_prescription = datePrescrip;
    Nom_patient = nomPatient;
    Nom_medecin = nomMedecin;
    Medicament = medicament;
    Date_Creation = dateCreation;
    Statut_prescription = statutPrescrip;
    Duree_traitement = dureeTraitement;
    Dosage = dosage;
    Frequence = frequence;
    Note = note;
}


int Prescription::getIDPrescription() {
    return ID_prescription;
}

string Prescription::getDatePrescription() {
    return Date_prescription;
}

string Prescription::getNomPatient() {
    return Nom_patient;
}

string Prescription::getNomMedecin() {
    return Nom_medecin;
}

string Prescription::getMedicament() {
    return Medicament;
}

string Prescription::getDateCreation() {
    return Date_Creation;
}

string Prescription::getStatutPrescription() {
    return Statut_prescription;
}

int Prescription::getDureeTraitement() {
    return Duree_traitement;
}

int Prescription::getDosage() {
    return Dosage;
}

int Prescription::getFrequence() {
    return Frequence;
}

string Prescription::getNote() {
    return Note;
}

void Prescription::setDatePrescription(string datePrescrip) {
    Date_prescription = datePrescrip;
}

void Prescription::setNomPatient(string nomPatient) {
    Nom_patient = nomPatient;
}

void Prescription::setNomMedecin(string nomMedecin) {
    Nom_medecin = nomMedecin;
}

void Prescription::setMedicament(string medicament) {
    Medicament = medicament;
}

void Prescription::setDateCreation(string dateCreation) {
    Date_Creation = dateCreation;
}

void Prescription::setStatutPrescription(string statutPrescrip) {
    Statut_prescription = statutPrescrip;
}

void Prescription::setDureeTraitement(int dureeTraitement) {
    Duree_traitement = dureeTraitement;
}

void Prescription::setDosage(int dosage) {
    Dosage = dosage;
}

void Prescription::setFrequence(int frequence) {
    Frequence = frequence;
}

void Prescription::setNote(string note) {
    Note = note;
}

void Prescription::afficherDetails() {
    cout << "ID Prescription: " << ID_prescription << endl;
    cout << "Date Prescription: " << Date_prescription << endl;
    cout << "Nom Patient: " << Nom_patient << endl;
    cout << "Nom Medecin: " << Nom_medecin << endl;
    cout << "Medicament: " << Medicament << endl;
    cout << "Date Creation: " << Date_Creation << endl;
    cout << "Statut Prescription: " << Statut_prescription << endl;
    cout << "Durée Traitement: " << Duree_traitement << endl;
    cout << "Dosage: " << Dosage << endl;
    cout << "Fréquence: " << Frequence << endl;
    cout << "Note: " << Note << endl;
}

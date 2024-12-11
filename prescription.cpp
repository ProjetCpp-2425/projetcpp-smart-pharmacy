
#include "prescription.h"
#include <QString>
#include <iostream>
#include <string>
#include <QCoreApplication>
#include <QMessageBox>
#include <QSqlError>


using namespace std;

Prescription::Prescription(int id, QDate datePrescrip, QString nomPatient, QString nomMedecin,QString medicament,QString statutPrescrip, int dureeTraitement, QString dosage, int frequence, QString note)
{
    this->ID_prescription = id;
    this->Date_prescription = datePrescrip;
    this->Nom_patient = nomPatient;
    this->Nom_medecin = nomMedecin;
    this->Medicament = medicament;
    this->Statut_prescription = statutPrescrip;
    this->Duree_traitement = dureeTraitement;
    this->Dosage = dosage;
    this->Frequence = frequence;
    this->Note = note;
}



//static QSqlQueryModel afficher();

QSqlQueryModel * Prescription :: afficher()
{

    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("SELECT ID_PERSCRIPTION,NOM_PATIENT,NOM_MEDECIN,DATE_CREATION,STATUT_PRESCRIPTION,MEDICAMENT,DUREE_TRAITEMENT,DOSAGE,FREQUENCE,NOTE FROM PRESCRIPTION");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Patient"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Medecin"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Date"));
    model->setHeaderData(4,Qt::Horizontal,QObject::tr("Statut"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Medicament"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("Durée"));
    model->setHeaderData(7,Qt::Horizontal,QObject::tr("Dosage"));
    model->setHeaderData(8,Qt::Horizontal,QObject::tr("Frequence"));
    model->setHeaderData(9,Qt::Horizontal,QObject::tr("Note"));


        return model;
}



/* Name                                      Null?    Type
 ----------------------------------------- -------- ----------------------------
 ID_PERSCRIPTION                           NOT NULL NUMBER(10)
 DATE_CREATION                             NOT NULL DATE
 NOM_PATIENT                               NOT NULL VARCHAR2(50)
 NOM_MEDECIN                                        VARCHAR2(50)
 STATUT_PRESCRIPTION                       NOT NULL VARCHAR2(10)
 DUREE_TRAITEMENT                                   NUMBER(5)
 DOSAGE                                             VARCHAR2(20)
 FREQUENCE                                          NUMBER(5)
 NOTE                                               VARCHAR2(200)
 ID_EMPLOYEE                                        NUMBER(10)
 MEDICAMENT                                         VARCHAR2(50)



*/






bool Prescription::ajouter()
{QSqlQuery query;
    query.prepare("INSERT INTO PRESCRIPTION (ID_PERSCRIPTION, DATE_CREATION, NOM_PATIENT, NOM_MEDECIN, STATUT_PRESCRIPTION, DUREE_TRAITEMENT, DOSAGE, FREQUENCE, NOTE, MEDICAMENT) "
                  "VALUES (PRESCRIPTION_SEQ.NEXTVAL, :date_creation, :nom_patient, :nom_medecin, :statut, :duree_traitement, :dosage, :frequence, :note, :medicament)");

    query.bindValue(":id", this->getID_Prescription());
    query.bindValue(":date_creation", this->getDate_Prescription());
    query.bindValue(":nom_patient", this->getNom_Patient());
    query.bindValue(":nom_medecin", this->getNom_Medecin());
    query.bindValue(":statut", this->getStatut());
    query.bindValue(":duree_traitement", this->getDuree_traitement());
    query.bindValue(":dosage", this->getDosage());
    query.bindValue(":frequence", this->getFrequence());
    query.bindValue(":note", this->getNote());  // Ensure this is valid
    query.bindValue(":medicament", this->getMedicament());


    qDebug() << "ID_PRESCRIPTION:" << this->getID_Prescription();
    qDebug() << "DATE_CREATION:" << this->getDate_Prescription();
    qDebug() << "NOM_PATIENT:" << this->getNom_Patient();
    qDebug() << "NOM_MEDECIN:" << this->getNom_Medecin();
    qDebug() << "STATUT:" << this->getStatut();
    qDebug() << "DUREE_TRAITEMENT:" << this->getDuree_traitement();
    qDebug() << "DOSAGE:" << this->getDosage();
    qDebug() << "FREQUENCE:" << this->getFrequence();
    qDebug() << "NOTE:" << this->getNote();
    qDebug() << "MEDICAMENT:" << this->getMedicament();


    if (!query.exec()) {
        qDebug() << "SQL error in ajouter:" << query.lastError().text();
        return false;
    }
    return true;
}











//static bool supprimer(int id);
bool Prescription :: supprimer(int id)
{


    qDebug()<< "on suppression ";
    QSqlQuery query ;;
    query.prepare("DELETE FROM PRESCRIPTION WHERE ID_PERSCRIPTION = :id");
    query.bindValue(":id",id);
    qDebug()<< "DELETE FROM PRESCRIPTION WHERE ID_PRESCRIPTION ="<<id;
    return query.exec();
}

//static bool modifier ();
bool Prescription:: modifier ( ){
    QSqlQuery query;

    if (query.exec())
    {
        qDebug()<<"la valeure a bien ete modifier\n";
        return true;
    }
    qDebug ()<< "Une erreur c'est produite\n";
    return false;
}



QSqlQueryModel* Prescription::trier_nom() {
    QSqlQueryModel* model = new QSqlQueryModel();

    model->setQuery("SELECT * FROM PRESCRIPTION ORDER BY NOM_PATIENT ASC");

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Date"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Patient"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Medecin"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Statut"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Durée"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Dosage"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Frequence"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Note"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("Medicament"));

    return model;
}

bool Prescription::renew(QString nom_patient, QString nom_medecin, QString medicament, QString dosage, int frequence, int duree_traitement) {
    QSqlQuery query;
    query.prepare(R"(
        UPDATE PRESCRIPTION
        SET STATUT_PRESCRIPTION = 'Active', DATE_CREATION = :date_creation
        WHERE NOM_PATIENT = :nom_patient
          AND NOM_MEDECIN = :nom_medecin
          AND MEDICAMENT = :medicament
          AND DOSAGE = :dosage
          AND FREQUENCE = :frequence
          AND DUREE_TRAITEMENT = :duree_traitement
    )");

    query.bindValue(":date_creation", QDate::currentDate());
    query.bindValue(":nom_patient", nom_patient);
    query.bindValue(":nom_medecin", nom_medecin);
    query.bindValue(":medicament", medicament);
    query.bindValue(":dosage", dosage);
    query.bindValue(":frequence", frequence);
    query.bindValue(":duree_traitement", duree_traitement);

    if (!query.exec()) {
        qDebug() << "SQL error in renew:" << query.lastError().text();
        return false;
    }
    return query.numRowsAffected() > 0; // Check if any row was updated
}



bool Prescription::exists(QString nom_patient, QString nom_medecin, QString medicament, QString dosage, int frequence, int duree_traitement) {
    QSqlQuery query;
    query.prepare(R"(
        SELECT ID_PERSCRIPTION FROM PRESCRIPTION
        WHERE NOM_PATIENT = :nom_patient
          AND NOM_MEDECIN = :nom_medecin
          AND MEDICAMENT = :medicament
          AND DOSAGE = :dosage
          AND FREQUENCE = :frequence
          AND DUREE_TRAITEMENT = :duree_traitement
    )");
    query.bindValue(":nom_patient", nom_patient);
    query.bindValue(":nom_medecin", nom_medecin);
    query.bindValue(":medicament", medicament);
    query.bindValue(":dosage", dosage);
    query.bindValue(":frequence", frequence);
    query.bindValue(":duree_traitement", duree_traitement);

    if (!query.exec()) {
        qDebug() << "SQL error in exists:" << query.lastError().text();
        return false;
    }
    return query.next(); // Returns true if a matching row exists
}


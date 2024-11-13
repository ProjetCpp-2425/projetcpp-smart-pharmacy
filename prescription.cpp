#include "Presentation.h"
#include "connection.h"
#include<QString>
#include <iostream>
#include <string>
#include <QCoreApplication>
#include <QMessageBox>

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
    model->setQuery("SELECT * FROM PRESCRIPTION");
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















//static bool ajouter (Prescription pres);
bool Prescription::ajouter(Prescription pres)
{
    QSqlQuery countQuery;

        QSqlQuery query;
        query.prepare("INSERT INTO prescription (ID_PERSCRIPTION, DATE_CREATION, NOM_PATIENT, NOM_MEDECIN, STATUT_PRESCRIPTION, DUREE_TRAITEMENT, DOSAGE, FREQUENCE, NOTE, MEDICAMENT) VALUES (:id, TO_DATE(:date, 'YYYY-MM-DD'), :nom, :medecin, :statut, :duree, :dosage, :frequence, :note, :medicament)");

        QString id =QString ::number (pres.ID_prescription);
        query.bindValue(":id",id);

        qDebug() << pres.ID_prescription<<"\n" << pres.Date_prescription;
        query.bindValue(":date", pres.Date_prescription.toString("yyyy-MM-dd"));
        query.bindValue(":nom", pres.Nom_patient);
        query.bindValue(":medecin", pres.Nom_medecin);
        query.bindValue(":statut", pres.Statut_prescription);
        query.bindValue(":duree", pres.Duree_traitement);
        query.bindValue(":dosage", pres.Dosage);
        query.bindValue(":frequence", pres.Frequence);
        query.bindValue(":note", pres.Note);
        query.bindValue(":medicament", pres.Medicament);

        qDebug() << "Executing query:" << query.executedQuery();

        if (!query.exec()) {
            qDebug() << "Error adding prescription:" << query.lastError().text();
            return false;
        }

        qDebug() << "Prescription added successfully";
        return true;
}


bool Prescription :: genereText()
{

    QString filePath ="C:/Users/binda77a/Desktop/Prescription/prescriptions.txt";


       QSqlQuery query;
       query.prepare("SELECT * FROM PRESCRIPTION ORDER BY NOM_PATIENT");


       if (!query.exec()) {
           qDebug() << "Error fetching data from database:" << query.lastError().text();
           return false;
       }

       // Open the file for writing
       QFile file(filePath);
       if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
           qDebug() << "Error opening file for writing:" << file.errorString();
           return false;
       }

       QTextStream out(&file);

       // Write a header to the file
       out << "ID_PRESCRIPTION\tDATE_CREATION\tNOM_PATIENT\tNOM_MEDECIN\tSTATUT_PRESCRIPTION\t"
              "DUREE_TRAITEMENT\tDOSAGE\tFREQUENCE\tNOTE\tMEDICAMENT\n";

       // Loop through the query results and write each record to the file
       while (query.next()) {
           out << query.value("ID_PERSCRIPTION").toString() << "\t"
               << query.value("DATE_CREATION").toDate().toString("yyyy-MM-dd") << "\t"
               << query.value("NOM_PATIENT").toString() << "\t"
               << query.value("NOM_MEDECIN").toString() << "\t"
               << query.value("STATUT_PRESCRIPTION").toString() << "\t"
               << query.value("DUREE_TRAITEMENT").toString() << "\t"
               << query.value("DOSAGE").toString() << "\t"
               << query.value("FREQUENCE").toString() << "\t"
               << query.value("NOTE").toString() << "\t"
               << query.value("MEDICAMENT").toString() << "\n";
       }


       file.close();
       qDebug() << "Data successfully written to" << filePath;

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






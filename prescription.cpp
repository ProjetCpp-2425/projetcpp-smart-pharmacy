#include "Prescription.h"
#include "connection.h"

#include <iostream>
#include <string>

using namespace std;

Prescription::Prescription(int id, QDate datePrescrip, QString nomPatient, QString nomMedecin,QString medicament, QDate dateCreation, QString statutPrescrip, QString dureeTraitement, QString dosage, QString frequence, QString note)
{
    this->ID_prescription = id;
    this->Date_prescription = datePrescrip;
    this->Nom_patient = nomPatient;
    this->Nom_medecin = nomMedecin;
    this->Medicament = medicament;
    this->Date_Creation = dateCreation;
    this->Statut_prescription = statutPrescrip;
    this->Duree_traitement = dureeTraitement;
    this->Dosage = dosage;
    this->Frequence = frequence;
    this->Note = note;
}

QSqlQueryModel* Prescription::affiche( int ID) {



    QSqlQuery query;

    QSqlQueryModel *model = new QSqlQueryModel();
    query.prepare("SELECT * FROM PRESCRIPTION WHERE ID_PRESCRIPTION = :id");
    query.bindValue(":id ",ID);

    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("NOM patient"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("NOM Médecin"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Médicament"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Date de Visite"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Statut"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Durée Traitement"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Dosage"));
    model->setHeaderData(8, Qt::Horizontal, QObject::tr("Fréquence"));
    model->setHeaderData(9, Qt::Horizontal, QObject::tr("Note"));
    model->setHeaderData(10, Qt::Horizontal, QObject::tr("Date de Création"));


    if (model->rowCount() == 0) {
        qDebug() << "No prescription found with ID:" << ID;
    } else {
        qDebug() << model->rowCount() << "prescription(s) found for ID:" << ID;
    }

    return model;
}

bool Prescription :: supprimer(int id)
{


    qDebug()<< "on suppression ";
    QSqlQuery query ;
    QString res=QString :: number(id);
    query.prepare("DELETE FROM PRESCRIPTION WHERE ID = :id");
    query.bindValue(":id",res);

    qDebug()<< "DELETE FROM PRESCRIPTION WHERE ID ="<<res;
    return query.exec();
}



 bool Prescription::modifier ( int ID,QString champ,QString nouvelle_valeure){
    QSqlQuery query;
    query.prepare("UPDATE PRESCRIPTION SET :champ = : nouvelle_valeure WHERE ID_PRESCRIPTION = : ID");
    query.bindValue(":champ",champ);
    query.bindValue(":nouvelle_valeure",nouvelle_valeure);
    query.bindValue(":ID",ID);
    if (query.exec())
    {
        qDebug()<<"la valeure a bien ete modifier\n";
        return true;
    }
    qDebug ()<< "Une erreur c'est produite\n";
    return false;
}



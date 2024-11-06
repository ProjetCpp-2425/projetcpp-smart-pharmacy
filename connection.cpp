#include "connection.h"
#include "Prescription.h"
#include <QSqlQuery>
#include <QSqlError>

Connection::Connection()
{
    db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("source2a32");//inserer le nom de la source de données
    db.setUserName("aouadi");//inserer nom de l'utilisateur
    db.setPassword("0000");//inserer mot de passe de cet utilisateur

}

bool Connection::createconnect()
{
    bool test =false;
    if (db.open())
    {
        test=true;
        qDebug()<<"Connexion reussie a la base de donne.";
    }
    else{
        qDebug()<<"Errueur de connexion"<<db.lastError().text();
    }
    return test;
}

void Connection::closeConnection()
    {
        if (db.isOpen())
        {
            db.close();
            qDebug()<<"Connexion fermee";
        }
        else
        {
            qDebug()<< "La connexion est deja fermee ou na pas ete ouverte ";
        }
    }



bool Connection :: insert_prescription(Prescription &prescription){
        QSqlQuery query;
        query.prepare("INSERT INTO PRESCRIPTION (ID_PRESCRIPTION, DATE_PRESCRIPTION, NOM_PATIENT, NOM_MEDECIN, "
                      "MEDICAMENT, DATE_CREATION, STATUS_PRESCRIPTION, DUREE_TRAITEMENT, DOSAGE, FREQUENCE, NOTE) "
                      "VALUES (:id, :datePrescrip, :nomPatient, :nomMedecin, :medicament, "
                      ":dateCreation, :statut, :dureeTraitement, :dosage, :frequence, :note)");


        if (prescription.getID_Prescription()==0){
            qDebug () << "is is empty ";
            return false;
        }
        else
        {
            qDebug ()<< "Id is not empty\n";
        }
        query.bindValue(":id", prescription.getID_Prescription());
        query.bindValue(":datePrescrip", prescription.getDate_Prescription());
        query.bindValue(":nomPatient", prescription.getNom_Patient());
        query.bindValue(":nomMedecin", prescription.getNom_Medecin());
        query.bindValue(":medicament", prescription.getMedicament());
        query.bindValue(":dateCreation", prescription.getDate_Creation());
        query.bindValue(":statut", prescription.getStatut());
        query.bindValue(":dureeTraitement", prescription.getDuree_traitement());
        query.bindValue(":dosage", prescription.getDosage());
        query.bindValue(":frequence", prescription.getFrequence());
        query.bindValue(":note", prescription.getNote());


        if (!query.exec()) {
            qDebug() << "Erreur insertion echoue :" << query.lastError().text();
            return false;
        }
        return true;
}
/*
Prescription Connection::readPrescription(int prescriptionID) {
    QSqlQuery query;
    Prescription temp;
    QString idText=prescriptionID.toString();

    query.prepare("SELECT ID_PRESCRIPTION, DATE_PRESCRIPTION, NOM_PATIENT, NOM_MEDECIN, "
                  "MEDICAMENT, DATE_CREATION, STATUS_PRESCRIPTION, DUREE_TRAITEMENT, "
                  "DOSAGE, FREQUENCE, NOTE FROM PRESCRIPTION WHERE ID_PRESCRIPTION = :id");
    query.bindValue(":id", prescriptionID);

    if (query.exec()) {
        if (query.next()) { /
            temp.setID(query.value(0).toString());
            temp.setDate_Prescription(query.value(1).toDate());
            temp.setNom_Patient(query.value(2).toString());
            temp.setNom_Medecin(query.value(3).toString());
            temp.setMedicament(query.value(4).toString());
            temp.setDate_Creation(query.value(5).toDate());
            temp.setStatut(query.value(6).toString());
            temp.setDuree_traitement(query.value(7).toString());
            temp.setDosage(query.value(8).toString());
            temp.setFrequence(query.value(9).toString());
            temp.setNote(query.value(10).toString());

        }
    } else {
        qDebug() << "Erreur lors de la lecture de la prescription :" << query.lastError().text();
    }

    return temp; // Return the populated Prescription object
}
*/

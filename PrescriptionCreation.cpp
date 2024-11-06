#include "PrescriptionCreation.h"
#include "ui_PrescriptionCreation.h"
#include "prescription.h"
#include "connection.h"
#include <QPushButton>
#include <QDebug>


PrescriptionCreation::PrescriptionCreation(QWidget *parent) : QMainWindow(parent) {
    ui.setupUi(this);

    connect(ui.Create , &QPushButton::clicked, this, &PrescriptionCreation::onSubmit);
}

void PrescriptionCreation::onSubmit() {
    Connection connexion;
    connexion.createconnect();
    if (connexion.isOpen()){
    qDebug ()<< "Conenxion ouverte ";}

    //PATIENT
    QString nom_patient = ui.Nom_Patient->toPlainText();
    //qDebug() << "Patient : " << nom_patient;

    //MEDEICIN
    QString nom_medecin =ui.Nom_medecin->toPlainText();
    //qDebug() << "medecin : " << nom_medecin;


    //MEDICAMENT
    QString medicament=ui.Medicament->toPlainText();
   // qDebug()<<"medicament : "<< medicament;


    //duree traitement
    QString duree_traitement=ui.duree_tritement->toPlainText();
   // qDebug()<< medicament;


    //dosage
    QString dosage =ui.dosage->toPlainText();
 //   qDebug()<< dosage;



    //FREQUENCE
    QString frequence =ui.frequence->toPlainText();
    //qDebug()<< frequence;

    //statut
    QString statut=ui.statut->toPlainText();
   // qDebug()<< statut;


    //note
    QString note=ui.note->toPlainText();
    qDebug()<< note;


    //ID
    QString ID_temp=ui.identifiant->toPlainText();
    //int ID =ID_temp.toInt(nullptr);
    //qDebug()<< ID;


    // Date creation de la prescription
    QDate date_creation =ui.date_creation->date();
    //qDebug ()<< "Date creation : "<< date_creation.toString();


    // Date de la visite chez le medecin
    QDate date_visite =ui.Date_visite->date();
    //qDebug ()<< "Date visite : "<< date_visite.toString();


    //    Prescription(int id, QDate datePrescrip, QString nomPatient, QString nomMedecin,
       //              QString medicament, QDate dateCreation, QString statutPrescrip,
         //            QString dureeTraitement, QString dosage, QString frequence, QString note);

    Prescription temp_pres(ID_temp.toInt(),date_creation,nom_patient,nom_medecin,
                           medicament,date_visite,statut,
                           duree_traitement,dosage,frequence,note);



    if (connexion.insert_prescription(temp_pres)){
        qDebug ()<< "Insertion reussi\n";
        this->close();
    }
    else{
        qDebug ()<< "insertion failed\n";
    }

     connexion.closeConnection();

}

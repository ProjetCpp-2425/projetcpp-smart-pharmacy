#include"mainwindow.h"
#include "ui_mainwindow.h"
#include "connection.h"
#include <QPushButton>
#include <QMessageBox>




MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {

    ui->setupUi(this);
    //affiche
    ui->tableView->setModel(Prescription::afficher());

    //boutons

     connect(ui->Ajouter, &QPushButton::clicked, this, &MainWindow::BasculerTabAjout);
     connect(ui-> Enregistrer ,&QPushButton::clicked,this, &MainWindow::on_enregistrerButton_clicked);
     connect(ui-> supprimer ,&QPushButton::clicked,this, &MainWindow::on_supprimer_clicked);
     connect(ui->chercher,&QPushButton :: clicked ,this, &MainWindow :: on_recherche_clicked);
     connect(ui->trier ,&QPushButton :: clicked ,this ,&MainWindow :: on_trier_clicked);
    connect (ui->Exporter,&QPushButton :: clicked ,this ,&MainWindow :: on_exporter_clicked);



  }

MainWindow::~MainWindow() {
    delete ui;
}
/*

void MainWindow::on_supprimerclicked(){
    qDebug()<< "on suppression \n";
    QString idText = ui->idRecherche->text();
    bool test = Prescription :: supprimer(idText.toInt());
    if (test)
    {
        QMessageBox ::  information (nullptr,QObject :: tr ("OK"),"Click canel to exit ",QMessageBox::Cancel);
    }
    else
    {
        QMessageBox ::  information (nullptr,QObject :: tr ("NOT OK"),"Click canel to exit",QMessageBox::Cancel);
    }

}


void MainWindow :: on_modifierclicked()
{
    qDebug()<<"fonction modofier\n";
    modification *modifierwindow = new modification(this);
    modifierwindow->show();
}
*/
/*    void setID(int id){this->ID_prescription=id;}
    void setDate_Prescription(QDate date_prescription){this->Date_prescription=date_prescription;}
    void setNom_Patient(QString nom){this->Nom_patient=nom;}
    void setNom_Medecin (QString nom){this->Nom_medecin= nom;}
    void setMedicament (QString medicament){this->Medicament=medicament;}
    void setStatut(QString statut){this->Statut_prescription=statut;}
    void setDuree_traitement(QString duree){this->Duree_traitement=duree;}
    void setDosage(QString dosage){this->Dosage=dosage;}
    void setFrequence (QString frequence){this->Frequence=frequence;}
    void setNote(QString note){this->Note=note;}*/
void MainWindow::enregistrer (Prescription * temp)
{

        bool isValid = true;

        temp->setID(Connection::get_size());

        QString dosage = this->ui->dosage->text();
        if (dosage.isEmpty()) {
            isValid = false;
            QMessageBox::warning(this, "Erreur de saisie", "Le dosage ne peut pas être vide.");
        } else {
            temp->setDosage(dosage);
        }

        bool dureeOk;
        int duree = this->ui->duree->text().toInt(&dureeOk);
        if (!dureeOk) {
            isValid = false;
            QMessageBox::warning(this, "Erreur de saisie", "La durée du traitement doit être un entier.");
        } else {
            temp->setDuree_traitement(duree);
        }

        bool frequenceOk;
        int frequence = this->ui->frequence->text().toInt(&frequenceOk);
        if (!frequenceOk) {
            isValid = false;
            QMessageBox::warning(this, "Erreur de saisie", "La fréquence doit être un entier.");
        } else {
            temp->setFrequence(frequence);
        }

        QString nomPatient = this->ui->nom->text();
        if (nomPatient.isEmpty()) {
            isValid = false;
            QMessageBox::warning(this, "Erreur de saisie", "Le nom du patient ne peut pas être vide.");
        } else {
            temp->setNom_Patient(nomPatient);
        }

        QString medicament = this->ui->medicament->text();
        if (medicament.isEmpty()) {
            isValid = false;
            QMessageBox::warning(this, "Erreur de saisie", "Le médicament ne peut pas être vide.");
        } else {
            temp->setMedicament(medicament);
        }

        QString nomMedecin = this->ui->nom_medecin->text();
        if (nomMedecin.isEmpty()) {
            isValid = false;
            QMessageBox::warning(this, "Erreur de saisie", "Le nom du médecin ne peut pas être vide.");
        } else {
            temp->setNom_Medecin(nomMedecin);
        }

        QString note = this->ui->note->text();
        temp->setNote(note);

        QString statut = this->ui->statut->text();
        temp->setStatut(statut);

        temp->setDate_Prescription(QDate::currentDate());

        if (isValid) {
            qDebug() << "Prescription enregistrée avec succès.";
        }
    }




void MainWindow::on_enregistrerButton_clicked()
{

    Prescription * temp=new Prescription();
    enregistrer(temp);

    if ( Prescription::ajouter(*temp))
    {
               QMessageBox::information(this, "PharmaFlow", "La prescriptiona  ete ajoutée  avec succes");
    }
    else
    {
               QMessageBox::information(this, "PharmaFlow", "Une erreure c'est prosuite lors de l'jout de cette prescription ");
    }



    this->ui->nom->clear();
    this->ui->nom_medecin->clear();
    this->ui->statut->clear();
    this->ui->duree->clear();
    this->ui->dosage->clear();
    this->ui->frequence->clear();
    this->ui->note->clear();
    this->ui->medicament->clear();
    ui->MainTab->setCurrentIndex(0);
    ui->tableView->setModel(Prescription::afficher());
    return ;


}


void MainWindow:: on_supprimer_clicked()
{
    int id =this->ui->idRecherche->text().toInt();
    if (Prescription :: supprimer(id)){
               QMessageBox::information(this, "PharmaFlow", "La prescription a ete supprimée avec succes");
    }
    else
    {
               QMessageBox::information(this, "PharmaFlow", "Une erreure c'est produite lors de la suppression de cette prescription");
    }
    ui->tableView->setModel(Prescription::afficher());
    return ;
}


void MainWindow::BasculerTabAjout()
{
    int IndiceTabAjout = 1;
        ui->MainTab->setCurrentIndex(IndiceTabAjout);
}


void MainWindow :: on_recherche_clicked()
{
    int id = this->ui->idRecherche->text().toInt();
    ui->MainTab->setCurrentIndex(2);

        QString searchfield = ui->searchfield->currentText();
        QString searchValue = ui->idRecherche->text(); // Valeur de recherche

        // Vérifier si la valeur de recherche est vide
        if (searchValue.isEmpty())
        {
            QMessageBox::warning(this, "Erreur"," Entrer une valeur");
            return;
        }

        QSqlQuery query;


        // Recherche par code

        if (searchfield == "id")
        {
            qDebug()<<"recherche scodef";
            query.prepare("SELECT * FROM PRESCRIPTION WHERE ID_PERSCRIPTION = :id");
            query.bindValue(":id", searchValue.toInt());
        }

        // Recherche par raison sociale et prepare de la req
        else if (searchfield == "Nom")
        {
            qDebug()<<"recherche res";
            query.prepare("SELECT * FROM PRESCRIPTION WHERE NOM_PATIENT = :nom");
            query.bindValue(":nom", searchValue);
        }
        else
        {
            query.prepare("SELECT * FROM fournisseurs WHERE nomf = :nomf");
            query.bindValue(":nomf", searchValue);
        }

        QSqlQueryModel *model = new QSqlQueryModel;
        if (query.exec())
        {
                model->setQuery(query);
        }

        else
        {
                QMessageBox::warning(this, "Erreur", "Échec de l'envoi de la requête.");
                return;
        }

        // Aucune ligne dans la table
        if (model->rowCount() == 0)
        {
                QMessageBox::information(this, "Résultat", "Aucun fournisseur trouvé.");
        }
        else
        {
                ui->tableView_2->setModel(model);
                ui->tableView->resizeColumnsToContents();
        }
     }


void MainWindow :: on_trier_clicked ()
{

    this->ui->tableView->setModel(Prescription :: trier_nom());

}



void MainWindow :: on_exporter_clicked ()
{
    if (Prescription ::genereText())
    {
               QMessageBox::information(this, "PharmaFlow", "Le ficher a ete creer avec succes");
    }
    else
    {
               QMessageBox::information(this, "Pharmaflow", "Une erreure c'est produit lors de la creation du ficher text ");
    }
}


#include "employeeui.h"
#include "ui_employeeui.h"
#include "statistique.h"

#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QFileInfo>
#include <QDebug>

#include <QFile>
#include <QPixmap>
#include <QPainter>
#include <QPrinter>
#include "login.h"
#include "sms.h"

employeeUI::employeeUI(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::employeeUI)
{
    ui->setupUi(this);


}

employeeUI::~employeeUI()
{
    delete ui;
}

void employeeUI::showEvent(QShowEvent *event)
{
    QDialog::showEvent(event);
    ui->tableView->setModel(e.afficher());
}

void employeeUI::on_ajouter_clicked()
{
    try {
        QString nom = ui->nom->text();
        QDate date_n = ui->date_n->date();
        QString adresse = ui->adresse->text();
        int numtel = ui->numtel->text().toInt();
        QString email = ui->email->text();
        int cin = ui->cin->text().toInt();
        QDate date_e = ui->date_e->date();
        QTime horaire_d = ui->h_d->time();
        QTime horaire_f = ui->h_f->time();
        int conge = ui->conge->text().toInt();
        int absence = ui->absennce->text().toInt();
        float salaire = ui->salaire->text().toFloat();
        float prime = ui->prime->text().toFloat();
        QString mdp = ui->mdp->text();

        // Création d'un objet employé
        employee e(nom, date_n, adresse, numtel, email, cin, date_e, horaire_d, horaire_f, conge, absence, salaire, prime, mdp);

        // Ajout de l'employé
        bool test = e.Ajouter();
        if (test) {
            // Envoi du SMS après ajout réussi
            ui->tableView->setModel(e.afficher());

        } else {
            throw std::runtime_error("Échec de l'ajout de l'employé dans la base de données.");
        }
    } catch (const std::exception &ex) {
        QMessageBox::critical(this, "Erreur critique", ex.what());
    } catch (...) {
        QMessageBox::critical(this, "Erreur inconnue", "Une erreur inattendue s'est produite.");
    }
}



void employeeUI::on_modifier_clicked()
{
    QString nom = ui->nom->text();
    QDate date_n = ui->date_n->date();
    QString adresse = ui->adresse->text();
    int numtel = ui->numtel->text().toInt();
    QString email = ui->email->text();
    int cin = ui->cin->text().toInt();
    QDate date_e = ui->date_e->date();
    QTime horaire_d = ui->h_d->time();
    QTime horaire_f = ui->h_f->time();
    int conge = ui->conge->text().toInt();
    int absence = ui->absennce->text().toInt();
    float salaire = ui->salaire->text().toFloat();
    float prime = ui->prime->text().toFloat();
    QString mdp = ui->mdp->text();

    employee e(nom, date_n, adresse, numtel, email, cin, date_e, horaire_d, horaire_f, conge, absence, salaire, prime, mdp);

    bool test;
    test = e.modifier();
    if(test==true){
        ui->tableView->setModel(e.afficher());
    }
    else
    {
        QMessageBox::critical(nullptr, QObject::tr("Error !!"),
                              QObject::tr(""
                                          "Can not edit employee."), QMessageBox::Cancel);
    }

}


void employeeUI::on_del_clicked()
{
    employee E1;
    E1.setCin(ui->del_line->text().toInt());
    E1.Supprimer(E1.getCin());
    ui->tableView->setModel(e.afficher());
}


void employeeUI::on_pushButton_rech_clicked()
{
    QString val = ui->lineEdit_rech->text();
    QString option = ui->comboBox_rech->currentText();
   ui->label_17->clear();
    // Vérification de la saisie si l'option sélectionnée est "Cin"
    if (option == "Cin") {
        QRegularExpression regex("^[0-9]+$"); // Expression régulière : uniquement des chiffres
        if (!regex.match(val).hasMatch()) {
            ui->label_17->setText("Veuillez entrer un CIN valide (uniquement des chiffres).");
            ui->tableView->setModel(nullptr); // Vider le tableau
            return; // Arrêter l'exécution
        }
    }

    // Pointeur pour stocker le modèle
    QAbstractItemModel *model = nullptr;

    if ((val != "") && (option == "Cin")) {
        model = e.afficher_cin(val);
    } else if ((val != "") && (option == "Nom")) {
        model = e.afficher_nom(val);
    } else if ((val != "") && (option == "Salaire")) {
        model = e.afficher_salaire(val);
    }

    if (model && model->rowCount() > 0) {
        // Si le modèle contient des données, les afficher dans le QTableView
        ui->tableView->setModel(model);
        ui->label_error->clear(); // Effacer le message d'erreur s'il existe
    } else {
        // Si le modèle est vide, afficher un message d'erreur dans le QLabel
        ui->label_error->setText("Aucun employé trouvé pour cette recherche.");
        ui->tableView->setModel(nullptr); // Supprimer les données du tableau
    }
}

void employeeUI::on_comboBox_tri_currentIndexChanged(int index)
{
    QString choix=ui->comboBox_tri->currentText();
    ui->tableView->setModel(e.afficher_choix(choix));
}


void employeeUI::on_pushButton_stat_clicked()
{
     statistique *S = new statistique(this);
    S->show();
}


void employeeUI::on_pushButton_pdf_clicked()
{
    // Récupérer le CIN depuis l'interface utilisateur
    int cin = ui->lineEdit_cin->text().toInt();
    employee *emp;
    emp = e.reademploye(cin);

    if (!emp) {
        QMessageBox::warning(this, "Erreur", "Employé introuvable !");
        return;
    }

    // Extraire les informations de l'employé
    QString cin_string = QString::number(emp->getCin());
    QString nom_string = emp->getNom();
    QString date_n_string = emp->getDateN().toString("dd-MM-yyyy");
    QString date_e_string = emp->getDateE().toString("dd-MM-yyyy");
    QString numtel_string = QString::number(emp->getNumTel());
    QString adresse_string = emp->getAdresse();
    QString email_string = emp->getEmail();
    QString conge_string = QString::number(emp->getConge());
    QString absences_string = QString::number(emp->getAbsences());
    QString salaire_string = QString::number(emp->getSalaire(), 'f', 2);
    QString prime_string = QString::number(emp->getPrime(), 'f', 2);

    // Chemin du fichier PDF
    QString pdfFilePath = "C:/Users/molka/OneDrive/Bureau/Molkaaa1/Nouveau dossier (3)" + nom_string + "_" + cin_string + ".pdf";

    QPrinter printer;
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(pdfFilePath);

    QPainter painter;
    if (!painter.begin(&printer)) {
        QMessageBox::critical(this, "Erreur", "Impossible de créer le fichier PDF !");
        return;
    }

    // En-tête du PDF
    painter.setFont(QFont("Bahnschrift Light", 30, QFont::Bold));
    painter.setPen(Qt::blue);
    painter.drawText(100, 100, "Employee Report");
    painter.setFont(QFont("Bahnschrift Light", 16));
    painter.setPen(Qt::darkGray);
    painter.drawText(100, 150, "Generated on: " + QDate::currentDate().toString("dd-MM-yyyy"));

    // Ligne de séparation
    painter.setPen(Qt::black);
    painter.drawLine(50, 200, 550, 200);

    // Informations générales
    painter.setFont(QFont("Bahnschrift Light", 14));
    int yPosition = 250;
    int lineSpacing = 40;

    painter.drawText(50, yPosition, "CIN: " + cin_string);
    yPosition += lineSpacing;
    painter.drawText(50, yPosition, "Name: " + nom_string);
    yPosition += lineSpacing;
    painter.drawText(50, yPosition, "Date of Birth: " + date_n_string);
    yPosition += lineSpacing;
    painter.drawText(50, yPosition, "Employment Date: " + date_e_string);
    yPosition += lineSpacing;
    painter.drawText(50, yPosition, "Phone Number: " + numtel_string);
    yPosition += lineSpacing;
    painter.drawText(50, yPosition, "Address: " + adresse_string);
    yPosition += lineSpacing;
    painter.drawText(50, yPosition, "Email: " + email_string);

    // Ligne de séparation
    yPosition += 30;
    painter.drawLine(50, yPosition, 550, yPosition);
    yPosition += 30;

    // Informations professionnelles
    painter.drawText(50, yPosition, "Days Off: " + conge_string);
    yPosition += lineSpacing;
    painter.drawText(50, yPosition, "Absences: " + absences_string);
    yPosition += lineSpacing;
    painter.drawText(50, yPosition, "Salary: " + salaire_string + " TND");
    yPosition += lineSpacing;
    painter.drawText(50, yPosition, "Bonus: " + prime_string + " TND");

    // Footer
    yPosition += 60;
    painter.setPen(Qt::darkGray);
    painter.setFont(QFont("Bahnschrift Light", 12));
    painter.drawText(50, yPosition, "This document is generated automatically. For internal use only.");

    // Terminer et enregistrer le PDF
    painter.end();

    // Message de confirmation
    QMessageBox::information(this, "Succès", "Le fichier PDF a été généré avec succès dans le chemin suivant : \n" + pdfFilePath);
}


void employeeUI::on_pushButton_clicked()
{
    ui->label_error->clear();
    ui->label_17->clear();
    ui->tableView->setModel(e.afficher());

}


void employeeUI::on_tableView_clicked(const QModelIndex &index)
{
    int row = index.row();
    QAbstractItemModel *model = ui->tableView->model();

    ui->nom->setText(model->index(row, 0).data().toString());
    ui->date_n->setDate(QDate::fromString(model->index(row, 1).data().toString(), "dd-MM-yyyy"));
    ui->adresse->setText(model->index(row, 2).data().toString());
    ui->numtel->setText(model->index(row, 3).data().toString());
    ui->email->setText(model->index(row, 4).data().toString());
    ui->cin->setText(model->index(row, 5).data().toString());
    ui->date_e->setDate(QDate::fromString(model->index(row, 6).data().toString(), "dd-MM-yyyy"));
    ui->h_d->setTime(QTime::fromString(model->index(row, 7).data().toString(), "HH:mm"));
    ui->h_f->setTime(QTime::fromString(model->index(row, 8).data().toString(), "HH:mm"));
    ui->conge->setText(model->index(row, 9).data().toString());
    ui->absennce->setText(model->index(row, 10).data().toString());
    ui->salaire->setText(model->index(row, 11).data().toString());
    ui->prime->setText(model->index(row, 12).data().toString());
    ui->mdp->setText(model->index(row, 13).data().toString());
}




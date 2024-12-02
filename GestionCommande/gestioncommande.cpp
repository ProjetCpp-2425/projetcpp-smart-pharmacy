#include "gestioncommande.h"
#include "ui_gestioncommande.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>

#include <QSqlQuery>

GestionCommande::GestionCommande(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::GestionCommande)
{
    ui->setupUi(this);

    ui->Error_adresse->clear();
    ui->errorDate->clear();
    ui->Error_remarque->clear();
    ui->Error_produit->clear();
    ui->Error_fournisseur->clear();

    ui->Error_adresse_2->clear();
    ui->errorDate_2->clear();
    ui->Error_remarque_2->clear();
    ui->Error_produit_2->clear();
    ui->Error_fournisseur_2->clear();

    ui->tableView_commande->setModel(this->CommandeTMP.afficher());
    ui->tableView_commande->resizeColumnsToContents();

    connect(ui->tableView_commande, &QTableView::clicked, this, &GestionCommande::onTableViewClicked);



}

GestionCommande::~GestionCommande()
{
    delete ui;
}


int getProduitId(const QString& produitName) {
    QSqlQuery query;
    query.prepare("SELECT ID_P FROM PRODUITS WHERE nom_p = :produitName");

    query.bindValue(":produitName", produitName);

    if (query.exec() && query.next()) {
        return query.value(0).toInt();
    } else {
        QMessageBox::critical(nullptr, "Error", "Produit ID not found for " + produitName);
        return -1;
    }
}

int getFournisseurId(const QString& fournisseurName) {
    QSqlQuery query;
    query.prepare("SELECT Code FROM MARIEM.FOURNISSEURS WHERE Nom_fr = :fournisseurName");
    query.bindValue(":fournisseurName", fournisseurName);

    if (query.exec() && query.next()) {
        return query.value(0).toInt();
    } else {
        QMessageBox::critical(nullptr, "Error", "Fournisseur ID not found for " + fournisseurName);
        return -1;
    }
}


void GestionCommande::on_pushButton_recherche_produit_clicked()
{

        ui->comboBox_produit->clear();


        QSqlDatabase db = QSqlDatabase::database();
        if (!db.isOpen()) {
            QMessageBox::critical(this, "Database Error", "Database connection is not open");
            return;
        }


        QSqlQuery query;
        query.prepare("SELECT nom_p FROM PRODUITS");


        if (query.exec() == false) {
            QMessageBox::critical(this, "Query Error", query.lastError().text());
            return;
        }


        while (query.next()) {
            QString productName = query.value(0).toString();
            ui->comboBox_produit->addItem(productName);
        }


        if (ui->comboBox_produit->count() == 0) {
            QMessageBox::information(this, "No Products", "No products found in the database.");
        }
}

void GestionCommande::on_pushButton_recherche_fourni_clicked()
{

    ui->comboBox_Fournisseur->clear();


    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        QMessageBox::critical(this, "Database Error", "Database connection is not open");
        return;
    }


    QSqlQuery queryFournisseur;
    queryFournisseur.prepare("SELECT nom_fr FROM FOURNISSEURS");

    if (!queryFournisseur.exec()) {
        QMessageBox::critical(this, "Query Error", queryFournisseur.lastError().text());
        return;
    }


    while (queryFournisseur.next()) {
        QString fournisseurName = queryFournisseur.value(0).toString();
        ui->comboBox_Fournisseur->addItem(fournisseurName);
    }


    if (ui->comboBox_Fournisseur->count() == 0) {
        QMessageBox::information(this, "No Fournisseurs", "No fournisseurs found in the database.");
    }

}

void GestionCommande::on_pushButton_clicked()
{

        ui->Error_adresse->clear();
        ui->errorDate->clear();
        ui->Error_remarque->clear();
        ui->Error_produit->clear();
        ui->Error_fournisseur->clear();


        QString adresse = ui->lineEdit_adresse->text();
        QDateTime dateCommande = ui->dateTimeEdit->dateTime();
        QString remarque = ui->lineEdit_remarque->text();
        QString produitName = ui->comboBox_produit->currentText();
        QString fournisseurName = ui->comboBox_Fournisseur->currentText();


        bool isValid = true;

        if (adresse.isEmpty()) {
            ui->Error_adresse->setText("Adresse cannot be empty.");
            isValid = false;
        }
        if (dateCommande < QDateTime::currentDateTime()) {
            ui->errorDate->setText("Date must be in the future.");
            isValid = false;
        }
        if (remarque.isEmpty()) {
            ui->Error_remarque->setText("Remarque cannot be empty.");
            isValid = false;
        }
        if (produitName.isEmpty()) {
            ui->Error_produit->setText("Produit cannot be empty.");
            isValid = false;
        }
        if (fournisseurName.isEmpty()) {
            ui->Error_fournisseur->setText("Fournisseur cannot be empty.");
            isValid = false;
        }


        if (isValid == false) {
            QMessageBox::critical(this, "Validation Error", "Please fix the errors and try again.");
            return;
        }




        int produitId = getProduitId(produitName);
        int fournisseurId = getFournisseurId(fournisseurName);


        if (produitId == -1 || fournisseurId == -1) {
            QMessageBox::critical(this, "Insert Error", "Invalid foreign key references.");
            return;
        }


        QSqlDatabase db = QSqlDatabase::database();
        if (!db.isOpen()) {
            QMessageBox::critical(this, "Database Error", "Database connection is not open");
            return;
        }


        QSqlQuery query;
        query.prepare(R"(
            INSERT INTO COMMANDES
            ("ADRESSE", "DATE_COMMANDE", "STATUS_COMMANDE", "REMARQUE", "CODEF", "CIN", "PRODUIT")
            VALUES (:adresse, TO_DATE(:date_commande, 'YYYY-MM-DD HH24:MI:SS'), :status_commande, :remarque, :codef, :cin, :produit)
        )");


        query.bindValue(":adresse", adresse);
        query.bindValue(":date_commande", dateCommande.toString("yyyy-MM-dd HH:mm:ss"));
        query.bindValue(":status_commande", "Pending");
        query.bindValue(":remarque", remarque);
        query.bindValue(":codef", fournisseurId);
        query.bindValue(":cin", 14525546);
        query.bindValue(":produit", produitId);


        if (query.exec() == false) {
            QMessageBox::critical(this, "Insert Error", query.lastError().text());
        } else {
            QMessageBox::information(this, "Success", "Commande inserted successfully!");
            ui->tableView_commande->setModel(this->CommandeTMP.afficher());
            ui->tableView_commande->resizeColumnsToContents();
        }
}

void GestionCommande::on_pushButton_10_clicked()
{

        QString code = ui->lineEdit_Supprimer->text().trimmed();


        if (code.isEmpty()) {
            QMessageBox::warning(this, "Warning", "Please enter a Code Commande to delete.");
            return;
        }  

            bool deletionSuccess = this->CommandeTMP.supprimer(code.toInt());

            if (deletionSuccess) {
                QMessageBox::information(this, "Success", "Commande deleted successfully with CodeCommande: " + code);
                ui->tableView_commande->setModel(CommandeTMP.afficher());
            } else {
                QMessageBox::critical(this, "Error", "Failed to delete Commande with Code " + code);
            }


}


void GestionCommande::onTableViewClicked(const QModelIndex &index)
{
    if (index.isValid()) {
        QAbstractItemModel *model = ui->tableView_commande->model();
        QString codeCommande = model->data(model->index(index.row(), 0), Qt::DisplayRole).toString();
        ui->lineEdit_Supprimer->setText(codeCommande);
    }
}

void GestionCommande::on_pushButton_setModifier_clicked()
{
    ui->tabWidget->setCurrentIndex(1);

    int code = ui->lineEdit_Modifier->text().toInt();

    Commande tmp = CommandeTMP.trouver(code);

    if (tmp.getCodeCommande() == 0) {
        QMessageBox::warning(this, "Error", "Commande not found.");
        return;
    }

    ui->lineEdit_codecommande->setText(QString::number(tmp.getCodeCommande()));
    ui->lineEdit_adresse_2->setText(tmp.getAdresse());
    ui->dateTimeEdit_2->setDateTime(tmp.getDateCommande());
    ui->lineEdit_remarque_2->setText(tmp.getRemarque());

    QSqlQuery queryProduit;
    queryProduit.prepare("SELECT nom_p FROM PRODUITS WHERE id_p = :produit");
    queryProduit.bindValue(":produit", tmp.getProduit());
    if (queryProduit.exec() && queryProduit.next()) {
        QString productName = queryProduit.value("nom_p").toString();

        int productIndex = ui->comboBox_produit_2->findText(productName);
        if (productIndex == -1) {
            ui->comboBox_produit_2->addItem(productName);
            productIndex = ui->comboBox_produit_2->findText(productName);
        }

        ui->comboBox_produit_2->setCurrentIndex(productIndex);
    } else {
        QMessageBox::warning(this, "Error", "Product not found.");
    }

    QSqlQuery queryFournisseur;
    queryFournisseur.prepare("SELECT nom_fr FROM FOURNISSEURS WHERE code = :codef");
    queryFournisseur.bindValue(":codef", tmp.getCodef());
    if (queryFournisseur.exec() && queryFournisseur.next()) {
        QString fournisseurName = queryFournisseur.value("nom_fr").toString();

        int fournisseurIndex = ui->comboBox_Fournisseur_2->findText(fournisseurName);
        if (fournisseurIndex == -1) {
            ui->comboBox_Fournisseur_2->addItem(fournisseurName);
            fournisseurIndex = ui->comboBox_Fournisseur_2->findText(fournisseurName);
        }

        ui->comboBox_Fournisseur_2->setCurrentIndex(fournisseurIndex);
    } else {
        QMessageBox::warning(this, "Error", "Fournisseur not found.");
    }
}


void GestionCommande::on_pushButton_recherche_fourni_2_clicked()
{
    ui->comboBox_Fournisseur_2->clear();

    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        QMessageBox::critical(this, "Database Error", "Database connection is not open");
        return;
    }

    QSqlQuery queryFournisseur;
    queryFournisseur.prepare("SELECT nom_fr FROM FOURNISSEURS");

    if (!queryFournisseur.exec()) {
        QMessageBox::critical(this, "Query Error", queryFournisseur.lastError().text());
        return;
    }

    while (queryFournisseur.next()) {
        QString fournisseurName = queryFournisseur.value(0).toString();
        ui->comboBox_Fournisseur_2->addItem(fournisseurName);
    }

    if (ui->comboBox_Fournisseur_2->count() == 0) {
        QMessageBox::information(this, "No Fournisseurs", "No fournisseurs found in the database.");
    }
}

void GestionCommande::on_pushButton_recherche_produit_2_clicked()
{
        ui->comboBox_produit_2->clear();

        QSqlDatabase db = QSqlDatabase::database();
        if (!db.isOpen()) {
            QMessageBox::critical(this, "Database Error", "Database connection is not open");
            return;
        }

        QSqlQuery query;
        query.prepare("SELECT nom_p FROM PRODUITS");

        if (!query.exec()) {
            QMessageBox::critical(this, "Query Error", query.lastError().text());
            return;
        }

        while (query.next()) {
            QString productName = query.value(0).toString();
            ui->comboBox_produit_2->addItem(productName);
        }

        if (ui->comboBox_produit_2->count() == 0) {
            QMessageBox::information(this, "No Products", "No products found in the database.");
        }
}

void GestionCommande::on_pushButton_validerModifier_clicked()
{
        ui->Error_adresse->clear();
        ui->errorDate->clear();
        ui->Error_remarque->clear();
        ui->Error_produit->clear();
        ui->Error_fournisseur->clear();

        QString adresse = ui->lineEdit_adresse_2->text();
        QDateTime dateCommande = ui->dateTimeEdit_2->dateTime();
        QString remarque = ui->lineEdit_remarque_2->text();
        QString produitName = ui->comboBox_produit_2->currentText();
        QString fournisseurName = ui->comboBox_Fournisseur_2->currentText();
        int codeCommande = ui->lineEdit_codecommande->text().toInt();

        bool isValid = true;

        if (adresse.isEmpty()) {
            ui->Error_adresse_2->setText("Adresse cannot be empty.");
            isValid = false;
        }
        if (dateCommande < QDateTime::currentDateTime()) {
            ui->errorDate_2->setText("Date must be in the future.");
            isValid = false;
        }
        if (remarque.isEmpty()) {
            ui->Error_remarque_2->setText("Remarque cannot be empty.");
            isValid = false;
        }
        if (produitName.isEmpty()) {
            ui->Error_produit_2->setText("Produit cannot be empty.");
            isValid = false;
        }
        if (fournisseurName.isEmpty()) {
            ui->Error_fournisseur_2->setText("Fournisseur cannot be empty.");
            isValid = false;
        }

        if (!isValid) {
            QMessageBox::critical(this, "Validation Error", "Please fix the errors and try again.");
            return;
        }

        int produitId = getProduitId(produitName);
        int fournisseurId = getFournisseurId(fournisseurName);


        if (produitId == -1 || fournisseurId == -1) {
            QMessageBox::critical(this, "Update Error", "Invalid foreign key references.");
            return;
        }


        QSqlDatabase db = QSqlDatabase::database();
        if (!db.isOpen()) {
            QMessageBox::critical(this, "Database Error", "Database connection is not open");
            return;
        }


        QSqlQuery query;
        query.prepare(R"(
            UPDATE COMMANDES
            SET "ADRESSE" = :adresse,
                "DATE_COMMANDE" = TO_DATE(:date_commande, 'YYYY-MM-DD HH24:MI:SS'),
                "STATUS_COMMANDE" = :status_commande,
                "REMARQUE" = :remarque,
                "CODEF" = :codef,
                "CIN" = :cin,
                "PRODUIT" = :produit
            WHERE "CODE_COMMANDE" = :code_commande
        )");

        query.bindValue(":adresse", adresse);
        query.bindValue(":date_commande", dateCommande.toString("yyyy-MM-dd HH:mm:ss"));
        query.bindValue(":status_commande", "Pending");
        query.bindValue(":remarque", remarque);
        query.bindValue(":codef", fournisseurId);
        query.bindValue(":cin", 14525546);
        query.bindValue(":produit", produitId);
        query.bindValue(":code_commande", codeCommande);
        if (query.exec()==false) {
            QMessageBox::critical(this, "Update Error", query.lastError().text());
        } else {
            QMessageBox::information(this, "Success", "Commande updated successfully!");
            ui->tableView_commande->setModel(this->CommandeTMP.afficher());
            ui->tableView_commande->resizeColumnsToContents();
        }
}

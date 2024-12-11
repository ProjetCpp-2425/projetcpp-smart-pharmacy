#include "mainwindow.h"
#include "ui_mainwindow.h"


#include "connection.h"



#include "stock.h"
#include <QSystemTrayIcon>


#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QFileDialog>
#include <QPrinter>
#include <QTextStream>
#include <QTextDocument>
#include <QSqlQuery>
#include <QChartView>
#include <QPieSeries>
#include <QPieSlice>
#include <QBarSeries>
#include <QBarSet>
//#include <QtCharts>
#include <iostream>
#include <QLineSeries>
#include <QInputDialog>

#include "prescription.h"
#include "arduino.h"
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include "qsqlerror.h"
#include <QBarSet>
#include <QChartView>
#include <QBarSeries>
#include <QSqlQuery>
#include "fournisseurs.h"
#include <QMessageBox>
#include <QString>
#include <QDebug>
#include <QWidget>
#include <QVariant>
#include <QPainter>
#include <QPageLayout>
#include <QComboBox>
#include <QtCharts/QChart>
#include <QVBoxLayout>
#include <QBarCategoryAxis>
#include <QCalendarWidget>
#include <QDate>
#include <QCheckBox>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>

#include <QtCharts/QValueAxis>
#include <QtCharts/QChartView>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QTimer>
#include "fournisseurs.h"





extern Arduino arduino;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    f(),
    ui(new Ui::MainWindow),
    model(new QSqlTableModel(this)),alertTimer(new QTimer(this)),alertActive(false)
{
    //Debut gestion Commande
    ui->setupUi(this);

    ui->stackedWidget->setCurrentWidget(ui->PageCommande);
    setActiveButtonStyle(ui->pushButton_page_Commande);

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

    ui->dateTimeEdit->setDateTime(QDateTime::currentDateTime());
    ui->dateEdit_datecommande->setDateTime(QDateTime::currentDateTime());

    ui->tableView_commande->setModel(this->CommandeTMP.afficher());
    ui->tableView_commande->resizeColumnsToContents();

    connect(ui->tableView_commande, &QTableView::clicked, this, &MainWindow::onTableViewClicked);

    arduino.is_connected = 0;

    updateComboBoxProduitEtFournisseur();
    //Fin Gestion Commande

    //Debut Gestion Fournisseur

    ui->tableView->setModel(f.afficherfour());



    //fin Gestion Fournisseur





    //prescription
    connect(ui->pushButton_page_Prescription, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentWidget(ui->PagePrescription);
        setActiveButtonStyle(ui->pushButton_page_Prescription);
    });



    ui->tableView_10->setModel(Prescription::afficher());

    //boutons

     connect(ui->Ajouter, &QPushButton::clicked, this, &MainWindow::BasculerTabAjout);
     connect(ui-> Enregistrer_4 ,&QPushButton::clicked,this, &MainWindow::on_enregistrerButton_clicked);
     connect(ui-> supprimer ,&QPushButton::clicked,this, &MainWindow::on_supprimer_clicked);
     connect(ui->chercher,&QPushButton :: clicked ,this, &MainWindow :: on_recherche_clicked);
     connect(ui->trier ,&QPushButton :: clicked ,this ,&MainWindow :: on_trier_clicked);
    connect (ui->Exporter,&QPushButton :: clicked ,this ,&MainWindow :: on_exporter_clicked);
    connect (ui->b_stat,&QPushButton :: clicked ,this, &MainWindow :: on_stat_clicked);




    //Stock
    connect(ui->pushButton_page_Stock, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentWidget(ui->PageStock);
        setActiveButtonStyle(ui->pushButton_page_Stock);
    });



    //Employees
    connect(ui->pushButton_page_Employees, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentWidget(ui->PageEmployees);
        setActiveButtonStyle(ui->pushButton_page_Employees);
    });

    //transaction
    connect(ui->pushButton_page_Transaction, &QPushButton::clicked, this, [=]() {
        ui->stackedWidget->setCurrentWidget(ui->PageTransaction);
        setActiveButtonStyle(ui->pushButton_page_Transaction);
    });




}

MainWindow::~MainWindow()
{
    delete ui;
    //arduino.close_arduino();
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


void MainWindow::on_pushButton_recherche_produit_clicked()
{

        ui->comboBox_produit->clear();

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

void MainWindow::on_pushButton_recherche_fourni_clicked()
{

    ui->comboBox_Fournisseur->clear();

    QSqlQuery queryFournisseur;
    queryFournisseur.prepare("SELECT nom_fr FROM FOURNISSEUR");

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

void MainWindow::on_pushButton_clicked()
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
        ui->Error_adresse->setText("L'adresse ne peut pas être vide.");
        isValid = false;
    }
    if (dateCommande < QDateTime::currentDateTime()) {
        ui->errorDate->setText("La date doit être dans le futur.");
        isValid = false;
    }
    if (remarque.isEmpty()) {
        ui->Error_remarque->setText("Remarque ne peut pas être vide.");
        isValid = false;
    }
    if (produitName.isEmpty()) {
        ui->Error_produit->setText("Produit ne peut pas être vide.");
        isValid = false;
    }
    if (fournisseurName.isEmpty()) {
        ui->Error_fournisseur->setText("Fournisseur ne peut pas être vide.");
        isValid = false;
    }

    if (isValid == false) {
        QMessageBox::critical(this, "Validation Erreur", "veuillez corriger les erreurs et réessayer.");
        return;
    }

    int produitId = getProduitId(produitName);
    int fournisseurId = getFournisseurId(fournisseurName);

    if (produitId == -1 || fournisseurId == -1) {
        QMessageBox::critical(this, "Insertion Erreur", "impossible de terminer l'opération (fk non valide).");
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
        QMessageBox::information(this, "Success", "Commande insérée avec succès!");
        ui->tableView_commande->setModel(this->CommandeTMP.afficher());
        ui->tableView_commande->resizeColumnsToContents();

        // Récupérer les détails de la commande pour l'historique
        QString action = "AJOUTER";
        QString actionDetail = QString("Nouvelle commande ajoutée. Adresse: %1, Date: %2, Produit: %3, Fournisseur: %4, Remarque: %5")
                                   .arg(adresse)
                                   .arg(dateCommande.toString("yyyy-MM-dd HH:mm:ss"))
                                   .arg(produitName)
                                   .arg(fournisseurName)
                                   .arg(remarque);

        int userId = 14525546; // Remplacez par l'ID utilisateur réel
        addToHistorique(userId, action, actionDetail);
    }
}


void MainWindow::on_pushButton_10_clicked()
{
    QString code = ui->lineEdit_Supprimer->text().trimmed();

    if (code.isEmpty()) {
        QMessageBox::warning(this, "Attention", "Veuillez saisir un code de commande pour supprimer.");
        return;
    }

    bool deletionSuccess = this->CommandeTMP.supprimer(code.toInt());

    if (deletionSuccess) {
        QMessageBox::information(this, "Succes", "Commande supprimée avec succès avec CodeCommande: " + code);

        ui->tableView_commande->setModel(CommandeTMP.afficher());
        ui->tableView_commande->resizeColumnsToContents();

        int userId = 14525546; // Replace with the actual user ID
        QString action = "SUPPRIMER";
        QString actionDetail = QString("Suppression de la commande avec CodeCommande: %1").arg(code);

        addToHistorique(userId, action, actionDetail);
    } else {
        QMessageBox::critical(this, "Erreur", "Échec de la suppression de la commande de code " + code);
    }
}



void MainWindow::onTableViewClicked(const QModelIndex &index)
{
    if (index.isValid()) {
        QAbstractItemModel *model = ui->tableView_commande->model();
        QString codeCommande = model->data(model->index(index.row(), 0), Qt::DisplayRole).toString();
        ui->lineEdit_Supprimer->setText(codeCommande);
    }
}

void MainWindow::on_pushButton_setModifier_clicked()
{
    ui->tabWidget->setCurrentIndex(1);

    int code = ui->lineEdit_Modifier->text().toInt();

    Commande tmp = CommandeTMP.trouver(code);

    if (tmp.getCodeCommande() == 0) {
        QMessageBox::warning(this, "Error", "Commande non trouvée.");
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
        QMessageBox::warning(this, "Erreur", "Produit non trouvé.");
    }

    QSqlQuery queryFournisseur;
    queryFournisseur.prepare("SELECT nom_fr FROM FOURNISSEUR WHERE code = :codef");
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
        QMessageBox::warning(this, "Erreur", "Fournisseur non trouvé.");
    }
}


void MainWindow::on_pushButton_recherche_fourni_2_clicked()
{
    ui->comboBox_Fournisseur_2->clear();


    QSqlQuery queryFournisseur;
    queryFournisseur.prepare("SELECT nom_fr FROM FOURNISSEUR");

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

void MainWindow::on_pushButton_recherche_produit_2_clicked()
{
        ui->comboBox_produit_2->clear();



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

void MainWindow::on_pushButton_validerModifier_clicked()
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
        ui->Error_adresse_2->setText("l'adresse ne peut pas être vide.");
        isValid = false;
    }
    if (dateCommande < QDateTime::currentDateTime()) {
        ui->errorDate_2->setText("La date doit être dans le futur.");
        isValid = false;
    }
    if (remarque.isEmpty()) {
        ui->Error_remarque_2->setText("Remarque ne peut pas être vide.");
        isValid = false;
    }
    if (produitName.isEmpty()) {
        ui->Error_produit_2->setText("Produit ne peut pas être vide.");
        isValid = false;
    }
    if (fournisseurName.isEmpty()) {
        ui->Error_fournisseur_2->setText("Fournisseur ne peut pas être vide.");
        isValid = false;
    }

    if (!isValid) {
        QMessageBox::critical(this, "Validation Erreur", "Veuillez corriger les erreurs et réessayer.");
        return;
    }

    int produitId = getProduitId(produitName);
    int fournisseurId = getFournisseurId(fournisseurName);

    if (produitId == -1 || fournisseurId == -1) {
        QMessageBox::critical(this, "Erreur de modification", "impossible de terminer l'opération (fk non valid).");
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

    if (query.exec() == false) {
        QMessageBox::critical(this, "erreur de modification", query.lastError().text());
    } else {
        QMessageBox::information(this, "Succes", "Commande modifié avec succès!");
        ui->tableView_commande->setModel(this->CommandeTMP.afficher());
        ui->tableView_commande->resizeColumnsToContents();

        // Récupérer les détails de la commande et du produit pour l'historique
        QString action = "MODIFIER";
        QString actionDetail = QString("Commande %1 modifiée. Adresse: %2, Date: %3, Produit: %4, Fournisseur: %5, Remarque: %6")
                                   .arg(codeCommande)
                                   .arg(adresse)
                                   .arg(dateCommande.toString("yyyy-MM-dd HH:mm:ss"))
                                   .arg(produitName)
                                   .arg(fournisseurName)
                                   .arg(remarque);

        int userId = 14525546; // Remplacez par l'ID utilisateur réel

        addToHistorique(userId, action, actionDetail);
    }
}


void MainWindow::on_pushButton_recherche_logs_clicked()
{
    // Récupérer l'ID utilisateur depuis le champ de saisie
    QString userId = ui->lineEdit_id_user_logs->text();

    // Vérifier si l'ID utilisateur est valide
    if (userId.isEmpty()) {
        QMessageBox::warning(this, "Entrée invalide", "Veuillez saisir un ID utilisateur valide.");
        return;
    }

    // Préparer la requête SQL
    QSqlQuery query;
    query.prepare("SELECT USER_ID, ACTION, ACTIONDETAIL, TO_CHAR(DATEACTION, 'YYYY-MM-DD HH24:MI:SS') AS LOG_DATE "
                  "FROM HISTORIQUE WHERE USER_ID = :userId ORDER BY DATEACTION DESC");
    query.bindValue(":userId", userId);

    // Exécuter la requête
    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur Base de Données", "Échec de la récupération des logs : " + query.lastError().text());
        return;
    }

    // Créer la sortie des logs
    QString sortieLogs;

    while (query.next()) {
        QString idUtilisateur = query.value("USER_ID").toString();
        QString action = query.value("ACTION").toString();
        QString detailAction = query.value("ACTIONDETAIL").toString();
        QString dateHeure = query.value("LOG_DATE").toString();

        // Formater le log en texte
        sortieLogs += QString("L'utilisateur avec l'ID %1 a effectué l'action (%2). %3 à %4.\n")
                          .arg(idUtilisateur)
                          .arg(action)
                          .arg(detailAction)
                          .arg(dateHeure);
    }

    // Vérifier si des logs ont été trouvés
    if (sortieLogs.isEmpty()) {
        sortieLogs = "Aucune activité trouvée pour l'ID utilisateur spécifié.";
    }

    // Afficher les logs dans un QTextBrowser ou QTextEdit
    ui->textBrowser->setPlainText(sortieLogs);
}


bool MainWindow::addToHistorique(int userId,  QString &action,  QString &actionDetail)
{
    QSqlQuery query;
    query.prepare(R"(
        INSERT INTO HISTORIQUE
        ("USER_ID", "ACTION", "ACTIONDETAIL", "DATEACTION")
        VALUES (:user_id, :action, :details, TO_DATE(:date_action, 'YYYY-MM-DD HH24:MI:SS'))
    )");

    QString currentDateTime = QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss");

    query.bindValue(":user_id", userId);
    query.bindValue(":action", action);
    query.bindValue(":details", actionDetail);
    query.bindValue(":date_action", currentDateTime);

    if (!query.exec()) {
        qDebug() << "Error inserting into HISTORIQUE:" << query.lastError().text();
        return false;
    }
    return true;
}





#include <QFileDialog>
#include <QImage>
#include <QPainter>
#include <QMessageBox>
#include "qrcodegen/qrcodegen.hpp"  // Include the QR code generation library



void MainWindow::on_pushButton_qr_clicked()
{
    int code = ui->lineEdit_id_qrcode->text().toInt();
    Commande commande = this->CommandeTMP.trouver(code);

    if (commande.getCodeCommande() == 0) {
        QMessageBox::warning(this, "Erreur", "Commande introuvable !");
        return;
    }

    // Generate text for the QR code
    QString qrData = QString("Code: %1\nAdresse: %2\nDate: %3\nStatus: %4\nRemarque: %5\nCodeF: %6\nCIN: %7\nProduit: %8")
                        .arg(commande.getCodeCommande())
                        .arg(commande.getAdresse())
                        .arg(commande.getDateCommande().toString("yyyy-MM-dd HH:mm:ss"))
                        .arg(commande.getStatusCommande())
                        .arg(commande.getRemarque())
                        .arg(commande.getCodef())
                        .arg(commande.getCin())
                        .arg(commande.getProduit());

    // Generate QR code using QrCode from qrcodegen
    using namespace qrcodegen;
    QrCode qr = QrCode::encodeText(qrData.toStdString().c_str(), QrCode::Ecc::LOW);

    int size = qr.getSize();
    QImage qrImage(size, size, QImage::Format_RGB32);
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {
            qrImage.setPixel(x, y, qr.getModule(x, y) ? qRgb(0, 0, 0) : qRgb(255, 255, 255));
        }
    }

    // Scale the image for better visibility
    qrImage = qrImage.scaled(300, 300);

    // Save or show the QR code
    QString savePath = QFileDialog::getSaveFileName(this, "Enregistrer le QR Code", "", "Images (*.png)");
    if (!savePath.isEmpty()) {
        qrImage.save(savePath);
        QMessageBox::information(this, "Succès", "QR Code généré et enregistré !");
    } else {
        QMessageBox::information(this, "Info", "Opération annulée.");
    }
}

QSqlQueryModel* Commande::afficherTri(QString &trierSelon, QString &OrdreTri) {
    QSqlQueryModel *model = new QSqlQueryModel();

    // Construct the query string with dynamic column and order
    QString queryString = QString(
        "SELECT code_commande, adresse, date_commande, status_commande, remarque, codef, TO_CHAR(cin) AS cin, produit "
        "FROM COMMANDES ORDER BY %1 %2"
    ).arg(trierSelon, OrdreTri);

    // Execute the query
    QSqlQuery query;
    if (!query.exec(queryString)) {
        qWarning() << "Query execution failed:" << query.lastError().text();
        return nullptr;
    }

    // Pass the query by move to avoid copying
    model->setQuery(std::move(query));

    // Set headers for each column
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Code Commande"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Adresse"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date Commande"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Status Commande"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Remarque"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("CodeF"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(7, Qt::Horizontal, QObject::tr("Produit"));

    return model;
}




void MainWindow::on_pushButton_11_clicked()
{
    QString trierSelon = ui->comboBox_triselon->currentText();
    QString ordreTri = ui->comboBox_ordretri->currentText();
    ui->tableView_commande->setModel(this->CommandeTMP.afficherTri(trierSelon,ordreTri));

    ui->tableView_commande->resizeColumnsToContents();
}


void MainWindow::on_pushButton_recherche_clickedStock()
{
    QString critere = ui->lineEdit_recherche->text();

    ui->tableView_commande->setModel(this->CommandeTMP.rechercher(critere));
    ui->tableView_commande->resizeColumnsToContents();
}


/*void MainWindow::on_pushButton_2_clicked()
{

    // Prepare a string stream to build the HTML content
    QString strStream;
    QTextStream out(&strStream);

    // Prompt the user to select a file name for the PDF
    QString fileName = QFileDialog::getSaveFileName(
        nullptr, "Export PDF", QString(), "*.pdf");
    if (QFileInfo(fileName).suffix().isEmpty()) {
        fileName.append(".pdf");
    }

    QPrinter printer(QPrinter::HighResolution);

    // Set paper size using QPageLayout
    QPageLayout pageLayout;
    pageLayout.setPageSize(QPageSize(QPageSize::A4));
    printer.setPageLayout(pageLayout);

    // Set the output file name
    printer.setOutputFileName(fileName);

    // Retrieve data from the table view
    int rowCount = ui->tableView_commande->model()->rowCount();
    int columnCount = ui->tableView_commande->model()->columnCount();

    // Get the current date
    QString currentDate = QDate::currentDate().toString("dd/MM/yyyy");

    // Begin constructing the HTML content
    out << "<html>\n"
        << "<head>\n"
        << "<meta Content=\"Text/html; charset=UTF-8\">\n"
        << "<title>ERP - Liste des Commandes</title>\n"
        << "<style>\n"
        << "    body { font-family: 'Arial', sans-serif; margin: 20px; }\n"
        << "    .header { text-align: left; font-size: 14px; margin-bottom: 20px; }\n"
        << "    .title { text-align: center; }\n"
        << "    .title h1 { margin-bottom: 5px; }\n"
        << "    .title h3 { margin-top: 0px; }\n"
        << "    table { width: 100%; border-collapse: collapse; margin-top: 20px; }\n"
        << "    th, td { border: 1px solid #ddd; padding: 8px; }\n"
        << "    th { background-color: #f2f2f2; }\n"
        << "</style>\n"
        << "</head>\n"
        << "<body>\n"

        // Header section
        << "<div class='header'>PharmaFLOW, Your Smart Pharmacy</div>\n"

        // Title section
        << "<div class='title'>\n"
        << "<h1>Liste des Commandes</h1>\n"
        << "<h3>Date : " << currentDate << "</h3>\n"
        << "</div>\n"

        // Begin table
        << "<table>\n";

    // Table headers
    out << "<thead><tr>";
    for (int column = 0; column < columnCount; ++column) {
        if (!ui->tableView_commande->isColumnHidden(column)) {
            QString headerText = ui->tableView_commande->model()->headerData(
                column, Qt::Horizontal).toString();
            out << "<th>" << headerText << "</th>";
        }
    }
    out << "</tr></thead>\n";

    // Table data
    out << "<tbody>\n";
    for (int row = 0; row < rowCount; ++row) {
        out << "<tr>";
        for (int column = 0; column < columnCount; ++column) {
            if (!ui->tableView_commande->isColumnHidden(column)) {
                QString data = ui->tableView_commande->model()->data(
                    ui->tableView_commande->model()->index(row, column))
                    .toString()
                    .simplified();
                out << "<td>" << (data.isEmpty() ? "&nbsp;" : data) << "</td>";
            }
        }
        out << "</tr>\n";
    }
    out << "</tbody>\n</table>\n"

        // End of HTML content
        << "</body>\n</html>\n";

    // Create a QTextDocument to render the HTML content
    QTextDocument document;
    document.setHtml(strStream);

    // Print the document to the specified printer (PDF)
    document.print(&printer);
}*/


#include "arduino.h"


void MainWindow::on_pushButton_connectarduino_clicked()
{

}

void MainWindow::on_pushButton_recherche_produit_3_clicked()
{

    ui->comboBox_produit_3->clear();



    QSqlQuery query;
    query.prepare("SELECT nom_p FROM PRODUITS");


    if (query.exec() == false) {
        QMessageBox::critical(this, "Query Error", query.lastError().text());
        return;
    }


    while (query.next()) {
        QString productName = query.value(0).toString();
        ui->comboBox_produit_3->addItem(productName);
    }


    if (ui->comboBox_produit_3->count() == 0) {
        QMessageBox::information(this, "No Products", "No products found in the database.");
    }
}

void MainWindow::on_pushButton_Commander_clicked()
{
    // Get the product name from the combo box
        QString productName = ui->comboBox_produit_3->currentText();

        // Get the quantity from the spin box
        //int quantity = ui->spinBox->value();

        // Format the data to send
        // dataToSend = productName + ":" + QString::number(quantity);
        QString dataToSend = "P:" + productName;
        // Send the data to Arduino
        if (arduino.write_to_arduino(dataToSend.toUtf8()) > 0) {
            qDebug() << "Data sent successfully:" << dataToSend;
            setupSerialListener();
        } else {
            qDebug() << "Failed to send data to Arduino.";
        }
}


void MainWindow::setupSerialListener()
{
    QSerialPort *serial = arduino.getserial(); // Get the serial port object
    if (serial->isOpen()) {
        connect(serial, &QSerialPort::readyRead, this, &MainWindow::onSerialDataReceived);
    } else {
        qDebug() << "Serial port is not open!";
    }
}


void MainWindow::onSerialDataReceived()
{
    QSerialPort *serial = arduino.getserial();
    if (serial->isOpen() && serial->bytesAvailable() > 0) {
        QByteArray rawData = serial->readAll();
        buffer.append(QString::fromUtf8(rawData)); // Accumulate data in the buffer
        qDebug() << "Data received:" << rawData;

        // Check if the message ends with \r\n (complete message)
        if (buffer.endsWith("\r\n")) {
            // Process the complete message
            QString message = buffer.trimmed(); // Remove trailing \r\n
            buffer.clear(); // Clear the buffer for the next message

            if (message.startsWith("D:")) {
                QString numberPart = message.mid(2).trimmed(); // Extract the part after "D:"
                bool ok;
                int value = numberPart.toInt(&ok);
                if (ok) {
                    ui->spinBox->setValue(value); // Set the value in the spinbox
                    qDebug() << "Updated spinBox with value:" << value;
                } else {
                    qDebug() << "Failed to convert to integer:" << numberPart;
                }
            }
        }
    }
}


void MainWindow::pauseSerialListener()
{
        disconnect(serial, &QSerialPort::readyRead, this, &MainWindow::onSerialDataReceived);
        qDebug() << "Serial listener paused.";
}




void MainWindow::on_pushButton_verify_clicked()
{
    int requestedQuantity = ui->spinBox->value();
    QString dataToSend = "Valide";
    QSqlQuery query;
    query.prepare("SELECT QUANTITE_EN_STOCK, NOM_P FROM PRODUITS WHERE NOM_P = :productName");
    query.bindValue(":productName", ui->comboBox_produit_3->currentText());  // Bind the product name to the query
    query.exec();

    if (query.next()) {
        int availableQuantity = query.value("QUANTITE_EN_STOCK").toInt();
        QString productName = query.value("NOM_P").toString();

        if (availableQuantity >= requestedQuantity) {


            if (arduino.write_to_arduino(dataToSend.toUtf8()) > 0) {
                qDebug() << "Data sent successfully:" << dataToSend;
            } else {
                qDebug() << "Failed to send data to Arduino.";
            }

            int newStock = availableQuantity - requestedQuantity;
            QSqlQuery updateQuery;
            updateQuery.prepare("UPDATE PRODUITS SET QUANTITE_EN_STOCK = :newStock WHERE NOM_P = :productName");
            updateQuery.bindValue(":newStock", newStock);
            updateQuery.bindValue(":productName", productName);

            if (updateQuery.exec()) {
                qDebug() << "Stock updated successfully.";
            } else {
                qDebug() << "Error updating stock: " << updateQuery.lastError().text();
            }
        } else {
            dataToSend = "NotValide";
            arduino.write_to_arduino(dataToSend.toUtf8());
            qDebug() << "Not enough stock.";
        }
    } else {
        qDebug() << "Product not found in the database.";
    }
}


void MainWindow::on_pushButton_stat_clicked()
{
    // Create a pie series instead of a line series
    QPieSeries *series = new QPieSeries();
    QSqlQuery query;
    query.prepare("SELECT ADRESSE, COUNT(*) FROM COMMANDES GROUP BY ADRESSE");

    // Check if the query execution is successful
    if (!query.exec()) {
        std::cerr << "Failed to execute the query: " << query.lastError().text().toStdString() << std::endl;
        return;
    }

    int totalCommands = 0;
    QHash<QString, int> addressCounts;

    // Process the results
    while (query.next()) {
        QString address = query.value(0).toString();
        int numberOfCommands = query.value(1).toInt();
        totalCommands += numberOfCommands;
        addressCounts.insert(address, numberOfCommands);
    }

    // Populate the pie chart
    for (auto it = addressCounts.constBegin(); it != addressCounts.constEnd(); ++it) {
        QString address = it.key();
        int numberOfCommands = it.value();
        double percentage = (numberOfCommands * 100.0) / totalCommands;
        QPieSlice *slice = series->append(address, numberOfCommands);
        slice->setLabel(QString("%1\n%2%").arg(address).arg(percentage, 0, 'f', 1));
    }

    // Create and set up the chart
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistiques - Répartition des commandes par adresse");
    series->setLabelsVisible();

    // Create the chart view
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Add the chartView to the layout
    QVBoxLayout *layout = ui->verticalLayout_stat; // Assume `verticalLayout_stat` is defined in the UI
    if (!layout->isEmpty()) {
        // Remove any existing widgets to prevent overlapping
        QLayoutItem *item;
        while ((item = layout->takeAt(0)) != nullptr) {
            delete item->widget(); // Delete existing widgets in the layout
            delete item;
        }
    }
    layout->addWidget(chartView);

}

#include <QSqlRecord>


    /*
    // Configure the printer for PDF output
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPageSize(QPageSize::A4);  // Use QPageSize for paper size
    printer.setOutputFileName(fileName);*/

    // Configure the printer for PDF output

void MainWindow::on_pushButton_pdf_clicked()
{
    QString strStream;
    QTextStream out(&strStream);

    QString fileName = QFileDialog::getSaveFileName(
        nullptr, "Export PDF", QString(), "*.pdf");
    if (QFileInfo(fileName).suffix().isEmpty()) {
        fileName.append(".pdf");
    }

    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);

    printer.setPageSize(QPageSize::A4);  // Use QPageSize for paper size
    printer.setOutputFileName(fileName);

    QString selectedDate = ui->dateEdit_datecommande->date().toString("yyyy-MM-dd");

    QSqlQuery query;
    query.prepare(
        "SELECT c.CODE_COMMANDE, c.ADRESSE, c.DATE_COMMANDE, "
        "c.STATUS_COMMANDE, c.REMARQUE, p.NOM_P "
        "FROM COMMANDES c "
        "JOIN PRODUITS p ON c.PRODUIT = p.ID_P "
        "WHERE c.DATE_COMMANDE >= TO_DATE(:selectedDate, 'YYYY-MM-DD')");
    query.bindValue(":selectedDate", selectedDate);

    if (!query.exec()) {
        QMessageBox::critical(this, "Error", "Failed to retrieve data from the database.");
        return;
    }

    QList<QStringList> tableData;
    QStringList headers = {"Code Commande", "Adresse", "Date Commande", "Status", "Remarque", "Nom du Produit"};

    while (query.next()) {
        QStringList row;
        row << query.value("CODE_COMMANDE").toString()
            << query.value("ADRESSE").toString()
            << query.value("DATE_COMMANDE").toDate().toString("yyyy-MM-dd")
            << query.value("STATUS_COMMANDE").toString()
            << query.value("REMARQUE").toString()
            << query.value("NOM_P").toString();
        tableData.append(row);
    }

    out << "<html>\n"
        << "<head>\n"
        << "<meta Content=\"Text/html; charset=UTF-8\">\n"
        << "<title>ERP - Liste des Commandes</title>\n"
        << "<style>\n"
        << "    body { font-family: 'Arial', sans-serif; margin: 20px; }\n"
        << "    .header { text-align: left; font-size: 14px; margin-bottom: 20px; }\n"
        << "    .title { text-align: center; }\n"
        << "    .title h1 { margin-bottom: 5px; }\n"
        << "    .title h3 { margin-top: 0px; }\n"
        << "    table { width: 100%; border-collapse: collapse; margin-top: 20px; }\n"
        << "    th, td { border: 1px solid #ddd; padding: 8px; }\n"
        << "    th { background-color: #f2f2f2; }\n"
        << "</style>\n"
        << "</head>\n"
        << "<body>\n"
        << "<div class='header'>PharmaFLOW, Your Smart Pharmacy</div>\n"
        << "<div class='title'>\n"
        << "<h1>Liste des Commandes</h1>\n"
        << "<h3>À partir de la date choisie : " << selectedDate << "</h3>\n"
        << "</div>\n"
        << "<table>\n"
        << "<thead><tr>";

    for (const QString &header : headers) {
        out << "<th>" << header << "</th>";
    }
    out << "</tr></thead>\n<tbody>\n";

    for (const QStringList &row : tableData) {
        out << "<tr>";
        for (const QString &cell : row) {
            out << "<td>" << cell << "</td>";
        }
        out << "</tr>";
    }

    out << "</tbody>\n</table>\n</body>\n</html>\n";

    QTextDocument document;
    document.setHtml(strStream);
    document.print(&printer);

    QMessageBox::information(this, "Succes", "PDF a été exporté avec succès !!");
}




void MainWindow::on_pushButton_destroyed() {
    // Implémentation (même si elle est vide, elle doit exister)
}


void MainWindow::updateComboBoxProduitEtFournisseur(){
    ui->comboBox_Fournisseur->clear();

    QSqlQuery queryFournisseur;
    queryFournisseur.prepare("SELECT nom_fr FROM FOURNISSEUR");

    if (!queryFournisseur.exec()) {
        QMessageBox::critical(this, "Query Error", queryFournisseur.lastError().text());
        return;
    }


    while (queryFournisseur.next()) {
        QString fournisseurName = queryFournisseur.value(0).toString();
        ui->comboBox_Fournisseur->addItem(fournisseurName);
    }

    ui->comboBox_produit->clear();
    ui->comboBox_produit_3->clear();

    QSqlQuery query;
    query.prepare("SELECT nom_p FROM PRODUITS");


    if (query.exec() == false) {
        QMessageBox::critical(this, "Query Error", query.lastError().text());
        return;
    }


    while (query.next()) {
        QString productName = query.value(0).toString();
        ui->comboBox_produit->addItem(productName);
        ui->comboBox_produit_3->addItem(productName);

    }


    if (ui->comboBox_produit->count() == 0) {
        QMessageBox::information(this, "No Products", "No products found in the database.");
    }



}





//gestion Fournisser Function
void MainWindow::on_validerf_clicked()
{
    int codef=ui->lineEdit_code->text().toInt();
    QString nomf=ui->lineEdit_nom->text();
    int numerof=ui->lineEdit_num->text().toInt();
    QString email=ui->lineEdit_mail->text();
    QString rs=ui->lineEdit_rs->text();
    QString produit=ui->lineEdit_produit->text();

//controle de saisie

    if (nomf.length()==0)
    {
            QMessageBox::warning(this, "Erreur de saisie", "chaque fournisseur doit avoir un nom !");
            return;
    }
    if (codef <= 0)
    {
            QMessageBox::warning(this, "Erreur de saisie", "Le code doit être supérieur à zéro !");
            return;
    }
    if (email.length()== 0)
    {
            QMessageBox::warning(this, "Erreur de saisie", " l'email du fournisseur ne doit pas être vide.");
            return;
    }

    if (numerof <=10000000)
    {
            QMessageBox::warning(this, "Erreur de saisie", "Le numéro doit être formé par 8 chiffres.");
            return;
    }

    if (rs.length()==0)
    {
            QMessageBox::warning(this, "Erreur de saisie", "La raison sociale du fournisseur est vide.");
            return;
    }


    if (produit.length()== 0)
    {
            QMessageBox::warning(this, "Erreur de saisie", "le produit est vide !");
            return;
    }

fournisseurs f(codef,numerof,nomf,email,rs,produit);
bool test=f.ajouterfour();

if(test)
{
    ui->tableView->setModel(f.afficherfour());
    QMessageBox::information(nullptr, QObject::tr("OK"),
                             QObject::tr("Ajout effectué\n"
                                         "click Cancel to exit."), QMessageBox::Cancel);
}

else
    QMessageBox::critical(nullptr, QObject::tr("not ok"),
                      QObject::tr("Ajout non effectué\n"
                                  "click Cancel to exit."), QMessageBox::Cancel);
}


void MainWindow::on_supprimerf_clicked()
{
    int codef =ui->lineEdit_code->text().toInt();
    if (codef==0)
    {
        QMessageBox::information(nullptr,"erreur", "entrer un code ");
    }
    bool test = f.suppfour(codef);
    if(test)
    {

        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Suppression effectué\n"
                                             "click Cancel to exit."), QMessageBox::Cancel);
         ui->tableView->setModel(f.afficherfour());
    }

    else
        QMessageBox::critical(nullptr,QObject::tr("not ok"),
                          QObject::tr("Suppression non effectueé\n"
                                      "click Cancel to exit."), QMessageBox::Cancel);
}





void MainWindow::on_modifier_f_clicked()
{
    int codef = ui->lineEdit_code->text().toInt();
    if (codef == 0)
    {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un code valide.");
        return;
    }
    // s'il existe
    QString queryStr = "SELECT COUNT(*) FROM fournisseur WHERE codef = :codef";
    QSqlQuery query;
    query.prepare(queryStr);
    query.bindValue(":codef", codef);

    if (!query.exec())
    {
        QMessageBox::critical(this, "Erreur SQL", "Erreur lors de l'exécution de la requête : " + query.lastError().text());
        return;
    }

    // Vérifier si le fournisseur existe
    if (query.next()) //req exécutable
    {
        int count = query.value(0).toInt();
        if (count == 0)
        {
            QMessageBox::warning(this, "Erreur", "Fournisseur introuvable.");
            return;
        }
    }


    fournisseurs fournisseurExistant;
    // update les champs modifiés
    QString nomf = ui->lineEdit_nom->text();
    if (!nomf.isEmpty())
    {
        fournisseurExistant.setnomf(nomf);
    }

    QString email = ui->lineEdit_mail->text();
    if (!email.isEmpty()) {
        fournisseurExistant.setmail(email);
    }

    QString rs = ui->lineEdit_rs->text();
    if (!rs.isEmpty())
    {
        fournisseurExistant.setrs(rs);
    }

    QString produit = ui->lineEdit_produit->text();
    if (!produit.isEmpty())
    {
        fournisseurExistant.setproduit(produit);
    }

    int numerof = ui->lineEdit_num->text().toInt();
    if(numerof!=0)
    {
        fournisseurExistant.setnumerof(numerof);
    }

    if (fournisseurExistant.modifier(codef,numerof,nomf,email,rs,produit))
    {
        QMessageBox::information(this, "Succès", "Fournisseur modifié avec succès.");
        f.afficherfour();
    }

    else
    {
        QMessageBox::critical(this, "Erreur", "Échec de la modification du fournisseur.");
    }
}





//metiers
void MainWindow::on_rechercher_f_clicked()
{
    QString searchField = ui->comboBox_2->currentText();
    QString searchValue = ui->LineEdit_rech_f->text().trimmed(); // Valeur de recherche

    // Vérifier si la valeur de recherche est vide
    if (searchValue.isEmpty())
    {
        QMessageBox::warning(this, "Erreur"," Entrer une valeur");

    }
    QSqlQuery query;

    // Recherche par code
    if (searchField == "codef")
    {
        qDebug()<<"recherche codef";
        query.prepare("SELECT * FROM fournisseur WHERE codef = :codef");
        query.bindValue(":codef", searchValue);
    }

    // Recherche par rs
    else if (searchField == "rs")
    {
        query.prepare("SELECT * FROM fournisseur WHERE rs = :rs");
        query.bindValue(":rs", searchValue);
    }
    else
    {
        query.prepare("SELECT * FROM fournisseur WHERE nomf = :nomf");
        query.bindValue(":nomf", searchValue);
    }

    //envoyer la req
    QSqlQueryModel *model = new QSqlQueryModel;
    if (query.exec())
    {
            model->setQuery(query);
    }

    else
    {
            QMessageBox::warning(this, "Erreur", "Échec de l'envoi de la requête.");

    }

    // Aucune ligne dans la table
    if (model->rowCount() == 0)
    {
            QMessageBox::information(this, "Résultat", "Aucun fournisseur trouvé.");
    }
    else
    {
            ui->tableView->setModel(model); // Affichage des résultats
            //ui->tableView->resizeColumnsToContents(); // Ajuste les colonnes
    }
}





void MainWindow::on_trier_f_clicked()
{
        QString selectedCriteria = ui->comboBox->currentText();
        QString queryStr;

        if (selectedCriteria == "Codef")
        {
            queryStr = "SELECT codef,nomf,produit "
                       "FROM fournisseur ORDER BY codef ASC";
        }
        else if (selectedCriteria == "Nomf")
        {
            queryStr = "SELECT codef,nomf,produit "
                       "FROM fournisseurs ORDER BY nomf ASC";
        }
        else if (selectedCriteria == "Produit")
        {
            queryStr = "SELECT codef,nomf,produit  "
                       "FROM fournisseur ORDER BY produit ASC";
        }
        else
        {
            QMessageBox::warning(this, "Erreur", "Critère de tri invalide.");
            return;
        }

        QSqlQueryModel *model = new QSqlQueryModel;
        model->setQuery(queryStr);

        if (model->lastError().isValid())
        {
            QMessageBox::critical(this, "Erreur", "Erreur lors du tri des fournisseurs : " + model->lastError().text());
        }
        else//affichage
        {
            ui->tableView->setModel(model);
            //ui->tableView->resizeColumnsToContents();
        }
}


void MainWindow::on_pdf_f_clicked()
{
    QSqlQuery query;
    // Requête pour récupérer les données nécessaires, triées par raison sociale
    if (!query.exec("SELECT rs, nomf, email, numerof FROM fournisseur ORDER BY rs, nomf"))
    {
        QMessageBox::critical(this, "Erreur", "Échec de la récupération des données des fournisseurs.");
        return;
    }

    // Enregistrer PDF
    QString filePath = QFileDialog::getSaveFileName(this, "Enregistrer le fichier PDF", "", "*.pdf");
    if (filePath.isEmpty())
    {
        return;
    }

    // Préparer le fichier PDF
    QPdfWriter pdfWriter(filePath);

    pdfWriter.setPageSize(QPageSize::A4);
    pdfWriter.setResolution(300);

    QPainter painter(&pdfWriter);
    if (!painter.isActive())
    {
        QMessageBox::critical(this, "Erreur", "Impossible de créer le fichier PDF.");
        return;
    }

    int y = 100; // Position verticale initiale
    int margin = 90; // Marge
    painter.setFont(QFont("Arial", 12));
    painter.drawText(margin, y, "Liste des Fournisseurs regroupés par Raisons Sociales :");

    y += 100;

    QString currentRaisonSociale = "";
    while (query.next())
    {
        QString raisonSociale = query.value(0).toString();
        QString nom = query.value(1).toString();
        QString email = query.value(2).toString();
        QString numero = query.value(3).toString();

        // Ajouter une nouvelle raison sociale si elle change
        if (raisonSociale != currentRaisonSociale)
        {
            if (!currentRaisonSociale.isEmpty())
            {
                y += 80; // Ajouter un espace entre les groupes
            }

            painter.setFont(QFont("Arial", 12, QFont::Bold));
            painter.drawText(margin, y, QString("Raison Sociale: %1").arg(raisonSociale));
            y += 100;
            currentRaisonSociale = raisonSociale;
        }

        // Ajouter les détails du fournisseur : Nom, Numéro, Email
        painter.setFont(QFont("Arial", 11));
        painter.drawText(margin + 30, y, QString("Nom: %1").arg(nom));
        y += 90; // Descendre pour afficher le numéro
        painter.drawText(margin + 30, y, QString("Numéro: %1").arg(numero));
        y += 90; // Descendre pour afficher l'email
        painter.drawText(margin + 30, y, QString("Email: %1").arg(email));
        y += 90;

        // Passer à une nouvelle page si nécessaire
        if (y > pdfWriter.height() - margin)
        {
            pdfWriter.newPage();
            y = margin;
        }
    }

    painter.end(); // Fin du dessin
    QMessageBox::information(this, "Succès", "Le fichier PDF a été généré avec succès !");
}



/*
void MainWindow::on_pdf_f_clicked()
{
        QSqlQuery query;
        if (!query.exec("SELECT nomf, rs FROM fournisseurs ORDER BY rs, nomf"))
        {
            QMessageBox::critical(this, "Erreur", "Échec de la récupération des données des fournisseurs.");
            return;
        }

        // enregistrer PDF
        QString filePath = QFileDialog::getSaveFileName(this, "Enregistrer le fichier PDF", "", "*.pdf");
        if (filePath.isEmpty())
        {
            return;
        }

        // Préparer le fichier PDF
        QPdfWriter pdfWriter(filePath);
        pdfWriter.setPageSize(QPageSize::A4);
        pdfWriter.setResolution(300);

        QPainter painter(&pdfWriter);
        if (!painter.isActive())
        {
            QMessageBox::critical(this, "Erreur", "Impossible de créer le fichier PDF.");
            return;
        }

        int y = 100; // Position verticale initiale
        int margin = 90; // Marge
        painter.setFont(QFont("Arial", 12));
        painter.drawText(margin, y, "Liste des Fournisseurs et leurs Raisons Sociales :");

        y += 100;

        // Parcourir les résultats et les ajouter au PDF
        while (query.next())
        {
            QString nom = query.value(0).toString();
            QString raisonSociale = query.value(1).toString();

            // Écrire dans le PDF
            painter.drawText(margin, y, QString("%1 : %2").arg(nom).arg(raisonSociale));
            y += 80;

            // passer à une nouvelle page
            if (y > pdfWriter.height() - margin)
            {
                pdfWriter.newPage();
                y = margin;
            }
        }

        painter.end(); // Fin du dessin
        QMessageBox::information(this, "Succès", "Le fichier PDF a été généré avec succès !");
}
*/

/*

void MainWindow::on_stat_f_clicked()
{
    QString queryStr = "SELECT rs FROM fournisseurs";
    QSqlQuery query;

    if (!query.exec(queryStr))
    {
        qDebug() << "Erreur SQL : " << query.lastError().text();
        QMessageBox::warning(this, "Erreur", "Impossible de récupérer les raisons sociales : " + query.lastError().text());
        return;
    }

    // Créer un QMap pour compter la fréquence des raisons sociales
    QMap<QString, int> rsFrequency;

    while (query.next())
    {
        QString rs = query.value(0).toString();
        if (!rs.isEmpty())
        {
            rsFrequency[rs] += 1;
        }
    }

    if (rsFrequency.isEmpty())
    {
        QMessageBox::information(this, "Aucune donnée", "Aucune raison sociale trouvée dans la base de données.");
        return;
    }

    // Trier les raisons sociales en fonction de la fréquence
    QList<QString> sortedRs = rsFrequency.keys();
    std::sort(sortedRs.begin(), sortedRs.end(), [&rsFrequency](const QString &a, const QString &b) {
        return rsFrequency[a] > rsFrequency[b];
    });

    // Créer un graphique à barres
    QBarSeries *series = new QBarSeries();

    // Créer un QBarSet et ajouter les fréquences (comptage) pour chaque raison sociale
    QBarSet *set = new QBarSet("Demandes");

    foreach (const QString &rs, sortedRs)
    {
        int freq = rsFrequency[rs];
        *set << freq;  // Ajouter la fréquence
    }

    // Ajouter le QBarSet à la série
    series->append(set);

    // Créer un graphique et ajouter la série
    QChart *chart = new QChart();
    chart->addSeries(series);

    // Créer et configurer l'axe X (raisons sociales)
    QStringList categories;
    foreach (const QString &rs, sortedRs)
    {
        categories << rs;
    }

    // Créer l'axe X avec les catégories (raisons sociales)
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);  // L'axe X affiche les raisons sociales
    chart->setAxisX(axisX, series);

    // Créer l'axe Y pour les fréquences (comptages)
    chart->createDefaultAxes();

    // Créer la vue du graphique
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Ajouter le graphique à un layout
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(chartView);

    // Créer une fenêtre pour afficher le graphique
    QWidget *chartWindow = new QWidget();
    chartWindow->setLayout(layout);
    chartWindow->setWindowTitle("Statistiques des Raisons Sociales les Plus Demandées");
    chartWindow->resize(600, 400);
    chartWindow->show();
}


*/
/*void MainWindow::on_stat_f_clicked()
{
    QString queryStr = "SELECT rs FROM fournisseurs";
    QSqlQuery query;

    if (!query.exec(queryStr))
    {
        qDebug() << "Erreur SQL : " << query.lastError().text();
        QMessageBox::warning(this, "Erreur", "Impossible de récupérer les raisons sociales : " + query.lastError().text());
        return;
    }

    // Créer QMap pour les fréquences des raisons sociales
    QMap<QString, int> rsFrequency;

    // Remplir le QMap avec les raisons sociales et leurs fréquences
    while (query.next())
    {
        QString rs = query.value(0).toString();
        if (!rs.isEmpty())
        {
            rsFrequency[rs] += 1;
        }
    }

    if (rsFrequency.isEmpty())
    {
        QMessageBox::information(this, "Aucune donnée", "Aucune raison sociale trouvée dans la base de données.");
        return;
    }

    // Trier les raisons sociales par fréquence
    QList<QString> sortedRs = rsFrequency.keys();
    std::sort(sortedRs.begin(), sortedRs.end(), [&rsFrequency](const QString &a, const QString &b) {
        return rsFrequency[a] > rsFrequency[b];
    });

    // Créer un graphique à barres
    QBarSet *set = new QBarSet("Demandes");

    // Ajouter les fréquences au graphique
    foreach (const QString &rs, sortedRs)
    {
        int freq = rsFrequency[rs];  // Fréquence de la raison sociale
        *set << freq;  // Ajouter la fréquence au QBarSet
    }

    // Créer une série de barres
    QBarSeries *series = new QBarSeries();
    series->append(set);

    // Créer le graphique
    QChart *chart = new QChart();
    chart->addSeries(series);

    // Ajouter les catégories (raisons sociales) à l'axe X
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(sortedRs);  // Mettre les raisons sociales sous les barres
    chart->setAxisX(axisX, series);

    // Créer un affichage pour le graphique
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Afficher le graphique
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(chartView);
    QWidget *chartWindow = new QWidget();
    chartWindow->setLayout(layout);
    chartWindow->setWindowTitle("Statistiques des Raisons Sociales les Plus Demandées");
    chartWindow->resize(600, 400);
    chartWindow->show();
}

*/

#include <QBarSet>
void MainWindow::on_stat_f_clicked()
{
    QString queryStr = "SELECT rs FROM fournisseur";
    QSqlQuery query;

    if (!query.exec(queryStr))
    {
        qDebug() << "Erreur SQL : " << query.lastError().text();
        QMessageBox::warning(this, "Erreur", "Impossible de récupérer les raisons sociales : " + query.lastError().text());
        return;
    }

    QMap<QString, int> rsFrequency;
    while (query.next())
    {
        QString rs = query.value(0).toString();
        if (!rs.isEmpty())
        {
            rsFrequency[rs] += 1;
        }
    }

    if (rsFrequency.isEmpty())
    {
        QMessageBox::information(this, "Aucune donnée", "Aucune raison sociale trouvée dans la base de données.");
        return;
    }

    QList<QString> sortedRs = rsFrequency.keys();
    std::sort(sortedRs.begin(), sortedRs.end(), [&rsFrequency](const QString &a, const QString &b) {
        return rsFrequency[a] > rsFrequency[b];
    });

    int total = 0;
    foreach (const QString &rs, sortedRs)
    {
        total += rsFrequency[rs];
    }

    // Créer un graphique à barres
    QBarSet *set = new QBarSet("Demandes");

    // Ajouter les fréquences au graphique
    foreach (const QString &rs, sortedRs)
    {
        int freq = rsFrequency[rs];  // Fréquence de la raison sociale
        *set << (static_cast<double>(freq)/total)*100;  // Ajouter la fréquence au QBarSet
    }

    // Créer une série de barres
    QBarSeries *series = new QBarSeries();
    series->append(set);

    // Créer le graphique
    QChart *chart = new QChart();
    chart->addSeries(series);

    // Ajouter les catégories (raisons sociales) à l'axe X
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(sortedRs);  // Mettre les raisons sociales sous les barres
    chart->setAxisX(axisX, series);

    // Créer un axe Y pour afficher les pourcentages sur la gauche
    QValueAxis *axisYLeft = new QValueAxis();
    axisYLeft->setRange(0, 100);
    chart->addAxis(axisYLeft, Qt::AlignLeft);
    series->attachAxis(axisYLeft);

    // Créer un affichage pour le graphique
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Afficher le graphique
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(chartView);
    QWidget *chartWindow = new QWidget();
    chartWindow->setLayout(layout);
    chartWindow->setWindowTitle("Statistiques des Raisons Sociales les Plus Demandées");
    chartWindow->resize(600, 400);
    chartWindow->show();
}


//avancées

void MainWindow::on_calendrier_clicked(const QDate &date)
{
    // Créer une instance de QSqlQuery pour récupérer les commandes pour la date sélectionnée
    QSqlQuery query;
    query.prepare("SELECT code_commande, date_commande, status_commande "
                  "FROM commandes "
                  "WHERE TRUNC(date_commande) = TO_DATE(:date, 'YYYY-MM-DD')");
    query.bindValue(":date", date.toString("yyyy-MM-dd"));

    // Exécuter la requête SQL
    if (!query.exec())
    {
        QMessageBox::critical(this, "Erreur SQL", "Erreur lors de l'exécution de la requête : " + query.lastError().text());
        return;
    }

    // Vérifier si des commandes ont été trouvées pour la date
    bool commandesTrouvees = false;
    while (query.next())
    {
        commandesTrouvees = true;
    }

    // Mettre à jour la couleur de la date dans le calendrier
    QTextCharFormat formatCommande;
    if (commandesTrouvees)
    {
        formatCommande.setBackground(Qt::yellow);  // Définir la couleur de fond de la date avec commande
        ui->calendrier->setDateTextFormat(date, formatCommande);  // Appliquer la couleur à la date
    }

    // Affichage des informations de la commande si des commandes ont été trouvées
    if (!commandesTrouvees)
    {
        QMessageBox::information(this, "Aucune commande", "Aucune commande trouvée pour la date sélectionnée.");
    }
    else
    {
        QString detailsCommandes = "Commandes prévues le " + date.toString("dd/MM/yyyy") + " :\n";
        query.seek(0);  // Revenir au début de la requête pour afficher les détails des commandes
        do
        {
            QString code = query.value("code_commande").toString();
            QString statut_commande = query.value("status_commande").toString();
            detailsCommandes += "- Code commande : " + code + ", Statut : " + statut_commande + "\n";
        }
        while (query.next());

        QMessageBox::information(this, "Commandes trouvées", detailsCommandes);
    }
}





void MainWindow::on_commandes_daujourdui_clicked()
{
    QDate date = QDate::currentDate();
        QSqlQuery query;
        query.prepare("SELECT code_commande FROM commandes WHERE TRUNC(date_commande) = TO_DATE(:date, 'YYYY-MM-DD')");
        query.bindValue(":date", date.toString("yyyy-MM-dd"));

        if (!query.exec())
        {
            QMessageBox::critical(this, "Erreur SQL", "Erreur lors de l'exécution de la requête.");
            return;
        }

        if (!query.next())
        {
            QMessageBox::information(this, "Aucune commande", "Aucune commande trouvée pour aujourd'hui.");
            return;
        }

        // Crée une fenêtre
        QWidget *commandeWindow = new QWidget();
        QVBoxLayout *layout = new QVBoxLayout();

        // une case à cocher
        do {
            QString code_commande = query.value("code_commande").toString();
            QCheckBox *checkBox = new QCheckBox("Commande " + code_commande);
            layout->addWidget(checkBox);

            // Connecter case à cocher à la validation
            connect(checkBox, &QCheckBox::toggled, [this, code_commande](bool checked)
            {
                if (checked)
                {
                    QSqlQuery updateQuery;
                    updateQuery.prepare("UPDATE commandes SET status_commande = 'Arrivée' WHERE code_commande = :code_commande");
                    updateQuery.bindValue(":code_commande", code_commande);
                    updateQuery.exec();
                }
            });
        } while (query.next());

        QPushButton *updateButton = new QPushButton("Valider");
        connect(updateButton, &QPushButton::clicked, [this]()
        {
            QMessageBox::information(this, "Succès", "Commandes validées.");
        });

        layout->addWidget(updateButton);
        commandeWindow->setLayout(layout);
        commandeWindow->resize(300, 200);
        commandeWindow->show();

}


/*
void MainWindow::handleArduinoData(const QByteArray &data)
{
    QString message = QString::fromUtf8(data);
    qDebug() << "Données reçues de Arduino : " << message;

    bool ok;
    double temperatureArduino = 0.0;

    if (message.contains("Temperature:"))
    {
        QString temperatureString = message.mid(message.indexOf("Temperature:") + 12).trimmed();
        temperatureArduino = temperatureString.toDouble(&ok);

        if (ok) {
            qDebug() << "Température lue : " << temperatureArduino;
            QSqlQuery query;
            query.prepare("SELECT medicaments, temperature FROM prescriptions");

            if (!query.exec())
            {
                qDebug() << "Erreur SQL : " << query.lastError().text();
                return;
            }

            while (query.next())
            {
                QString nomMedicament = query.value(0).toString();
                double storedTemperature = query.value(1).toDouble();

                qDebug() << "Nom du médicament : " << nomMedicament;
                qDebug() << "Température seuil : " << storedTemperature;

                if (temperatureArduino > storedTemperature)
                {
                    QString alertMessage = "La température a dépassé la temperature idéale du \"" + nomMedicament;
                    QMessageBox::warning(this, "Alerte", alertMessage);
                }
            }
        } else {
            qDebug() << "Erreur : Impossible de convertir la température en nombre flottant.";
        }
    } else {
        qDebug() << "Erreur : Le message reçu ne contient pas de température.";
    }
}

*/



void MainWindow::handleArduinoData(const QByteArray &data)
{

    QString message = QString::fromUtf8(data);
    qDebug() << "Données reçues de Arduino : " << message;

    bool ok;
    double temperatureArduino = 0.0;

    if (message.contains("Temperature:"))
    {
        QString temperatureString = message.mid(message.indexOf("Temperature:") + 12).trimmed();
        temperatureArduino = temperatureString.toDouble(&ok);

        if (ok) {
            qDebug() << "Température lue : " << temperatureArduino;
            QSqlQuery query;
            query.prepare("SELECT medicaments, temperature FROM prescriptions");

            if (!query.exec())
            {
                qDebug() << "Erreur SQL : " << query.lastError().text();
                return;
            }

            while (query.next())
            {
                QString nomMedicament = query.value(0).toString();
                double storedTemperature = query.value(1).toDouble();

                qDebug() << "Nom du médicament : " << nomMedicament;
                qDebug() << "Température seuil : " << storedTemperature;

                if (temperatureArduino > storedTemperature)
                {

                    QString alertMessage = "La température a dépassé la temperature idéale du \"" + nomMedicament;
                    QMessageBox::warning(this, "Alerte", alertMessage);

                }
            }
        } else {
            qDebug() << "Erreur : Impossible de convertir la température en nombre flottant.";
        }
    } else {
        qDebug() << "Erreur : Le message reçu ne contient pas de température.";
    }
}


void MainWindow::setActiveButtonStyle(QPushButton* activeButton) {
    // Reset the style for all buttons
    ui->pushButton_page_Commande->setStyleSheet("");
    ui->pushButton_page_Prescription->setStyleSheet("");
    ui->pushButton_page_Employees->setStyleSheet("");
    ui->pushButton_page_Fournisseur->setStyleSheet("");
    ui->pushButton_page_Stock->setStyleSheet("");
    ui->pushButton_page_Transaction->setStyleSheet("");

    // Set the green style for the active button
    if (activeButton) {
        activeButton->setStyleSheet("background-color: green; color: white; font-weight: bold;");
    }
}


void MainWindow::on_pushButton_page_Fournisseur_clicked()
{
    setActiveButtonStyle(ui->pushButton_page_Fournisseur);
    ui->stackedWidget->setCurrentWidget(ui->PageFournisseur);
}



void MainWindow::on_pushButton_page_Commande_clicked()
{
    setActiveButtonStyle(ui->pushButton_page_Commande);
    ui->stackedWidget->setCurrentWidget(ui->PageCommande);

}


















//prescription


// Function to check employee code and log results
void MainWindow::checkEmployeeCode(const QString &code)
{

    QSqlQuery insertQuery;
              insertQuery.prepare("INSERT INTO EMPLOYEE (ID_EMPLOYE, MOT_DE_PASSE, DATE_EMBAUCHE) VALUES (100, '123', TO_DATE('2024-12-03', 'YYYY-MM-DD'))");

              // Execute the insert query with the hardcoded date
              if (insertQuery.exec()) {
                  qDebug() << "Inserted new employee into the database.";
              } else {
                  qDebug() << "Error inserting employee:" << insertQuery.lastError().text();
              }

    QSqlQuery query;
    qDebug() << "Data received from the read function: " << code;

    query.prepare("SELECT ID_EMPLOYE , ADRESSE FROM EMPLOYEE WHERE MOT_DE_PASSE = :code");
    query.bindValue(":code", code);

    bool isCodeCorrect = false;  // Flag to track if the code is correct
    QString logMessage;  // Message to be written to the log file

    if (query.exec()) {
        if (query.next()) {
            // If employee exists, get their details
            QString id = query.value(0).toString();
            QString adresse = query.value(1).toString();

            // Code is correct
            isCodeCorrect = true;

            // Show a pop-up with employee info
            QMessageBox::information(this, "employe trouvé", "ID employé : " + id +"Adresse : "+adresse );

            // Prepare log message for correct code
            logMessage = QString("[%1] Code '%2' trouvé: ID employe: %3")
                            .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"))
                            .arg(code)
                            .arg(id);
        } else {
            // If no employee is found with that code
            QMessageBox::warning(this, "utilisateur inconnu", "Un inconnu tente d'ouvrire la porte ");

            // Prepare log message for incorrect code
            logMessage = QString("[%1] Code '%2' employe inconnu ")
                            .arg(QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss"))
                            .arg(code);
        }

        // Write the log message to the file
        logToFile(logMessage);

    } else {
        // Handle query execution failure
        qDebug() << "Error executing query: " << query.lastError().text();
    }
}
void MainWindow::logToFile(const QString &message)
{
    QString logFilePath = "employee_check_log.txt"; // Fixed log file name in the app directory
    QFile file(logFilePath);

    if (file.open(QIODevice::Append | QIODevice::Text)) {
        QTextStream out(&file);
        out << message << "\n";  // Write the log message
        file.close();
    }
}

void MainWindow::showSecurityAlert(const QString &code) {
    QMessageBox::information(this, "Security Alert",
                             "Someone is trying to enter using this code: " + code);
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
/*void MainWindow::enregistrer (Prescription * temp)
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


*/

void MainWindow::on_enregistrerButton_clicked()
{

    Prescription * temp=new Prescription();
    enregistrer(temp);

    if ( temp->ajouter())
    {
               QMessageBox::information(this, "PharmaFlow", "La prescriptiona  ete ajoutée  avec succes");
    }
    else
    {
               QMessageBox::information(this, "PharmaFlow", "Une erreure c'est prosuite lors de l'jout de cette prescription ");
    }



    this->ui->nom_8->clear();
    this->ui->nom_medecin_4->clear();
    this->ui->statut_4->clear();
    this->ui->duree_4->clear();
    this->ui->dosage_4->clear();
    this->ui->frequence_4->clear();
    this->ui->note_8->clear();
    this->ui->medicament_4->clear();
    ui->MainTab->setCurrentIndex(0);
    ui->tableView->setModel(Prescription::afficher());
    return ;


}
void MainWindow::enregistrer(Prescription* temp) {
    bool isValid = true;

    temp->setID(Connection::get_size());
    temp->setDate_Prescription(QDate::currentDate());

    QString dosage = this->ui->dosage_4->text();
    if (dosage.isEmpty()) {
        isValid = false;
        QMessageBox::warning(this, "Erreur de saisie", "Le dosage ne peut pas être vide.");
    } else {
        temp->setDosage(dosage);
    }

    bool dureeOk;
    int duree = this->ui->duree_4->text().toInt(&dureeOk);
    if (!dureeOk) {
        isValid = false;
        QMessageBox::warning(this, "Erreur de saisie", "La durée du traitement doit être un entier.");
    } else {
        temp->setDuree_traitement(duree);
    }

    bool frequenceOk;
    int frequence = this->ui->frequence_4->text().toInt(&frequenceOk);
    if (!frequenceOk) {
        isValid = false;
        QMessageBox::warning(this, "Erreur de saisie", "La fréquence doit être un entier.");
    } else {
        temp->setFrequence(frequence);
    }

    QString nomPatient = this->ui->nom_8->text();
    if (nomPatient.isEmpty()) {
        isValid = false;
        QMessageBox::warning(this, "Erreur de saisie", "Le nom du patient ne peut pas être vide.");
    } else {
        temp->setNom_Patient(nomPatient);
    }

    QString medicament = this->ui->medicament_4->text().trimmed();
    medicament = medicament.replace("\"", ""); // Enlève les guillemets éventuels

    if (medicament.isEmpty()) {
        isValid = false;
        QMessageBox::warning(this, "Erreur de saisie", "Le médicament ne peut pas être vide.");
    } else {
        temp->setMedicament(medicament);
    }

    QString nomMedecin = this->ui->nom_medecin_4->text();
    if (nomMedecin.isEmpty()) {
        isValid = false;
        QMessageBox::warning(this, "Erreur de saisie", "Le nom du médecin ne peut pas être vide.");
    } else {
        temp->setNom_Medecin(nomMedecin);
    }

    QString note = this->ui->note_8->text();
    temp->setNote(note);

    temp->setStatut("Pending");

    qDebug()<<"ENREGISTRER done ";
    ui->tableView_10->setModel(Prescription::afficher());


    if (!isValid) return;
}

    /*
    // Vérification si le médicament est en stock
    if (!isMedicamentInStock(medicament)) {
        // Si le médicament est hors stock, afficher les médicaments de la même catégorie
        QString category = getCategoryOfMedicament(medicament);
        if (!category.isEmpty()) {
            QStringList medicamentsInCategory = getMedicamentsInCategory(category);
            if (!medicamentsInCategory.isEmpty()) {
                QString message = "Le médicament '" + medicament + "' est hors stock. Voici les médicaments disponibles dans la même catégorie :\n";
                for (const QString &med : medicamentsInCategory) {
                    message += "- " + med + "\n";
                }
                QMessageBox::information(this, "Médicaments disponibles", message);
            } else {
                QMessageBox::warning(this, "Stock épuisé", "Aucun médicament disponible dans cette catégorie.");
            }
        } else {
            QMessageBox::warning(this, "Médicament inconnu", "Le médicament spécifié n'existe pas dans notre stock.");
        }
        return;  // Ne pas ajouter la prescription si le médicament est hors stock
    }

    // Vérification si une prescription similaire existe déjà
    if (Prescription::exists(nomPatient, nomMedecin, medicament, dosage, frequence, duree)) {
        QMessageBox::StandardButton reply = QMessageBox::question(
            this, "Prescription Exists",
            "Une prescription similaire existe déjà. Voulez-vous la renouveler ?",
            QMessageBox::Yes | QMessageBox::No
        );

        if (reply == QMessageBox::Yes) {
            // Si le renouvellement réussit
            if (temp->renew(nomPatient, nomMedecin, medicament, dosage, frequence, duree)) {
                QMessageBox::information(this, "Renouvellement réussi", "La prescription a été renouvelée avec succès.");
            } else {
                QMessageBox::warning(this, "Erreur", "Le renouvellement a échoué.");
            }
        } else {
            // Ajouter une nouvelle prescription
            if (temp->ajouter()) {
                QMessageBox::information(this, "Ajout réussi", "Une nouvelle prescription a été ajoutée.");
            } else {
                QMessageBox::warning(this, "Erreur", "L'ajout de la prescription a échoué.");
            }
        }
    } else {
        // Ajouter une nouvelle prescription
        if (temp->ajouter()) {
            QMessageBox::information(this, "Ajout réussi", "Une nouvelle prescription a été ajoutée.");
        } else {
            QMessageBox::warning(this, "Erreur", "L'ajout de la prescription a échoué.");
        }
    }
}
*/
/*
void MainWindow::on_enregistrerButton_clicked()
{
    Prescription *temp = new Prescription();
    enregistrer(temp);

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
}

*/


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
    ui->tableView_10->setModel(Prescription::afficher());

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

        if (searchfield == "ID")
        {
            qDebug()<<"recherche scodef";
            query.prepare("SELECT * FROM PRESCRIPTION WHERE ID_PERSCRIPTION = :id");
            query.bindValue(":id", searchValue.toInt());
        }

        // Recherche par raison sociale et prepare de la req
        else {if (searchfield == "Nom")
        {
           // qDebug()<<"recherche res";
            query.prepare("SELECT * FROM PRESCRIPTION WHERE NOM_PATIENT = :nom");
            query.bindValue(":nom", searchValue);
        }
        else if (searchfield == "Nom_Medecin")
        {
           // qDebug()<<"recherche res";
            query.prepare("SELECT * FROM PRESCRIPTION WHERE NOM_MEDECIN = :nom");
            query.bindValue(":nom", searchValue);
        }
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
                ui->tableView_11->setModel(model);
                ui->tableView->resizeColumnsToContents();
        }
     }


void MainWindow :: on_trier_clicked ()
{

    this->ui->tableView->setModel(Prescription :: trier_nom());

}
void MainWindow::on_exporter_clicked() {
    // Prompt user for the client name
    bool ok;
    QString clientName = QInputDialog::getText(this, "Client Bill",
                                               "Enter client name:",
                                               QLineEdit::Normal, "", &ok);

    if (!ok || clientName.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "No client name provided.");
        return;
    }

    // Prepare SQL query to fetch client data
    QSqlQuery query;
    query.prepare("SELECT P.ID_PERSCRIPTION, P.DATE_CREATION, P.MEDICAMENT, S.PRIX_VENTE "
                  "FROM PRESCRIPTION P "
                  "JOIN STOCK S ON LOWER(P.MEDICAMENT) = LOWER(S.NOM_PRODUIT) "
                  "WHERE LOWER(P.NOM_PATIENT) = LOWER(:clientName)");

    query.bindValue(":clientName", clientName);

    if (!query.exec()) {
        qDebug() << "SQL error in generateBillForClient:" << query.lastError().text();
        QMessageBox::critical(this, "Database Error", "Failed to execute query.");
        return;
    }

    // Check if data exists for the client
    if (!query.next()) {
        QMessageBox::information(this, "No Data", "No prescriptions found for the provided client.");
        return;
    }

    // Start creating the PDF
    QString filePath = QFileDialog::getSaveFileName(this, "Save Bill as PDF",
                                                    QString("%1_Bill.pdf").arg(clientName),
                                                    "PDF Files (*.pdf)");
    if (filePath.isEmpty()) {
        QMessageBox::warning(this, "Save Error", "No file path provided.");
        return;
    }

    QPdfWriter pdfWriter(filePath);
    pdfWriter.setPageSize(QPageSize::A4);
    pdfWriter.setTitle("Client Bill");
    pdfWriter.setCreator("Pharmacy Management System");

    QPainter painter(&pdfWriter);

    // Set up a much larger font for the entire PDF content (both title and table)
    QFont font("Arial", 240);  // Making the font size 10 times bigger (240px)
    painter.setFont(font);

    // Prepare HTML content for the bill with much larger font sizes
    QString htmlContent = QString("<h1 style='font-size: 360px;'>Bill for Client: %1</h1>"
                                  "<table border='1' cellpadding='40' cellspacing='0' style='width: 100%; border-collapse: collapse;'>"
                                  "<tr>"
                                  "<th style='font-size: 240px;'>Prescription ID</th>"
                                  "<th style='font-size: 240px;'>Date</th>"
                                  "<th style='font-size: 240px;'>Medication</th>"
                                  "<th style='font-size: 240px;'>Price</th>"
                                  "</tr>").arg(clientName);

    double totalPrice = 0;

    do {
        QString prescriptionID = query.value(0).toString();
        QString date = query.value(1).toString();
        QString medication = query.value(2).toString();
        double price = query.value(3).toDouble();

        // Add a row for each prescription with much larger font
        htmlContent += QString("<tr>"
                               "<td style='font-size: 240px;'>%1</td>"
                               "<td style='font-size: 240px;'>%2</td>"
                               "<td style='font-size: 240px;'>%3</td>"
                               "<td style='font-size: 240px;'>%4</td>"
                               "</tr>").arg(prescriptionID, date, medication, QString::number(price, 'f', 2));

        totalPrice += price;
    } while (query.next());

    // Add the total price row with larger font
    htmlContent += QString("<tr>"
                           "<td colspan='3' style='text-align: right; font-size: 240px;'><strong>Total:</strong></td>"
                           "<td style='font-size: 240px;'><strong>%1</strong></td>"
                           "</tr>"
                           "</table>").arg(QString::number(totalPrice, 'f', 2));

    // Now use QTextDocument to render the HTML content to PDF
    QTextDocument doc;
    doc.setHtml(htmlContent);

    // Set default font size for QTextDocument (if desired)
    doc.setDefaultFont(font);

    // Render the HTML content in the PDF
    doc.drawContents(&painter);

    painter.end();

    QMessageBox::information(this, "Success", "Bill has been generated successfully.");
}


/*
void MainWindow::on_exporter_clicked()
{
        // Ouvrir une boîte de dialogue pour sélectionner l'emplacement de sauvegarde du fichier PDF
        QString fileName = QFileDialog::getSaveFileName(this, tr("Enregistrer PDF"), "", "*.pdf");
        if (QFileInfo(fileName).suffix().isEmpty()) {
            fileName.append(".pdf");
        }

        // Configurer l'imprimante pour la sortie PDF
        QPrinter pdfPrinter(QPrinter::HighResolution);
        pdfPrinter.setOutputFormat(QPrinter::PdfFormat);
        pdfPrinter.setOutputFileName(fileName);

        // Utiliser QPageLayout pour définir la taille de la page en A4
        QPageLayout pageLayout;
        pageLayout.setPageSize(QPageSize(QPageSize::A4));
        pdfPrinter.setPageLayout(pageLayout);

        // Initialiser le contenu HTML pour le PDF
        QString htmlContent;

        // Date actuelle
        QString todayDate = QDate::currentDate().toString("dd/MM/yyyy");

        // Construire le contenu HTML
        htmlContent += "<html><head>"
                       "<meta charset='UTF-8'>"
                       "<title>Rapport des Médicaments Demandés</title>"
                       "<style>"
                       "body { font-family: Arial, sans-serif; margin: 25px; }"
                       ".header { font-size: 18px; margin-bottom: 15px; }"
                       ".title { text-align: center; }"
                       ".title h1 { margin-bottom: 10px; }"
                       ".title h4 { margin-top: 0; }"
                       "table { width: 100%; border-collapse: collapse; margin-top: 20px; }"
                       "th, td { border: 1px solid #333; padding: 8px; text-align: left; }"
                       "th { background-color: #f0f0f0; font-weight: bold; }"
                       "</style>"
                       "</head><body>";

        // En-tête et titre
        htmlContent += "<div class='header'>Gestion des Médicaments</div>";
        htmlContent += "<div class='title'><h1>Rapport des prescriptions</h1>"
                       "<h4>Date : " + todayDate + "</h4></div>";

        // Début du tableau
        htmlContent += "<table><thead><tr>"
                       "<th>Medicament</th><th>Fréquence</th>"
                       "</tr></thead><tbody>";

        // Exécuter la requête pour obtenir toutes les prescriptions
        QSqlQuery query;
        query.prepare("SELECT medicament FROM prescription");

        if (!query.exec()) {
            QMessageBox::critical(this, "Erreur", "Erreur lors de l'exécution de la requête : " + query.lastError().text());
            return;
        }

        // Créer QMap pour compter la fréquence des médicaments
        QMap<QString, int> medicamentFrequency;
        while (query.next()) {
            QString medicament = query.value(0).toString();
            if (!medicament.isEmpty()) {
                medicamentFrequency[medicament] += 1;  // Incrémenter la fréquence
            }
        }

        // Remplir les lignes du tableau avec les médicaments et leur fréquence
        for (auto it = medicamentFrequency.begin(); it != medicamentFrequency.end(); ++it) {
            htmlContent += "<tr>";
            htmlContent += "<td>" + it.key() + "</td>";
            htmlContent += "<td>" + QString::number(it.value()) + "</td>";
            htmlContent += "</tr>";
        }

        // Fermer le tableau et le HTML
        htmlContent += "</tbody></table></body></html>";

        // Créer un document texte pour le rendu HTML
        QTextDocument document;
        document.setHtml(htmlContent);

        // Imprimer le document dans le fichier PDF
        document.print(&pdfPrinter);

        // Confirmation de succès
        QMessageBox::information(this, "Succès", "PDF généré avec succès !");
    }*/

void MainWindow::on_stat_clicked()
{
    QString queryStr = "SELECT medicament FROM prescription";
    QSqlQuery query;

    if (!query.exec(queryStr))
    {
        qDebug() << "Erreur SQL : " << query.lastError().text();
        QMessageBox::warning(this, "Erreur", "Impossible de récupérer les Medicament : " + query.lastError().text());
        return;
    }

    // Create QMap to store frequencies
    QMap<QString, int> rsFrequency;

    // Total count of medications
    int totalCount = 0;

    // Populate QMap with frequencies and calculate total count
    while (query.next())
    {
        QString rs = query.value(0).toString();
        if (!rs.isEmpty())
        {
            rsFrequency[rs] += 1;
            totalCount++;
        }
    }

    if (rsFrequency.isEmpty()) {
        QMessageBox::information(this, "Aucune donnée", "Aucune medicament trouvée dans la base de données.");
        return;
    }


    QList<QString> sortedRs = rsFrequency.keys();
    std::sort(sortedRs.begin(), sortedRs.end(), [&rsFrequency](const QString &a, const QString &b) {
        return rsFrequency[a] > rsFrequency[b];
    });


    QBarSet *set = new QBarSet("Demandes");


    foreach (const QString &rs, sortedRs)
    {
        int freq = rsFrequency[rs];
        *set << (static_cast<double>(freq) / totalCount)*100;
    }


    QBarSeries *series = new QBarSeries();
    series->append(set);


    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistiques des Medicament les Plus Demandées");
    chart->setAnimationOptions(QChart::SeriesAnimations);


    QStringList categories;
    foreach (const QString &rs, sortedRs)
    {
        categories << rs;
    }

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);


    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Fréquence (Fraction)");
    axisY->setRange(0,100);
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);


    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);


    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(chartView);
    QWidget *chartWindow = new QWidget();
    chartWindow->setLayout(layout);
    chartWindow->setWindowTitle("Statistiques des Medicament les Plus Demandées");
    chartWindow->resize(800, 600);
    chartWindow->show();
}







QStringList MainWindow::getMedicamentsInCategory( QString &category) {
    QStringList medicamentsList;

    QSqlQuery query;
    query.prepare("SELECT NOM_PRODUIT FROM STOCK WHERE categorie = :category AND quantity > 0");
    query.bindValue(":category", category);

    if (query.exec()) {
        while (query.next()) {
            medicamentsList.append(query.value(0).toString());
        }
    }

    return medicamentsList;
}


QString MainWindow::getCategoryOfMedicament(QString& medicament) {
    QSqlQuery query;
    query.prepare("SELECT CATEGORIE FROM STOCK WHERE TRIM(NOM_PRODUIT) = :medicament");
    query.bindValue(":medicament", medicament);

    if (query.exec() && query.next()) {
        return query.value(0).toString();
    }
    return "";
}


bool MainWindow::isMedicamentInStock(QString medicament) {
    QSqlQuery query;


    query.prepare("SELECT QUANTITE FROM STOCK WHERE NOM_PRODUIT = :medicament");

    QString medicamentSansGuillemets = medicament.trimmed().replace("\"", "");
    query.bindValue(":medicament", medicamentSansGuillemets);
    qDebug()<<medicamentSansGuillemets;


    if (!query.exec()) {
        qDebug() << "Erreur SQL:" << query.lastError().text();
        return false;
    }

    if (query.next()) {
        int quantite = query.value(0).toInt();
        return quantite > 0;
    }

    qDebug() << "Aucun médicament trouvé avec le nom:" << medicamentSansGuillemets;
    return false;
}





//Stock

void MainWindow::on_pushButton_ajouter_clicked() {
    // Retrieve input data from the UI elements
    int id = ui->lineEdit_idp->text().toInt();
    QString nomProduit = ui->lineEdit_nom->text();
    QString categorie = ui->comboBox_categorie->currentText();
    int quantite = ui->spinBox_quantite->value();
    QDate dateExp = ui->dateEdit_expiration->date();
    float prixAchat = ui->lineEdit_prixachat->text().toFloat();
    float prixVente = ui->lineEdit_prixvente->text().toFloat();

    // Validate inputs
    if (nomProduit.isEmpty() || categorie.isEmpty() || quantite <= 0 || prixAchat <= 0 || prixVente <= 0) {
        QMessageBox::warning(this, "Input Error", "Please fill in all required fields with valid values.");
        return;  // Exit the function if validation fails
    }

    // Price validation: Ensure that prixAchat is not greater than prixVente
    if (prixAchat > prixVente) {
        QMessageBox::warning(this, "Price Error", "The purchase price cannot be greater than the selling price.");
        return;  // Exit the function if price validation fails
    }

    // ID validation: Check if the ID already exists in the database
    Stock stock;  // Use an existing Stock object to call a method for checking if the ID is unique
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM stock WHERE id = :id");
    checkQuery.bindValue(":id", id);
    if (checkQuery.exec()) {
        checkQuery.next();
        int count = checkQuery.value(0).toInt();
        if (count > 0) {
            QMessageBox::warning(this, "ID Error", "The product ID already exists. Please choose a different ID.");
            return;  // Exit the function if the ID already exists
        }
    } else {
        qDebug() << "Error checking ID uniqueness:" << checkQuery.lastError().text();
        return;  // Exit if there is an error checking the ID
    }
    if (dateExp < QDate::currentDate()) {
            QMessageBox::warning(this, "Invalid Date", "The expiration date cannot be in the past.");
            return;
        }

    // Create a new Stock object with the provided input data
    Stock newStock(id, nomProduit, categorie, quantite, dateExp, prixAchat, prixVente);

    // Attempt to add the new stock item to the database
    if (newStock.ajouter()) {
        QMessageBox::information(this, "Success", "New product added successfully!");

        // Clear input fields after successful insertion
        ui->lineEdit_idp->clear();
        ui->lineEdit_nom->clear();
        ui->comboBox_categorie->setCurrentIndex(0);
        ui->spinBox_quantite->setValue(0);
        ui->dateEdit_expiration->setDate(QDate::currentDate());
        ui->lineEdit_prixachat->clear();
        ui->lineEdit_prixvente->clear();

        // Update the table view with the new stock data
        ui->tableView_stock->setModel(newStock.afficher());
    } else {
        QMessageBox::warning(this, "Error", "Failed to add the product.");
    }
}


void MainWindow::on_pushButton_modifier_clicked() {
    int id = ui->lineEdit_idp->text().toInt();
    QString nomProduit = ui->lineEdit_nom->text();
    QString categorie = ui->comboBox_categorie->currentText();
    int quantite = ui->spinBox_quantite->value();
    QDate dateExp = ui->dateEdit_expiration->date();
    float prixAchat = ui->lineEdit_prixachat->text().toFloat();
    float prixVente = ui->lineEdit_prixvente->text().toFloat();

    Stock stockToModify(id, nomProduit, categorie, quantite, dateExp, prixAchat, prixVente);

    if (stockToModify.modifier()) {
        QMessageBox::information(this, "Success", "Product updated successfully!");
        ui->tableView_stock->setModel(stock.afficher());
    } else {
        QMessageBox::warning(this, "Error", "ID doesn't exist. Please check the ID and try again.");
    }
}

void MainWindow::on_pushButton_afficher_clicked() {
    Stock stock;
    QSqlQueryModel* model = stock.afficher();
    if (model) {
        ui->tableView_stock->setModel(model);
    } else {
        QMessageBox::warning(this, "Error", "Failed to retrieve stock data.");
    }
}

void MainWindow::on_pushButton_supprimer_clicked() {
    int id = ui->lineEdit_idp->text().toInt();

    // Validate that the ID is not empty or invalid
    if (id <= 0) {
        QMessageBox::warning(this, "Invalid Input", "Please enter a valid numeric ID.");
        return;
    }

    Stock stock;
    // Attempt to delete the stock item with the specified ID
    if (stock.supprimer(id)) {
        QMessageBox::information(this, "Success", "Product deleted successfully!");
        ui->lineEdit_idp->clear(); // Clear the input field after successful deletion
        ui->tableView_stock->setModel(stock.afficher());
    } else {
        QMessageBox::warning(this, "Error", "ID doesn't exist. Please check the ID and try again.");
    }
    ui->tableView_stock->setModel(stock.afficher());
}

void MainWindow::on_pushButton_stats_clicked() {
    // Query the database to get the categories and their summed quantities
    QSqlQuery query;
    query.prepare("SELECT CATEGORIE, SUM(QUANTITE) AS total_quantite FROM STOCK GROUP BY CATEGORIE");

    if (!query.exec()) {
        qDebug() << "SQL Query Failed:" << query.lastError();
        QMessageBox::warning(this, "Database Error", "Failed to load categories data.");
        return;
    }

    // Initialize variables for category data and total stock
    QPieSeries *pieSeries = new QPieSeries();
    int totalStock = 0;
    QMap<QString, int> categoryQuantities;

    while (query.next()) {
        QString category = query.value(0).toString();  // Category name
        int totalQuantity = query.value(1).toInt();   // Total quantity for the category
        totalStock += totalQuantity;

        // Store the category and its total quantity
        if (!category.isEmpty() && totalQuantity > 0) {
            categoryQuantities[category] = totalQuantity;
        }
    }

    // Check if any data was loaded
    if (categoryQuantities.isEmpty()) {
        qDebug() << "No category data available.";
        QMessageBox::information(this, "No Data", "No category data to display.");
        return;
    }

    // Populate the pie series with categories and their percentages
    for (auto it = categoryQuantities.begin(); it != categoryQuantities.end(); ++it) {
        QString category = it.key();
        int totalQuantity = it.value();
        double percentage = (static_cast<double>(totalQuantity) / totalStock) * 100.0;

        QString label = QString("%1 (%2%)").arg(category).arg(percentage, 0, 'f', 1);
        QPieSlice *slice = pieSeries->append(label, totalQuantity);

        // Optionally set styling for better visualization
        slice->setLabelVisible(true);  // Show the label on the chart
    }

    // Create the chart
    QChart *chart = new QChart();
    chart->addSeries(pieSeries);
    chart->setTitle("Category Distribution in Percentage");
    chart->legend()->setVisible(false);  // Hide legend since labels are on the slices

    // Configure the graphics view to display the chart
    QGraphicsScene *scene = new QGraphicsScene(this);
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(600, 400); // Optional: Adjust size as needed
    scene->addWidget(chartView);

    // Set the scene for the graphics view
    ui->graphicsView_stats->setScene(scene);
    ui->graphicsView_stats->show();
}

void MainWindow::on_pushButton_recherche_clicked() {
    // Get the selected option and input value
    QString searchOption = ui->comboBox_recherche->currentText().trimmed();
    QString searchValue = ui->lineEdit_recherche->text().trimmed();

    if (searchOption.isEmpty() || searchValue.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please select a valid search criterion and provide input.");
        return;
    }

    QSqlQuery query;

    // Handle the "Seuil" option separately
    if (searchOption == "Seuil") {
        bool isNumeric = false;
        int seuil = searchValue.toInt(&isNumeric);

        if (!isNumeric || seuil < 0 || seuil > 999) {
            QMessageBox::warning(this, "Invalid Input", "Please enter a number between 0 and 999 for the threshold.");
            return;
        }

        // Query for products with quantities <= seuil
        query.prepare("SELECT * FROM STOCK WHERE QUANTITE <= :seuil");
        query.bindValue(":seuil", seuil);

    } else if (searchOption == "ID_Produit") {
        // Validate numeric input for ID_Produit
        bool isNumeric = false;
        int idValue = searchValue.toInt(&isNumeric);

        if (!isNumeric || idValue <= 0) {
            QMessageBox::warning(this, "Invalid Input", "Please enter a valid numeric ID.");
            return;
        }

        query.prepare("SELECT * FROM STOCK WHERE id = :id");
        query.bindValue(":id", idValue);

    } else if (searchOption == "Nom_Produit") {
        // Validate length for Nom_Produit
        if (searchValue.length() > 20) {
            QMessageBox::warning(this, "Invalid Input", "The product name is too long. Maximum 20 characters allowed.");
            return;
        }

        query.prepare("SELECT * FROM STOCK WHERE nom_produit LIKE :name");
        query.bindValue(":name", "%" + searchValue + "%");

    } else if (searchOption == "Selon_Categorie") {
        // Validate the category
        QStringList validCategories = {
            "Antalogiques", "Antibiotiques", "Digestif", "Respiratoire",
            "Vitamines et supplements", "Cosmetiques", "Anti-inflammatoires", "Paracetamol"
        };

        QString matchedCategory;
        for (const QString &category : validCategories) {
            if (category.toLower().contains(searchValue.toLower())) {
                matchedCategory = category;
                break;
            }
        }

        if (matchedCategory.isEmpty()) {
            QMessageBox::warning(this, "Invalid Input", "Invalid category. Please choose a valid one.");
            return;
        }

        query.prepare("SELECT * FROM STOCK WHERE categorie = :category");
        query.bindValue(":category", matchedCategory);

    } else {
        QMessageBox::warning(this, "Invalid Selection", "Please select a valid search criterion.");
        return;
    }

    // Execute the query and display results
    if (!query.exec()) {
        qDebug() << "Search query failed:" << query.lastError();
        QMessageBox::critical(this, "Database Error", "Failed to execute the search query.");
        return;
    }

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(query);

    if (model->rowCount() > 0) {
        ui->tableView_12->setModel(model);
        ui->tableView_12->resizeColumnsToContents(); // Adjust column sizes
    } else {
        QMessageBox::information(this, "No Results", "No products match your search criteria.");
        delete model; // Clean up memory if no results
    }
}


void MainWindow::on_pushButton_trier_clicked() {
    // Check which radio button is selected
    bool isCategorieSelected = ui->radioButton_categorie->isChecked();
    bool isQuantiteSelected = ui->radioButton_quantite->isChecked();
    bool isExpirationSelected = ui->radioButton_expiration->isChecked();

    // Ensure only one filter is selected
    int selectedFilters = isCategorieSelected + isQuantiteSelected + isExpirationSelected;
    if (selectedFilters > 1) {
        QMessageBox::warning(this, "Filter Error", "You can't select more than one filter.");
        return;
    }

    // Prepare the Stock object and variables
    Stock stock;
    QSqlQueryModel* model = nullptr;

    // Filter by category
    if (isCategorieSelected) {
        QString selectedCategory = ui->comboBox_categorie_trie->currentText().trimmed();

        // Validate the category
        QStringList validCategories = {
            "Antalogiques", "Antibiotiques", "Digestif", "Respiratoire",
            "Vitamines et supplements", "Cosmetiques", "Anti-inflammatoires", "Paracetamol"
        };

        if (!validCategories.contains(selectedCategory)) {
            QMessageBox::warning(this, "Invalid Category", "Please select a valid category.");
            return;
        }

        // Retrieve and display sorted data
        model = stock.trierParCategorie(selectedCategory);
    }

    // Filter by quantity
    else if (isQuantiteSelected) {
        QString sortOrder = ui->comboBox_ordre->currentText().trimmed();

        // Validate the sort order
        if (sortOrder != "Croissante" && sortOrder != "Decroissante") {
            QMessageBox::warning(this, "Invalid Order", "Please select a valid order (Croissante or Decroissante).");
            return;
        }

        // Retrieve and display sorted data
        bool ascending = (sortOrder == "Croissante");
        model = stock.trierParQuantite(ascending);
    }

    // Filter by expiration date
    else if (isExpirationSelected) {
        // Retrieve and display sorted data
        model = stock.trierParExpiration();
    }

    // No radio button selected
    else {
        QMessageBox::warning(this, "No Filter Selected", "Please select a filter.");
        return;
    }

    // Display results in the tableView_2
    if (model && model->rowCount() > 0) {
        ui->tableView_12->setModel(model);
    } else {
        QMessageBox::information(this, "No Results", "No data found for the selected filter.");
        delete model; // Clean up memory
    }
}

void MainWindow::on_pushButton_exportpdf_clicked() {


    // Now proceed to handle PDF generation as before

    QString filenameCriterion;
    QString filterType;

    if (ui->radioButton_categorie->isChecked()) {
        filterType = "produits_trie_par_categorie_" + ui->comboBox_categorie_trie->currentText();
        filenameCriterion = "trie_par_categorie";
    } else if (ui->radioButton_quantite->isChecked()) {
        filterType = "produits_trie_par_quantite_" + ui->comboBox_ordre->currentText();
        filenameCriterion = "trie_par_quantite";
    } else if (ui->radioButton_expiration->isChecked()) {
        filterType = "produits_trie_par_expiration";
        filenameCriterion = "trie_par_expiration";
    } else if (!ui->lineEdit_recherche->text().isEmpty()) {
        // If there's search text in lineEdit_recherche
        filterType = "produits_recherches";
        filenameCriterion = "recherche";
    } else {
        QMessageBox::warning(this, "Invalid Selection", "Please select a valid filter.");
        return;
    }

    // Construct filename with date and filter type
    QString filename = "bordeaux_des_" + filterType + "_" + QDate::currentDate().toString("yyyyMMdd") + ".pdf";
    QString filePath = QFileDialog::getSaveFileName(this, "Save PDF", filename, "*.pdf");
    if (filePath.isEmpty()) return;

    // Create a QTextDocument for PDF content
    QTextDocument doc;
    QString htmlContent;

    // Document Title (Dynamic Title)
    htmlContent += "<h1 style='text-align: center;'>Bordeaux des produits: " + filterType + "</h1>";
    htmlContent += "<hr/>";  // Separator line

    // Create HTML table for the data
    htmlContent += "<table border='1' cellpadding='4' cellspacing='0' width='100%'>"
                   "<tr>"
                   "<th>ID</th>"
                   "<th>Product Name</th>"
                   "<th>Category</th>"
                   "<th>Quantity</th>"
                   "<th>Expiration Date</th>"
                   "<th>Purchase Price</th>"
                   "<th>Selling Price</th>"
                   "</tr>";

    // Get model from tableView_2
    QAbstractItemModel* model = ui->tableView_12->model();
    if (!model) {
        QMessageBox::warning(this, "Export Failed", "No data available to export.");
        return;
    }

    // Populate table with data from the model
    for (int row = 0; row < model->rowCount(); ++row) {
        htmlContent += "<tr>";
        for (int col = 0; col < model->columnCount(); ++col) {
            QString cellData = model->data(model->index(row, col)).toString();
            htmlContent += "<td>" + cellData + "</td>";
        }
        htmlContent += "</tr>";
    }
    htmlContent += "</table>";

    // Set HTML content to the QTextDocument
    doc.setHtml(htmlContent);

    // Set up printer for PDF output
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filePath);
    printer.setPageSize(QPageSize(QPageSize::A4));

    // Print document to PDF
    doc.print(&printer);

    // Confirmation message
    QMessageBox::information(this, "Export Successful", "The PDF file has been saved to: " + filePath);
    // Disable the auto-exclusive mode (this ensures that the radio buttons don't auto-uncheck)
    ui->radioButton_categorie->setAutoExclusive(false);
    ui->radioButton_quantite->setAutoExclusive(false);
    ui->radioButton_expiration->setAutoExclusive(false);

    // Manually uncheck the radio buttons
    ui->radioButton_categorie->setChecked(false);
    ui->radioButton_quantite->setChecked(false);
    ui->radioButton_expiration->setChecked(false);

    // Optionally clear the lineEdit and combo boxes
    ui->lineEdit_recherche->clear();
    ui->comboBox_categorie_trie->setCurrentIndex(0);
    ui->comboBox_ordre->setCurrentIndex(0);
}


void MainWindow::showNotification() {
    qDebug() << "showNotification() is called.";

    // Query to get the products with quantity < 20
    QSqlQuery query;
    query.prepare("SELECT ID, NOM_PRODUIT, QUANTITE FROM STOCK WHERE QUANTITE < 20");

    if (!query.exec()) {
        qDebug() << "Error fetching products in shortage:" << query.lastError();
        return;
    }

    QString productList;
    while (query.next()) {
        int productId = query.value(0).toInt();       // ID column
        QString productName = query.value(1).toString(); // NOM_PRODUIT column
        int quantity = query.value(2).toInt();       // QUANTITE column
        productList += QString("ID: %1 - %2 (Quantity: %3)\n")
                       .arg(productId)
                       .arg(productName)
                       .arg(quantity);
    }

    if (productList.isEmpty()) {
        productList = "No products are in shortage.";
    }

    // Check if the system tray icon is supported
    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        qDebug() << "System tray not available. Falling back to QMessageBox.";
        QMessageBox::information(this, "Low Stock Alert", "Products with low stock (< 20):\n\n" + productList);
        return;
    }

    // Create the system tray icon
    QSystemTrayIcon *trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QApplication::style()->standardIcon(QStyle::SP_MessageBoxWarning));
    trayIcon->setVisible(true);

    // Show the notification
    trayIcon->showMessage(
        "Low Stock Alert",
        "Products with low stock (< 20):\n" + productList,
        QSystemTrayIcon::Warning,
        5000 // Duration in milliseconds
    );

    qDebug() << "Notification should be displayed.";
}

void MainWindow::on_sendButton_clicked()
{
    // Get the email details from the form
    QString recipient = ui->recipientLineEdit->text();
    QString subject = ui->subjectLineEdit->text();
    QString message = ui->messageTextEdit->toPlainText();

    // Check if all fields are filled
    if (recipient.isEmpty() || subject.isEmpty() || message.isEmpty()) {
        QMessageBox::warning(this, "Missing Information", "Please fill in all fields.");
        return;
    }

    // Email sending function (using curl)
    bool success = sendEmail(recipient, subject, message);

    // Show success or failure message
    if (success) {
        QMessageBox::information(this, "Success", "Email sent successfully!");
    } else {
        QMessageBox::critical(this, "Error", "Failed to send email.");
    }
}


bool MainWindow::sendEmail(const QString &recipient, const QString &subject, const QString &message)
{
    QString emailUser = "sarahba64@gmail.com";
    QString emailPassword = "fsqu phtq qjpg mgoo"; // Make sure to keep this secure
    QString smtpServer = "smtp.gmail.com";
    int smtpPort = 465; // SSL port

    QString fullBody = "Subject: " + subject + "\n\n" + message;
    QStringList arguments;
    arguments << "--url" << "smtps://" + smtpServer + ":" + QString::number(smtpPort)
              << "--ssl-reqd"
              << "--mail-from" << emailUser
              << "--mail-rcpt" << recipient
              << "--user" << emailUser + ":" + emailPassword
              << "--insecure"
              << "-T" << "-" // Use "-" to indicate input from stdin
              << "-v"; // Verbose mode to see detailed output

    QProcess curlProcess;
    curlProcess.start("curl", arguments);
    curlProcess.write(fullBody.toUtf8());
    curlProcess.closeWriteChannel();

    if (!curlProcess.waitForFinished(5000)) {
        qDebug() << "Error: Timed out waiting for curl process to finish.";
        return false;
    }

    int exitCode = curlProcess.exitCode();
    if (exitCode == 0) {
        qDebug() << "Email sent successfully!";
        return true;
    } else {
        qDebug() << "Error sending email. Exit code:" << exitCode;
        qDebug() << curlProcess.readAllStandardError();
        return false;
    }
}


/*
void MainWindow::on_pushButton_2_clicked()
{
    int numero = ui->numeroInput->text().toInt();
    QString date = ui->dateInput->text();
    QString mode = ui->modeInput->text();
    QString status = ui->statusInput->text();
    double montant = ui->montantInput->text().toDouble();

    Transactions t(numero, date, mode, status, montant);
    if (t.ajouter()) {
        QMessageBox::information(this, "Success", "Transaction ajoutée.");
    } else {
        QMessageBox::critical(this, "Erreur", "Erreur lors de l'ajout.");
    }
}

void MainWindow::on_supprimerButton_clicked()
{
    int numero = ui->numeroInput->text().toInt();
    if (trans.supprimer(numero)) {
        QMessageBox::information(this, "Success", "Transaction supprimée.");
    } else {
        QMessageBox::critical(this, "Erreur", "Erreur lors de la suppression.");
    }
}

void MainWindow::on_afficherButton_clicked()
{
    ui->tableView->setModel(trans.afficher());
}

void MainWindow::on_trierButton_clicked()
{
    QString critere = ui->critereInput->text();
    ui->tableView->setModel(trans.trier(critere));
}

void MainWindow::on_rechercherButton_clicked()
{
    QString valeur = ui->rechercheInput->text();
    ui->tableView->setModel(trans.rechercher(valeur));
}

void MainWindow::afficherStatistiques()
{
    // Affiche le total des montants
    double total = trans.calculerTotal();
    int verifiees = trans.compterTransactions("verifie");
    int nonVerifiees = trans.compterTransactions("non verifie");

    // Obtenir la transaction avec le montant maximum
    QSqlQuery maxMontant = trans.transactionMaxMontant();
    QString transactionMax;
    if (maxMontant.next()) {
        transactionMax = "Numéro: " + maxMontant.value("numero").toString() +
                         ", Montant: " + maxMontant.value("montant").toString();
    }

    // Obtenir la transaction la plus ancienne
    QSqlQuery minDate = trans.transactionMinDate();
    QString transactionMin;
    if (minDate.next()) {
        transactionMin = "Numéro: " + minDate.value("numero").toString() +
                         ", Date: " + minDate.value("dateHeure").toString();
    }

    // Affiche les résultats
    QMessageBox::information(this, "Statistiques des Transactions",
                             "Total des montants: " + QString::number(total) + "\n" +
                             "Transactions vérifiées: " + QString::number(verifiees) + "\n" +
                             "Transactions non vérifiées: " + QString::number(nonVerifiees) + "\n" +
                             "Transaction avec montant maximum: " + transactionMax + "\n" +
                             "Transaction la plus ancienne: " + transactionMin);
}

*/

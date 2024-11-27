#include "gestioncommande.h"
#include "ui_gestioncommande.h"
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
#include <QtCharts>
#include <iostream>
#include <QLineSeries>

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
    connect(ui->pushButton_verify, &QPushButton::clicked, this, &GestionCommande::on_pushButton_verify_clicked);

    arduino.is_connected = 0;



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


            int userId = 14525546; // Remplacez par l'ID utilisateur réel
            QString action = "AJOUTER";
            QString actionDetail = "Ajout d'une nouvelle commande";

            addToHistorique(userId, action, actionDetail);



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
                int userId = 14525546; // Remplacez par l'ID utilisateur réel
                QString action = "SUPPRIMER";
                QString actionDetail = "Suppression d'une commande existante";

                addToHistorique(userId, action, actionDetail);
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

            int userId = 14525546; // Remplacez par l'ID utilisateur réel
            QString action = "MODIFIER";
            QString actionDetail = "Modification d'une commande existante";

            addToHistorique(userId, action, actionDetail);
        }
}

void GestionCommande::on_pushButton_recherche_logs_clicked()
{
    // Get the User ID from the line edit
        QString userId = ui->lineEdit_id_user_logs->text();

        // Check if the User ID is valid
        if (userId.isEmpty()) {
            QMessageBox::warning(this, "Invalid Input", "Please enter a valid User ID.");
            return;
        }

        // Prepare the SQL query
        QSqlQuery query;
        query.prepare("SELECT USER_ID, ACTION, ACTIONDETAIL, TO_CHAR(DATEACTION, 'YYYY-MM-DD HH24:MI:SS') AS LOG_DATE FROM HISTORIQUE WHERE USER_ID = :userId ORDER BY DATEACTION DESC");
        query.bindValue(":userId", userId);

        // Execute the query
        if (!query.exec()) {
            QMessageBox::critical(this, "Database Error", "Failed to retrieve logs: " + query.lastError().text());
            return;
        }

        // Create the log output string
        QString logOutput;

        while (query.next()) {
            QString userId = query.value("USER_ID").toString();
            QString action = query.value("ACTION").toString();
            QString actionDetail = query.value("ACTIONDETAIL").toString();
            QString dateTime = query.value("LOG_DATE").toString();

            // Format the log as text
            logOutput += QString("User ID %1 has action (%2: %3) at %4.\n")
                             .arg(userId)
                             .arg(action)
                             .arg(actionDetail)
                             .arg(dateTime);
        }

        // Check if any logs were found
        if (logOutput.isEmpty()) {
            logOutput = "No logs found for the specified User ID.";
        }

        // Display the logs in a QTextBrowser or QTextEdit
        ui->textBrowser->setPlainText(logOutput);
}


bool GestionCommande::addToHistorique(int userId, QString &action, QString &actionDetail)
{
    // Prepare the SQL query
    QSqlQuery query;
    query.prepare("INSERT INTO HISTORIQUE (USER_ID, ACTION, ACTIONDETAIL, DATEACTION) "
                  "VALUES (:userId, :action, :actionDetail, SYSDATE)");

    // Bind values to the query
    query.bindValue(":userId", userId);
    query.bindValue(":action", action);
    query.bindValue(":actionDetail", actionDetail);

    // Execute the query and handle errors
    if (!query.exec()) {
        qDebug() << "Failed to add to HISTORIQUE: " << query.lastError().text();
        return false;
    }

    qDebug() << "Record successfully added to HISTORIQUE.";
    return true;
}
#include <QFileDialog>
#include <QImage>
#include <QPainter>
#include <QMessageBox>
#include "qrcodegen/qrcodegen.hpp"  // Include the QR code generation library



void GestionCommande::on_pushButton_qr_clicked()
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




void GestionCommande::on_pushButton_11_clicked()
{
    QString trierSelon = ui->comboBox_triselon->currentText();
    QString ordreTri = ui->comboBox_ordretri->currentText();
    ui->tableView_commande->setModel(this->CommandeTMP.afficherTri(trierSelon,ordreTri));

    ui->tableView_commande->resizeColumnsToContents();
}


void GestionCommande::on_pushButton_recherche_clicked()
{
    QString critere = ui->lineEdit_recherche->text();

    ui->tableView_commande->setModel(this->CommandeTMP.rechercher(critere));
    ui->tableView_commande->resizeColumnsToContents();
}


/*void GestionCommande::on_pushButton_2_clicked()
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


void GestionCommande::on_pushButton_connectarduino_clicked()
{
       int result = arduino.connect_arduino(); // Attempt to connect to Arduino

       if (result == 0) {
           qDebug() << "Connected to Arduino on port:" << arduino.getarduino_port_name();
           ui->label_etatarduino->setText("Connected to Arduino!"); // Update label
           arduino.is_connected = 1;

       } else if (result == 1) {
           qDebug() << "Failed to open the serial port.";
           ui->label_etatarduino->setText("Serial port busy or unavailable."); // Update label
           arduino.close_arduino();
           arduino.is_connected = 0;


       } else {
           qDebug() << "Arduino not found.";
           ui->label_etatarduino->setText("Arduino not found."); // Update label
           arduino.close_arduino();
           arduino.is_connected = 0;


       }
}

void GestionCommande::on_pushButton_recherche_produit_3_clicked()
{

    ui->comboBox_produit_3->clear();


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
        ui->comboBox_produit_3->addItem(productName);
    }


    if (ui->comboBox_produit_3->count() == 0) {
        QMessageBox::information(this, "No Products", "No products found in the database.");
    }
}

void GestionCommande::on_pushButton_Commander_clicked()
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
            ui->label->setText("Commande envoyée!"); // Update a label to confirm success
            setupSerialListener();
        } else {
            qDebug() << "Failed to send data to Arduino.";
            ui->label->setText("Erreur lors de l'envoi."); // Update a label to show failure
        }
}


void GestionCommande::setupSerialListener()
{
    QSerialPort *serial = arduino.getserial(); // Get the serial port object
    if (serial->isOpen()) {
        connect(serial, &QSerialPort::readyRead, this, &GestionCommande::onSerialDataReceived);
    } else {
        qDebug() << "Serial port is not open!";
    }
}


void GestionCommande::onSerialDataReceived()
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


void GestionCommande::pauseSerialListener()
{
        disconnect(serial, &QSerialPort::readyRead, this, &GestionCommande::onSerialDataReceived);
        qDebug() << "Serial listener paused.";
}




void GestionCommande::on_pushButton_verify_clicked()
{
    int requestedQuantity = ui->spinBox->value();

    QSqlQuery query;
    query.prepare("SELECT QUANTITE_EN_STOCK, NOM_P FROM PRODUITS WHERE NOM_P = :productName");
    query.bindValue(":productName", ui->comboBox_produit_3->currentText());  // Bind the product name to the query
    query.exec();

    if (query.next()) {
        int availableQuantity = query.value("QUANTITE_EN_STOCK").toInt();
        QString productName = query.value("NOM_P").toString();

        if (availableQuantity >= requestedQuantity) {
            QString dataToSend = "Valide";

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
            arduino.write_to_arduino("NotValide");
            qDebug() << "Not enough stock.";
        }
    } else {
        qDebug() << "Product not found in the database.";
    }
}


void GestionCommande::on_pushButton_stat_clicked()
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

void GestionCommande::on_pushButton_pdf_clicked()
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

    // Configure the printer for PDF output
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setPageSize(QPageSize::A4);  // Use QPageSize for paper size
    printer.setOutputFileName(fileName);

    // Retrieve the selected date from dateEdit_datecommande
    QString selectedDate = ui->dateEdit_datecommande->date().toString("yyyy-MM-dd");

    // Execute the filtered query
    QSqlQuery query;
    query.prepare("SELECT * FROM commandes WHERE date_Commande > TO_DATE(:selectedDate, 'YYYY-MM-DD')");
    query.bindValue(":selectedDate", selectedDate);

    if (!query.exec()) {
        QMessageBox::critical(this, "Error", "Failed to retrieve data from the database.");
        return;
    }

    // Prepare table data from the query results
    QList<QStringList> tableData;
    QStringList headers;

    if (query.first()) {
        // Capture the headers dynamically
        for (int i = 0; i < query.record().count(); ++i) {
            headers << query.record().fieldName(i);
        }
        query.previous(); // Reset query to process all rows
    }

    while (query.next()) {
        QStringList row;
        for (int i = 0; i < query.record().count(); ++i) {
            row << query.value(i).toString();
        }
        tableData.append(row);
    }

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
        << "<h3>Date selectionnee : " << selectedDate << "</h3>\n"
        << "</div>\n"

        // Begin table
        << "<table>\n";

    // Table headers
    out << "<thead><tr>";
    for (const QString &header : headers) {
        out << "<th>" << header << "</th>";
    }
    out << "</tr></thead>\n";

    // Table data
    out << "<tbody>\n";
    for (const QStringList &row : tableData) {
        out << "<tr>";
        for (const QString &cell : row) {
            out << "<td>" << cell << "</td>";
        }
        out << "</tr>";
    }
    out << "</tbody>\n";

    out << "</table>\n"
        << "</body>\n"
        << "</html>\n";

    // Write the HTML content to the PDF
    QTextDocument document;
    document.setHtml(strStream);
    document.print(&printer);

    QMessageBox::information(this, "Success", "PDF has been exported successfully!");

}

void GestionCommande::on_pushButton_destroyed() {
    // Implémentation (même si elle est vide, elle doit exister)
}

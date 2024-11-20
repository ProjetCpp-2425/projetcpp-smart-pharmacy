#include"mainwindow.h"
#include "ui_mainwindow.h"
#include "connection.h"
#include <QPushButton>
#include <QMessageBox>
#include <QFileDialog>
#include <QPdfWriter>
#include <QPainter>
#include <QFont>
#include <QPageSize>
#include <QSqlQuery>
#include <QSqlError>
#include <QMap>
#include <QString>
#include <QList>
#include <QtCharts/QBarSet>
#include <QtCharts/QBarSeries>
#include <QtCharts/QChart>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QChartView>
#include <QVBoxLayout>
#include <QWidget>
#include <algorithm>
#include <QPrinter>
#include <QtCharts/QValueAxis>
#include <string>
#include <QRegularExpression>





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
    connect (ui->b_stat,&QPushButton :: clicked ,this, &MainWindow :: on_stat_clicked);



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


}*/
void MainWindow::enregistrer(Prescription* temp) {
    bool isValid = true;

    temp->setID(Connection::get_size());
    temp->setDate_Prescription(QDate::currentDate());

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

    QString medicament = this->ui->medicament->text().trimmed();
    medicament = medicament.replace("\"", ""); // Enlève les guillemets éventuels

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

    temp->setStatut("Pending");

    if (!isValid) return;

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
    }

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
            totalCount++; // Increment total count for each valid entry
        }
    }

    if (rsFrequency.isEmpty()) {
        QMessageBox::information(this, "Aucune donnée", "Aucune medicament trouvée dans la base de données.");
        return;
    }

    // Sort results by frequency
    QList<QString> sortedRs = rsFrequency.keys();
    std::sort(sortedRs.begin(), sortedRs.end(), [&rsFrequency](const QString &a, const QString &b) {
        return rsFrequency[a] > rsFrequency[b];
    });

    // Create a bar set
    QBarSet *set = new QBarSet("Demandes");

    // Add fractions to the bar set
    foreach (const QString &rs, sortedRs)
    {
        int freq = rsFrequency[rs];
        *set << (static_cast<double>(freq) / totalCount);  // Add fraction instead of raw count
    }

    // Create a bar series
    QBarSeries *series = new QBarSeries();
    series->append(set);

    // Create the chart
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistiques des Medicament les Plus Demandées");
    chart->setAnimationOptions(QChart::SeriesAnimations);

    // Add medication names to X-axis as categories
    QStringList categories;
    foreach (const QString &rs, sortedRs)
    {
        categories << rs;
    }

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    // Set up the Y-axis for frequencies
    QValueAxis *axisY = new QValueAxis();
    axisY->setTitleText("Fréquence (Fraction)");
    axisY->setRange(0, 1); // As the values are fractions, the range is [0, 1]
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    // Create a chart view for display
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    // Display the chart in a new window
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
            medicamentsList.append(query.value(0).toString());  // Ajoute chaque médicament à la liste
        }
    }

    return medicamentsList;  // Retourne la liste des médicaments en stock dans la même catégorie
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

    // Préparation de la requête
    query.prepare("SELECT QUANTITE FROM STOCK WHERE NOM_PRODUIT = :medicament");

    // Suppression des guillemets et des espaces superflus
    QString medicamentSansGuillemets = medicament.trimmed().replace("\"", "");
    query.bindValue(":medicament", medicamentSansGuillemets);
    qDebug()<<medicamentSansGuillemets;

    // Exécution de la requête
    if (!query.exec()) {
        qDebug() << "Erreur SQL:" << query.lastError().text();
        return false; // Retourne faux si la requête échoue
    }

    // Vérification de la quantité
    if (query.next()) {
        int quantite = query.value(0).toInt();
        return quantite > 0; // Retourne vrai si la quantité est supérieure à 0
    }

    qDebug() << "Aucun médicament trouvé avec le nom:" << medicamentSansGuillemets;
    return false; // Retourne faux si aucun résultat n'est trouvé
}

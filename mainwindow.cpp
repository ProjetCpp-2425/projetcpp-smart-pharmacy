#include "mainwindow.h"
#include "arduino.h"
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include "qsqlerror.h"
#include "ui_mainwindow.h"
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


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    f(),ui(new Ui::MainWindow),model(new QSqlTableModel(this))
{
    ui->setupUi(this);
    ui->tableView->setModel(f.afficherfour());
    Arduino = new class arduino(this);
        connect(Arduino, &arduino::dataReceived, this, &MainWindow::handleArduinoData);

        if (!Arduino->connect_arduino())
        {
            QMessageBox::critical(this, "Erreur", "Impossible de se connecter à Arduino.");
}
}




MainWindow::~MainWindow()
{
    delete ui;
    delete Arduino;
}



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

fournisseurs f (codef,numerof,nomf,email,rs,produit);
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
    QString queryStr = "SELECT COUNT(*) FROM fournisseurs WHERE codef = :codef";
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
        query.prepare("SELECT * FROM fournisseurs WHERE codef = :codef");
        query.bindValue(":codef", searchValue);
    }

    // Recherche par rs
    else if (searchField == "rs")
    {
        query.prepare("SELECT * FROM fournisseurs WHERE rs = :rs");
        query.bindValue(":rs", searchValue);
    }
    else
    {
        query.prepare("SELECT * FROM fournisseurs WHERE nomf = :nomf");
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
                       "FROM fournisseurs ORDER BY codef ASC";
        }
        else if (selectedCriteria == "Nomf")
        {
            queryStr = "SELECT codef,nomf,produit "
                       "FROM fournisseurs ORDER BY nomf ASC";
        }
        else if (selectedCriteria == "Produit")
        {
            queryStr = "SELECT codef,nomf,produit  "
                       "FROM fournisseurs ORDER BY produit ASC";
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
    if (!query.exec("SELECT rs, nomf, email, numerof FROM fournisseurs ORDER BY rs, nomf"))
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
    query.prepare("SELECT code_commande, date_commande, statut_commande "
                  "FROM commandess "
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
            QString statut_commande = query.value("statut_commande").toString();
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
        query.prepare("SELECT code_commande FROM commandess WHERE TRUNC(date_commande) = TO_DATE(:date, 'YYYY-MM-DD')");
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
                    updateQuery.prepare("UPDATE commandess SET statut_commande = 'Arrivée' WHERE code_commande = :code_commande");
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



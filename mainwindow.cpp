#include "mainwindow.h"
#include <QPdfWriter>
#include <QPainter>
#include <QFileDialog>
#include "qsqlerror.h"
#include "ui_mainwindow.h"
#include <QSqlQuery>
#include "fournisseurs.h"
#include <QMessageBox>
#include <QString>
#include <QDebug>
#include <QVariant>
#include <QComboBox>
#include <QChar>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QChart>
#include <QVBoxLayout>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    f(),ui(new Ui::MainWindow),model(new QSqlTableModel(this))
{
    ui->setupUi(this);
    ui->tableView->setModel(f.afficherfour());
}

MainWindow::~MainWindow()
{
    delete ui;
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

    if (numerof <=0)
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
    QItemSelectionModel *select=this->ui->tableView->selectionModel();

    int codef =ui->lineEdit_code->text().toInt();
    int numerof =ui->lineEdit_num->text().toInt();
    QString nomf =ui->lineEdit_nom->text();
    QString email =ui->lineEdit_mail->text();
    QString rs =ui->lineEdit_rs->text();
    QString produit =ui->lineEdit_produit->text();

    bool test = f.modifier(codef,numerof,nomf,email,rs,produit);

    if(test)
    {
        QMessageBox::information(nullptr, QObject::tr("OK"),
                                 QObject::tr("Modification effectuée\n"
                                             "click Cancel to exit."), QMessageBox::Cancel);
    }
    else
    {
        QMessageBox::critical(nullptr,QObject::tr("not ok"),
                          QObject::tr("Modification non effectueé\n"
                                      "click Cancel to exit."), QMessageBox::Cancel);
    }
}


void MainWindow::on_rechercher_f_clicked()
{
    QString searchField = ui->comboBox_2->currentText();
    QString searchValue = ui->LineEdit_rech_f->text().trimmed(); // Valeur de recherche

    // Vérifier si la valeur de recherche est vide
    if (searchValue.isEmpty())
    {
        QMessageBox::warning(this, "Erreur"," Entrer une valeur");
        return;
    }

    QSqlQuery query;

    query.prepare("SELECT * FROM fournisseurs WHERE codef = :codef");
    query.bindValue(":codef", searchValue);

    // Recherche par code

    if (searchField == "codef")
    {
        qDebug()<<"recherche scodef";
        query.prepare("SELECT * FROM fournisseurs WHERE codef = :codef");
        query.bindValue(":codef", searchValue);
    }

    // Recherche par raison sociale et prepare de la req
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
            return;
    }

    // Aucune ligne dans la table
    if (model->rowCount() == 0)
    {
            QMessageBox::information(this, "Résultat", "Aucun fournisseur trouvé.");
    }
    else
    {
            ui->tableView->setModel(model); // Affichage des résultats
            ui->tableView->resizeColumnsToContents(); // Ajuste les colonnes
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
        else
        {
            ui->tableView->setModel(model);
            //ui->tableView->resizeColumnsToContents();
        }
}





void MainWindow::on_pdf_f_clicked()
{
    //enregistrement
        QString fileName = QFileDialog::getSaveFileName(nullptr, "Enregistrer le fichier PDF", "", "*.pdf");
        if (fileName.isEmpty())
            return;

        if (QFileInfo(fileName).suffix().isEmpty())
        {
            fileName.append(".pdf");
        }
//creation
            QPdfWriter pdfWriter(fileName);
            pdfWriter.setPageSize(QPageSize(QPageSize::A4));
            pdfWriter.setPageMargins(QMargins(30, 30, 30, 30));

            QPainter painter(&pdfWriter);
            int yPosition = 50;

            // Titre du PDF
            painter.setFont(QFont("Arial", 14, QFont::Bold));
            painter.drawText(0, yPosition, "liste des fournisseurs : " );
            yPosition += 30;

            painter.setFont(QFont("Arial", 10));

            // Exécuter la requête
            QSqlQuery query("SELECT codef, nomf, produit FROM fournisseurs ORDER BY codef ASC");


            if (!query.exec())
            {
                QMessageBox::critical(this, "Erreur", "Erreur lors de l'exécution de la requête : " + query.lastError().text());
                return;
            }

            // En-têtes des colonnes
            painter.drawText(0, yPosition, "codef");
            painter.drawText(50, yPosition, "nomf");
            painter.drawText(150, yPosition, "numerof");
            painter.drawText(250, yPosition, "email");
            painter.drawText(350, yPosition, "rs");
            painter.drawText(450, yPosition, "produit");
            yPosition += 20;

            // Afficher les données
                while (query.next())
                {
                    painter.drawText(0, yPosition, query.value(0).toString());
                    painter.drawText(100, yPosition, query.value(1).toString());
                    painter.drawText(300, yPosition, query.value(2).toString());
                    painter.drawText(500, yPosition, query.value(3).toString());
                    painter.drawText(700, yPosition, query.value(4).toString());
                    painter.drawText(900, yPosition, query.value(5).toString());

                yPosition += 40;

                //la page suivante
                if (yPosition > pdfWriter.height() - 50)
                {
                    pdfWriter.newPage();
                    yPosition = 50;
                }
              }

            QMessageBox::information(this, "Succès", "PDF généré !");
 }


/*
void MainWindow::on_stat_f_clicked()
{
//raison
    QtCharts::QPieSeries *seriesRaisonSociale = new QtCharts::QPieSeries();

    // Exécuter la requête
    QSqlQuery queryRaisonSociale("SELECT rs, COUNT(*) FROM fournisseurs GROUP BY rs");
    if (!queryRaisonSociale.exec()) {
        QMessageBox::critical(this, "Erreur", "Erreur lors de l'exécution de la requête : " + queryRaisonSociale.lastError().text());
        return;
    }

    // Remplir avec données
    while (queryRaisonSociale.next()) {
        QString raisonSociale = queryRaisonSociale.value(0).toString();
        int count = queryRaisonSociale.value(1).toInt();
        seriesRaisonSociale->append(raisonSociale, count);
    }

    // produits
    QtCharts::QPieSeries *seriesProduit = new QtCharts::QPieSeries();

    // Exécuter la requête pour les produits
    QSqlQuery queryProduit("SELECT produit, COUNT(*) FROM fournisseurs GROUP BY produit");
    if (!queryProduit.exec()) {
        QMessageBox::critical(this, "Erreur", "Erreur lors de l'exécution de la requête : " + queryProduit.lastError().text());
        return;
    }
}
*/

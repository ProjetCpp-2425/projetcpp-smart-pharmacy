#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ajouterButton_clicked()
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

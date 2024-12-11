#include "login.h"
#include "ui_login.h"
#include<QMessageBox>
#include<QtDebug>
#include"employee.h"
#include "employeeui.h"
#include "sms.h"
#include <QRandomGenerator>
int login::Idg=0;
int cin1;
login::login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::login)
{
    ui->setupUi(this);
    int ret=A.connect_arduino(); // lancer la connexion à arduino
    switch(ret){
    case(0):qDebug()<< "arduino is available and connected to : "<< A.getarduino_port_name();
        break;
    case(1):qDebug() << "arduino is available but not connected to :" <<A.getarduino_port_name();
        break;
    case(-1):qDebug() << "arduino is not available";
    }
    QObject::connect(A.getserial(),SIGNAL(readyRead()),this,SLOT(update_label())); // permet de lancer
    //le slot update_label suite à la reception du signal readyRead (reception des données).
}

login::~login()
{
    delete ui;
}
void login::on_pushButton_4_clicked()
{

    int cinn = ui->line_cin->text().toInt();  // Assuming you get the CIN as input
    QString mdp = ui->line_mdp->text();      // Get the password from the line edit



    employee e;

    // Vérification si sin et le mot de passe sont valides
    if (!e.doesCINExist(cinn)) {
        QMessageBox::warning(nullptr, QObject::tr("Erreur"),
                             QObject::tr("CIN introuvable : accès refusé.\n"
                                         "Veuillez réessayer."), QMessageBox::Ok);
        A.write_to_arduino("0");
    } else if (!e.isMdpCorrect(cinn, mdp)) {
        QMessageBox::warning(nullptr, QObject::tr("Erreur"),
                             QObject::tr("Mot de passe incorrect : accès refusé.\n"
                                         "Veuillez réessayer."), QMessageBox::Ok);
        A.write_to_arduino("0");

    }
    else {
        QMessageBox::information(nullptr, QObject::tr("Valide"),
                                 QObject::tr("CIN et mot de passe corrects : accès valide.\n"
                                             "Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);
        A.write_to_arduino("1");












































































































































        // Ouvrir la fenêtre principale
        ma = new employeeUI(this);
        ma->show();
        this->close();  // Ferme la fenêtre de login
    }
}


void login::on_pushButton_2_clicked()
{
    ui->line_cin->clear();
    ui->line_mdp->clear();
    ui->stackedWidget->setCurrentIndex(1);
}

QString genererCodeOTP(int longueur = 6) {
    const QString possibleCharacters = "123456789";
    QString otp;
    QRandomGenerator randGen(QRandomGenerator::securelySeeded());  // Initialisation sécurisée avec un seed unique

    for (int i = 0; i < longueur; ++i) {
        int index = randGen.bounded(possibleCharacters.length());
        otp.append(possibleCharacters.at(index));
    }

    return otp;
}

void login::on_Envoyer_clicked()
{
     sms s;
    QString num = ui->line_numero->text();
    num = "+216" + num;
    QString otp = genererCodeOTP(6);
    cin1 = ui->line_cin_2->text().toInt();
      qDebug() << "Code OTP généré : " << otp;
    s.sendSMS( num , "Votre code de réinitialisation est:"+ otp);

      // Mise à jour du token dans la table employee
      QSqlQuery query;
      query.prepare("UPDATE employee SET jeton = :jeton WHERE cin = :cin");
      query.bindValue(":jeton", otp);
      query.bindValue(":cin", cin1);           // Le token est l'OTP généré
           // Numéro correspondant

      if (query.exec()) {
          qDebug() << "Token mis à jour avec succès pour le numéro :" ;
      } else {
          qDebug() << "Erreur lors de la mise à jour du token :" ;
      }
      ui->stackedWidget->setCurrentIndex(2);

}


void login::on_verifier_clicked()
{
    // Récupérer le jeton depuis l'interface utilisateur
    QString jeton = ui->jeton->text(); // Récupère le texte entré par l'utilisateur

    if (jeton.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer un jeton !");
        return;
    }

    // Préparer une requête SQL
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM employee WHERE jeton = :jeton");
    query.bindValue(":jeton", jeton); // Lier la valeur du jeton à la requête

    // Exécuter la requête
    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur", "Erreur lors de l'exécution de la requête SQL : ");
        return;
    }

    // Lire le résultat de la requête
    if (query.next()) {
        int count = query.value(0).toInt(); // Récupérer la première colonne du résultat
        if (count > 0) {
            QMessageBox::information(this, "Succès", "Jeton correct !");
              ui->stackedWidget->setCurrentIndex(3);
        } else {
            QMessageBox::warning(this, "Erreur", "Jeton incorrect !");
        }
    } else {
        QMessageBox::critical(this, "Erreur", "Erreur lors de la récupération des résultats.");
    }
}


/*void login::update_label(){

    data= A.read_from_arduino();

    QSqlQuery q;
    q.prepare("Select * from employee where badge = :badge");
    q.bindValue(":badge", data.toInt());
    qDebug() << data.toInt();
    q.exec();
    q.first();
    if (q.value(5).toString()!= ""){
    ui->line_cin->setText(q.value(5).toString());
        ui->line_mdp->setText(q.value(13).toString());
    QMessageBox::information(nullptr, QObject::tr("Valide"),
                             QObject::tr("Emoloyee trouvé\n"
                                         "Cliquez sur Annuler pour quitter."), QMessageBox::Cancel);


    }
    else {    QMessageBox::critical(nullptr, QObject::tr("non validé"),
                                 QObject::tr("Emoloyee non trouvé\n"
                                             "Cliquez sur Annuler pour quitter."), QMessageBox::Cancel); }



}
*/

void login::update_label() {
    // Lire les données reçues de l'Arduino
    data = A.read_from_arduino();

    // Créer et préparer la requête SQL pour rechercher l'employé en fonction du badge
    QSqlQuery q;
    q.prepare("SELECT * FROM employee WHERE badge = :badge");
    q.bindValue(":badge", data.toInt());
    qDebug() << data.toInt();

    // Exécuter la requête
    q.exec();

    // Vérifier si un employé a été trouvé avec le badge scanné
    if (q.first() && !q.value(5).toString().isEmpty()) {  // q.value(5) correspond au CIN de l'employé
        // Afficher les informations de l'employé dans les champs correspondants
        ui->line_cin->setText(q.value(5).toString());  // CIN
        ui->line_mdp->setText(q.value(13).toString()); // Mot de passe

        // Afficher un message de validation
        QMessageBox::information(nullptr, QObject::tr("Valide"),
                                 QObject::tr("Employé trouvé.\n"
                                             "Accès autorisé."),
                                 QMessageBox::Cancel);

        // Ouvrir la fenêtre principale de l'employé
        ma = new employeeUI(this);  // Instancier la fenêtre principale
        ma->show();  // Afficher la fenêtre
        this->close();  // Fermer la fenêtre de login

    } else {
        // Si l'employé n'est pas trouvé, afficher un message d'erreur
        QMessageBox::critical(nullptr, QObject::tr("Non validé"),
                              QObject::tr("Employé non trouvé.\n"
                                          "Accès refusé."),
                              QMessageBox::Cancel);
        A.write_to_arduino("0");  // Envoyer un signal à l'Arduino indiquant l'accès refusé
    }
}

void login::on_verifier_2_clicked()
{
    // Récupérer les données saisies dans l'interface
    int password1 = ui->motpasse->text().toInt();   // Nouveau mot de passe
    int password2 = ui->confirmer->text().toInt();  // Confirmation du mot de passe
                 // CIN de l'employé

     // Vérifier si les mots de passe correspondent
    if (password1 != password2) {
        QMessageBox::warning(this, "Erreur", "Les mots de passe ne correspondent pas.");
        return;
    }

    // Vérification dans la base de données
    QSqlQuery query;

    // Vérifier si le CIN existe
    query.prepare("SELECT COUNT(*) FROM employee WHERE cin = :cin");
    query.bindValue(":cin", cin1);

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur", "Erreur lors de la vérification du CIN : ");
        return;
    }

    if (query.next() && query.value(0).toInt() == 0) {

        QMessageBox::warning(this, "Erreur", "CIN introuvable.");
        return;
    }

    // Modifier le mot de passe
    query.prepare("UPDATE employee SET MDP = :MDP WHERE cin = :cin");
    query.bindValue(":MDP", password1); // Nouveau mot de passe
    query.bindValue(":cin", cin1);           // CIN de l'employé

    if (query.exec()) {
        QMessageBox::information(this, "Succès", "Mot de passe modifié avec succès !");
        ui->stackedWidget->setCurrentIndex(0);
    } else {
        QMessageBox::critical(this, "Erreur", "Erreur lors de la modification du mot de passe : ");
    }




}




#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <QSqlQuery>
#include <QString>
#include <QSqlQueryModel>
#include <QDate>

class employee
{
private:
    int numtel , cin , conge , absences;
    QString nom , adresse , email , mdp;
    QDate date_n , date_e;
    QTime horaire_debut , horaire_fin;
    float salaire , prime;
public:
    employee();
    employee(QString Nom, QDate DateN, QString Adresse, int NumTel, QString Email, int Cin,
            QDate DateE, QTime HoraireDebut, QTime HoraireFin, int Conge, int Absences,
            float Salaire, float Prime, QString Mdp);

    // Getters
    int getNumTel();
    int getCin();
    int getConge();
    int getAbsences();
    QString getNom();
    QString getAdresse();
    QString getEmail();
    QString getMdp();
    QDate getDateN();
    QDate getDateE();
    QTime getHoraireDebut();
    QTime getHoraireFin();
    float getSalaire();
    float getPrime();
    bool isPasswordCorrect(int cinn, const QString& mdp);
    bool doesSINExist(int cinn);  // Add this declaration
    bool isMdpCorrect(int cinn, const QString& mdp);  // Declaration
    bool doesCINExist(int cinn);  // Declaration





    // Setters
    void setNumTel(int numtel);
    void setCin(int cin);
    void setConge(int conge);
    void setAbsences(int absences);
    void setNom(QString nom);
    void setAdresse(QString adresse);
    void setEmail(QString email);
    void setMdp(QString mdp);
    void setDateN(QDate date_n);
    void setDateE(QDate date_e);
    void setHoraireDebut(QTime horaire_debut);
    void setHoraireFin(QTime horaire_fin);
    void setSalaire(float salaire);
    void setPrime(float prime);


    //CRUD
    bool Ajouter();
    QSqlQueryModel* afficher();
    bool Supprimer(int);
    bool modifier();
    bool reset();

    /*Recherche*/
    QSqlQueryModel *afficher_cin(QString ch);
    QSqlQueryModel *afficher_nom(QString ch);
    QSqlQueryModel *afficher_salaire(QString ch);
    /*Tri*/
    QSqlQueryModel *afficher_choix(QString choix);
    /*Statistique*/
    int statistique1();
    int statistique2();
    /*PDF*/
    employee* reademploye (int val);
};

#endif // EMPLOYEE_H

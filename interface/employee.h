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
};

#endif // EMPLOYEE_H

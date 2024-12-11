#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include "employeeui.h"
#include "arduino.h"
namespace Ui {
class login;
}

class login : public QDialog
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();
    static int Idg;
private slots:

    void on_pushButton_4_clicked();

    void on_pushButton_2_clicked();

    void on_Envoyer_clicked();

    void on_verifier_clicked();

    void on_verifier_2_clicked();
    void update_label();
private:
    Ui::login *ui;
    employeeUI *ma;

    QByteArray data; // variable contenant les données reçues

    Arduino A;

};

#endif // LOGIN_H

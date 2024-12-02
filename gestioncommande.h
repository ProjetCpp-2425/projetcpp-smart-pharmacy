#ifndef GESTIONCOMMANDE_H
#define GESTIONCOMMANDE_H

#include <QMainWindow>
#include "commande.h"
#include "arduino.h"

#include <QTimer>
#include <QSerialPort>
#include <QSerialPortInfo>

QT_BEGIN_NAMESPACE
namespace Ui { class GestionCommande; }
QT_END_NAMESPACE

class GestionCommande : public QMainWindow
{
    Q_OBJECT

public:
    GestionCommande(QWidget *parent = nullptr);
    ~GestionCommande();
    bool addToHistorique(int userId, QString &action, QString &actionDetail);

    void updateComboBoxProduitEtFournisseur();

private slots:
    void on_pushButton_recherche_produit_clicked();

    void on_pushButton_recherche_fourni_clicked();

    void on_pushButton_clicked();

    void on_pushButton_10_clicked();

    void onTableViewClicked(const QModelIndex &index);

    void on_pushButton_setModifier_clicked();

    void on_pushButton_recherche_fourni_2_clicked();

    void on_pushButton_recherche_produit_2_clicked();

    void on_pushButton_validerModifier_clicked();

    void on_pushButton_11_clicked();

    void on_pushButton_recherche_clicked();

    void on_pushButton_pdf_clicked();

    void on_pushButton_stat_clicked();

    void on_pushButton_qr_clicked();

    void on_pushButton_recherche_logs_clicked();

    void on_pushButton_destroyed();

    void on_pushButton_connectarduino_clicked();

    void on_pushButton_recherche_produit_3_clicked();


    void on_pushButton_Commander_clicked();

    void setupSerialListener();              // Setup timer for listening to serial data
    void onSerialDataReceived();
    void pauseSerialListener();

    void on_pushButton_verify_clicked();

private:
    Ui::GestionCommande *ui;
    Commande CommandeTMP;
    QTimer *serialTimer;                    // Timer for listening to serial data
    QSerialPort *serial; // Define serial as a member
    QString buffer;
};
#endif // GESTIONCOMMANDE_H

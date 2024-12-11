#ifndef MainWindow_H
#define MainWindow_H
//gestion commande
#include <QMainWindow>
#include "commande.h"
#include "arduino.h"

#include "prescription.h"



#include <QTimer>
#include <QSerialPort>
#include <QSerialPortInfo>

//gestion fournisseur
#include "fournisseurs.h"
#include <QSqlQuery>
#include <QVariant>
#include <QSqlQueryModel>
#include <QSqlTableModel>
#include <QMessageBox>
#include <QtSerialPort>

#include <QPushButton>

//Stock
#include "stock.h"
#include <QSystemTrayIcon>


//transaction
#include "transaction.h"












QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    //gestion Commande
        bool addToHistorique(int userId, QString &action, QString &actionDetail);
        void updateComboBoxProduitEtFournisseur();
    //gestion Fournisseur
        fournisseurs f;



private slots:
//gestion Commande
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
//gestion Fournisseur
    void on_validerf_clicked();
    void on_supprimerf_clicked();
    void on_modifier_f_clicked();
    void on_rechercher_f_clicked();
    void on_trier_f_clicked();
    void on_pdf_f_clicked();
    void on_stat_f_clicked();
    void on_calendrier_clicked(const QDate &date);
    void on_commandes_daujourdui_clicked();
    void handleArduinoData(const QByteArray &data);


    void on_pushButton_page_Fournisseur_clicked();


    void on_pushButton_page_Commande_clicked();

    void setActiveButtonStyle(QPushButton* activeButton);


    //prescription
    void BasculerTabAjout();
    void on_enregistrerButton_clicked();
    void on_supprimer_clicked();
    void enregistrer(Prescription * temp);
    void on_recherche_clicked();
    void on_trier_clicked ();
    void on_exporter_clicked();
    void on_stat_clicked();
    QStringList getMedicamentsInCategory(QString &category);
    QString getCategoryOfMedicament(QString &medicament);
    bool isMedicamentInStock(QString medicament);

    //void readFromArduino();
    void showSecurityAlert(const QString &code);
    void checkEmployeeCode(const QString &code);
    void logToFile(const QString &message);


    //Stock
    // Slot declarations for various UI button actions
     void on_pushButton_ajouter_clicked();   // Add item to stock
     void on_pushButton_modifier_clicked();  // Modify stock item
     void on_pushButton_afficher_clicked();  // Display stock items
     void on_pushButton_supprimer_clicked(); // Delete stock item
     void on_pushButton_recherche_clickedStock(); // Search stock items
     void on_pushButton_trier_clicked();     // Sort stock items
     void on_pushButton_exportpdf_clicked(); // Export stock details to PDF
     void on_pushButton_stats_clicked();    // Show statistics about stock
     void on_sendButton_clicked();          // Send email for certain operations

     // System tray notification functions
     void showNotification();                           // Show stock-related notifications


     // Email functionality
     bool sendEmail(const QString &recipient, const QString &subject, const QString &message);



/*
     //transaction
     void on_pushButton_2_clicked();
     void on_supprimerButton_clicked();
     void on_afficherButton_clicked();
     void on_trierButton_clicked();
     void on_rechercherButton_clicked();
     void afficherStatistiques();

*/



private:
//gestion Commande
    Ui::MainWindow *ui;
    Commande CommandeTMP;
    QTimer *serialTimer;                    // Timer for listening to serial data
    QSerialPort *serial; // Define serial as a member
    QString buffer;
    //gestion Fournisseur

    QSqlTableModel *model;
    Arduino *Arduino;
    QTimer *alertTimer;
    bool alertActive;

    //Stock
    Stock stock;              // Stock management object for handling inventory
    QSystemTrayIcon *trayIcon;



    //Employees

    //transaction
        Transactions trans;


};
#endif // MainWindow_H

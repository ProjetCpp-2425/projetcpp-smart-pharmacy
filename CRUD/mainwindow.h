#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSystemTrayIcon>
#include <QMessageBox>  // Include for potential message box usage
#include "stock.h"      // Include for stock management
#include <QString>      // Include for QString usage

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    // Constructor and Destructor
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    // Slot declarations for various UI button actions
    void on_pushButton_ajouter_clicked();   // Add item to stock
    void on_pushButton_modifier_clicked();  // Modify stock item
    void on_pushButton_afficher_clicked();  // Display stock items
    void on_pushButton_supprimer_clicked(); // Delete stock item
    void on_pushButton_recherche_clicked(); // Search stock items
    void on_pushButton_trier_clicked();     // Sort stock items
    void on_pushButton_exportpdf_clicked(); // Export stock details to PDF
    void on_pushButton_stats_clicked();    // Show statistics about stock
    void on_sendButton_clicked();          // Send email for certain operations

    // System tray notification functions
    void showNotification();                           // Show stock-related notifications


    // Email functionality
    bool sendEmail(const QString &recipient, const QString &subject, const QString &message);

private:
    Ui::MainWindow *ui;       // UI pointer for interaction with the main window
    Stock stock;              // Stock management object for handling inventory
    QSystemTrayIcon *trayIcon; // System tray icon for notifications
};

#endif // MAINWINDOW_H

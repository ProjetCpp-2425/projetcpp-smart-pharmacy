#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "prescription.h"
#include "ui_mainwindow.h"

namespace Ui {
class MainWindow;  // Forward declaration for UI class
}

class MainWindow : public QMainWindow {
    Q_OBJECT;

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void BasculerTabAjout();
    void on_enregistrerButton_clicked();
    void on_supprimer_clicked();
    void enregistrer (Prescription * temp);
    void on_recherche_clicked();
    void on_trier_clicked ();
    void on_exporter_clicked();


private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "prescription.h"
#include "ui_mainwindow.h"

namespace Ui {
class MainWindow;  // Forward declaration for UI class
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openPrescriptionCreation();
    void on_rechercheButton_clicked();
    void on_supprimerclicked();
    void on_modifierclicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
public slots:
    void on_pushButton_ajouter_clicked();
    void on_pushButton_modifier_clicked();
    void on_pushButton_afficher_clicked();
    void on_pushButton_supprimer_clicked();
    void on_pushButton_recherche_clicked();
    void on_pushButton_trier_clicked();
    void on_pushButton_exportpdf_clicked();

};

#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "fournisseurs.h"
#include <QMainWindow>
#include <QSqlQuery>
#include <QVariant>
#include <QSqlQueryModel>
#include <QMainWindow>
#include <QSqlTableModel>

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_validerf_clicked();
    void on_supprimerf_clicked();
    void on_modifier_f_clicked();
    void on_rechercher_f_clicked();
    void on_trier_f_clicked();
    void on_pdf_f_clicked();
    //void on_stat_f_clicked();

private:
    fournisseurs f;
    Ui::MainWindow *ui;
    QSqlTableModel *model;
};

#endif // MAINWINDOW_H

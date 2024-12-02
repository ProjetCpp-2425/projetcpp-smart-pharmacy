#ifndef GESTIONCOMMANDE_H
#define GESTIONCOMMANDE_H

#include <QMainWindow>
#include "commande.h"

QT_BEGIN_NAMESPACE
namespace Ui { class GestionCommande; }
QT_END_NAMESPACE

class GestionCommande : public QMainWindow
{
    Q_OBJECT

public:
    GestionCommande(QWidget *parent = nullptr);
    ~GestionCommande();

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

private:
    Ui::GestionCommande *ui;
    Commande CommandeTMP;
};
#endif // GESTIONCOMMANDE_H

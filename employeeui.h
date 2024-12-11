#ifndef EMPLOYEEUI_H
#define EMPLOYEEUI_H

#include <QDialog>
#include <QMessageBox>
#include "arduino.h"
#include "employee.h"

namespace Ui {
class employeeUI;
}

class employeeUI : public QDialog
{
    Q_OBJECT

public:
    explicit employeeUI(QWidget *parent = nullptr);
    ~employeeUI();

protected:
    void showEvent(QShowEvent *event) override;

private slots:
    void on_ajouter_clicked();

    void on_modifier_clicked();

    void on_del_clicked();

    void on_pushButton_rech_clicked();

    void on_comboBox_tri_currentIndexChanged(int index);

    void on_pushButton_stat_clicked();

    void on_pushButton_pdf_clicked();

    void on_pushButton_clicked();

    void on_tableView_clicked(const QModelIndex &index);





private:
    Ui::employeeUI *ui;
    employee e;
    QByteArray data; // variable contenant les données reçues

    Arduino A; // objet temporaire
};

#endif // EMPLOYEEUI_H

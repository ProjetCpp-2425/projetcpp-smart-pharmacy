#ifndef PRESCRIPTIONCREATION_H
#define PRESCRIPTIONCREATION_H

#include <QMainWindow>
#include "ui_PrescriptionCreation.h"
class PrescriptionCreation : public QMainWindow {
    Q_OBJECT

public:
    PrescriptionCreation(QWidget *parent = nullptr);


private slots:
    void onSubmit();

private:
    Ui :: PrescriptionCreation ui;
};

#endif

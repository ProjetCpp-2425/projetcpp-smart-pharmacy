#include "modification.h"
#include "ui_modification.h"
#include "prescription.h"

modification::modification(QWidget *parent) :QMainWindow(parent),ui(new Ui::modification)
 //PrescriptionCreation::PrescriptionCreation(QWidget *parent) : QMainWindow(parent)
{
    ui->setupUi(this);
    connect(ui->enregistrer , &QPushButton::clicked, this, &modification :: onsubmit);

}

modification::~modification()
{
    delete ui;
}


void modification :: onsubmit(int id )
{
    QString champ=ui->champ_modifier->text();
    QString nouvelle_valeure=ui->nouvelle_valeure->text();
    Prescription :: modifier(id ,champ,nouvelle_valeure);
}

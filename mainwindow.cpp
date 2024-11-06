#include "mainwindow.h"
#include "PrescriptionCreation.h"
#include "ui_mainwindow.h"
#include <QPushButton>
#include <QMessageBox>
#include "modification.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {
    ui->setupUi(this);
    connect(ui->chercher, &QPushButton::clicked, this, &MainWindow::on_rechercheButton_clicked);
    connect(ui->Create, &QPushButton::clicked, this, &MainWindow::openPrescriptionCreation);
    connect(ui->supprimer, &QPushButton::clicked, this, &MainWindow::on_supprimerclicked);
    connect (ui->modifier ,&QPushButton::clicked,this,&MainWindow::on_modifierclicked);
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::openPrescriptionCreation() {
    PrescriptionCreation *prescriptionWindow = new PrescriptionCreation(this);
    prescriptionWindow->show();
}

void MainWindow::on_rechercheButton_clicked() {
    qDebug()<< "on recherche \n";

    QString idText = ui->idRecherche->text().trimmed();
    qDebug()<< idText;
    Prescription temp;
    QSqlQueryModel* model = temp.affiche(idText.toInt());
    ui->tableaffiche->setModel(model);

}


void MainWindow::on_supprimerclicked(){
    qDebug()<< "on suppression \n";
    QString idText = ui->idRecherche->text();
    bool test = Prescription :: supprimer(idText.toInt());
    if (test)
    {
        QMessageBox ::  information (nullptr,QObject :: tr ("OK"),"Click canel to exit ",QMessageBox::Cancel);
    }
    else
    {
        QMessageBox ::  information (nullptr,QObject :: tr ("NOT OK"),"Click canel to exit",QMessageBox::Cancel);
    }

}


void MainWindow :: on_modifierclicked()
{
    qDebug()<<"fonction modofier\n";
    modification *modifierwindow = new modification(this);
    modifierwindow->show();
}

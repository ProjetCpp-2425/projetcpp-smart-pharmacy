#include "statistique.h"
#include "ui_statistique.h"

#include "employee.h"

#include <QPainter>
#include <QPaintEvent>


statistique::statistique(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::statistique)
{
    ui->setupUi(this);
}
void statistique::paintEvent(QPaintEvent *)
{
    int A = e.statistique1();
    int B = e.statistique2();
    float total = A + B;

    // Calcul des pourcentages
    float percentageA = (A / total) * 100;
    float percentageB = (B / total) * 100;

    // Création de la série de données pour le graphique
    QPieSeries *series = new QPieSeries();
    series->append(QString("Salaire inférieur à 500 (%%1)").arg(percentageA), A);
    series->append(QString("Salaire supérieur à 500 (%%1)").arg(percentageB), B);

    // Rendre les étiquettes visibles
    for (auto slice : series->slices()) {
        slice->setLabelVisible(true);
    }

    // Configuration du graphique
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("Statistique par rapport au salaire supérieur ou inférieur à 500");

    // Affichage du graphique dans un QChartView
    QChartView *chartView = new QChartView(chart, ui->label_chat);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(850, 600);
    chartView->show();
}

statistique::~statistique()
{
    delete ui;
}


void statistique::on_pushButton_11_clicked()
{
    this->close();
}


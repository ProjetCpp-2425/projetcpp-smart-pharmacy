#include "stock.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QTableView>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlQueryModel>
#include <QPdfWriter>
#include <QPrinter>
#include <QPainter>
#include <QDate>
#include <QFileDialog>

// In the constructor or initialization method
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

}
MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_ajouter_clicked() {
    // Retrieve values from the UI
    int id = ui->lineEdit_idp->text().toInt();
    QString nomProduit = ui->lineEdit_nom->text();
    QString categorie = ui->comboBox_categorie->currentText();
    int quantite = ui->spinBox_quantite->value();
    QDate dateExp = ui->dateEdit_expiration->date();
    float prixAchat = ui->lineEdit_prixachat->text().toFloat();
    float prixVente = ui->lineEdit_prixvente->text().toFloat();

    // Create a Stock object
    Stock newStock(id, nomProduit, categorie, quantite, dateExp, prixAchat, prixVente);

    // Call the ajouter method
    if (newStock.ajouter()) {
        QMessageBox::information(this, "Success", "New product added successfully!");

        // Optionally, clear the input fields
        ui->lineEdit_idp->clear();
        ui->lineEdit_nom->clear();
        ui->comboBox_categorie->setCurrentIndex(0);
        ui->spinBox_quantite->setValue(0);
        ui->dateEdit_expiration->setDate(QDate::currentDate());
        ui->lineEdit_prixachat->clear();
        ui->lineEdit_prixvente->clear();
    } else {
        QMessageBox::warning(this, "Error", "Failed to add the product.");
    }
}

void MainWindow::on_pushButton_modifier_clicked() {
    // Retrieve the ID entered by the user
    int id = ui->lineEdit_idp->text().toInt();

    // Retrieve other values from the UI fields
    QString nomProduit = ui->lineEdit_nom->text();
    QString categorie = ui->comboBox_categorie->currentText();
    int quantite = ui->spinBox_quantite->value();
    QDate dateExp = ui->dateEdit_expiration->date();
    float prixAchat = ui->lineEdit_prixachat->text().toFloat();
    float prixVente = ui->lineEdit_prixvente->text().toFloat();

    // Create a Stock object with these values
    Stock stockToModify(id, nomProduit, categorie, quantite, dateExp, prixAchat, prixVente);

    // Try to modify the stock item
    if (stockToModify.modifier()) {
        QMessageBox::information(this, "Success", "Product updated successfully!");
    } else {
        QMessageBox::warning(this, "Error", "ID doesn't exist. Please check the ID and try again.");
    }
}
void MainWindow::on_pushButton_afficher_clicked() {
    Stock stock;
    QSqlQueryModel* model = stock.afficher();

    if (model) {
        ui->tableView_stock->setModel(model);  // Set the model on the QTableView
    } else {
        QMessageBox::warning(this, "Error", "Failed to retrieve data from stock.");
    }
}
void MainWindow::on_pushButton_supprimer_clicked() {
    // Retrieve the ID from the line edit
    int id = ui->lineEdit_idp->text().toInt();

    // Create a Stock object and attempt to delete the record
    Stock stock;
    if (stock.supprimer(id)) {
        QMessageBox::information(this, "Success", "Product deleted successfully!");
    } else {
        QMessageBox::warning(this, "Error", "ID doesn't exist. Please check the ID and try again.");
    }
}




void MainWindow::on_pushButton_recherche_clicked() {
    // Determine the search criterion from comboBox_recherche
    QString searchCriterion = ui->comboBox_recherche->currentText();
    QString inputValue = ui->lineEdit_recherche->text();
    bool isNumber = false;

    // Validate input based on search criterion
    if (searchCriterion == "recherche_par_id") {
        int idValue = inputValue.toInt(&isNumber);  // Attempt conversion and check if it's a number
        if (!isNumber) {
            QMessageBox::warning(this, "Invalid Input", "Please enter a valid number for ID.");
            return;
        }
    } else if (searchCriterion == "recherche_par_nom") {
        if (inputValue.isEmpty()) {
            QMessageBox::warning(this, "Invalid Input", "Please enter a valid product name.");
            return;
        }
    }

    // Set up the criteria for the search function
    QString criterion = (searchCriterion == "recherche_par_id") ? "id" : "nom_produit";
    QVariant value = (criterion == "id") ? QVariant(inputValue.toInt()) : QVariant(inputValue);

    // Perform the search
    Stock stock;
    QSqlQueryModel* model = stock.recherche(criterion, value);

    // Display results or show an error if no results
    if (model && model->rowCount() > 0) {
        ui->tableView_2->setModel(model);
    } else {
        QMessageBox::information(this, "No Results", "No stock item matches the search criteria.");
    }
}

void MainWindow::on_pushButton_trier_clicked() {
    // Determine the sorting criterion from comboBox_Trier
    QString sortCriterion = ui->comboBox_Trier->currentText();
    QString criterion;

    if (sortCriterion == "trier_par_date_expiration") {
        criterion = "trier_par_date_expiration";
    } else if (sortCriterion == "trier_par_quantite") {
        criterion = "trier_par_quantite";
    } else {
        QMessageBox::warning(this, "Invalid Selection", "Please select a valid sorting criterion.");
        return;
    }

    // Perform sorting
    Stock stock;
    QSqlQueryModel* model = stock.trier(criterion);

    // Display sorted results
    if (model) {
        ui->tableView_2->setModel(model);
    } else {
        QMessageBox::warning(this, "Sorting Failed", "Failed to retrieve sorted data.");
    }
}


void MainWindow::on_pushButton_exportpdf_clicked() {
    QString sortCriterion = ui->comboBox_Trier->currentText();
    QString filenameCriterion;

    if (sortCriterion == "trier_par_date_expiration") {
        filenameCriterion = "trie_par_dateexpiration";
    } else if (sortCriterion == "trier_par_quantite") {
        filenameCriterion = "trie_par_quantite";
    } else {
        QMessageBox::warning(this, "Invalid Selection", "Please select a valid sorting criterion.");
        return;
    }

    // Construct filename with date
    QString filename = filenameCriterion + "_" + QDate::currentDate().toString("yyyyMMdd") + ".pdf";
    QString filePath = QFileDialog::getSaveFileName(this, "Save PDF", filename, "*.pdf");
    if (filePath.isEmpty()) return;

    // Create a QTextDocument for PDF content
    QTextDocument doc;
    QString htmlContent;

    // Document Title
    htmlContent += "<h1 style='text-align: center;'>Stock List</h1>";
    htmlContent += "<hr/>";  // Separator line

    // Create HTML table for the data
    htmlContent += "<table border='1' cellpadding='4' cellspacing='0' width='100%'>"
                   "<tr>"
                   "<th>ID</th>"
                   "<th>Product Name</th>"
                   "<th>Category</th>"
                   "<th>Quantity</th>"
                   "<th>Expiration Date</th>"
                   "<th>Purchase Price</th>"
                   "<th>Selling Price</th>"
                   "</tr>";

    // Get model from tableView_2
    QAbstractItemModel* model = ui->tableView_2->model();
    if (!model) {
        QMessageBox::warning(this, "Export Failed", "No data available to export.");
        return;
    }

    // Populate table with data from the model
    for (int row = 0; row < model->rowCount(); ++row) {
        htmlContent += "<tr>";
        for (int col = 0; col < model->columnCount(); ++col) {
            QString cellData = model->data(model->index(row, col)).toString();
            htmlContent += "<td>" + cellData + "</td>";
        }
        htmlContent += "</tr>";
    }
    htmlContent += "</table>";

    // Set HTML content to the QTextDocument
    doc.setHtml(htmlContent);

    // Set up printer for PDF output
    QPrinter printer(QPrinter::HighResolution);
    printer.setOutputFormat(QPrinter::PdfFormat);
    printer.setOutputFileName(filePath);
    printer.setPageSize(QPageSize(QPageSize::A4));

    // Print document to PDF
    doc.print(&printer);

    // Confirmation message
    QMessageBox::information(this, "Export Successful", "The PDF file has been saved to: " + filePath);
}




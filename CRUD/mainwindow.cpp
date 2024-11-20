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
//stats
#include <QtCharts>
#include <QChartView>
#include <QPieSeries>
#include <QLineSeries>
#include <QChart>
//pdf

#include <QtGui/QPainter>
#include <QFileDialog>

#include <QtSql>
#include <QtCore>
#include <QtNetwork>
#include <QProcess>
#include <QMessageBox>
#include <QPixmap>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pixmap(" C:/Users/Youssef store/Desktop/logopharma.png");
    ui->label_5->setPixmap(pixmap);
    ui->label_5->setScaledContents(true);
}

MainWindow::~MainWindow()
{
    delete ui;
    connect(ui->sendButton, &QPushButton::clicked, this, &MainWindow::on_sendButton_clicked);
}

void MainWindow::on_pushButton_ajouter_clicked() {
    int id = ui->lineEdit_idp->text().toInt();
    QString nomProduit = ui->lineEdit_nom->text();
    QString categorie = ui->comboBox_categorie->currentText();
    int quantite = ui->spinBox_quantite->value();
    QDate dateExp = ui->dateEdit_expiration->date();
    float prixAchat = ui->lineEdit_prixachat->text().toFloat();
    float prixVente = ui->lineEdit_prixvente->text().toFloat();

    Stock newStock(id, nomProduit, categorie, quantite, dateExp, prixAchat, prixVente);

    if (newStock.ajouter()) {
        QMessageBox::information(this, "Success", "New product added successfully!");
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
    int id = ui->lineEdit_idp->text().toInt();
    QString nomProduit = ui->lineEdit_nom->text();
    QString categorie = ui->comboBox_categorie->currentText();
    int quantite = ui->spinBox_quantite->value();
    QDate dateExp = ui->dateEdit_expiration->date();
    float prixAchat = ui->lineEdit_prixachat->text().toFloat();
    float prixVente = ui->lineEdit_prixvente->text().toFloat();

    Stock stockToModify(id, nomProduit, categorie, quantite, dateExp, prixAchat, prixVente);

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
        ui->tableView_stock->setModel(model);
    } else {
        QMessageBox::warning(this, "Error", "Failed to retrieve stock data.");
    }
}

void MainWindow::on_pushButton_supprimer_clicked() {
    int id = ui->lineEdit_idp->text().toInt();

    // Validate that the ID is not empty or invalid
    if (id <= 0) {
        QMessageBox::warning(this, "Invalid Input", "Please enter a valid numeric ID.");
        return;
    }

    Stock stock;
    // Attempt to delete the stock item with the specified ID
    if (stock.supprimer(id)) {
        QMessageBox::information(this, "Success", "Product deleted successfully!");
        ui->lineEdit_idp->clear(); // Clear the input field after successful deletion
    } else {
        QMessageBox::warning(this, "Error", "ID doesn't exist. Please check the ID and try again.");
    }
}

void MainWindow::on_pushButton_recherche_clicked() {
    // Get selected search criterion and user input
    QString searchCriterion = ui->comboBox_recherche->currentText().trimmed();
    QString inputValue = ui->lineEdit_recherche->text().trimmed();

    if (searchCriterion.isEmpty() || inputValue.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please select a valid search criterion and provide input.");
        return;
    }

    QString criterion;
    QVariant value;

    // Match the search criterion
    if (searchCriterion == "ID_Produit") {
        bool isNumber = false;
        int idValue = inputValue.toInt(&isNumber);
        if (!isNumber || idValue <= 0) {
            QMessageBox::warning(this, "Invalid Input", "Please enter a valid numeric ID.");
            return;
        }
        criterion = "id";
        value = idValue;
    } else if (searchCriterion == "Nom_Produit") {
        if (inputValue.length() > 20) {
            QMessageBox::warning(this, "Invalid Input", "The product name is too long. Maximum 20 characters allowed.");
            return;
        }
        criterion = "nom_produit";
        value = inputValue;
    } else if (searchCriterion == "Selon_Categorie") {
        QStringList validCategories = {
            "Antalogiques", "Antibiotiques", "Digestif", "Respiratoire",
            "Vitamines et supplements", "Cosmetiques", "Anti-inflammatoires", "Paracetamol"
        };

        QString matchedCategory;
        for (const QString &category : validCategories) {
            if (category.toLower().contains(inputValue.toLower())) {
                matchedCategory = category;
                break;
            }
        }
        if (matchedCategory.isEmpty()) {
            QMessageBox::warning(this, "Invalid Input", "Invalid category. Please choose a valid one.");
            return;
        }
        criterion = "categorie";
        value = matchedCategory;
    } else {
        QMessageBox::warning(this, "Invalid Selection", "Please select a valid search criterion.");
        return;
    }

    // Perform the search using the Stock class
    Stock stock;
    QSqlQueryModel* model = stock.recherche(criterion, value);

    if (model && model->rowCount() > 0) {
        ui->tableView_2->setModel(model); // Display results in tableView_2
    } else {
        QMessageBox::information(this, "No Results", "No stock items match the search criteria.");
        delete model; // Clean up memory
    }
}

void MainWindow::on_pushButton_trier_clicked() {
    // Check which radio button is selected
    bool isCategorieSelected = ui->radioButton_categorie->isChecked();
    bool isQuantiteSelected = ui->radioButton_quantite->isChecked();
    bool isExpirationSelected = ui->radioButton_expiration->isChecked();

    // Ensure only one filter is selected
    int selectedFilters = isCategorieSelected + isQuantiteSelected + isExpirationSelected;
    if (selectedFilters > 1) {
        QMessageBox::warning(this, "Filter Error", "You can't select more than one filter.");
        return;
    }

    // Prepare the Stock object and variables
    Stock stock;
    QSqlQueryModel* model = nullptr;

    // Filter by category
    if (isCategorieSelected) {
        QString selectedCategory = ui->comboBox_categorie_trie->currentText().trimmed();

        // Validate the category
        QStringList validCategories = {
            "Antalogiques", "Antibiotiques", "Digestif", "Respiratoire",
            "Vitamines et supplements", "Cosmetiques", "Anti-inflammatoires", "Paracetamol"
        };

        if (!validCategories.contains(selectedCategory)) {
            QMessageBox::warning(this, "Invalid Category", "Please select a valid category.");
            return;
        }

        // Retrieve and display sorted data
        model = stock.trierParCategorie(selectedCategory);
    }

    // Filter by quantity
    else if (isQuantiteSelected) {
        QString sortOrder = ui->comboBox_ordre->currentText().trimmed();

        // Validate the sort order
        if (sortOrder != "Croissante" && sortOrder != "Decroissante") {
            QMessageBox::warning(this, "Invalid Order", "Please select a valid order (Croissante or Decroissante).");
            return;
        }

        // Retrieve and display sorted data
        bool ascending = (sortOrder == "Croissante");
        model = stock.trierParQuantite(ascending);
    }

    // Filter by expiration date
    else if (isExpirationSelected) {
        // Retrieve and display sorted data
        model = stock.trierParExpiration();
    }

    // No radio button selected
    else {
        QMessageBox::warning(this, "No Filter Selected", "Please select a filter.");
        return;
    }

    // Display results in the tableView_2
    if (model && model->rowCount() > 0) {
        ui->tableView_2->setModel(model);
    } else {
        QMessageBox::information(this, "No Results", "No data found for the selected filter.");
        delete model; // Clean up memory
    }
}

void MainWindow::on_pushButton_exportpdf_clicked() {


    // Now proceed to handle PDF generation as before

    QString filenameCriterion;
    QString filterType;

    if (ui->radioButton_categorie->isChecked()) {
        filterType = "produits_trie_par_categorie_" + ui->comboBox_categorie_trie->currentText();
        filenameCriterion = "trie_par_categorie";
    } else if (ui->radioButton_quantite->isChecked()) {
        filterType = "produits_trie_par_quantite_" + ui->comboBox_ordre->currentText();
        filenameCriterion = "trie_par_quantite";
    } else if (ui->radioButton_expiration->isChecked()) {
        filterType = "produits_trie_par_expiration";
        filenameCriterion = "trie_par_expiration";
    } else if (!ui->lineEdit_recherche->text().isEmpty()) {
        // If there's search text in lineEdit_recherche
        filterType = "produits_recherches";
        filenameCriterion = "recherche";
    } else {
        QMessageBox::warning(this, "Invalid Selection", "Please select a valid filter.");
        return;
    }

    // Construct filename with date and filter type
    QString filename = "bordeaux_des_" + filterType + "_" + QDate::currentDate().toString("yyyyMMdd") + ".pdf";
    QString filePath = QFileDialog::getSaveFileName(this, "Save PDF", filename, "*.pdf");
    if (filePath.isEmpty()) return;

    // Create a QTextDocument for PDF content
    QTextDocument doc;
    QString htmlContent;

    // Document Title (Dynamic Title)
    htmlContent += "<h1 style='text-align: center;'>Bordeaux des produits: " + filterType + "</h1>";
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
    // Disable the auto-exclusive mode (this ensures that the radio buttons don't auto-uncheck)
    ui->radioButton_categorie->setAutoExclusive(false);
    ui->radioButton_quantite->setAutoExclusive(false);
    ui->radioButton_expiration->setAutoExclusive(false);

    // Manually uncheck the radio buttons
    ui->radioButton_categorie->setChecked(false);
    ui->radioButton_quantite->setChecked(false);
    ui->radioButton_expiration->setChecked(false);

    // Optionally clear the lineEdit and combo boxes
    ui->lineEdit_recherche->clear();
    ui->comboBox_categorie_trie->setCurrentIndex(0);
    ui->comboBox_ordre->setCurrentIndex(0);
}

void MainWindow::on_pushButton_stats_clicked() {
    // Query the database to get the categories and their summed quantities
    QSqlQuery query;
    query.prepare("SELECT CATEGORIE, SUM(QUANTITE) AS total_quantite FROM STOCK GROUP BY CATEGORIE ORDER BY total_quantite ASC");

    if (!query.exec()) {
        qDebug() << "Échec de la requête SQL :" << query.lastError();
        return;
    }

    // A map to hold the categories and their corresponding quantities
    QMap<QString, int> categoryQuantities;

    while (query.next()) {
        QString category = query.value(0).toString();  // Category name
        int totalQuantity = query.value(1).toInt();  // Total quantity for that category

        // Add the category and its total quantity to the map
        categoryQuantities[category] = totalQuantity;
    }

    if (categoryQuantities.isEmpty()) {
        qDebug() << "No data found.";
        return;
    }

    // Create a pie chart series to represent the categories and quantities
    QPieSeries *pieSeries = new QPieSeries();

    // Add categories to the pie chart, where the category name is used exactly as is from the database
    for (auto it = categoryQuantities.begin(); it != categoryQuantities.end(); ++it) {
        pieSeries->append(it.key(), it.value());  // Category name (exact from DB) and its quantity
    }

    // Highlight the category with the lowest total quantity
    QString lowestCategory = categoryQuantities.key(categoryQuantities.values().first());
    int lowestQuantity = categoryQuantities.values().first();
    for (auto it = categoryQuantities.begin(); it != categoryQuantities.end(); ++it) {
        if (it.value() < lowestQuantity) {
            lowestCategory = it.key();
            lowestQuantity = it.value();
        }
    }

    // Iterate through the pie slices to set label color for the lowest quantity category
    QList<QPieSlice *> slices = pieSeries->slices();
    for (QPieSlice *slice : slices) {
        if (slice->label() == lowestCategory) {
            slice->setLabelColor(Qt::red);  // Highlight the lowest category in red
        }
    }

    // Create a chart and add the pie series
    QChart *chart = new QChart();
    chart->addSeries(pieSeries);
    chart->setTitle("Quantités par catégorie");

    // Set chart labels to visible
    pieSeries->setLabelsVisible(true);

    // Create a chart view to display the pie chart
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setFixedSize(600, 400);

    // Show the chart in a dialog
    QDialog *chartDialog = new QDialog(this);
    QVBoxLayout *layout = new QVBoxLayout(chartDialog);
    layout->addWidget(chartView);
    chartDialog->setFixedSize(650, 450);
    chartDialog->exec();
}
void MainWindow::showNotification() {
    qDebug() << "showNotification() is called.";

    // Query to get the products with quantity < 25
    QSqlQuery query;
    query.prepare("SELECT ID, NOM_PRODUIT, QUANTITE FROM STOCK WHERE QUANTITE < 25");

    if (!query.exec()) {
        qDebug() << "Error fetching products in shortage:" << query.lastError();
        return;
    }

    QString productList;
    while (query.next()) {
        int productId = query.value(0).toInt();       // ID column
        QString productName = query.value(1).toString(); // NOM_PRODUIT column
        int quantity = query.value(2).toInt();       // QUANTITE column
        productList += QString("ID: %1 - %2 (Quantity: %3)\n")
                       .arg(productId)
                       .arg(productName)
                       .arg(quantity);
    }

    if (productList.isEmpty()) {
        productList = "No products in shortage.";
    }

    // Create the notification pop-up
    QMessageBox::StandardButton reply = QMessageBox::information(this, "Les produits en rupture",
        "Products with low stock (< 25):\n\n" + productList,
        QMessageBox::Close | QMessageBox::Ok);

    if (reply == QMessageBox::Ok) {
        // Handle the response, if needed
    }
}
void MainWindow::on_sendButton_clicked()
{
    // Get the email details from the form
    QString recipient = ui->recipientLineEdit->text();
    QString subject = ui->subjectLineEdit->text();
    QString message = ui->messageTextEdit->toPlainText();

    // Check if all fields are filled
    if (recipient.isEmpty() || subject.isEmpty() || message.isEmpty()) {
        QMessageBox::warning(this, "Missing Information", "Please fill in all fields.");
        return;
    }

    // Email sending function (using curl)
    bool success = sendEmail(recipient, subject, message);

    // Show success or failure message
    if (success) {
        QMessageBox::information(this, "Success", "Email sent successfully!");
    } else {
        QMessageBox::critical(this, "Error", "Failed to send email.");
    }
}


bool MainWindow::sendEmail(const QString &recipient, const QString &subject, const QString &message)
{
    QString emailUser = "sarahba64@gmail.com";
    QString emailPassword = "fsqu phtq qjpg mgoo"; // Make sure to keep this secure
    QString smtpServer = "smtp.gmail.com";
    int smtpPort = 465; // SSL port

    QString fullBody = "Subject: " + subject + "\n\n" + message;
    QStringList arguments;
    arguments << "--url" << "smtps://" + smtpServer + ":" + QString::number(smtpPort)
              << "--ssl-reqd"
              << "--mail-from" << emailUser
              << "--mail-rcpt" << recipient
              << "--user" << emailUser + ":" + emailPassword
              << "--insecure"
              << "-T" << "-" // Use "-" to indicate input from stdin
              << "-v"; // Verbose mode to see detailed output

    QProcess curlProcess;
    curlProcess.start("curl", arguments);
    curlProcess.write(fullBody.toUtf8());
    curlProcess.closeWriteChannel();

    if (!curlProcess.waitForFinished(5000)) {
        qDebug() << "Error: Timed out waiting for curl process to finish.";
        return false;
    }

    int exitCode = curlProcess.exitCode();
    if (exitCode == 0) {
        qDebug() << "Email sent successfully!";
        return true;
    } else {
        qDebug() << "Error sending email. Exit code:" << exitCode;
        qDebug() << curlProcess.readAllStandardError();
        return false;
    }
}


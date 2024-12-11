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
#include <QString>
#include <QMap>
#include <QPieSeries>
#include <QPieSlice>
#include <QChart>
#include <QChartView>
#include <QGraphicsScene>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

#include <QSystemTrayIcon>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pic(" C:/Users/Youssef store/Desktop/logopharma.png");
    ui->lablogo->setPixmap(pic);
    ui->lablogo->setScaledContents(true);
}

MainWindow::~MainWindow()
{
    delete ui;
    connect(ui->sendButton, &QPushButton::clicked, this, &MainWindow::on_sendButton_clicked);
}

void MainWindow::on_pushButton_ajouter_clicked() {
    // Retrieve input data from the UI elements
    int id = ui->lineEdit_idp->text().toInt();
    QString nomProduit = ui->lineEdit_nom->text();
    QString categorie = ui->comboBox_categorie->currentText();
    int quantite = ui->spinBox_quantite->value();
    QDate dateExp = ui->dateEdit_expiration->date();
    float prixAchat = ui->lineEdit_prixachat->text().toFloat();
    float prixVente = ui->lineEdit_prixvente->text().toFloat();

    // Validate inputs
    if (nomProduit.isEmpty() || categorie.isEmpty() || quantite <= 0 || prixAchat <= 0 || prixVente <= 0) {
        QMessageBox::warning(this, "Input Error", "Please fill in all required fields with valid values.");
        return;  // Exit the function if validation fails
    }

    // Price validation: Ensure that prixAchat is not greater than prixVente
    if (prixAchat > prixVente) {
        QMessageBox::warning(this, "Price Error", "The purchase price cannot be greater than the selling price.");
        return;  // Exit the function if price validation fails
    }

    // ID validation: Check if the ID already exists in the database
    Stock stock;  // Use an existing Stock object to call a method for checking if the ID is unique
    QSqlQuery checkQuery;
    checkQuery.prepare("SELECT COUNT(*) FROM stock WHERE id = :id");
    checkQuery.bindValue(":id", id);
    if (checkQuery.exec()) {
        checkQuery.next();
        int count = checkQuery.value(0).toInt();
        if (count > 0) {
            QMessageBox::warning(this, "ID Error", "The product ID already exists. Please choose a different ID.");
            return;  // Exit the function if the ID already exists
        }
    } else {
        qDebug() << "Error checking ID uniqueness:" << checkQuery.lastError().text();
        return;  // Exit if there is an error checking the ID
    }
    if (dateExp < QDate::currentDate()) {
            QMessageBox::warning(this, "Invalid Date", "The expiration date cannot be in the past.");
            return;
        }

    // Create a new Stock object with the provided input data
    Stock newStock(id, nomProduit, categorie, quantite, dateExp, prixAchat, prixVente);

    // Attempt to add the new stock item to the database
    if (newStock.ajouter()) {
        QMessageBox::information(this, "Success", "New product added successfully!");

        // Clear input fields after successful insertion
        ui->lineEdit_idp->clear();
        ui->lineEdit_nom->clear();
        ui->comboBox_categorie->setCurrentIndex(0);
        ui->spinBox_quantite->setValue(0);
        ui->dateEdit_expiration->setDate(QDate::currentDate());
        ui->lineEdit_prixachat->clear();
        ui->lineEdit_prixvente->clear();

        // Update the table view with the new stock data
        ui->tableView_stock->setModel(newStock.afficher());
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
        ui->tableView_stock->setModel(stock.afficher());
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
        ui->tableView_stock->setModel(stock.afficher());
    } else {
        QMessageBox::warning(this, "Error", "ID doesn't exist. Please check the ID and try again.");
    }
    ui->tableView_stock->setModel(stock.afficher());
}

void MainWindow::on_pushButton_stats_clicked() {
    // Query the database to get the categories and their summed quantities
    QSqlQuery query;
    query.prepare("SELECT CATEGORIE, SUM(QUANTITE) AS total_quantite FROM STOCK GROUP BY CATEGORIE");

    if (!query.exec()) {
        qDebug() << "SQL Query Failed:" << query.lastError();
        QMessageBox::warning(this, "Database Error", "Failed to load categories data.");
        return;
    }

    // Initialize variables for category data and total stock
    QPieSeries *pieSeries = new QPieSeries();
    int totalStock = 0;
    QMap<QString, int> categoryQuantities;

    while (query.next()) {
        QString category = query.value(0).toString();  // Category name
        int totalQuantity = query.value(1).toInt();   // Total quantity for the category
        totalStock += totalQuantity;

        // Store the category and its total quantity
        if (!category.isEmpty() && totalQuantity > 0) {
            categoryQuantities[category] = totalQuantity;
        }
    }

    // Check if any data was loaded
    if (categoryQuantities.isEmpty()) {
        qDebug() << "No category data available.";
        QMessageBox::information(this, "No Data", "No category data to display.");
        return;
    }

    // Populate the pie series with categories and their percentages
    for (auto it = categoryQuantities.begin(); it != categoryQuantities.end(); ++it) {
        QString category = it.key();
        int totalQuantity = it.value();
        double percentage = (static_cast<double>(totalQuantity) / totalStock) * 100.0;

        QString label = QString("%1 (%2%)").arg(category).arg(percentage, 0, 'f', 1);
        QPieSlice *slice = pieSeries->append(label, totalQuantity);

        // Optionally set styling for better visualization
        slice->setLabelVisible(true);  // Show the label on the chart
    }

    // Create the chart
    QChart *chart = new QChart();
    chart->addSeries(pieSeries);
    chart->setTitle("Category Distribution in Percentage");
    chart->legend()->setVisible(false);  // Hide legend since labels are on the slices

    // Configure the graphics view to display the chart
    QGraphicsScene *scene = new QGraphicsScene(this);
    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setMinimumSize(600, 400); // Optional: Adjust size as needed
    scene->addWidget(chartView);

    // Set the scene for the graphics view
    ui->graphicsView_stats->setScene(scene);
    ui->graphicsView_stats->show();
}

void MainWindow::on_pushButton_recherche_clicked() {
    // Get the selected option and input value
    QString searchOption = ui->comboBox_recherche->currentText().trimmed();
    QString searchValue = ui->lineEdit_recherche->text().trimmed();

    if (searchOption.isEmpty() || searchValue.isEmpty()) {
        QMessageBox::warning(this, "Input Error", "Please select a valid search criterion and provide input.");
        return;
    }

    QSqlQuery query;

    // Handle the "Seuil" option separately
    if (searchOption == "Seuil") {
        bool isNumeric = false;
        int seuil = searchValue.toInt(&isNumeric);

        if (!isNumeric || seuil < 0 || seuil > 999) {
            QMessageBox::warning(this, "Invalid Input", "Please enter a number between 0 and 999 for the threshold.");
            return;
        }

        // Query for products with quantities <= seuil
        query.prepare("SELECT * FROM STOCK WHERE QUANTITE <= :seuil");
        query.bindValue(":seuil", seuil);

    } else if (searchOption == "ID_Produit") {
        // Validate numeric input for ID_Produit
        bool isNumeric = false;
        int idValue = searchValue.toInt(&isNumeric);

        if (!isNumeric || idValue <= 0) {
            QMessageBox::warning(this, "Invalid Input", "Please enter a valid numeric ID.");
            return;
        }

        query.prepare("SELECT * FROM STOCK WHERE id = :id");
        query.bindValue(":id", idValue);

    } else if (searchOption == "Nom_Produit") {
        // Validate length for Nom_Produit
        if (searchValue.length() > 20) {
            QMessageBox::warning(this, "Invalid Input", "The product name is too long. Maximum 20 characters allowed.");
            return;
        }

        query.prepare("SELECT * FROM STOCK WHERE nom_produit LIKE :name");
        query.bindValue(":name", "%" + searchValue + "%");

    } else if (searchOption == "Selon_Categorie") {
        // Validate the category
        QStringList validCategories = {
            "Antalogiques", "Antibiotiques", "Digestif", "Respiratoire",
            "Vitamines et supplements", "Cosmetiques", "Anti-inflammatoires", "Paracetamol"
        };

        QString matchedCategory;
        for (const QString &category : validCategories) {
            if (category.toLower().contains(searchValue.toLower())) {
                matchedCategory = category;
                break;
            }
        }

        if (matchedCategory.isEmpty()) {
            QMessageBox::warning(this, "Invalid Input", "Invalid category. Please choose a valid one.");
            return;
        }

        query.prepare("SELECT * FROM STOCK WHERE categorie = :category");
        query.bindValue(":category", matchedCategory);

    } else {
        QMessageBox::warning(this, "Invalid Selection", "Please select a valid search criterion.");
        return;
    }

    // Execute the query and display results
    if (!query.exec()) {
        qDebug() << "Search query failed:" << query.lastError();
        QMessageBox::critical(this, "Database Error", "Failed to execute the search query.");
        return;
    }

    QSqlQueryModel *model = new QSqlQueryModel();
    model->setQuery(query);

    if (model->rowCount() > 0) {
        ui->tableView_2->setModel(model);
        ui->tableView_2->resizeColumnsToContents(); // Adjust column sizes
    } else {
        QMessageBox::information(this, "No Results", "No products match your search criteria.");
        delete model; // Clean up memory if no results
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


void MainWindow::showNotification() {
    qDebug() << "showNotification() is called.";

    // Query to get the products with quantity < 20
    QSqlQuery query;
    query.prepare("SELECT ID, NOM_PRODUIT, QUANTITE FROM STOCK WHERE QUANTITE < 20");

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
        productList = "No products are in shortage.";
    }

    // Check if the system tray icon is supported
    if (!QSystemTrayIcon::isSystemTrayAvailable()) {
        qDebug() << "System tray not available. Falling back to QMessageBox.";
        QMessageBox::information(this, "Low Stock Alert", "Products with low stock (< 20):\n\n" + productList);
        return;
    }

    // Create the system tray icon
    QSystemTrayIcon *trayIcon = new QSystemTrayIcon(this);
    trayIcon->setIcon(QApplication::style()->standardIcon(QStyle::SP_MessageBoxWarning));
    trayIcon->setVisible(true);

    // Show the notification
    trayIcon->showMessage(
        "Low Stock Alert",
        "Products with low stock (< 20):\n" + productList,
        QSystemTrayIcon::Warning,
        5000 // Duration in milliseconds
    );

    qDebug() << "Notification should be displayed.";
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

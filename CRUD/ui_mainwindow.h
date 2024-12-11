/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.3.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QTabWidget *tabWidget;
    QWidget *tab_2;
    QPushButton *pushButton_6;
    QPushButton *pushButton_7;
    QLabel *label_10;
    QTabWidget *tabWidget1;
    QWidget *tabWidgetPage1;
    QGroupBox *groupBox;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLineEdit *lineEdit_nom;
    QDateEdit *dateEdit_expiration;
    QLineEdit *lineEdit_idp;
    QSpinBox *spinBox_quantite;
    QComboBox *comboBox_categorie;
    QLineEdit *lineEdit_prixachat;
    QLineEdit *lineEdit_prixvente;
    QPushButton *pushButton_ajouter;
    QPushButton *pushButton_modifier;
    QPushButton *pushButton_supprimer;
    QTableView *tableView_stock;
    QPushButton *pushButton_afficher;
    QWidget *tab_3;
    QPushButton *pushButton_recherche;
    QComboBox *comboBox_recherche;
    QLineEdit *lineEdit_recherche;
    QTableView *tableView_2;
    QPushButton *pushButton_trier;
    QPushButton *pushButton_exportpdf;
    QRadioButton *radioButton_expiration;
    QRadioButton *radioButton_quantite;
    QComboBox *comboBox_ordre;
    QRadioButton *radioButton_categorie;
    QComboBox *comboBox_categorie_trie;
    QLineEdit *recipientLineEdit;
    QLineEdit *subjectLineEdit;
    QTextEdit *messageTextEdit;
    QPushButton *sendButton;
    QPushButton *pushButton;
    QLabel *label_9;
    QLabel *label_11;
    QLabel *label_12;
    QWidget *tab;
    QGraphicsView *graphicsView_stats;
    QPushButton *pushButton_stats;
    QPushButton *pushButton_4;
    QPushButton *pushButton_3;
    QPushButton *pushButton_5;
    QLabel *lablogo;
    QLabel *label_5;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1539, 1112);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        tabWidget = new QTabWidget(centralwidget);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(10, 30, 1501, 831));
        tabWidget->setStyleSheet(QString::fromUtf8("background-color: rgb(129, 194, 100);"));
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        pushButton_6 = new QPushButton(tab_2);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        pushButton_6->setGeometry(QRect(20, 310, 111, 41));
        pushButton_6->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        pushButton_7 = new QPushButton(tab_2);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        pushButton_7->setGeometry(QRect(20, 230, 111, 41));
        pushButton_7->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_10 = new QLabel(tab_2);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(490, 20, 571, 111));
        tabWidget1 = new QTabWidget(tab_2);
        tabWidget1->setObjectName(QString::fromUtf8("tabWidget1"));
        tabWidget1->setGeometry(QRect(170, 120, 1311, 621));
        tabWidget1->setStyleSheet(QString::fromUtf8("background-color: rgb(207, 227, 251);"));
        tabWidget1->setTabBarAutoHide(false);
        tabWidgetPage1 = new QWidget();
        tabWidgetPage1->setObjectName(QString::fromUtf8("tabWidgetPage1"));
        groupBox = new QGroupBox(tabWidgetPage1);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(20, 30, 421, 441));
        groupBox->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"\n"
""));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 60, 91, 16));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 20, 81, 16));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 90, 81, 31));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(280, 90, 61, 31));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(20, 120, 71, 31));
        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(20, 160, 91, 41));
        label_8 = new QLabel(groupBox);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(20, 220, 81, 21));
        lineEdit_nom = new QLineEdit(groupBox);
        lineEdit_nom->setObjectName(QString::fromUtf8("lineEdit_nom"));
        lineEdit_nom->setGeometry(QRect(130, 50, 161, 31));
        dateEdit_expiration = new QDateEdit(groupBox);
        dateEdit_expiration->setObjectName(QString::fromUtf8("dateEdit_expiration"));
        dateEdit_expiration->setGeometry(QRect(130, 130, 101, 31));
        lineEdit_idp = new QLineEdit(groupBox);
        lineEdit_idp->setObjectName(QString::fromUtf8("lineEdit_idp"));
        lineEdit_idp->setGeometry(QRect(130, 10, 161, 31));
        spinBox_quantite = new QSpinBox(groupBox);
        spinBox_quantite->setObjectName(QString::fromUtf8("spinBox_quantite"));
        spinBox_quantite->setGeometry(QRect(350, 90, 51, 31));
        comboBox_categorie = new QComboBox(groupBox);
        comboBox_categorie->addItem(QString());
        comboBox_categorie->addItem(QString());
        comboBox_categorie->addItem(QString());
        comboBox_categorie->addItem(QString());
        comboBox_categorie->addItem(QString());
        comboBox_categorie->addItem(QString());
        comboBox_categorie->addItem(QString());
        comboBox_categorie->setObjectName(QString::fromUtf8("comboBox_categorie"));
        comboBox_categorie->setGeometry(QRect(130, 90, 141, 31));
        lineEdit_prixachat = new QLineEdit(groupBox);
        lineEdit_prixachat->setObjectName(QString::fromUtf8("lineEdit_prixachat"));
        lineEdit_prixachat->setGeometry(QRect(130, 170, 91, 31));
        lineEdit_prixvente = new QLineEdit(groupBox);
        lineEdit_prixvente->setObjectName(QString::fromUtf8("lineEdit_prixvente"));
        lineEdit_prixvente->setGeometry(QRect(130, 220, 91, 31));
        pushButton_ajouter = new QPushButton(groupBox);
        pushButton_ajouter->setObjectName(QString::fromUtf8("pushButton_ajouter"));
        pushButton_ajouter->setGeometry(QRect(150, 280, 121, 41));
        pushButton_ajouter->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 170, 0);"));
        pushButton_modifier = new QPushButton(groupBox);
        pushButton_modifier->setObjectName(QString::fromUtf8("pushButton_modifier"));
        pushButton_modifier->setGeometry(QRect(150, 330, 121, 41));
        pushButton_supprimer = new QPushButton(groupBox);
        pushButton_supprimer->setObjectName(QString::fromUtf8("pushButton_supprimer"));
        pushButton_supprimer->setGeometry(QRect(320, 20, 91, 51));
        pushButton_supprimer->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 0, 0);"));
        tableView_stock = new QTableView(tabWidgetPage1);
        tableView_stock->setObjectName(QString::fromUtf8("tableView_stock"));
        tableView_stock->setGeometry(QRect(460, 30, 771, 431));
        pushButton_afficher = new QPushButton(tabWidgetPage1);
        pushButton_afficher->setObjectName(QString::fromUtf8("pushButton_afficher"));
        pushButton_afficher->setGeometry(QRect(790, 470, 101, 51));
        pushButton_afficher->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        tabWidget1->addTab(tabWidgetPage1, QString());
        tab_3 = new QWidget();
        tab_3->setObjectName(QString::fromUtf8("tab_3"));
        pushButton_recherche = new QPushButton(tab_3);
        pushButton_recherche->setObjectName(QString::fromUtf8("pushButton_recherche"));
        pushButton_recherche->setGeometry(QRect(120, 70, 191, 41));
        pushButton_recherche->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        comboBox_recherche = new QComboBox(tab_3);
        comboBox_recherche->addItem(QString());
        comboBox_recherche->addItem(QString());
        comboBox_recherche->addItem(QString());
        comboBox_recherche->addItem(QString());
        comboBox_recherche->setObjectName(QString::fromUtf8("comboBox_recherche"));
        comboBox_recherche->setGeometry(QRect(230, 20, 161, 31));
        comboBox_recherche->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        lineEdit_recherche = new QLineEdit(tab_3);
        lineEdit_recherche->setObjectName(QString::fromUtf8("lineEdit_recherche"));
        lineEdit_recherche->setGeometry(QRect(20, 10, 201, 41));
        lineEdit_recherche->setStyleSheet(QString::fromUtf8("\n"
"background-color: rgb(255, 255, 255);"));
        tableView_2 = new QTableView(tab_3);
        tableView_2->setObjectName(QString::fromUtf8("tableView_2"));
        tableView_2->setGeometry(QRect(10, 130, 841, 361));
        tableView_2->setStyleSheet(QString::fromUtf8("background-color: rgb(210, 231, 255);"));
        pushButton_trier = new QPushButton(tab_3);
        pushButton_trier->setObjectName(QString::fromUtf8("pushButton_trier"));
        pushButton_trier->setGeometry(QRect(480, 10, 101, 51));
        pushButton_trier->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        pushButton_exportpdf = new QPushButton(tab_3);
        pushButton_exportpdf->setObjectName(QString::fromUtf8("pushButton_exportpdf"));
        pushButton_exportpdf->setGeometry(QRect(70, 510, 191, 71));
        pushButton_exportpdf->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 0, 0);"));
        radioButton_expiration = new QRadioButton(tab_3);
        radioButton_expiration->setObjectName(QString::fromUtf8("radioButton_expiration"));
        radioButton_expiration->setGeometry(QRect(600, 90, 151, 26));
        radioButton_quantite = new QRadioButton(tab_3);
        radioButton_quantite->setObjectName(QString::fromUtf8("radioButton_quantite"));
        radioButton_quantite->setGeometry(QRect(600, 50, 151, 26));
        comboBox_ordre = new QComboBox(tab_3);
        comboBox_ordre->addItem(QString());
        comboBox_ordre->addItem(QString());
        comboBox_ordre->setObjectName(QString::fromUtf8("comboBox_ordre"));
        comboBox_ordre->setGeometry(QRect(760, 50, 121, 28));
        comboBox_ordre->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        radioButton_categorie = new QRadioButton(tab_3);
        radioButton_categorie->setObjectName(QString::fromUtf8("radioButton_categorie"));
        radioButton_categorie->setGeometry(QRect(600, 10, 151, 26));
        comboBox_categorie_trie = new QComboBox(tab_3);
        comboBox_categorie_trie->addItem(QString());
        comboBox_categorie_trie->addItem(QString());
        comboBox_categorie_trie->addItem(QString());
        comboBox_categorie_trie->addItem(QString());
        comboBox_categorie_trie->addItem(QString());
        comboBox_categorie_trie->addItem(QString());
        comboBox_categorie_trie->setObjectName(QString::fromUtf8("comboBox_categorie_trie"));
        comboBox_categorie_trie->setGeometry(QRect(760, 10, 141, 31));
        comboBox_categorie_trie->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        recipientLineEdit = new QLineEdit(tab_3);
        recipientLineEdit->setObjectName(QString::fromUtf8("recipientLineEdit"));
        recipientLineEdit->setGeometry(QRect(970, 130, 321, 51));
        recipientLineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        subjectLineEdit = new QLineEdit(tab_3);
        subjectLineEdit->setObjectName(QString::fromUtf8("subjectLineEdit"));
        subjectLineEdit->setGeometry(QRect(970, 190, 171, 51));
        subjectLineEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        messageTextEdit = new QTextEdit(tab_3);
        messageTextEdit->setObjectName(QString::fromUtf8("messageTextEdit"));
        messageTextEdit->setGeometry(QRect(970, 260, 321, 201));
        messageTextEdit->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        sendButton = new QPushButton(tab_3);
        sendButton->setObjectName(QString::fromUtf8("sendButton"));
        sendButton->setGeometry(QRect(1070, 480, 131, 51));
        sendButton->setStyleSheet(QString::fromUtf8("background-color: rgb(65, 141, 255);"));
        pushButton = new QPushButton(tab_3);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(1170, 200, 101, 41));
        label_9 = new QLabel(tab_3);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(870, 140, 101, 31));
        label_11 = new QLabel(tab_3);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(920, 200, 51, 31));
        label_12 = new QLabel(tab_3);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(890, 280, 71, 41));
        tabWidget1->addTab(tab_3, QString());
        pushButton_recherche->raise();
        lineEdit_recherche->raise();
        tableView_2->raise();
        pushButton_trier->raise();
        pushButton_exportpdf->raise();
        radioButton_expiration->raise();
        radioButton_quantite->raise();
        comboBox_ordre->raise();
        radioButton_categorie->raise();
        comboBox_categorie_trie->raise();
        comboBox_recherche->raise();
        recipientLineEdit->raise();
        subjectLineEdit->raise();
        messageTextEdit->raise();
        sendButton->raise();
        pushButton->raise();
        label_9->raise();
        label_11->raise();
        label_12->raise();
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        graphicsView_stats = new QGraphicsView(tab);
        graphicsView_stats->setObjectName(QString::fromUtf8("graphicsView_stats"));
        graphicsView_stats->setGeometry(QRect(35, 51, 1201, 441));
        pushButton_stats = new QPushButton(tab);
        pushButton_stats->setObjectName(QString::fromUtf8("pushButton_stats"));
        pushButton_stats->setGeometry(QRect(510, 510, 211, 71));
        pushButton_stats->setStyleSheet(QString::fromUtf8("background-color: rgb(29, 139, 170);"));
        tabWidget1->addTab(tab, QString());
        pushButton_4 = new QPushButton(tab_2);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(20, 390, 111, 41));
        pushButton_4->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        pushButton_3 = new QPushButton(tab_2);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(20, 470, 111, 41));
        pushButton_5 = new QPushButton(tab_2);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        pushButton_5->setGeometry(QRect(20, 550, 111, 41));
        pushButton_5->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        lablogo = new QLabel(tab_2);
        lablogo->setObjectName(QString::fromUtf8("lablogo"));
        lablogo->setGeometry(QRect(20, 30, 141, 151));
        label_5 = new QLabel(tab_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 40, 161, 161));
        label_5->setPixmap(QPixmap(QString::fromUtf8("../logopharma.png")));
        label_5->setScaledContents(true);
        tabWidget->addTab(tab_2, QString());
        label_10->raise();
        pushButton_6->raise();
        pushButton_7->raise();
        tabWidget->raise();
        pushButton_4->raise();
        pushButton_3->raise();
        pushButton_5->raise();
        lablogo->raise();
        label_5->raise();
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1539, 28));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        tabWidget->setCurrentIndex(0);
        tabWidget1->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton_6->setText(QCoreApplication::translate("MainWindow", "Clients", nullptr));
        pushButton_7->setText(QCoreApplication::translate("MainWindow", "Employees", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"center\"><span style=\" font-size:48pt; font-weight:700; color:#d2e7ff;\">PharmaFlow</span></p></body></html>", nullptr));
        groupBox->setTitle(QString());
        label->setText(QCoreApplication::translate("MainWindow", "Nom Produit", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "ID Produit", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Categorie", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Quantite", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Date Exp", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Prix Achat", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Prix Vente", nullptr));
        comboBox_categorie->setItemText(0, QCoreApplication::translate("MainWindow", "Antibiotiques", nullptr));
        comboBox_categorie->setItemText(1, QCoreApplication::translate("MainWindow", "Digestif", nullptr));
        comboBox_categorie->setItemText(2, QCoreApplication::translate("MainWindow", "Respiratoire", nullptr));
        comboBox_categorie->setItemText(3, QCoreApplication::translate("MainWindow", "Vitamines et supplements", nullptr));
        comboBox_categorie->setItemText(4, QCoreApplication::translate("MainWindow", "Cosmetiques", nullptr));
        comboBox_categorie->setItemText(5, QCoreApplication::translate("MainWindow", "Anti-inflammatoires", nullptr));
        comboBox_categorie->setItemText(6, QCoreApplication::translate("MainWindow", "Paracetamol", nullptr));

        pushButton_ajouter->setText(QCoreApplication::translate("MainWindow", "Ajouter", nullptr));
        pushButton_modifier->setText(QCoreApplication::translate("MainWindow", "Modifier", nullptr));
        pushButton_supprimer->setText(QCoreApplication::translate("MainWindow", "Supprimer", nullptr));
        pushButton_afficher->setText(QCoreApplication::translate("MainWindow", "Afficher", nullptr));
        tabWidget1->setTabText(tabWidget1->indexOf(tabWidgetPage1), QCoreApplication::translate("MainWindow", "CRUD", nullptr));
        pushButton_recherche->setText(QCoreApplication::translate("MainWindow", "RECHERCHER", nullptr));
        comboBox_recherche->setItemText(0, QCoreApplication::translate("MainWindow", "ID_Produit", nullptr));
        comboBox_recherche->setItemText(1, QCoreApplication::translate("MainWindow", "Nom_Produit", nullptr));
        comboBox_recherche->setItemText(2, QCoreApplication::translate("MainWindow", "Selon_Categorie", nullptr));
        comboBox_recherche->setItemText(3, QCoreApplication::translate("MainWindow", "Seuil", nullptr));

        lineEdit_recherche->setText(QString());
        pushButton_trier->setText(QCoreApplication::translate("MainWindow", "TRIER", nullptr));
        pushButton_exportpdf->setText(QCoreApplication::translate("MainWindow", "Exporter Pdf", nullptr));
        radioButton_expiration->setText(QCoreApplication::translate("MainWindow", "Date Expiration", nullptr));
        radioButton_quantite->setText(QCoreApplication::translate("MainWindow", "Quantite en stock", nullptr));
        comboBox_ordre->setItemText(0, QCoreApplication::translate("MainWindow", "Croissante", nullptr));
        comboBox_ordre->setItemText(1, QCoreApplication::translate("MainWindow", "Decroissante", nullptr));

        radioButton_categorie->setText(QCoreApplication::translate("MainWindow", "Categorie", nullptr));
        comboBox_categorie_trie->setItemText(0, QCoreApplication::translate("MainWindow", "Antibiotiques", nullptr));
        comboBox_categorie_trie->setItemText(1, QCoreApplication::translate("MainWindow", "Digestif", nullptr));
        comboBox_categorie_trie->setItemText(2, QCoreApplication::translate("MainWindow", "Respiratoire", nullptr));
        comboBox_categorie_trie->setItemText(3, QCoreApplication::translate("MainWindow", "Cosmetiques", nullptr));
        comboBox_categorie_trie->setItemText(4, QCoreApplication::translate("MainWindow", "Anti-inflammatoires", nullptr));
        comboBox_categorie_trie->setItemText(5, QCoreApplication::translate("MainWindow", "Paracetamol", nullptr));

        recipientLineEdit->setText(QString());
        sendButton->setText(QCoreApplication::translate("MainWindow", "Envoyer", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Attacher", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Adresse Mail", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "Objet", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p align=\"right\">Mail</p></body></html>", nullptr));
        tabWidget1->setTabText(tabWidget1->indexOf(tab_3), QCoreApplication::translate("MainWindow", "Metiers", nullptr));
        pushButton_stats->setText(QCoreApplication::translate("MainWindow", "Statistiques", nullptr));
        tabWidget1->setTabText(tabWidget1->indexOf(tab), QCoreApplication::translate("MainWindow", "statistiques", nullptr));
        pushButton_4->setText(QCoreApplication::translate("MainWindow", "Fournisseurs", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "Stock", nullptr));
        pushButton_5->setText(QCoreApplication::translate("MainWindow", "Transactions", nullptr));
        lablogo->setText(QString());
        label_5->setText(QString());
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("MainWindow", "Tab 2", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

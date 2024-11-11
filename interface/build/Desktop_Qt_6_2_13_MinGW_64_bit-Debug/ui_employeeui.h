/********************************************************************************
** Form generated from reading UI file 'employeeui.ui'
**
** Created by: Qt User Interface Compiler version 6.2.13
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_EMPLOYEEUI_H
#define UI_EMPLOYEEUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTimeEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_employeeUI
{
public:
    QGroupBox *groupBox;
    QWidget *widget_2;
    QLabel *label_11;
    QWidget *widget_3;
    QWidget *widget_4;
    QLabel *label_12;
    QWidget *widget;
    QLabel *employee;
    QPushButton *ajouter;
    QLineEdit *numtel;
    QLineEdit *email;
    QLineEdit *nom;
    QLineEdit *adresse;
    QLineEdit *cin;
    QLineEdit *conge;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QLineEdit *salaire;
    QLabel *label_10;
    QDateEdit *date_n;
    QDateEdit *date_e;
    QTimeEdit *h_d;
    QTimeEdit *h_f;
    QLabel *label_13;
    QLabel *label_14;
    QLineEdit *absennce;
    QPushButton *modifier;
    QLineEdit *prime;
    QLabel *label_15;
    QLineEdit *mdp;
    QLabel *label_16;
    QPushButton *pushButton_3;
    QPushButton *del;
    QPushButton *pushButton_4;
    QLineEdit *del_line;
    QLineEdit *lineEdit_12;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QRadioButton *radioButton_3;
    QLineEdit *lineEdit_13;
    QRadioButton *radioButton_4;
    QRadioButton *radioButton_5;
    QRadioButton *radioButton_6;
    QTableView *tableView;

    void setupUi(QDialog *employeeUI)
    {
        if (employeeUI->objectName().isEmpty())
            employeeUI->setObjectName(QString::fromUtf8("employeeUI"));
        employeeUI->resize(1525, 991);
        groupBox = new QGroupBox(employeeUI);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 10, 1511, 971));
        widget_2 = new QWidget(groupBox);
        widget_2->setObjectName(QString::fromUtf8("widget_2"));
        widget_2->setGeometry(QRect(0, 60, 91, 911));
        widget_2->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 170, 0);"));
        label_11 = new QLabel(widget_2);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(10, 580, 101, 20));
        label_11->setStyleSheet(QString::fromUtf8("color: rgb(170, 255, 255);"));
        widget_3 = new QWidget(groupBox);
        widget_3->setObjectName(QString::fromUtf8("widget_3"));
        widget_3->setGeometry(QRect(0, 20, 1411, 41));
        widget_3->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 170, 0);"));
        widget_4 = new QWidget(widget_3);
        widget_4->setObjectName(QString::fromUtf8("widget_4"));
        widget_4->setGeometry(QRect(-60, 20, 1041, 31));
        label_12 = new QLabel(widget_3);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(550, 10, 181, 20));
        label_12->setMinimumSize(QSize(0, 20));
        label_12->setStyleSheet(QString::fromUtf8("font: 700 10pt \"Segoe UI\";\n"
"font: 14pt \"Segoe UI\";\n"
"color: rgb(0, 255, 255);"));
        widget = new QWidget(groupBox);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(90, 56, 191, 921));
        widget->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 255, 255);"));
        employee = new QLabel(widget);
        employee->setObjectName(QString::fromUtf8("employee"));
        employee->setGeometry(QRect(20, 30, 111, 20));
        employee->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);\n"
"font: 14pt \"Segoe UI\";\n"
"font: 12pt \"Segoe UI\";\n"
"color: rgb(0, 85, 0);\n"
"font: 9pt \"Tw Cen MT Condensed Extra Bold\";"));
        ajouter = new QPushButton(widget);
        ajouter->setObjectName(QString::fromUtf8("ajouter"));
        ajouter->setGeometry(QRect(6, 869, 83, 29));
        ajouter->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        numtel = new QLineEdit(widget);
        numtel->setObjectName(QString::fromUtf8("numtel"));
        numtel->setGeometry(QRect(30, 300, 113, 28));
        numtel->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        email = new QLineEdit(widget);
        email->setObjectName(QString::fromUtf8("email"));
        email->setGeometry(QRect(30, 350, 113, 28));
        email->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        nom = new QLineEdit(widget);
        nom->setObjectName(QString::fromUtf8("nom"));
        nom->setGeometry(QRect(30, 140, 113, 28));
        nom->setStyleSheet(QString::fromUtf8("alternate-background-color: rgb(255, 255, 255);\n"
"background-color: rgb(255, 255, 255);"));
        adresse = new QLineEdit(widget);
        adresse->setObjectName(QString::fromUtf8("adresse"));
        adresse->setGeometry(QRect(30, 250, 113, 28));
        adresse->setStyleSheet(QString::fromUtf8("alternate-background-color: rgb(255, 255, 255);\n"
"background-color: rgb(255, 255, 255);"));
        cin = new QLineEdit(widget);
        cin->setObjectName(QString::fromUtf8("cin"));
        cin->setGeometry(QRect(30, 404, 113, 28));
        cin->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        conge = new QLineEdit(widget);
        conge->setObjectName(QString::fromUtf8("conge"));
        conge->setGeometry(QRect(30, 621, 113, 28));
        conge->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 120, 111, 20));
        label->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(30, 176, 131, 20));
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(50, 230, 63, 20));
        label_3->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_4 = new QLabel(widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(60, 280, 63, 20));
        label_4->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_5 = new QLabel(widget);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(60, 330, 63, 20));
        label_5->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_6 = new QLabel(widget);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(60, 383, 63, 20));
        label_6->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_7 = new QLabel(widget);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(30, 441, 121, 20));
        label_7->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_8 = new QLabel(widget);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(20, 491, 151, 20));
        label_8->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_9 = new QLabel(widget);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(20, 601, 141, 20));
        label_9->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        salaire = new QLineEdit(widget);
        salaire->setObjectName(QString::fromUtf8("salaire"));
        salaire->setGeometry(QRect(30, 731, 113, 28));
        salaire->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_10 = new QLabel(widget);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(30, 711, 101, 20));
        label_10->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        date_n = new QDateEdit(widget);
        date_n->setObjectName(QString::fromUtf8("date_n"));
        date_n->setGeometry(QRect(30, 200, 110, 25));
        date_e = new QDateEdit(widget);
        date_e->setObjectName(QString::fromUtf8("date_e"));
        date_e->setGeometry(QRect(32, 463, 110, 25));
        h_d = new QTimeEdit(widget);
        h_d->setObjectName(QString::fromUtf8("h_d"));
        h_d->setGeometry(QRect(30, 514, 118, 25));
        h_f = new QTimeEdit(widget);
        h_f->setObjectName(QString::fromUtf8("h_f"));
        h_f->setGeometry(QRect(29, 566, 118, 25));
        label_13 = new QLabel(widget);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(19, 543, 151, 20));
        label_13->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        label_14 = new QLabel(widget);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(20, 653, 141, 20));
        label_14->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        absennce = new QLineEdit(widget);
        absennce->setObjectName(QString::fromUtf8("absennce"));
        absennce->setGeometry(QRect(30, 681, 113, 28));
        absennce->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        modifier = new QPushButton(widget);
        modifier->setObjectName(QString::fromUtf8("modifier"));
        modifier->setGeometry(QRect(99, 870, 83, 29));
        modifier->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);\n"
"color: rgb(0, 0, 0);"));
        prime = new QLineEdit(widget);
        prime->setObjectName(QString::fromUtf8("prime"));
        prime->setGeometry(QRect(30, 781, 113, 28));
        prime->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_15 = new QLabel(widget);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(30, 761, 101, 20));
        label_15->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        mdp = new QLineEdit(widget);
        mdp->setObjectName(QString::fromUtf8("mdp"));
        mdp->setGeometry(QRect(30, 831, 113, 28));
        mdp->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 255);"));
        label_16 = new QLabel(widget);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(30, 811, 101, 20));
        label_16->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 0);"));
        pushButton_3 = new QPushButton(groupBox);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(940, 850, 121, 29));
        del = new QPushButton(groupBox);
        del->setObjectName(QString::fromUtf8("del"));
        del->setGeometry(QRect(300, 220, 83, 29));
        pushButton_4 = new QPushButton(groupBox);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        pushButton_4->setGeometry(QRect(1220, 820, 83, 29));
        del_line = new QLineEdit(groupBox);
        del_line->setObjectName(QString::fromUtf8("del_line"));
        del_line->setGeometry(QRect(380, 220, 113, 28));
        lineEdit_12 = new QLineEdit(groupBox);
        lineEdit_12->setObjectName(QString::fromUtf8("lineEdit_12"));
        lineEdit_12->setGeometry(QRect(960, 160, 201, 28));
        radioButton = new QRadioButton(groupBox);
        radioButton->setObjectName(QString::fromUtf8("radioButton"));
        radioButton->setGeometry(QRect(1150, 190, 191, 26));
        radioButton_2 = new QRadioButton(groupBox);
        radioButton_2->setObjectName(QString::fromUtf8("radioButton_2"));
        radioButton_2->setGeometry(QRect(1150, 210, 112, 26));
        radioButton_3 = new QRadioButton(groupBox);
        radioButton_3->setObjectName(QString::fromUtf8("radioButton_3"));
        radioButton_3->setGeometry(QRect(1150, 230, 131, 26));
        lineEdit_13 = new QLineEdit(groupBox);
        lineEdit_13->setObjectName(QString::fromUtf8("lineEdit_13"));
        lineEdit_13->setGeometry(QRect(380, 830, 113, 28));
        radioButton_4 = new QRadioButton(groupBox);
        radioButton_4->setObjectName(QString::fromUtf8("radioButton_4"));
        radioButton_4->setGeometry(QRect(450, 860, 112, 26));
        radioButton_5 = new QRadioButton(groupBox);
        radioButton_5->setObjectName(QString::fromUtf8("radioButton_5"));
        radioButton_5->setGeometry(QRect(450, 880, 191, 26));
        radioButton_6 = new QRadioButton(groupBox);
        radioButton_6->setObjectName(QString::fromUtf8("radioButton_6"));
        radioButton_6->setGeometry(QRect(450, 900, 221, 26));
        tableView = new QTableView(groupBox);
        tableView->setObjectName(QString::fromUtf8("tableView"));
        tableView->setGeometry(QRect(310, 280, 1111, 521));
        widget_2->raise();
        widget->raise();
        pushButton_3->raise();
        del->raise();
        pushButton_4->raise();
        del_line->raise();
        lineEdit_12->raise();
        radioButton->raise();
        radioButton_2->raise();
        radioButton_3->raise();
        lineEdit_13->raise();
        radioButton_4->raise();
        radioButton_5->raise();
        radioButton_6->raise();
        tableView->raise();
        widget_3->raise();

        retranslateUi(employeeUI);

        QMetaObject::connectSlotsByName(employeeUI);
    } // setupUi

    void retranslateUi(QDialog *employeeUI)
    {
        employeeUI->setWindowTitle(QCoreApplication::translate("employeeUI", "Dialog", nullptr));
        groupBox->setTitle(QCoreApplication::translate("employeeUI", "GroupBox", nullptr));
        label_11->setText(QCoreApplication::translate("employeeUI", "Employe\303\251", nullptr));
        label_12->setText(QCoreApplication::translate("employeeUI", "PharmaFlow", nullptr));
        employee->setText(QCoreApplication::translate("employeeUI", "<html><head/><body><p><span style=\" font-size:10pt;\">Ajouter un employe\303\251</span></p><p><br/></p></body></html>", nullptr));
        ajouter->setText(QCoreApplication::translate("employeeUI", "Ajouter", nullptr));
        label->setText(QCoreApplication::translate("employeeUI", "Nom et pr\303\251nom", nullptr));
        label_2->setText(QCoreApplication::translate("employeeUI", "Date de naissance", nullptr));
        label_3->setText(QCoreApplication::translate("employeeUI", "Adresse", nullptr));
        label_4->setText(QCoreApplication::translate("employeeUI", "Num", nullptr));
        label_5->setText(QCoreApplication::translate("employeeUI", "Email", nullptr));
        label_6->setText(QCoreApplication::translate("employeeUI", "CIN", nullptr));
        label_7->setText(QCoreApplication::translate("employeeUI", "Date d'\303\251mbauche", nullptr));
        label_8->setText(QCoreApplication::translate("employeeUI", "Horaires debut", nullptr));
        label_9->setText(QCoreApplication::translate("employeeUI", "cong\303\251s ", nullptr));
        label_10->setText(QCoreApplication::translate("employeeUI", "salaire de base", nullptr));
        label_13->setText(QCoreApplication::translate("employeeUI", "Horaires fin", nullptr));
        label_14->setText(QCoreApplication::translate("employeeUI", "absennces", nullptr));
        modifier->setText(QCoreApplication::translate("employeeUI", "Modifier", nullptr));
        label_15->setText(QCoreApplication::translate("employeeUI", "prime", nullptr));
        label_16->setText(QCoreApplication::translate("employeeUI", "Mot de passe", nullptr));
        pushButton_3->setText(QCoreApplication::translate("employeeUI", "Exporter en PDF", nullptr));
        del->setText(QCoreApplication::translate("employeeUI", "supprimer", nullptr));
        pushButton_4->setText(QCoreApplication::translate("employeeUI", "statistiques", nullptr));
        lineEdit_12->setPlaceholderText(QCoreApplication::translate("employeeUI", "recherche", nullptr));
        radioButton->setText(QCoreApplication::translate("employeeUI", " Selon Nom et p\303\251nom", nullptr));
        radioButton_2->setText(QCoreApplication::translate("employeeUI", " Selon CIN", nullptr));
        radioButton_3->setText(QCoreApplication::translate("employeeUI", "Selon Adresse", nullptr));
        lineEdit_13->setText(QString());
        lineEdit_13->setPlaceholderText(QCoreApplication::translate("employeeUI", "trier par", nullptr));
        radioButton_4->setText(QCoreApplication::translate("employeeUI", "Selon l'age", nullptr));
        radioButton_5->setText(QCoreApplication::translate("employeeUI", "Selon date d'embauche ", nullptr));
        radioButton_6->setText(QCoreApplication::translate("employeeUI", "Selon les horaires de travail", nullptr));
    } // retranslateUi

};

namespace Ui {
    class employeeUI: public Ui_employeeUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_EMPLOYEEUI_H

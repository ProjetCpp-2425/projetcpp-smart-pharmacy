#ifndef CONNECTION_H
#define CONNECTION_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
#include "prescription.h"

class Connection
{
private :
        QSqlDatabase db;
public:
    Connection();
    bool createconnect();
    void closeConnection();
    bool isOpen(){
        if (this->db.isOpen())
        {
            return true ;
        }
        else {
            return false;
        }
    }


    //Creation prescription
    bool insert_prescription(Prescription &prescription);
    //lecture Prescription
    Prescription readPrescription(int prescriptionID);
};

#endif // CONNECTION_H

#ifndef CONNECTION_H
#define CONNECTION_H
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>

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



   static int get_size();
};

#endif // CONNECTION_H

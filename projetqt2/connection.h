    #ifndef CONNECTION_H
    #define CONNECTION_H
    #include <QSqlDatabase>

    class Connection
    {
    private:
    QSqlDatabase db; // Attribut de la classe Connection

    public:
    Connection();
    bool createconnection();
    void closeConnection();
    };

    #endif // CONNECTION_H

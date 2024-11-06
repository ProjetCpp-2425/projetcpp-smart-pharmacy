#ifndef MODIFICATION_H
#define MODIFICATION_H

#include <QWidget>
#include "ui_modification.h"
#include <QMainWindow>


class modification: public QMainWindow
{
        Q_OBJECT

    public:
        explicit modification(QWidget *parent = nullptr);
        ~modification();

    private:
        Ui::modification *ui;


    public slots :
        void onsubmit(int id);

};

#endif

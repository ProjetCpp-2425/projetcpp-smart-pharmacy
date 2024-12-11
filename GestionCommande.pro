QT       += core gui
QT += sql
QT += printsupport widgets charts network serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
INCLUDEPATH += $$PWD/qrcodegen

SOURCES += \
    arduino.cpp \
    commande.cpp \
    connection.cpp \
    employee.cpp \
    employeeui.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    prescription.cpp \
    qrcodegen/qrcodegen.cpp \
    fournisseurs.cpp \
    sms.cpp \
    statistique.cpp \
    stock.cpp \
    transaction.cpp



HEADERS += \
    arduino.h \
    commande.h \
    connection.h \
    employee.h \
    employeeui.h \
    login.h \
    mainwindow.h \
    prescription.h \
    qrcodegen/qrcodegen.h \
    fournisseurs.h \
    sms.h \
    statistique.h \
    stock.h \
    transaction.h


FORMS += \
    ../PULL/employeeui.ui \
    ../PULL/login.ui \
    ../PULL/statistique.ui \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    resourceImage.qrc

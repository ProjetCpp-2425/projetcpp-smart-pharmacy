QT       += core gui network serialport
greaterThan(QT_MAJOR_VERSION, 4): QT +=  widgets sql charts multimedia multimediawidgets printsupport widgets axcontainer

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    arduino.cpp \
    connexion.cpp \
    employee.cpp \
    employeeui.cpp \
    login.cpp \
    main.cpp \
    mainwindow.cpp \
    sms.cpp \
    statistique.cpp

HEADERS += \
    arduino.h \
    connexion.h \
    employee.h \
    employeeui.h \
    login.h \
    mainwindow.h \
    sms.h \
    statistique.h

FORMS += \
    employeeui.ui \
    login.ui \
    mainwindow.ui \
    statistique.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

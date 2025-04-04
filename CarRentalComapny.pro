QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Car.cpp \
    ElectricCar.cpp \
    PassengerCar.cpp \
    SportCar.cpp \
    TruckCar.cpp \
    allreservationswindow.cpp \
    main.cpp \
    mainwindow.cpp \
    menuwindow.cpp \
    reservationwindow.cpp

HEADERS += \
    Car.h \
    ElectricCar.h \
    PassengerCar.h \
    SportCar.h \
    TruckCar.h \
    allreservationswindow.h \
    mainwindow.h \
    menuwindow.h \
    reservationwindow.h

FORMS += \
    allreservationswindow.ui \
    mainwindow.ui \
    menuwindow.ui \
    reservationwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../../Downloads/car2.jpg \
    ../../Downloads/car3.jpg

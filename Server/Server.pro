QT       += core gui network sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    attackpokemon.cpp \
    defencepokemon.cpp \
    healthpokemon.cpp \
    main.cpp \
    mainwindow.cpp \
    manager.cpp \
    pokemon.cpp \
    speedpokemon.cpp

HEADERS += \
    attackpokemon.h \
    config.h \
    defencepokemon.h \
    healthpokemon.h \
    mainwindow.h \
    manager.h \
    pokemon.h \
    speedpokemon.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

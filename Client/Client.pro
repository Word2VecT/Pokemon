QT       += core gui sql network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++20

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    bag.cpp \
    battle.cpp \
    home.cpp \
    listitem.cpp \
    logindialog.cpp \
    main.cpp \
    mainwindow.cpp \
    pokemoninfo.cpp \
    rank.cpp \
    result.cpp \
    stadium.cpp \
    user.cpp

HEADERS += \
    bag.h \
    battle.h \
    config.h \
    home.h \
    listitem.h \
    logindialog.h \
    mainwindow.h \
    pokemoninfo.h \
    rank.h \
    result.h \
    stadium.h \
    user.h

FORMS += \
    bag.ui \
    battle.ui \
    home.ui \
    listitem.ui \
    logindialog.ui \
    mainwindow.ui \
    pokemoninfo.ui \
    rank.ui \
    result.ui \
    stadium.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    elements.qrc

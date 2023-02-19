QT       += core gui concurrent network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ice_plate.cpp \
    main.cpp \
    mainwindow.cpp \
    settingdialog.cpp \
    tcpclient.cpp

HEADERS += \
    SDK/include/ice_ipcsdk.h \
    ice_plate.h \
    mainwindow.h \
    settingdialog.h \
    tcpclient.h

FORMS += \
    mainwindow.ui \
    settingdialog.ui

TRANSLATIONS += \
    ZBY_PlateInterface_zh_CN.ts

MOC_DIR=tmp/moc
RCC_DIR=tmp/rcc
UI_DIR=tmp/ui
OBJECTS_DIR=tmp/obj

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32: LIBS += -L$$PWD/SDK/lib/ -lice_ipcsdk

INCLUDEPATH += $$PWD/SDK/include
DEPENDPATH += $$PWD/SDK/include

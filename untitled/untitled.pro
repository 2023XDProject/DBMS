QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Dao/cdbdao.cpp \
    Dao/ctabledao.cpp \
    Logic/cdblogic.cpp \
    Logic/cfilelogic.cpp \
    Logic/crkdbmsdoc.cpp \
    Logic/ctablelogic.cpp \
    UI/connectionui.cpp \
    UI/loginui.cpp \
    UI/mainwindow.cpp \
    Util/cfilehelper.cpp \
    Util/syntaxtree.cpp \
    main.cpp

HEADERS += \
    Dao/cdbdao.h \
    Dao/ctabledao.h \
    Logic/cdblogic.h \
    Logic/cfilelogic.h \
    Logic/crkdbmsdoc.h \
    Logic/ctablelogic.h \
    UI/connectionui.h \
    UI/loginui.h \
    UI/mainwindow.h \
    Util/DataStructure.h \
    Util/cfilehelper.h \
    Util/syntaxtree.h

FORMS += \
    UI/connectionui.ui \
    UI/loginui.ui \
    UI/mainwindow.ui \

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

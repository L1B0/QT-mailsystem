######################################################################
# Automatically generated by qmake (3.1) Fri Sep 7 13:54:03 2018
######################################################################

TEMPLATE = app
TARGET = mailclient
INCLUDEPATH += .
QT+=sql core gui widgets
# The following define makes your compiler warn you if you use any
# feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS += draft.h \
           findpassworddialog.h \
           firststack.h \
           logindialog.h \
           mainwindow.h \
           protocol.h \
           receive.h \
           recyclebin.h \
           registerdialog.h \
           sendmail.h \
           writemail.h
FORMS += draft.ui \
         findpassworddialog.ui \
         firststack.ui \
         logindialog.ui \
         mainwindow.ui \
         receive.ui \
         recyclebin.ui \
         registerdialog.ui \
         sendmail.ui \
         writemail.ui
SOURCES += draft.cpp \
           findpassworddialog.cpp \
           firststack.cpp \
           logindialog.cpp \
           main.cpp \
           mainwindow.cpp \
           receive.cpp \
           recyclebin.cpp \
           registerdialog.cpp \
           sendmail.cpp \
           writemail.cpp
RESOURCES += image.qrc

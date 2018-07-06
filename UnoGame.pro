#-------------------------------------------------
#
# Project created by QtCreator 2018-05-18T13:15:14
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = UnoGame
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        CWidget.cpp \
    CStateMachine/CState.cpp \
    CStateMachine/CStateMachine.cpp \
    CStateMachine/CTFAddToWait.cpp \
    CStateMachine/CTFMyToAdd.cpp \
    CStateMachine/CTFMyToError.cpp \
    CStateMachine/CTFMyToSub.cpp \
    CStateMachine/CTFOtherToAdd.cpp \
    CStateMachine/CTFOtherToSub.cpp \
    CStateMachine/CTFStartToWait.cpp \
    CStateMachine/CTFSubToEnd.cpp \
    CStateMachine/CTFSubToWait.cpp \
    CStateMachine/CTFWaitToMy.cpp \
    CStateMachine/CTFWaitToOther.cpp \
    CGame/CCardInfo.cpp \
    CGame/CCardInfoEnd.cpp \
    CGame/CDeskBox.cpp \
    CGame/CGameLoop.cpp \
    CGame/CPlayer.cpp \
    CGameOverDialog.cpp \
    CGame/CDataBase.cpp

HEADERS += \
        CWidget.h \
    CStateMachine/CAbstractState.h \
    CStateMachine/CAbstractTransform.h \
    CStateMachine/CState.h \
    CStateMachine/CStateMachine.h \
    CStateMachine/CTFAddToWait.h \
    CStateMachine/CTFMyToAdd.h \
    CStateMachine/CTFMyToError.h \
    CStateMachine/CTFMyToSub.h \
    CStateMachine/CTFOtherToAdd.h \
    CStateMachine/CTFOtherToSub.h \
    CStateMachine/CTFStartToWait.h \
    CStateMachine/CTFSubToEnd.h \
    CStateMachine/CTFSubToWait.h \
    CStateMachine/CTFWaitToMy.h \
    CStateMachine/CTFWaitToOther.h \
    CGame/CCardInfo.h \
    CGame/CCardInfoEnd.h \
    CGame/CDeskBox.h \
    CGame/CGameLoop.h \
    CGame/CPlayer.h \
    CGame/datatypedefine.h \
    CGameOverDialog.h \
    CGame/CDataBase.h

FORMS += \
        CWidget.ui \
    CGameOverDialog.ui

RESOURCES += \
    src.qrc

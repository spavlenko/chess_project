TEMPLATE = app

QT += qml quick widgets

CONFIG += c++11

SOURCES += main.cpp \
    Figure.cpp \
    GameController.cpp \
    LogicController.cpp \
    Transition.cpp \
    BoardController.cpp \
    TransitionHistory.cpp

RESOURCES += resources/qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    Figure.h \
    GameController.h \
    LogicController.h \
    Transition.h \
    BoardController.h \
    Types.h \
    TransitionHistory.h

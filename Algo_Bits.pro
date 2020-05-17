TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        fen.cpp \
        king.cpp \
        knight.cpp \
        main.cpp \
        truckdrivers.cpp


LIBS += -lstdc++fs

HEADERS += \
    fen.h \
    itask.h \
    king.h \
    knight.h \
    tester.h \
    truckdrivers.h

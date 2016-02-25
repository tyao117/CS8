TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    basenode.cpp \
    linkedlist.cpp \
    driver.cpp

HEADERS += \
    basenode.h \
    linkedlist.h \
    linkedlistqueue.h \
    driver.h

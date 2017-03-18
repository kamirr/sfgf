TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp
LIBS += -lsfml-graphics -lsfml-window -lsfml-system

HEADERS += \
    CopyLock.hpp \
    GameObject.hpp \
    Polygon.hpp \
    Plane.hpp

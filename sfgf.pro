TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp
LIBS += -lsfml-graphics -lsfml-window -lsfml-system

HEADERS += \
    SFGF/CopyLock.hpp \
    SFGF/GameObject.hpp \
    SFGF/Polygon.hpp \
    SFGF/Plane.hpp \
    SFGF/Collider.hpp

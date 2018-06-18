QT += testlib

TEMPLATE = app

CONFIG += console c++14
CONFIG -= app_bundle

SOURCES += main.cpp \
    unittest.cpp \
    ../src/core/common/math/vectorxd.cpp

HEADERS += \
    unittest.h \
    ../src/core/common/math/vectorxd.h

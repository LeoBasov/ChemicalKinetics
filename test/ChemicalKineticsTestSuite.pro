QT += testlib

TEMPLATE = app

CONFIG += console c++14
CONFIG -= app_bundle

SOURCES += main.cpp \
    unittest.cpp \
    ../src/core/common/math/vectorxd.cpp \
    ../src/core/exceptions/exception.cpp \
    ../src/core/exceptions/logic_errors/outofrange.cpp \
    core/common/math/vectorxdtest.cpp

HEADERS += \
    unittest.h \
    ../src/core/common/math/vectorxd.h \
    ../src/core/exceptions/exception.h \
    ../src/core/exceptions/logic_errors/outofrange.h \
    core/common/math/vectorxdtest.h

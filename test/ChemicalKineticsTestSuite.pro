QT += testlib

TEMPLATE = app

CONFIG += console c++14
CONFIG -= app_bundle

SOURCES += main.cpp \
    unittest.cpp \
    ../src/core/common/math/vectorxd.cpp \
    ../src/core/exceptions/exception.cpp \
    ../src/core/exceptions/logic_errors/outofrange.cpp \
    core/common/math/vectorxdtest.cpp \
    ../src/core/common/math/matrixxd.cpp \
    core/common/math/matrixxdtest.cpp \
    ../src/core/entities/chemistry/chemistryalgorithms.cpp \
    core/entities/chemistry/chemistryalgorithmstest.cpp \
    ../src/core/use_case_interactor/usecaseinteractor.cpp \
    ../src/core/entities/chemistry/chemistry.cpp \
    ../src/core/entities/integrator/integratoralgorithms.cpp \
    core/entities/integrator/integratoralgorithmstest.cpp \
    ../src/core/entities/integrator/integrator.cpp \
    ../src/core/common/data_types/interpolationtable.cpp \
    core/common/data_types/interpolationtabletest.cpp \
    ../src/core/use_case_interactor/abortcriterium.cpp \
    core/entities/integrator/integratortest.cpp \
    ../src/core/use_case_interactor/converter.cpp \
    core/use_case_interactor/convertertest.cpp \
    ../src/core/output_boundary/observer.cpp \
    ../src/core/output_boundary/subject.cpp \
    ../src/core/output_boundary/simulationstate.cpp

HEADERS += \
    unittest.h \
    ../src/core/common/math/vectorxd.h \
    ../src/core/exceptions/exception.h \
    ../src/core/exceptions/logic_errors/outofrange.h \
    core/common/math/vectorxdtest.h \
    ../src/core/common/math/matrixxd.h \
    core/common/math/matrixxdtest.h \
    ../src/core/common/data_types/state.h \
    ../src/core/entities/chemistry/chemistryalgorithms.h \
    ../src/core/common/constants.h \
    core/entities/chemistry/chemistryalgorithmstest.h \
    ../src/core/use_case_interactor/usecaseinteractor.h \
    ../src/core/entities/chemistry/chemistry.h \
    ../src/core/entities/integrator/integratoralgorithms.h \
    core/entities/integrator/integratoralgorithmstest.h \
    ../src/core/entities/integrator/integrator.h \
    ../src/core/common/data_types/interpolationtable.h \
    core/common/data_types/interpolationtabletest.h \
    ../src/core/use_case_interactor/abortcriterium.h \
    ../src/core/common/data_types/inputdata.h \
    core/entities/integrator/integratortest.h \
    ../src/core/use_case_interactor/converter.h \
    core/use_case_interactor/convertertest.h \
    ../src/core/output_boundary/observer.h \
    ../src/core/output_boundary/subject.h \
    ../src/core/output_boundary/simulationstate.h

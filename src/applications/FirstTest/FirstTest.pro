TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    ../../core/common/data_types/interpolationtable.cpp \
    ../../core/common/math/matrixxd.cpp \
    ../../core/common/math/vectorxd.cpp \
    ../../core/entities/chemistry/chemistry.cpp \
    ../../core/entities/chemistry/chemistryalgorithms.cpp \
    ../../core/entities/integrator/integrator.cpp \
    ../../core/entities/integrator/integratoralgorithms.cpp \
    ../../core/exceptions/logic_errors/outofrange.cpp \
    ../../core/exceptions/exception.cpp \
    ../../core/output_boundary/observer.cpp \
    ../../core/output_boundary/simulationstate.cpp \
    ../../core/output_boundary/subject.cpp \
    ../../core/use_case_interactor/abortcriterium.cpp \
    ../../core/use_case_interactor/converter.cpp \
    ../../core/use_case_interactor/usecaseinteractor.cpp \
    testpresenter.cpp \
    view.cpp

HEADERS += \
    ../../core/common/data_types/inputdata.h \
    ../../core/common/data_types/interpolationtable.h \
    ../../core/common/data_types/state.h \
    ../../core/common/math/matrixxd.h \
    ../../core/common/math/vectorxd.h \
    ../../core/common/constants.h \
    ../../core/entities/chemistry/chemistry.h \
    ../../core/entities/chemistry/chemistryalgorithms.h \
    ../../core/entities/integrator/integrator.h \
    ../../core/entities/integrator/integratoralgorithms.h \
    ../../core/exceptions/logic_errors/outofrange.h \
    ../../core/exceptions/exception.h \
    ../../core/output_boundary/observer.h \
    ../../core/output_boundary/simulationstate.h \
    ../../core/output_boundary/subject.h \
    ../../core/use_case_interactor/abortcriterium.h \
    ../../core/use_case_interactor/converter.h \
    ../../core/use_case_interactor/usecaseinteractor.h \
    testpresenter.h \
    view.h

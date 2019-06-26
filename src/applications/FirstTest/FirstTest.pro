TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
    ../../core/common/abstractions/observer.cpp \
    ../../core/common/abstractions/subject.cpp \
    ../../core/common/data_types/datanode.cpp \
    ../../core/input_boundary/controller.cpp \
    ../../core/input_boundary/filereader.cpp \
    ../../core/input_boundary/xmlreader.cpp \
    ../../core/view_boundary/view.cpp \
    ../../core/view_boundary/viewmodel.cpp \
    ../../third_party/tinyxml/tinystr.cpp \
    ../../third_party/tinyxml/tinyxml.cpp \
    ../../third_party/tinyxml/tinyxmlerror.cpp \
    ../../third_party/tinyxml/tinyxmlparser.cpp \
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
    ../../core/output_boundary/simulationstate.cpp \
    ../../core/use_case_interactor/abortcriterium.cpp \
    ../../core/use_case_interactor/converter.cpp \
    ../../core/use_case_interactor/usecaseinteractor.cpp \
    testpresenter.cpp

HEADERS += \
    ../../core/common/abstractions/observer.h \
    ../../core/common/abstractions/subject.h \
    ../../core/common/data_types/datanode.h \
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
    ../../core/input_boundary/controller.h \
    ../../core/input_boundary/filereader.h \
    ../../core/input_boundary/xmlreader.h \
    ../../core/output_boundary/simulationstate.h \
    ../../core/use_case_interactor/abortcriterium.h \
    ../../core/use_case_interactor/converter.h \
    ../../core/use_case_interactor/usecaseinteractor.h \
    ../../core/view_boundary/view.h \
    ../../core/view_boundary/viewmodel.h \
    ../../third_party/tinyxml/tinystr.h \
    ../../third_party/tinyxml/tinyxml.h \
    testpresenter.h

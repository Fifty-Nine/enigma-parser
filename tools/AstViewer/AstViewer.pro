TEMPLATE = app

unix { 
    QMAKE_CXXFLAGS += -std=gnu++0x
    debug { 
        OBJECTS_DIR=build/debug
        MOC_DIR=build/debug
        UI_DIR=build/debug
        TARGET=AstViewer-debug
    }
    release { 
        OBJECTS_DIR=build/release
        MOC_DIR=build/release
        UI_DIR=build/release
        TARGET=AstViewer-release
    }
}

FORMS += \
    AstViewer.ui \

HEADERS += \
    AstModel.h\
    AstViewer.h\

SOURCES += \
    AstModel.cpp \
    AstViewer.cpp \
    main.cpp \

LIBS += -lenigma
debug:LIBS += -L../../enigma/build/debug
release:LIBS += -L../../enigma/build/release

INCLUDEPATH += ../../

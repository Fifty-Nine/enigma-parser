include( Overrides.pri )

TEMPLATE = app

unix { 
    QMAKE_CXXFLAGS += -std=gnu++0x
    debug { 
        OBJECTS_DIR=debug
        MOC_DIR=debug
        UI_DIR=debug
        TARGET=AstViewer-debug
    }
    release { 
        OBJECTS_DIR=release
        MOC_DIR=release
        UI_DIR=release
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

debug:LIBS += -L$$PWD/../../enigma/debug
release:LIBS += -L$$PWD/../../enigma/release
LIBS += -lenigma

INCLUDEPATH += ../../

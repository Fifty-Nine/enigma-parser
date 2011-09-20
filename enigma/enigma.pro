TEMPLATE = lib
CONFIG += staticlib

exists( Overrides.pri ) { 
    include( Overrides.pri )
}

unix { 
    QMAKE_CXXFLAGS += -std=gnu++0x
    debug { 
        OBJECTS_DIR=build/debug
        MOC_DIR=build/debug
        UI_DIR=build/debug
        DESTDIR=build/debug
    }
    release { 
        OBJECTS_DIR=build/release
        MOC_DIR=build/release
        UI_DIR=build/release
        DESTDIR=build/release
    }
}

INCLUDEPATH += ..

HEADERS +=\
    Date.h \
    Lexer.h \
    Location.h \ 
    Parser.h \
    FileReader.h \

SOURCES +=\
    Date.cpp \
    Lexer.cpp \
    Parser.cpp \
    FileReader.cpp \

include( exceptions/exceptions.pri )
include( tokens/tokens.pri )
include( ast/ast.pri )
include( util/util.pri )
include( visitors/visitors.pri )

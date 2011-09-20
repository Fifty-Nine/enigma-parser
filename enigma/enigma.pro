TEMPLATE = lib
CONFIG += staticlib

exists( Overrides.pri ) { 
    include( Overrides.pri )
}

unix { 
    QMAKE_CXXFLAGS += -std=gnu++0x
    debug { 
        OBJECTS_DIR=debug
        MOC_DIR=debug
        UI_DIR=debug
        DESTDIR=debug
    }
    release { 
        OBJECTS_DIR=release
        MOC_DIR=release
        UI_DIR=release
        DESTDIR=release
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

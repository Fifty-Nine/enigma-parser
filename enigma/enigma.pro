TEMPLATE = lib
CONFIG += staticlib 

include( ../Common.pri )

INCLUDEPATH += ..
VPATH = ..

HEADERS +=\
    enigma/Date.h \
    enigma/Lexer.h \
    enigma/Location.h \ 
    enigma/Parser.h \
    enigma/FileReader.h \

SOURCES +=\
    enigma/Date.cpp \
    enigma/Lexer.cpp \
    enigma/Parser.cpp \
    enigma/FileReader.cpp \

include( exceptions/exceptions.pri )
include( tokens/tokens.pri )
include( ast/ast.pri )
include( util/util.pri )
include( visitors/visitors.pri )
exists( Overrides.pri ) { 
    include( Overrides.pri )
}

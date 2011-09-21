TEMPLATE = lib
CONFIG += staticlib 

include( ../Common.pri )

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
exists( Overrides.pri ) { 
    include( Overrides.pri )
}

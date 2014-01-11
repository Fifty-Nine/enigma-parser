HEADERS +=\
    enigma/Date.h \
    enigma/Lexer.h\
    enigma/Location.h\ 
    enigma/Parser.h \

SOURCES +=\
    enigma/Date.cpp \
    enigma/Lexer.cpp \
    enigma/Parser.cpp \

include( exceptions/exceptions.pri )
include( tokens/tokens.pri )
include( ast/ast.pri )
include( util/util.pri )
include( visitors/visitors.pri )

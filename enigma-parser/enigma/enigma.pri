HEADERS +=\
    enigma/Date.h \
    enigma/FilePos.h \ 
    enigma/Lexer.h \
    enigma/Parser.h \
    enigma/File.h \
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


TEMPLATE = lib
CONFIG += shared staticlib

include( ../Common.pri )

INCLUDEPATH += ../enigma-parser

include( enigma/enigma.pri )

exists( Overrides.pri ) { 
    include( Overrides.pri )
}

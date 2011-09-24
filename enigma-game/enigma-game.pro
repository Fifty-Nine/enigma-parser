TEMPLATE = lib
CONFIG += staticlib shared

include( ../Common.pri )

INCLUDEPATH += ../enigma-parser

include( enigma/enigma.pri )

exists( Overrides.pri ) { 
    include( Overrides.pri )
}

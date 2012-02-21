TEMPLATE = lib
CONFIG += staticlib 

include( ../Common.pri )
include( enigma/enigma.pri )

exists( Overrides.pri ) { 
    include( Overrides.pri )
}

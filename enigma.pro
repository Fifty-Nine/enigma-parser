TEMPLATE = lib
CONFIG += qt console staticlib

include( enigma/enigma.pri )

unix { 
    QMAKE_CXXFLAGS += -std=gnu++0x
    debug { 
        OBJECTS_DIR=build/debug
        MOCS_DIR=build/debug
        UICS_DIR=build/debug
        TARGET=build/debug/libenigma.a
    }
    release { 
        OBJECTS_DIR=build/release
        MOCS_DIR=build/release
        UICS_DIR=build/release
        TARGET=build/release/libenigma.a
    }
}

win32 {
    INCLUDEPATH += /Users/princet/Downloads/boost_1_46_0/boost_1_46_0
}

INCLUDEPATH += .


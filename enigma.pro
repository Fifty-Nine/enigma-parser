TEMPLATE = lib
CONFIG += qt staticlib

include( enigma/enigma.pri )

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

win32 {
    INCLUDEPATH += /Users/princet/Downloads/boost_1_46_0/boost_1_46_0
}

INCLUDEPATH += .


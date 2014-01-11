TEMPLATE = lib
CONFIG += qt console staticlib

include( enigma/enigma.pri )

unix { 
    QMAKE_CXXFLAGS += -std=gnu++0x
}

win32 {
    INCLUDEPATH += /Users/princet/Downloads/boost_1_46_0/boost_1_46_0
}

INCLUDEPATH += .


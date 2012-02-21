CONFIG += debug_and_release build_all

unix:QMAKE_CXXFLAGS += -std=gnu++0x -Wall -Werror

INCLUDEPATH += /home/tprince/venom35/Components
QMAKE_CXX = g++-4.6

CONFIG(debug, debug|release) { 
    OBJECTS_DIR=debug
    MOC_DIR=debug
    UI_DIR=debug
    DESTDIR=debug
}
CONFIG(release, debug|release) { 
    OBJECTS_DIR=release
    MOC_DIR=release
    UI_DIR=release
    DESTDIR=release
}

clang { 
    QMAKE_CC = clang
    QMAKE_CXX = clang++
    QMAKE_LINK = clang++
    QMAKE_CXXFLAGS += -stdlib=libc++
    QMAKE_LFLAGS += -stdlib=libc++
}

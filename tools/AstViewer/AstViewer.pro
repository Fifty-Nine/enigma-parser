exists( Overrides.pri ) { 
    include( Overrides.pri )
}

include( ../../Common.pri )

TEMPLATE = app

unix:QMAKE_CXXFLAGS += -std=gnu++0x

CONFIG(debug, debug|release) { 
    OBJECTS_DIR=debug
    MOC_DIR=debug
    UI_DIR=debug
    TARGET=AstViewer-debug
    LIBS += -L../../enigma/debug
    win32:PRE_TARGETDEPS += ../../enigma/debug/enigma.lib
    unix:PRE_TARGETDEPS += ../../enigma/debug/libenigma.a
}

CONFIG(release, debug|release) { 
    OBJECTS_DIR=release
    MOC_DIR=release
    UI_DIR=release
    TARGET=AstViewer-release
    LIBS += -L../../enigma/release
    win32:PRE_TARGETDEPS += ../../enigma/release/enigma.lib
    unix:PRE_TARGETDEPS += ../../enigma/release/libenigma.a
}

FORMS += \
    AstViewer.ui \

HEADERS += \
    AstModel.h\
    AstViewer.h\
    NodeToString.h\

SOURCES += \
    AstModel.cpp \
    AstViewer.cpp \
    NodeToString.cpp \
    main.cpp \

LIBS += -lenigma

INCLUDEPATH += ../../

TEMPLATE = app

include( ../../Common.pri )

LIBS += -lenigma
CONFIG(debug, debug|release) { 
    DESTDIR=.
    TARGET=AstViewer-debug
    LIBS += -L../../enigma/debug
    win32:PRE_TARGETDEPS += ../../enigma/debug/enigma.lib
    unix:PRE_TARGETDEPS += ../../enigma/debug/libenigma.a
}

CONFIG(release, debug|release) { 
    DESTDIR=.
    TARGET=AstViewer-release
    LIBS += -L../../enigma/release
    win32:PRE_TARGETDEPS += ../../enigma/release/enigma.lib
    unix:PRE_TARGETDEPS += ../../enigma/release/libenigma.a
}

QMAKE_CLEAN += $$TARGET

INCLUDEPATH += ../../enigma

FORMS += \
    AstViewer.ui \

HEADERS += \
    AstModel.h\
    AstViewer.h\
    NodeUtils.h\

SOURCES += \
    AstModel.cpp \
    AstViewer.cpp \
    NodeUtils.cpp\
    main.cpp \

exists( Overrides.pri ) { 
    include( Overrides.pri )
}

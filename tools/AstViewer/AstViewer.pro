TEMPLATE = app

include( ../../Common.pri )

LIBS += -lenigma-parser
CONFIG(debug, debug|release) { 
    DESTDIR=.
    TARGET=AstViewer-debug
    LIBS += -L../../enigma-parser/debug
    win32:PRE_TARGETDEPS += ../../enigma-parser/debug/enigma-parser.lib
    unix:PRE_TARGETDEPS += ../../enigma-parser/debug/libenigma-parser.a
}

CONFIG(release, debug|release) { 
    DESTDIR=.
    TARGET=AstViewer-release
    LIBS += -L../../enigma-parser/release
    win32:PRE_TARGETDEPS += ../../enigma-parser/release/enigma-parser.lib
    unix:PRE_TARGETDEPS += ../../enigma-parser/release/libenigma-parser.a
}

QMAKE_CLEAN += $$TARGET

INCLUDEPATH += ../../enigma-parser

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

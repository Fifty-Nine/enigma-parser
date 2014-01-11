TEMPLATE = app

include(../../Common.pri)

DESTDIR = .
LOCAL_LIBS += enigma-parser enigma-ck2

CONFIG(debug, debug|release) { 
    TARGET = DumpNames-debug

    for(libname, LOCAL_LIBS) { 
        LIBS += -l$$libname -L../../$$libname/debug
        win32:PRE_TARGETDEPS += ../../$$libname/debug/$${libname}.lib
        unix:PRE_TARGETDEPS += ../../$$libname/debug/lib$${libname}.a
        unix:QMAKE_LFLAGS += -Wl,-rpath,../../$$libname/debug
        INCLUDEPATH += ../../$$libname
    }
}

CONFIG(release, debug|release) { 
    TARGET=DumpNames-release

    for(libname, LOCAL_LIBS) { 
        LIBS += -l$$libname -L../../$$libname/release
        win32:PRE_TARGETDEPS += ../../$$libname/release/$${libname}.lib
        unix:PRE_TARGETDEPS += ../../$$libname/release/lib$${libname}.a
        unix:QMAKE_LFLAGS += -Wl,-rpath,../../$$libname/release
        INCLUDEPATH += ../../$$libname
    }
}

SOURCES += main.cpp

exists(Overrides.pri) { 
    include(Overrides.pri)
}

QT += testlib \
    gui \
    sql \
    widgets

CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

#QMAKE_CXXFLAGS += -Wall -Wextra -Werror
#QMAKE_CFLAGS += -Wall -Wextra -Werror

HEADERS += \
    ../../src/adif.h \
    ../../src/utilities.h \
    ../../src/dataproxy_sqlite.h \
    ../../src/database.h \
    ../../src/qso.h \
    ../../src/klogdefinitions.h \
    ../../src/locator.h

SOURCES +=  tst_utilities.cpp \
    ../../src/adif.cpp \
    ../../src/utilities.cpp \
    ../../src/dataproxy_sqlite.cpp \
    ../../src/database.cpp \
    ../../src/qso.cpp \
    ../../src/locator.cpp



isEmpty(QMAKE_LRELEASE) {
    win32|os2:QMAKE_LRELEASE = $$[QT_INSTALL_BINS]\lrelease.exe
    else:QMAKE_LRELEASE = $$[QT_INSTALL_BINS]/lrelease
    unix {
        !exists($$QMAKE_LRELEASE) { QMAKE_LRELEASE = lrelease-qt5 }
    } else {
        !exists($$QMAKE_LRELEASE) { QMAKE_LRELEASE = lrelease }
    }
}

QT += testlib

HEADERS += \
    ../hrlib/exceptions.h \
    ../hrlib/version.h \
    ../hrlib/unittesting.h \
    ../hrlib/math/brent.hpp \
    ../hrlib/qgraphics/pathutils.h \
    ../hrlib/hrlibfwd/qtfwd.h \
    ../hrlib/math/spline.hpp

SOURCES += \
    ../hrlib/exceptions.cpp \
    ../hrlib/version.cpp \
    ../hrlib/unittesting.cpp \
    ../hrlib/math/brent.cpp \
    ../hrlib/qgraphics/pathutils.cpp \
    ../hrlib/math/spline.cpp

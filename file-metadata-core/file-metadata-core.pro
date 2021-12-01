QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
CONFIG += precompile_header
PRECOMPILED_HEADER = pch.h

HEADERS += \
        pch.h \
    handler.h \
    new.h \
    binary.h \
    v22.h \
    v23.h \
    v24.h \
    v1.h \
    frame2.h \
    frame3.h \
    frame4.h \
    frames2.h \
    frames3.h \
    frames4.h \
    file-holder.h

SOURCES += \
        main.cpp \
    handler.cpp \
    new.cpp \
    binary.cpp \
    v22.cpp \
    v23.cpp \
    v24.cpp \
    v1.cpp \
    frame2.cpp \
    frame3.cpp \
    frame4.cpp \
    garbage.cpp \
    frames2.cpp \
    frames3.cpp \
    frames4.cpp \
    file-holder.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

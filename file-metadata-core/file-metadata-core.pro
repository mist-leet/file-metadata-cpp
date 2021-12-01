QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = file-metadata-core
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0
CONFIG += c++11
CONFIG += precompile_header
PRECOMPILED_HEADER = pch.h

HEADERS += \
        pch.h \
    new.h \
    binary.h \
    v22.h \
    v23.h \
    v24.h \
    v1.h \
    frame2.h \
    frame3.h \
    frame4.h \
    file-holder.h \
    tag.h \
    frame.h \
    tag34.h \
    frame_34.h \
    easy_ptr.h \
    frame_structs.h \
    tag_structs.h \
    file_contents.h \
    char_conversions.h \
    file_structs.h

SOURCES += \
        main.cpp \
    new.cpp \
    binary.cpp \
    v22.cpp \
    v23.cpp \
    v24.cpp \
    v1.cpp \
    frame2.cpp \
    frame3.cpp \
    frame4.cpp \
    frames2.cpp \
    frames3.cpp \
    file-holder.cpp \
    tag.cpp \
    frame.cpp \
    tag34.cpp \
    frames4RP.cpp \
    frames4GCLO.cpp \
    frames4SA.cpp \
    frames4UEM.cpp \
    frames4text.cpp \
    frames4url.cpp \
    frame_34.cpp \
    frames4unknown.cpp \
    file_contents.cpp \
    char_conversions.cpp \
    file_structs.cpp \
    monsterous_functions.cpp \
    new_char_extracting.cpp \
    tagparser.cpp \
    frameparser.cpp \
    widget1.cpp

FORMS += \
    widget1.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


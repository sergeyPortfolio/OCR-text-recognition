#-------------------------------------------------
#
# Project created by QtCreator 2018-11-20T21:06:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OCR-text-recognition
TEMPLATE = app

CONFIG(debug, debug|release) {
    DESTDIR = $$PWD/bin/debug
} else {
    DESTDIR = $$PWD/bin/release
}
win32 {
    PWD_WIN = $${PWD}
    DESTDIR_WIN = $${DESTDIR}
    PWD_WIN ~= s,/,\\,g
    DESTDIR_WIN ~= s,/,\\,g

    copyfiles.commands = $$quote(cmd /c xcopy /S /I /Y $${PWD_WIN}\\third-party\\tesseract\\include\\tessdata $${DESTDIR_WIN}\\tessdata)
    QMAKE_EXTRA_TARGETS += copyfiles
    POST_TARGETDEPS += copyfiles
}

INCLUDEPATH += third-party/tesseract/include/tesseract_3.05/api \
               third-party/tesseract/include/leptonica/src \
               third-party/tesseract/include/tesseract_3.05/ccutil \
               third-party/tesseract/include/tesseract_3.05/ccmain \
               third-party/tesseract/include/tesseract_3.05/ccstruct \
               third-party/tesseract/include/liblept \
               third-party/tesseract/include/tessdata
CONFIG(debug, debug|release)
{
LIBS += $$PWD/third-party/tesseract/lib/Debug/libtesseract.lib \
        $$PWD/third-party/tesseract/lib/Debug/giflib.lib \
        $$PWD/third-party/tesseract/lib/Debug/libjpeg.lib \
        $$PWD/third-party/tesseract/lib/Debug/liblept.lib \
        $$PWD/third-party/tesseract/lib/Debug/libpng.lib \
        $$PWD/third-party/tesseract/lib/Debug/libtiff.lib \
        $$PWD/third-party/tesseract/lib/Debug/libwebp.lib \
        $$PWD/third-party/tesseract/lib/Debug/openjpeg.lib \
        $$PWD/third-party/tesseract/lib/Debug/zlib.lib
}


# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    qimagewidget.cpp

HEADERS += \
        mainwindow.h \
    qimagewidget.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

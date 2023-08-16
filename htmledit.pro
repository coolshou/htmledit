QT += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
CONFIG += c++11

requires(qtConfig(filedialog))
qtHaveModule(printsupport): QT += printsupport

TEMPLATE        = app
TARGET          = htmledit

HEADERS         = \
    src/htmlsubwin.h \
    src/textedit.h \
    src/htmledit.h \
    src/mainwindow.h \
    src/version.h

SOURCES         = \
    src/htmlsubwin.cpp \
    src/textedit.cpp \
    src/htmledit.cpp \
    src/main.cpp \
    src/mainwindow.cpp

FORMS += \
    src/mainwindow.ui

RESOURCES += \
    htmledit.qrc

OBJECTS_DIR = \
    obj
MOC_DIR = \
    obj
QRC_DIR = \
    obj

build_all:!build_pass {
    CONFIG -= build_all
    CONFIG += release
}

EXAMPLE_FILES = htmledit.qdoc

# install
#target.path = $$[QT_INSTALL_EXAMPLES]/widgets/richtext/textedit
#INSTALLS += target

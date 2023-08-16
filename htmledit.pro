QT += widgets
requires(qtConfig(filedialog))
qtHaveModule(printsupport): QT += printsupport

TEMPLATE        = app
TARGET          = htmledit

HEADERS         = \
    src/textedit.h
SOURCES         = \
    src/textedit.cpp \
    src/main.cpp

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

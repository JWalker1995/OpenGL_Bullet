TEMPLATE = app
#CONFIG -= qt

SOURCES += main.cpp \
    glmanager.cpp \
    3rd_party/pugixml.cpp \
    colladaloader.cpp

INCLUDEPATH += c:/bullet_280/src

LIBS = -lglu32 -lglfw -lopengl32 \
    c:/bullet_280/lib/libBulletDynamics.a c:/bullet_280/lib/libBulletCollision.a c:/bullet_280/lib/libLinearMath.a

HEADERS += \
    glmanager.h \
    3rd_party/pugixml.hpp \
    colladaloader.h

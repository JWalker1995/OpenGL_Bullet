TEMPLATE = app
#CONFIG -= qt

SOURCES += main.cpp \
    3rd_party/pugixml.cpp \
    colladaloader.cpp \
    3rd_party/glew.c \
    scenemanager.cpp

INCLUDEPATH += c:/bullet_280/src

LIBS = -lglu32 -lglfw -lopengl32 \
    c:/bullet_280/lib/libBulletDynamics.a c:/bullet_280/lib/libBulletCollision.a c:/bullet_280/lib/libLinearMath.a

HEADERS += \
    3rd_party/pugixml.hpp \
    colladaloader.h \
    scenemanager.h

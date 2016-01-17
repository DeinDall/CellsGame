CONFIG -= qt
CONFIG += c++11

QMAKE_LFLAGS += -static

# [start] SFML Inclusion

INCLUDEPATH += C:/SFML/include
LIBS += -LC:/SFML/lib

#CONFIG(debug) {
#    LIBS += -lsfml-network-s-d -lsfml-graphics-s-d -lsfml-window-s-d -lsfml-system-s-d -lsfml-main-d
#} else {
    LIBS += -lsfml-network-s -lsfml-graphics-s -lsfml-window-s -lsfml-system-s -lsfml-main
#}

LIBS += -lws2_32 -lfreetype -ljpeg -lopengl32 -lgdi32 -lwinmm

DEFINES += SFML_STATIC

# [end] SFML Inclusion

SOURCES += \
    main.cpp \
    game/cell.cpp \
    game/cell.link.cpp \
    stk/vec2.cpp \
    graphics/graphicscell.cpp \
    client/clientcell.cpp \
    client/clientworld.cpp \
    graphics/graphicsworld.cpp \
    game/world.cpp \
    server/serverworld.cpp \
    network/gameevent.cpp \
    server/servercell.cpp \
    network/events/cellupdateevent.cpp \
    network/networkcell.cpp \
    network/events/cellcreateevent.cpp \
    network/servernetworkmanager.cpp \
    network/events/celldestroyevent.cpp

HEADERS += \
    game/cell.h \
    stk/vec2.h \
    graphics/graphicscell.h \
    client/clientcell.h \
    client/clientworld.h \
    graphics/graphicsworld.h \
    game/world.h \
    server/serverworld.h \
    network/gameevent.h \
    server/servercell.h \
    network/events/cellupdateevent.h \
    network/networkcell.h \
    network/events/cellcreateevent.h \
    network/servernetworkmanager.h \
    network/events/celldestroyevent.h

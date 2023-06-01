TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
           bot_shoot.c \
           generate_bot_field.c \
           init.c \
           main_loop.c \
           place_ships.c \
           user_shoot.c

HEADERS += battleship.h \
           bot_shoot.h \
           generate_bot_field.h \
           init.h \
           main_loop.h \
           place_ships.h \
           user_shoot.h
           

QMAKE_CFLAGS += -Wall -Wextra

# gcov
QMAKE_CFLAGS += -fprofile-arcs -ftest-coverage
LIBS += -lgcov \
        -lncursesw \
        -lpanelw
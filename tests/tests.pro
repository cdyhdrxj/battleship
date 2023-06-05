include(gtest_dependency.pri)

TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG += thread
CONFIG -= qt

QMAKE_CXXFLAGS += -Wall -Wextra
QMAKE_CFLAGS += -Wall -Wextra

# gcov
QMAKE_CXXFLAGS += -fprofile-arcs -ftest-coverage
QMAKE_CFLAGS += -fprofile-arcs -ftest-coverage


SOURCES += main.cpp \
           ../app/bot_shoot.c \
           ../app/generate_bot_field.c \
           ../app/init.c \
           ../app/main_loop.c \
           ../app/place_ships.c \
           ../app/user_shoot.c

HEADERS += test_bot_shoot.h \
           test_generate_bot_field.h \
           test_init.h \
           test_main_loop.h \
           test_place_ships.h \
           test_user_shoot.h \
           ../app/battleship.h \
           ../app/bot_shoot.h \
           ../app/generate_bot_field.h \
           ../app/init.h \
           ../app/main_loop.h \
           ../app/place_ships.h \
           ../app/user_shoot.h \
           ../external/fff/fff.h
           

INCLUDEPATH += ../app \
               ../external/fff

LIBS += -lgcov \
        -lncursesw \
        -lpanelw

#ifndef INIT_H
#define INIT_H

#include <ncursesw/ncurses.h>
#include <ncursesw/panel.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

#define LINE_MAX 200

typedef struct _help {
    WINDOW *win;
    PANEL *pan;
    char *text;
} help;

typedef struct _game {
    WINDOW *win, *pl, *bot;
    PANEL *pan;
    help *h;
} game;

void init_help(help *h);
void print_help(help *h);

#endif /* INIT_H */
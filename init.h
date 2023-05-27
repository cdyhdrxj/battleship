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
    int user_field[12][12];
    int bot_field[12][12];
    WINDOW *win, *pl, *bot;
    PANEL *pan;
    help *h;
} game;

void print_grid(game *g);
int init_help(help *h);
void print_help(help *h);
void help_loop(help *h);

#endif /* INIT_H */
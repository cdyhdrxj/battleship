#ifndef INIT_H
#define INIT_H

#include <ncursesw/ncurses.h>
#include <ncursesw/panel.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>

#define LINE_MAX 200
#define FIELD_X(x) 2*(x)-1 
#define FIELD_Y(y) 4*(y)-2

#define MAIN_MSG    "Press h to get help, q to quit"
#define ROTATE_MSG  "Can't rotate"
#define MOVE_MSG    "Move this ship"
#define HELP_MSG    "Help (press q to quit, arrows to scroll)"
#define TURN_MSG    "It's your turn"
#define HIT_MSG     "Hit!"
#define DESTROY_MSG "Destroyed!"
#define WIN_MSG     "You win! (press any key to quit)"
#define LOSE_MSG    "You lose... (press any key to quit)"


typedef struct __ship {
    int num;
    int size;
    int hit_cells;
} ship;


typedef struct _help {
    WINDOW *win;
    PANEL *pan;
    char *text;
} help;


typedef struct _game {
    int user_field[12][12]; 
    int user_shot[12][12];
    

    int bot_field[12][12];
    int bot_shot[12][12];
    ship bot_ships[10];

    WINDOW *win, *pl, *bot;
    PANEL *pan;
    help *h;
} game;

void print_grid(game *g);
int init_help(help *h);
void print_help(help *h);
void help_loop(help *h);

#endif /* INIT_H */
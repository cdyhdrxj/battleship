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

#define MAIN_MSG    "Press h for help, q to quit"
#define ROTATE_MSG  "Can't rotate (h for help, q to quit)"
#define MOVE_MSG    "Move this ship (h for help, q to quit)"
#define HELP_MSG    "Help (press q to quit, arrows to scroll)"
#define BOT_MSG     "It's bot's turn (h for help, q to quit)"
#define YOU_MSG     "It's your turn (h for help, q to quit)"
#define HIT_MSG     "Hit! It's your turn (h for help, q to quit)"
#define DESTROY_MSG "Destroyed! It's your turn (h for help, q to quit)"
#define WIN_MSG     "You win! (press any key to quit)"
#define LOSE_MSG    "You lose... (press any key to quit)"

enum PLAYERS {user, bot};
enum CURRENT_MSG {you, hit, destr};


typedef struct __ship {
    int size;
    int hit_cells;
} ship;


typedef struct __shoot {
    int cells_left;
    int battleship_search;
    int diagonals;
    int is_destroyed;
    int current_ship;
    int poss_cell[4][2];
} shoot;


typedef struct _help {
    WINDOW *win;
    PANEL *pan;
    char *text;
} help;


typedef struct _game {
    int user_field[12][12]; 
    int user_shot[12][12];
    ship user_ships[10];
    int cells_left;    

    int bot_field[12][12];
    int bot_shot[12][12];
    ship bot_ships[10];

    shoot bot_shoot;

    WINDOW *win, *pl, *bot;
    PANEL *pan;
    help *h;
} game;


void print_grid(game *g);
int init_help(help *h);
void print_help(help *h);
void help_loop(help *h);

#endif /* INIT_H */
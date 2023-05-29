#include "init.h"
#include "place_ships.h"
#include "generate_bot_field.h"
#include "shoot.h"
#include "bot_shoot.h"
#include <unistd.h>

int main(){
    setlocale(LC_ALL, "");
    initscr();
    keypad(stdscr, TRUE);
    //raw();
    noecho();

    game *g;
    g = (game *) malloc(sizeof(game));
    if (g == NULL)
        return 0;

    g->h = (help *) malloc(sizeof(help));
    if (g->h == NULL)
        return 0;

    g->win = newwin(LINES, COLS, 0, 0);
    g->pan = new_panel(g->win);

    g->h->win = newwin(LINES, COLS, 0, 0);
    g->h->pan = new_panel(g->h->win);

    top_panel(g->pan);
    update_panels();
    doupdate();

    print_grid(g);
    init_help(g->h);

    place_ships(g);

    gener_field(g->bot_field);
    fill_bot_ships(g);

    shooting_loop(g);

    g->bot_shoot.battleship_search = 0;
    g->bot_shoot.diagonals = 0;
    g->bot_shoot.is_destroyed = 1;
    g->bot_shoot.cells_left = 20;

    while(g->bot_shoot.cells_left > 0){
        bot_shooting(g);
    }

    int c;
    while((c = getch()) != 'q');

    endwin();

    return 0;
}
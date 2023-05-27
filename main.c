#include "init.h"
#include "place_ships.h"
#include "generate_bot_field.h"
#include "shoot.h"

int main(){
    setlocale(LC_ALL, "");
    initscr();
    keypad(stdscr, TRUE);
    raw();
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

    shooting_loop(g);

    endwin();

    return 0;
}
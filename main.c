#include "init.h"
#include "place_ships.h"
#include "generate_bot_field.h"
#include "shoot.h"
#include "bot_shoot.h"

int main(){
    setlocale(LC_ALL, "");
    initscr();
    keypad(stdscr, TRUE);
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

    int need_to_quit = place_ships(g);
    if(need_to_quit){
        endwin();
        return 0;
    }

    gener_field(g->bot_field);
    fill_bot_ships(g);

    int winner = shooting_loop(g);

    if(winner == -1){
        endwin();
        return 0;
    }

    wmove(g->win, LINES - 1, 0);
    wclrtoeol(g->win);
    wattron(g->win, A_REVERSE);
    if(winner == user)
        mvwprintw(g->win, LINES - 1, 0, WIN_MSG);
    else
        mvwprintw(g->win, LINES - 1, 0, LOSE_MSG);
    wattroff(g->win, A_REVERSE);
    wrefresh(g->win);

    getch();

    endwin();

    return 0;
}
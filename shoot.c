#include "shoot.h"


// название не очень
static void print_current_state(game *g, int x, int y) {
    mvwprintw(g->bot, 2*x-1, 4*y-2-1, " ");
    mvwprintw(g->bot, 2*x-1, 4*y-2+1, " ");
    if (g->bot_shot[x][y] == 1) {
        if (g->bot_field[x][y] == 1)
            mvwprintw(g->bot, 2*x-1, 4*y-2, "x");
        else
            mvwprintw(g->bot, 2*x-1, 4*y-2, ".");
    }
    else
        mvwprintw(g->bot, 2*x-1, 4*y-2, " ");
}


static void print_shot(game *g) {
    for (int i = 1; i <= 10; i++)
        for (int j = 1; j <= 10; j++)
            print_current_state(g, i, j);
}


static void print_current_cell(game *g, int x, int y) {
    mvwprintw(g->bot, 2*x-1, 4*y-2-1, ">");
    mvwprintw(g->bot, 2*x-1, 4*y-2+1, "<");
}


void shooting_loop(game *g) {
    for (int i = 0; i < 12; i++)
        for (int j = 0; j < 12; j++) 
            g->bot_shot[i][j] = 0;

    int x = 1, y = 1;
    int cells_left = 20; // откуда такое число?

    print_current_cell(g, x, y);
    wrefresh(g->bot);

    while (cells_left > 0) {
        int c = getch();
        switch(c) {
            case KEY_DOWN:
                print_current_state(g, x, y);
                if (x < 10)
                    x++;
                print_current_cell(g, x, y);
                break;

            case KEY_UP:
                print_current_state(g, x, y);
                if (x > 1)
                    x--;
                print_current_cell(g, x, y);
                break;

            case KEY_LEFT:
                print_current_state(g, x, y);
                if (y > 1)
                    y--;
                print_current_cell(g, x, y);
                break;

            case KEY_RIGHT:
                print_current_state(g, x, y);
                if (y < 10)
                    y++;
                print_current_cell(g, x, y);
                break;

            case 10: // enter
                if (g->bot_field[x][y] == 1) {
                    mvwprintw(g->bot, 2*x-1, 4*y-2, "x");
                    if (g->bot_shot[x][y] == 0)
                        cells_left--;
                    //else
                }
                else {
                    mvwprintw(g->bot, 2*x-1, 4*y-2, ".");
                }
                g->bot_shot[x][y] = 1;
                break;

            case 'h':
                help_loop(g->h);
                top_panel(g->pan);
                update_panels();
                doupdate();
                print_grid(g);
                print_ships(g); wrefresh(g->pl);
                print_shot(g);
                print_current_cell(g, x, y);
                break;

            case KEY_RESIZE:
                endwin();
                refresh();
                wclear(g->win);
                wrefresh(g->win);
                print_grid(g);
                print_ships(g); wrefresh(g->pl);
                print_shot(g);
                print_current_cell(g, x, y);
                break;

            case 'q':
                return;
        }
        wrefresh(g->bot);
    }
}
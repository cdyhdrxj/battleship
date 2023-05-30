#include "shoot.h"


// название не очень
static void print_current_state(game *g, int x, int y) {
    mvwprintw(g->bot, FIELD_X(x), FIELD_Y(y)-1, " ");
    mvwprintw(g->bot, FIELD_X(x), FIELD_Y(y)+1, " ");
    if (g->bot_shot[x][y] == 1) {
        if (g->bot_field[x][y] > 0)
            mvwprintw(g->bot, FIELD_X(x), FIELD_Y(y), "x");
        else
            mvwprintw(g->bot, FIELD_X(x), FIELD_Y(y), ".");
    }
    else
        mvwprintw(g->bot, FIELD_X(x), FIELD_Y(y), " ");
}


static void print_shot(game *g) {
    for (int i = 1; i <= 10; i++)
        for (int j = 1; j <= 10; j++){
            print_current_state(g, i, j);
            if(abs(g->user_shot[i][j]) == 1){
                mvwprintw(g->pl, FIELD_X(i), FIELD_Y(j)-1, ">");
                mvwprintw(g->pl, FIELD_X(i), FIELD_Y(j)+1, "<");
                wrefresh(g->pl);
            }
        }
}


static void print_current_cell(game *g, int x, int y) {
    mvwprintw(g->bot, FIELD_X(x), FIELD_Y(y)-1, ">");
    mvwprintw(g->bot, FIELD_X(x), FIELD_Y(y)+1, "<");
}


static int user_shooting(game *g) {
    int next_player = user;

    int x = 1, y = 1;

    int current_msg = you;

    int c;
    while (next_player == user) {
        print_shot(g);
        print_current_cell(g, x, y);
        wrefresh(g->bot);

        wmove(g->win, LINES - 1, 0);
        wclrtoeol(g->win);
        wattron(g->win, A_REVERSE);
        switch(current_msg){
            case you:
                mvwprintw(g->win, LINES - 1, 0, YOU_MSG);
                break;
            case hit:
                mvwprintw(g->win, LINES - 1, 0, HIT_MSG);
                break;
            case destr:
                mvwprintw(g->win, LINES - 1, 0, DESTROY_MSG);
                break;
        }
        wattroff(g->win, A_REVERSE);
        wrefresh(g->win);

        c = getch();
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

            case 10: //enter
                if (g->bot_field[x][y] > 0) {
                    mvwprintw(g->bot, FIELD_X(x), FIELD_Y(y), "x");
                    if (g->bot_shot[x][y] == 0){
                        int ship = g->bot_field[x][y] - 1;
                        g->bot_ships[ship].hit_cells++;
                        g->cells_left--;

                        if(g->bot_ships[ship].hit_cells == g->bot_ships[ship].size)
                            current_msg = destr;
                        else
                            current_msg = hit;
                    }
                }
                else {
                    if(g->bot_shot[x][y] == 0){
                        mvwprintw(g->bot, FIELD_X(x), FIELD_Y(y), ".");
                        next_player = bot;
                    }
                }
                g->bot_shot[x][y] = 1;
                print_shot(g);
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
                return 1;
        }
        wrefresh(g->bot);
    }

    return 0;
}


int shooting_loop(game *g){
    for (int i = 0; i < 12; i++)
        for (int j = 0; j < 12; j++){ 
            g->bot_shot[i][j] = 0;
            g->user_shot[i][j] = 0;
        }

    g->bot_shoot.is_battleship_found = 0;
    g->bot_shoot.multicells_found = 0;
    g->bot_shoot.is_destroyed = 1;
    g->bot_shoot.cells_left = 20;

    g->cells_left = 20;

    int first_player = rand() % 2;
    int need_to_quit = 0;

    while(1){
        if(first_player == user)
            need_to_quit = user_shooting(g);

        if(need_to_quit)
            return -1;
        
        bot_shooting(g);

        if(first_player == bot)
            need_to_quit = user_shooting(g);

        if(g->cells_left == 0)
            return user;

        if(g->bot_shoot.cells_left == 0)
            return bot;
    }
}
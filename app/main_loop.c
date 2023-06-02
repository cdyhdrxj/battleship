#include "main_loop.h"


// Цикл игры
void start_game(game *g) {
    print_grid(g);

    int need_to_quit = place_ships(g);
    if(need_to_quit)
        return;

    gener_field(g->bot_field);
    fill_bot_ships(g);

    int winner = shooting_loop(g);
    if(winner == -1)
        return;

    // Отобразить сообщение о выигрыше или проигрыше
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
}


// Цикл перестрелки
int shooting_loop(game *g){
    for (int i = 0; i < FIELD_SIZE + 2; i++)
        for (int j = 0; j < FIELD_SIZE + 2; j++){ 
            g->bot_shot[i][j] = not_shot;
            g->user_shot[i][j] = not_shot;
        }

    g->bot_shoot.is_battleship_found = 0;
    g->bot_shoot.multicells_found = 0;
    g->bot_shoot.is_destroyed = 1;
    g->bot_shoot.cells_left = NUMBER_OF_CELLS;

    g->cells_left = NUMBER_OF_CELLS;

    int first_player = rand() % 2;
    int need_to_quit = 0;

    while(1){
        if(first_player == user)
            need_to_quit = user_shooting(g);

        if(g->cells_left == 0)
            return user;

        if(need_to_quit)
            return -1;
        
        bot_shooting(g);

        if(g->bot_shoot.cells_left == 0)
            return bot;
        
        if(first_player == bot)
            need_to_quit = user_shooting(g);
    }
}
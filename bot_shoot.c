#include "bot_shoot.h"


static void make_buffer_zone(game *g) {
    for(int i = 1; i <= 10; i++){
        for(int j = 1; j <= 10; j++){
            if(g->user_shot[i][j] != 1)
                continue;

            for(int a = -1; a <= 1; a++)
                for(int b = -1; b <= 1; b++)
                    if(g->user_shot[i+a][j+b] < 1){
                        g->user_shot[i+a][j+b] = 2;

                        if((i+a+2) % 4 == (j+b) % 4)
                            g->bot_shoot.battleship_search++;

                        if((i+a) % 2 == (j+b) % 2)
                            g->bot_shoot.diagonals++;
                    }
        }
    }
}


static void finish_ship(game *g){
    int x, y;
    int i;

    for(i = 0; i < 4; i++){
        if(g->bot_shoot.poss_cell[i][0] == -1)
            continue;

        if(g->bot_shoot.poss_cell[i][1] == -1)
            continue;

        x = g->bot_shoot.poss_cell[i][0];
        y = g->bot_shoot.poss_cell[i][1];

        break;
    }

    mvwprintw(g->pl, FIELD_X(x), FIELD_Y(y)-1, ">");
    mvwprintw(g->pl, FIELD_X(x), FIELD_Y(y)+1, "<");
    wrefresh(g->pl);

    if(y % 4 == (x+2) % 4)
        g->bot_shoot.battleship_search++;

    if(x % 2 == y % 2)
        g->bot_shoot.diagonals++;

    if(g->user_field[x][y] == 0){
        g->bot_shoot.poss_cell[i][0] = -1;
        g->bot_shoot.poss_cell[i][1] = -1;
        g->user_shot[x][y] = -1;
        return;
    }

    g->user_shot[x][y] = 1;
    g->bot_shoot.cells_left--;

    g->user_ships[g->bot_shoot.current_ship].hit_cells++;

    if(g->user_ships[g->bot_shoot.current_ship].size == g->user_ships[g->bot_shoot.current_ship].hit_cells){
        g->bot_shoot.is_destroyed = 1;
        make_buffer_zone(g);
        return;
    }

    int x_new, y_new;

    switch(i){
        case 0:
            x_new = x-1; y_new = y;
            break;
        case 1:
            x_new = x; y_new = y+1;
            break;
        case 2:
            x_new = x+1; y_new = y;
            break;
        case 3:
            x_new = x; y_new = y-1;
            break;
    }

    if(x_new == 0 || y_new == 0 || x_new == 11 || y_new == 11 || g->user_shot[x_new][y_new] < 0){
        g->bot_shoot.poss_cell[i][0] = -1;
        g->bot_shoot.poss_cell[i][1] = -1;
    }
    else{
        g->bot_shoot.poss_cell[i][0] = x_new;
        g->bot_shoot.poss_cell[i][1] = y_new;
    }
}


static void hit(game *g, int x, int y) {
    g->bot_shoot.cells_left--;

    g->bot_shoot.current_ship = g->user_field[x][y] - 1;
    g->user_ships[g->bot_shoot.current_ship].hit_cells++;

    if(g->user_ships[g->bot_shoot.current_ship].size == 1){
        make_buffer_zone(g);
        return;
    }

    g->bot_shoot.is_destroyed = 0;

    if(x == 1 || g->user_shot[x-1][y] > 0){
        g->bot_shoot.poss_cell[0][0] = -1;
        g->bot_shoot.poss_cell[0][1] = -1;
    }
    else{
        g->bot_shoot.poss_cell[0][0] = x-1;
        g->bot_shoot.poss_cell[0][1] = y;
    }

    if(y == 10 || g->user_shot[x][y+1] > 0){
        g->bot_shoot.poss_cell[1][0] = -1;
        g->bot_shoot.poss_cell[1][1] = -1;
    }
    else{
        g->bot_shoot.poss_cell[1][0] = x;
        g->bot_shoot.poss_cell[1][1] = y+1;
    }

    if(x == 10 || g->user_shot[x+1][y] > 0){
        g->bot_shoot.poss_cell[2][0] = -1;
        g->bot_shoot.poss_cell[2][1] = -1;
    }
    else{
        g->bot_shoot.poss_cell[2][0] = x+1;
        g->bot_shoot.poss_cell[2][1] = y;
    }

    if(y == 1 || g->user_shot[x][y-1] > 0){
        g->bot_shoot.poss_cell[3][0] = -1;
        g->bot_shoot.poss_cell[3][1] = -1;
    }
    else{
        g->bot_shoot.poss_cell[3][0] = x;
        g->bot_shoot.poss_cell[3][1] = y-1;
    }
}


void bot_shooting(game *g) {
    usleep(300000);

    if(!g->bot_shoot.is_destroyed){
        finish_ship(g);
        return;
    }

    int x, y;

    if(g->bot_shoot.battleship_search < 24){
        do {
            x = 1 + rand() % 10;
            y = 1 + rand() % 10;
        } while(y % 4 != (x+2) % 4 || g->user_shot[x][y]);

        if(g->user_field[x][y] > 0){
            g->user_shot[x][y] = 1;
            hit(g, x, y);
        }
        else
            g->user_shot[x][y] = -1;

        mvwprintw(g->pl, FIELD_X(x), FIELD_Y(y)-1, ">");
        mvwprintw(g->pl, FIELD_X(x), FIELD_Y(y)+1, "<");
        wrefresh(g->pl);

        g->bot_shoot.battleship_search++;
        g->bot_shoot.diagonals++;
        return;
    }

    if(g->bot_shoot.diagonals < 50){
        do {
            x = 1 + rand() % 10;
            y = 1 + rand() % 10;
        } while(x % 2 != y % 2 || g->user_shot[x][y]);

        if(g->user_field[x][y] > 0){
            g->user_shot[x][y] = 1;
            hit(g, x, y);
        }
        else
            g->user_shot[x][y] = -1;

        mvwprintw(g->pl, FIELD_X(x), FIELD_Y(y)-1, ">");
        mvwprintw(g->pl, FIELD_X(x), FIELD_Y(y)+1, "<");
        wrefresh(g->pl);

        g->bot_shoot.diagonals++;
        return;
    }

    do {
        x = 1 + rand() % 10;
        y = 1 + rand() % 10;
    } while(g->user_shot[x][y]);

    if(g->user_field[x][y] > 0){
        g->user_shot[x][y] = 1;
        hit(g, x, y);
    }
    else
        g->user_shot[x][y] = -1;

    mvwprintw(g->pl, FIELD_X(x), FIELD_Y(y)-1, ">");
    mvwprintw(g->pl, FIELD_X(x), FIELD_Y(y)+1, "<");
    wrefresh(g->pl);

    return;
}
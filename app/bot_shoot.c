#include "bot_shoot.h"

/* user_shot[i][j] ==  0 - не было удара
                   ==  1 - был удар, успешно
                   == -1 - был удар, мимо
                   ==  2 - зона вокруг убитого корабля
*/


// Отмечает клетки вокруг убитых кораблей
static void make_buffer_zone(game *g) {
    for(int i = 1; i <= FIELD_SIZE; i++){
        for(int j = 1; j <= FIELD_SIZE; j++){
            if(g->user_shot[i][j] != shot)
                continue;

            for(int a = -1; a <= 1; a++)
                for(int b = -1; b <= 1; b++)
                    if(g->user_shot[i+a][j+b] == not_shot)
                        g->user_shot[i+a][j+b] = buffer;
        }
    }
}


// Добивает корабль
// Возвращает следующего игрока
static int finish_ship(game *g){
    // Координаты клетки для удара
    int x = -1, y = -1;
    // Кто ходит следующим
    int next_player = user;

    // Берём из массива первую клетку, в которую можно ударить
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

    // Ударяем
    mvwprintw(g->user, FIELD_X(x), FIELD_Y(y)-1, ">");
    mvwprintw(g->user, FIELD_X(x), FIELD_Y(y)+1, "<");
    wrefresh(g->user);

    // Мимо
    if(g->user_field[x][y] == 0){
        g->bot_shoot.poss_cell[i][0] = -1;
        g->bot_shoot.poss_cell[i][1] = -1;
        g->user_shot[x][y] = miss;
        return next_player;
    }

    // Попали
    g->user_shot[x][y] = shot;
    g->bot_shoot.cells_left--;
    next_player = bot;

    g->user_ships[g->bot_shoot.current_ship].hit_cells++;

    // Убили корабль
    if(g->user_ships[g->bot_shoot.current_ship].size == g->user_ships[g->bot_shoot.current_ship].hit_cells){
        if(g->user_ships[g->bot_shoot.current_ship].size == 4)
            g->bot_shoot.is_battleship_found = 1;

        g->bot_shoot.multicells_found++;

        g->bot_shoot.is_destroyed = 1;
        make_buffer_zone(g);
        return next_player;
    }

    // Если не убили, обновляем массив клеток, в которые можно стрелять
    int x_new = -1, y_new = -1;

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

    if(x_new == 0 || y_new == 0 || x_new == FIELD_SIZE+1 || y_new == FIELD_SIZE+1 || g->user_shot[x_new][y_new] != not_shot){
        g->bot_shoot.poss_cell[i][0] = -1;
        g->bot_shoot.poss_cell[i][1] = -1;
    }
    else{
        g->bot_shoot.poss_cell[i][0] = x_new;
        g->bot_shoot.poss_cell[i][1] = y_new;
    }

    // Если попали по вертикали, горизонтальные клетки не подойдут (и наоборот)
    g->bot_shoot.poss_cell[(i+1) % 4][0] = -1;
    g->bot_shoot.poss_cell[(i+1) % 4][1] = -1;

    g->bot_shoot.poss_cell[(i+3) % 4][0] = -1;
    g->bot_shoot.poss_cell[(i+3) % 4][1] = -1;

    return next_player;
}


// Для впервые раненного корабля составляет массив клеток, в которых он может находится
static void hit_ship(game *g, int x, int y) {
    g->bot_shoot.cells_left--;

    g->bot_shoot.current_ship = g->user_field[x][y] - 1;
    g->user_ships[g->bot_shoot.current_ship].hit_cells++;

    // Если катер - выходим, он уже убит
    if(g->user_ships[g->bot_shoot.current_ship].size == 1){
        make_buffer_zone(g);
        return;
    }

    // Есть неубитый корабль
    g->bot_shoot.is_destroyed = 0;

    // Клетка сверху
    if(x == 1 || g->user_shot[x-1][y] != not_shot){
        g->bot_shoot.poss_cell[0][0] = -1; // -1 - нельзя ударить
        g->bot_shoot.poss_cell[0][1] = -1;
    }
    else{
        g->bot_shoot.poss_cell[0][0] = x-1;
        g->bot_shoot.poss_cell[0][1] = y;
    }

    // Клетка справа
    if(y == FIELD_SIZE || g->user_shot[x][y+1] != not_shot){
        g->bot_shoot.poss_cell[1][0] = -1;
        g->bot_shoot.poss_cell[1][1] = -1;
    }
    else{
        g->bot_shoot.poss_cell[1][0] = x;
        g->bot_shoot.poss_cell[1][1] = y+1;
    }

    // Клетка снизу
    if(x == FIELD_SIZE || g->user_shot[x+1][y] != not_shot){
        g->bot_shoot.poss_cell[2][0] = -1;
        g->bot_shoot.poss_cell[2][1] = -1;
    }
    else{
        g->bot_shoot.poss_cell[2][0] = x+1;
        g->bot_shoot.poss_cell[2][1] = y;
    }

    // Клетка слева
    if(y == 1 || g->user_shot[x][y-1] != not_shot){
        g->bot_shoot.poss_cell[3][0] = -1;
        g->bot_shoot.poss_cell[3][1] = -1;
    }
    else{
        g->bot_shoot.poss_cell[3][0] = x;
        g->bot_shoot.poss_cell[3][1] = y-1;
    }
}


// Ход бота
void bot_shooting(game *g) {
    // Печатаем сообщение о ходе бота
    wmove(g->win, LINES - 1, 0);
    wclrtoeol(g->win);
    wattron(g->win, A_REVERSE);
    mvwprintw(g->win, LINES - 1, 0, BOT_MSG);
    wattroff(g->win, A_REVERSE);
    wrefresh(g->win);

    // Кому принадлежит следующий ход
    int next_player = bot;

    // Стреляем, пока не попадём мимо
    while(next_player == bot){
        if(g->bot_shoot.cells_left == 0)
            return;

        usleep(2000000);

        // Если есть раненый корабль, добиваем его
        if(!g->bot_shoot.is_destroyed){
            next_player = finish_ship(g);
            continue;
        }

        // Координаты клетки для удара
        int x, y;

        // Ищем линкор
        if(!g->bot_shoot.is_battleship_found){
            do {
                x = 1 + rand() % FIELD_SIZE;
                y = 1 + rand() % FIELD_SIZE;
            } while(y % 4 != (x+2) % 4 || g->user_shot[x][y] != not_shot);

            if(g->user_field[x][y] > 0){
                g->user_shot[x][y] = shot;
                hit_ship(g, x, y);
            }
            else{
                g->user_shot[x][y] = miss;
                next_player = user;
            }
        }
        // Ищем остальные многопалубники
        else if(g->bot_shoot.multicells_found != NUMBER_OF_MULTICELLS){
            do {
                x = 1 + rand() % FIELD_SIZE;
                y = 1 + rand() % FIELD_SIZE;
            } while(x % 2 != y % 2 || g->user_shot[x][y] != not_shot);

            if(g->user_field[x][y] > 0){
                g->user_shot[x][y] = shot;
                hit_ship(g, x, y);
            }
            else{
                g->user_shot[x][y] = miss;
                next_player = user;
            }
        }
        // Ищем катера
        else{
            do {
                x = 1 + rand() % FIELD_SIZE;
                y = 1 + rand() % FIELD_SIZE;
            } while(g->user_shot[x][y] != not_shot);

            if(g->user_field[x][y] > 0){
                g->user_shot[x][y] = shot;
                hit_ship(g, x, y);
            }
            else{
                g->user_shot[x][y] = miss;
                next_player = user;
            }
        }

        // Выделяем выбранную клетку
        mvwprintw(g->user, FIELD_X(x), FIELD_Y(y)-1, ">");
        mvwprintw(g->user, FIELD_X(x), FIELD_Y(y)+1, "<");
        wrefresh(g->user);
    }
}
#include "generate_bot_field.h"

/* bot_field[x][y] == 0 - нет корабля
                   == i - в клетке расположен корабль под номером i (g->bot_ships[i-1])
*/

// Расстановка многопалубных кораблей "змейкой"
void snake(int field[][FIELD_SIZE + 2], int var1, int var2){
    int a, b;

    if(var1 % 2)
        a = 4;
    else
        a = 5;

    if(var2 % 2)
        b = 5;
    else
        b = 6;

    int current_ship = 1;

    for(int i = 1; i <= 8; i++){
        if(i == a){
            current_ship++;
            continue;  
        }
        
        field[i][1] = current_ship;
    }

    current_ship++;

    for(int j = 3; j <= 8; j++){
        if(j == b){
            current_ship++;
            continue;
        }

        field[1][j] = current_ship;
    }

    current_ship++;
    field[FIELD_SIZE][1] = current_ship;
    field[FIELD_SIZE][2] = current_ship;
    current_ship++;
    field[1][FIELD_SIZE] = current_ship;
    field[2][FIELD_SIZE] = current_ship;
}


// Расстановка многопалубных кораблей двумя параллельными линиями
void line(int field[][FIELD_SIZE + 2], int var1, int var2, int var3) {
    int row1, row2;
    int a1, a2, b1, b2;

    switch(var1 % 3){
        case 0:
            row1 = 1;
            row2 = 3;
            break;
        case 1:
            row1 = 1;
            row2 = 10;
            break;
        default:
            row1 = 3;
            row2 = 1;
            break;
    }

    switch(var2 % 2){
        case 0:
            a1 = 5;
            a2 = 8;
            break;
        default:
            a1 = 3;
            a2 = 8;
            break;
    }

    switch(var3 % 3){
        case 0:
            b1 = 4;
            b2 = 8;
            break;
        case 1:
            b1 = 4;
            b2 = 7;
            break;
        default:
            b1 = 3;
            b2 = 7;
            break;
    }

    int current_ship = 1;

    for(int j = 1; j <= FIELD_SIZE; j++){
        if(j == a1 || j == a2){
            current_ship++;
            continue;
        }

        field[row1][j] = current_ship;            
    }

    current_ship++;

    for(int j = 1; j <= FIELD_SIZE; j++) {
        if(j == b1 || j == b2){
            current_ship++;
            continue;
        }

        field[row2][j] = current_ship; 
    }
}


// По матрице поля бота формирует массив кораблей ships[]
void fill_bot_ships(game *g) {
    for (int i = 0; i < NUMBER_OF_SHIPS; i++) {
        g->bot_ships[i].size = 0;
        g->bot_ships[i].hit_cells = 0;
    }


    for (int i = 0; i < FIELD_SIZE + 2; i++) {
        for (int j = 0; j < FIELD_SIZE + 2; j++) {
            if (g->bot_field[i][j] == 0)
                continue;

            int current_ship = g->bot_field[i][j];
            g->bot_ships[current_ship-1].size += 1;
        }
    }
}


// Генерирует поле бота
void gener_field(int field[][FIELD_SIZE + 2], int var1, int var2, int var3) {
    int f[FIELD_SIZE + 2][FIELD_SIZE + 2];
    for(int i = 0; i < FIELD_SIZE + 2; i++)
        for(int j = 0; j < FIELD_SIZE + 2; j++)
            f[i][j] = 0;

    // Выбираем одну из стратегий расстановки
    srand(time(NULL));
    if(rand() % 2)
        line(f, rand() % 3, rand() % 2, rand() % 3);
    else
        snake(f, rand() % 2, rand() % 2);

    // Рандомно выбираем координаты для катеров
    for(int i = NUMBER_OF_MULTICELLS + 1; i <= NUMBER_OF_SHIPS; i++){
        int flag = 1;
        int x, y;
        while(flag){
            flag = 0;
            x = 1 + rand() % FIELD_SIZE;
            y = 1 + rand() % FIELD_SIZE;

            for(int j = x-1; j <= x+1; j++)
                for(int k = y-1; k <= y+1; k++)
                     if(f[j][k] > 0)
                        flag = 1;
        }

            f[x][y] = i;
    }

    // Рандомно поворачиваем и зеркально отображаем получившееся поле
    int d1 = (var1 % 2) * (FIELD_SIZE + 1);
    int d2 = (var2 % 2) * (FIELD_SIZE + 1);

    int var = var3 % 2;
    for(int i = 1; i <= FIELD_SIZE; i++) {
        for(int j = 1; j <= FIELD_SIZE; j++) {
            if(var)
                field[i][j] = f[abs(d1 - i)][abs(d2 - j)];
            else
                field[i][j] = f[abs(d1 - j)][abs(d2 - i)];           
        }
    }
}

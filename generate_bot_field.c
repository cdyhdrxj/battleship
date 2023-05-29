#include "generate_bot_field.h"


static void snake(int field[][12]){
    int a, b;

    if(rand() % 2)
        a = 4;
    else
        a = 5;

    if(rand() % 2)
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
    field[10][1] = current_ship;
    field[10][2] = current_ship;
    current_ship++;
    field[1][10] = current_ship;
    field[2][10] = current_ship;
}


static void line(int field[][12]) {
    int row1, row2;
    int a1, a2, b1, b2;

    switch(rand() % 3){
        case 0:
            row1 = 1;
            row2 = 3;
            break;
        case 1:
            row1 = 1;
            row2 = 10;
            break;
        case 2:
            row1 = 3;
            row2 = 1;
            break;
    }

    switch(rand() % 3){
        case 0:
            a1 = 5;
            a2 = 8;
            break;
        case 1:
            a1 = 3;
            a2 = 8;
            break;
        case 2:
            a1 = 3;
            a2 = 6;
            break;
    }

    switch(rand() % 3){
        case 0:
            b1 = 4;
            b2 = 8;
            break;
        case 1:
            b1 = 4;
            b2 = 7;
            break;
        case 2:
            b1 = 3;
            b2 = 7;
            break;
    }

    int current_ship = 1;

    for(int j = 1; j <= 10; j++){
        if(j == a1 || j == a2){
            current_ship++;
            continue;
        }

        field[row1][j] = current_ship;            
    }

    current_ship++;

    for(int j = 1; j <= 10; j++) {
        if(j == b1 || j == b2){
            current_ship++;
            continue;
        }

        field[row2][j] = current_ship; 
    }
}


void fill_bot_ships(game *g) {
    for (int i = 0; i < 10; i++) {
        g->bot_ships[i].size = 0;
        g->bot_ships[i].hit_cells = 0;
    }


    for (int i = 0; i < 12; i++) {
        for (int j = 0; j < 12; j++) {
            if (g->bot_field[i][j] == 0)
                continue;

            int current_ship = g->bot_field[i][j];
            g->bot_ships[current_ship-1].size += 1;
        }
    }
}


void gener_field(int field[][12]){
    int f[12][12];
    for(int i = 0; i < 12; i++)
        for(int j = 0; j < 12; j++)
            f[i][j] = 0;

    srand(time(NULL));
    int var = rand() % 2;
    if(var)
        line(f);
    else
        snake(f);

    for(int i = 7; i <= 10; i++){
        int flag = 1;
        int x, y;
        while(flag){
            flag = 0;
            x = 1 + rand() % 10;
            y = 1 + rand() % 10;

            for(int j = x-1; j <= x+1; j++)
                for(int k = y-1; k <= y+1; k++)
                     if(f[j][k] > 0)
                        flag = 1;
            }

            f[x][y] = i;
        }

    int d1 = (rand() % 2) * 11;
    int d2 = (rand() % 2) * 11;

    var = rand() % 2;

    for(int i = 1; i <= 10; i++) {
        for(int j = 1; j <= 10; j++) {
            if(var)
                field[i][j] = f[abs(d1 - i)][abs(d2 - j)];
            else
                field[i][j] = f[abs(d1 - j)][abs(d2 - i)];           
        }
    }
}
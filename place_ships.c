#include "place_ships.h"


static void ship_down(game *g, int *x_gl, int *y_gl, int orient, int size) {
    int x = *x_gl;
    int y = *y_gl;

    if(orient == 0) {
        if(x < 10){
            *x_gl += 1; x++;
            for(int i = 0; i < size; i++){
                mvwprintw(g->pl, FIELD_X(x), FIELD_Y(y+i), "o");
                if(!g->user_field[x-1][y+i])
                    mvwprintw(g->pl, FIELD_X(x-1), FIELD_Y(y+i), " ");
                else
                    mvwprintw(g->pl, FIELD_X(x-1), FIELD_Y(y+i), "x");
            }
        }
    }
    else {
        if(x + size <= 10){
            mvwprintw(g->pl, FIELD_X(x+size), FIELD_Y(y), "o");
            if(!g->user_field[x][y])
                mvwprintw(g->pl, FIELD_X(x), FIELD_Y(y), " ");
            else
                mvwprintw(g->pl, FIELD_X(x), FIELD_Y(y), "x");
            *x_gl += 1;
        } 
    }
}


static void ship_up(game *g, int *x_gl, int *y_gl, int orient, int size) {
    int x = *x_gl;
    int y = *y_gl;

    if(orient == 0) {
        if(x > 1){
            *x_gl -= 1; x--;
            for(int i = 0; i < size; i++){
                mvwprintw(g->pl, FIELD_X(x), FIELD_Y(y+i), "o");
                if(!g->user_field[x+1][y+i])
                    mvwprintw(g->pl, FIELD_X(x+1), FIELD_Y(y+i), " ");
                else
                    mvwprintw(g->pl, FIELD_X(x+1), FIELD_Y(y+i), "x");
            }
        }
    }
    else {
        if(x > 1){
            *x_gl -= 1; x--;
            mvwprintw(g->pl, FIELD_X(x), FIELD_Y(y), "o");
            if(!g->user_field[x+size][y])
                mvwprintw(g->pl, FIELD_X(x+size), FIELD_Y(y), " ");
            else
                mvwprintw(g->pl, FIELD_X(x+size), FIELD_Y(y), "x");
        } 
    }
}


static void ship_left(game *g, int *x_gl, int *y_gl, int orient, int size) {
    int x = *x_gl;
    int y = *y_gl;

    if(orient == 0) {
        if(y > 1){
            *y_gl -= 1; y--;
            mvwprintw(g->pl, FIELD_X(x), FIELD_Y(y), "o");
            if(!g->user_field[x][y+size])
                mvwprintw(g->pl, FIELD_X(x), FIELD_Y(y+size), " ");
            else
                mvwprintw(g->pl, FIELD_X(x), FIELD_Y(y+size), "x");
        } 
    }
    else {
        if(y > 1){
            *y_gl -= 1; y--;
            for(int i = 0; i < size; i++){
                mvwprintw(g->pl, FIELD_X(x+i), FIELD_Y(y), "o");
                if(!g->user_field[x+i][y+1])
                    mvwprintw(g->pl, FIELD_X(x+i), FIELD_Y(y+1), " ");
                else
                    mvwprintw(g->pl, FIELD_X(x+i), FIELD_Y(y+1), "x");
            }
        }
    }
}


static void ship_right(game *g, int *x_gl, int *y_gl, int orient, int size) {
    int x = *x_gl;
    int y = *y_gl;

    if(orient == 0) {
        if(y + size <= 10){
            mvwprintw(g->pl, FIELD_X(x), FIELD_Y(y+size), "o");
            if(!g->user_field[x][y])
                mvwprintw(g->pl, FIELD_X(x), FIELD_Y(y), " ");
            else
                mvwprintw(g->pl, FIELD_X(x), FIELD_Y(y), "x"); 
            *y_gl += 1; y++;
        }  
    }
    else {
        if(y < 10){
            *y_gl += 1; y++;
            for(int i = 0; i < size; i++){
                mvwprintw(g->pl, FIELD_X(x+i), FIELD_Y(y), "o");
                if(!g->user_field[x+i][y-1])
                    mvwprintw(g->pl, FIELD_X(x+i), FIELD_Y(y-1), " ");
                else
                    mvwprintw(g->pl, FIELD_X(x+i), FIELD_Y(y-1), "x");
            }
        }
    }
}


static void ship_rotate(game *g, int x, int y, int *orient_gl, int size) {
    if(*orient_gl == 0){
        if(x + size - 1 <= 10){
            *orient_gl = !(*orient_gl);
            for(int i = 1; i < size; i++){
                mvwprintw(g->pl, FIELD_X(x+i), FIELD_Y(y), "o");
                if(!g->user_field[x][y+i])
                    mvwprintw(g->pl, FIELD_X(x), FIELD_Y(y+i), " ");
                else
                    mvwprintw(g->pl, FIELD_X(x), FIELD_Y(y+i), "x");
            }
        }
        else{
            wmove(g->win, LINES - 1, 0);
            wclrtoeol(g->win);
            wattron(g->win, A_REVERSE);
            mvwprintw(g->win, LINES - 1, 0, ROTATE_MSG);
            wattroff(g->win, A_REVERSE);
            wrefresh(g->win);
        }
    }
    else{
        if(y + size - 1 <= 10){
            *orient_gl = !(*orient_gl);
            for(int i = 1; i < size; i++){
                mvwprintw(g->pl, FIELD_X(x), FIELD_Y(y+i), "o");
                if(!g->user_field[x+i][y])
                    mvwprintw(g->pl, FIELD_X(x+i), FIELD_Y(y), " ");
                else
                    mvwprintw(g->pl, FIELD_X(x+i), FIELD_Y(y), "x");
            }
        }
        else{
            wmove(g->win, LINES - 1, 0);
            wclrtoeol(g->win);
            wattron(g->win, A_REVERSE);
            mvwprintw(g->win, LINES - 1, 0, ROTATE_MSG);
            wattroff(g->win, A_REVERSE);
            wrefresh(g->win);
        }
    }      
}


static int ship_place(game *g, int x, int y, int orient, int size) {
    if(orient == 0) {
        int flag = 1;
        for (int row = x-1; row <= x+1; row++) {
            for (int col = y-1; col <= y + size; col++) {
                if (g->user_field[row][col] == 1)
                    flag = 0;
            }
        }

        if (flag == 0){
            wmove(g->win, LINES - 1, 0);
            wclrtoeol(g->win);
            wattron(g->win, A_REVERSE);
            mvwprintw(g->win, LINES - 1, 0, MOVE_MSG);
            wattroff(g->win, A_REVERSE);
            wrefresh(g->win);
            return 0;
        }
        
        for(int i = 0; i < size; i++){
            g->user_field[x][y+i] = 1;
            mvwprintw(g->pl, FIELD_X(x), FIELD_Y(y+i), "x");

        }
    }
    else {
        int flag = 1;
        for (int row = x-1; row <= x + size; row++) {
            for (int col = y-1; col <= y+1; col++) {
                if (g->user_field[row][col] == 1)
                    flag = 0;
            }
        }

        if (flag == 0){
            wmove(g->win, LINES - 1, 0);
            wclrtoeol(g->win);
            wattron(g->win, A_REVERSE);
            mvwprintw(g->win, LINES - 1, 0, MOVE_MSG);
            wattroff(g->win, A_REVERSE);
            wrefresh(g->win);
            return 0;
        }
        
        for(int i = 0; i < size; i++){
            g->user_field[x+i][y] = 1;  
            mvwprintw(g->pl, FIELD_X(x+i), FIELD_Y(y), "x");
        }
    }
    return 1;
}


void print_ships(game *g) {
    for (int i = 1; i <= 10; i++)
        for (int j = 1; j <= 10; j++)
            if (g->user_field[i][j] == 1)
                mvwprintw(g->pl, FIELD_X(i), FIELD_Y(j), "x");
            else
                mvwprintw(g->pl, FIELD_X(i), FIELD_Y(j), " ");
}


static void print_current_ship(game *g, int x, int y, int orient, int size) {
    if (orient == 0) {
        for(int i = 0; i < size; i++)
            mvwprintw(g->pl, FIELD_X(x), FIELD_Y(y+i), "o");
    }
    else {
        for(int i = 0; i < size; i++)
            mvwprintw(g->pl, FIELD_X(x+i), FIELD_Y(y), "o");
    }
}


void place_ships(game *g) {
    keypad(g->pl, TRUE);
    curs_set(0);

    int size[] = {4, 3, 3, 2, 2, 2, 1, 1, 1, 1};
    int current_ship = 0;
    int orientation = 0; // 0 --, 1 |

    for(int col = 0; col < 12; col++)
        for(int row = 0; row < 12; row++)
            g->user_field[col][row] = 0;

    int x = 1, y = 1;
    print_current_ship(g, x, y, orientation, size[current_ship]);
    wrefresh(g->pl);

    int c;
    while(current_ship < 10) {
        c = getch();
        wmove(g->win, LINES - 1, 0);
        wclrtoeol(g->win);
        wattron(g->win, A_REVERSE);
        mvwprintw(g->win, LINES - 1, 0, "%s", MAIN_MSG);
        wattroff(g->win, A_REVERSE);
        wrefresh(g->win);

        switch(c) {
            case KEY_DOWN:
                ship_down(g, &x, &y, orientation, size[current_ship]);
                break;

            case KEY_UP:
                ship_up(g, &x, &y, orientation, size[current_ship]);
                break;

            case KEY_LEFT:
                ship_left(g, &x, &y, orientation, size[current_ship]);
                break;
                
            case KEY_RIGHT:
                ship_right(g, &x, &y, orientation, size[current_ship]);
                break;

            case 32: // space
                ship_rotate(g, x, y, &orientation, size[current_ship]);
                break;

            case 10: // enter
                if (!ship_place(g, x, y, orientation, size[current_ship]))
                    break;

                current_ship++;
                if(current_ship == 10)
                    break;

                orientation = 0;
                x = 1;
                y = 1;
                print_current_ship(g, x, y, orientation, size[current_ship]);
                break;

            case 'h':
                help_loop(g->h);
                top_panel(g->pan);
                update_panels();
                doupdate();
                print_grid(g);
                print_ships(g);
                print_current_ship(g, x, y, orientation, size[current_ship]);
                break;

            case 'q':
                return;

            case KEY_RESIZE:
                endwin();
                refresh();
                wclear(g->win);
                wrefresh(g->win);
                print_grid(g);
                print_ships(g);
                print_current_ship(g, x, y, orientation, size[current_ship]);
                break;

            default:
                break;
        }
        
        wrefresh(g->pl);
    }
}
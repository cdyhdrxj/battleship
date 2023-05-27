#include "place_ships.h"


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
    mvwprintw(g->pl, 2*x-1, 4*y-2, "o | o | o | o");
    wrefresh(g->pl);

    int c;
    while(current_ship < 10) {
        c = wgetch(g->pl);
        switch(c) {
            case KEY_DOWN:
                if(orientation == 0) {
                    if(x < 10){
                        x++;
                        for(int i = 0; i < size[current_ship]; i++){
                            mvwprintw(g->pl, 2*x-1, 4*(y+i)-2, "o");
                            if(!g->user_field[x-1][y+i])
                                mvwprintw(g->pl, 2*(x-1)-1, 4*(y+i)-2, " ");
                            else
                                mvwprintw(g->pl, 2*(x-1)-1, 4*(y+i)-2, "x");
                        }
                    }
                }
                else {
                    if(x + size[current_ship] <= 10){
                        mvwprintw(g->pl, 2*(x+size[current_ship])-1, 4*y-2, "o");
                        if(!g->user_field[x][y])
                            mvwprintw(g->pl, 2*x-1, 4*y-2, " ");
                        else
                            mvwprintw(g->pl, 2*x-1, 4*y-2, "x");
                        x++;
                    } 
                }
                break;

            case KEY_UP:
                if(orientation == 0) {
                    if(x > 1){
                        x--;
                        for(int i = 0; i < size[current_ship]; i++){
                            mvwprintw(g->pl, 2*x-1, 4*(y+i)-2, "o");
                            if(!g->user_field[x+1][y+i])
                                mvwprintw(g->pl, 2*(x+1)-1, 4*(y+i)-2, " ");
                            else
                                mvwprintw(g->pl, 2*(x+1)-1, 4*(y+i)-2, "x");

                        }
                    }
                }
                else {
                    if(x > 1){
                        x--;
                        mvwprintw(g->pl, 2*x-1, 4*y-2, "o");
                        if(!g->user_field[x+size[current_ship]][y])
                            mvwprintw(g->pl, 2*(x+size[current_ship])-1, 4*y-2, " ");
                        else
                            mvwprintw(g->pl, 2*(x+size[current_ship])-1, 4*y-2, "x");
                    } 
                }
                break;

            case KEY_LEFT:
                if(orientation == 0) {
                    if(y > 1){
                        y--;
                        mvwprintw(g->pl, 2*x-1, 4*y-2, "o");
                        if(!g->user_field[x][y+size[current_ship]])
                            mvwprintw(g->pl, 2*x-1, 4*(y+size[current_ship])-2, " ");
                        else
                            mvwprintw(g->pl, 2*x-1, 4*(y+size[current_ship])-2, "x");
                    } 
                }
                else {
                    if(y > 1){
                        y--;
                        for(int i = 0; i < size[current_ship]; i++){
                            mvwprintw(g->pl, 2*(x+i)-1, 4*y-2, "o");
                            if(!g->user_field[x+i][y+1])
                                mvwprintw(g->pl, 2*(x+i)-1, 4*(y+1)-2, " ");
                            else
                                mvwprintw(g->pl, 2*(x+i)-1, 4*(y+1)-2, "x");
                        }
                    }
                }
                break;
                
            case KEY_RIGHT:
                if(orientation == 0) {
                    if(y + size[current_ship] <= 10){
                        mvwprintw(g->pl, 2*x-1, 4*(y+size[current_ship])-2, "o");
                        if(!g->user_field[x][y])
                            mvwprintw(g->pl, 2*x-1, 4*y-2, " ");
                        else
                            mvwprintw(g->pl, 2*x-1, 4*y-2, "x"); 
                        y++;
                    }  
                }
                else {
                    if(y < 10){
                        y++;
                        for(int i = 0; i < size[current_ship]; i++){
                            mvwprintw(g->pl, 2*(x+i)-1, 4*y-2, "o");
                            if(!g->user_field[x+i][y-1])
                                mvwprintw(g->pl, 2*(x+i)-1, 4*(y-1)-2, " ");
                            else
                                mvwprintw(g->pl, 2*(x+i)-1, 4*(y-1)-2, "x");
                        }
                    }
                }
                break;

            case 32: // space
                if(orientation == 0){
                    if(x + size[current_ship] - 1 <= 10){
                        orientation = !orientation;
                        for(int i = 1; i < size[current_ship]; i++){
                            mvwprintw(g->pl, 2*(x+i)-1, 4*y-2, "o");
                            if(!g->user_field[x][y+i])
                                mvwprintw(g->pl, 2*x-1, 4*(y+i)-2, " ");
                            else
                                mvwprintw(g->pl, 2*x-1, 4*(y+i)-2, "x");
                        }
                    }
                    else{
                        wattron(g->win, A_REVERSE);
                        mvwprintw(g->win, LINES - 2, 0, "Can't rotate");
                        wattroff(g->win, A_REVERSE);
                        wrefresh(g->win);
                    }
                }
                else{
                    if(y + size[current_ship] - 1 <= 10){
                        orientation = !orientation;
                        for(int i = 1; i < size[current_ship]; i++){
                            mvwprintw(g->pl, 2*x-1, 4*(y+i)-2, "o");
                            if(!g->user_field[x+i][y])
                                mvwprintw(g->pl, 2*(x+i)-1, 4*y-2, " ");
                            else
                                mvwprintw(g->pl, 2*(x+i)-1, 4*y-2, "x");
                        }
                    }
                    else{
                        wattron(g->win, A_REVERSE);
                        mvwprintw(g->win, LINES - 2, 0, "Can't rotate");
                        wattroff(g->win, A_REVERSE);
                        wrefresh(g->win);
                    }
                }             
                break;

            case 10: // enter
                if(orientation == 0) {
                    int flag = 1;
                    for (int row = x-1; row <= x+1; row++) {
                        for (int col = y-1; col <= y + size[current_ship]; col++) {
                            if (g->user_field[row][col] == 1)
                                flag = 0;
                        }
                    }

                    if (flag == 0){
                        wattron(g->win, A_REVERSE);
                        mvwprintw(g->win, LINES - 2, 0, "Move this ship");
                        wattroff(g->win, A_REVERSE);
                        wrefresh(g->win);
                        break;
                    }
                    
                    for(int i = 0; i < size[current_ship]; i++){
                        g->user_field[x][y+i] = 1;
                        mvwprintw(g->pl, 2*x-1, 4*(y+i)-2, "x");

                    }
                }
                else {
                    int flag = 1;
                    for (int row = x-1; row <= x + size[current_ship]; row++) {
                        for (int col = y-1; col <= y+1; col++) {
                            if (g->user_field[row][col] == 1)
                                flag = 0;
                        }
                    }

                    if (flag == 0){
                        wattron(g->win, A_REVERSE);
                        mvwprintw(g->win, LINES - 2, 0, "Move this ship");
                        wattroff(g->win, A_REVERSE);
                        wrefresh(g->win);
                        break;
                    }
                    
                    for(int i = 0; i < size[current_ship]; i++){
                        g->user_field[x+i][y] = 1;  
                        mvwprintw(g->pl, 2*(x+i)-1, 4*y-2, "x");
                    }

                }

                wmove(g->win, LINES-2, 0);
                wclrtoeol(g->win);
                wrefresh(g->win);  

                current_ship++;
                if(current_ship == 10)
                    break;

                orientation = 0;
                x = 1;
                y = 1;
                for(int i = 0; i < size[current_ship]; i++)
                    mvwprintw(g->pl, 2*x-1, 4*(x+i)-2, "o");
                break;

            case 'h':
                help_loop(g->h);
                top_panel(g->pan);
                update_panels();
                doupdate();
                print_grid(g);
                break;

            case 'q':
                return;
                break;

            case KEY_RESIZE:
                endwin();
                refresh();
                print_grid(g);
                break;

            default:
                break;
        }
        
        wrefresh(g->pl);
    }
}
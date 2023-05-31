#include "place_ships.h"

/* user_field[x][y] == 0 - нет корабля
                    == i - в клетке расположен корабль под номером i (g->user_ships[i-1])
*/

// Опускает корабль на 1 клетку
static void ship_down(game *g, int *x_gl, int *y_gl, int orient, int size) {
    int x = *x_gl;
    int y = *y_gl;

    // Каждую клетку горизонтального корабля перемещаем вниз, если можно
    if(orient == horizontal) {
        if(x < FIELD_SIZE){
            *x_gl += 1; x++;
            for(int i = 0; i < size; i++){
                mvwprintw(g->user, FIELD_X(x), FIELD_Y(y+i), "o");
                if(!g->user_field[x-1][y+i])
                    mvwprintw(g->user, FIELD_X(x-1), FIELD_Y(y+i), " ");
                else
                    mvwprintw(g->user, FIELD_X(x-1), FIELD_Y(y+i), "x");
            }
        }
    }
    // У вертикального корабля перемещаем вниз только верхнюю клетку, если можно
    else {
        if(x + size <= FIELD_SIZE){
            mvwprintw(g->user, FIELD_X(x+size), FIELD_Y(y), "o");
            if(!g->user_field[x][y])
                mvwprintw(g->user, FIELD_X(x), FIELD_Y(y), " ");
            else
                mvwprintw(g->user, FIELD_X(x), FIELD_Y(y), "x");
            *x_gl += 1;
        } 
    }
}


// Поднимает корабль на 1 клетку
static void ship_up(game *g, int *x_gl, int *y_gl, int orient, int size) {
    int x = *x_gl;
    int y = *y_gl;

    // Каждую клетку горизонтального корабля перемещаем вверх, если можно
    if(orient == horizontal) {
        if(x > 1){
            *x_gl -= 1; x--;
            for(int i = 0; i < size; i++){
                mvwprintw(g->user, FIELD_X(x), FIELD_Y(y+i), "o");
                if(!g->user_field[x+1][y+i])
                    mvwprintw(g->user, FIELD_X(x+1), FIELD_Y(y+i), " ");
                else
                    mvwprintw(g->user, FIELD_X(x+1), FIELD_Y(y+i), "x");
            }
        }
    }
    // У вертикального корабля перемещаем вверх только нижнюю клетку, если можно
    else {
        if(x > 1){
            *x_gl -= 1; x--;
            mvwprintw(g->user, FIELD_X(x), FIELD_Y(y), "o");
            if(!g->user_field[x+size][y])
                mvwprintw(g->user, FIELD_X(x+size), FIELD_Y(y), " ");
            else
                mvwprintw(g->user, FIELD_X(x+size), FIELD_Y(y), "x");
        } 
    }
}


// Перемещает корабль влево на 1 клетку
static void ship_left(game *g, int *x_gl, int *y_gl, int orient, int size) {
    int x = *x_gl;
    int y = *y_gl;

    // У горизонтального корабля перемещаем влево только правую клетку, если можно
    if(orient == horizontal) {
        if(y > 1){
            *y_gl -= 1; y--;
            mvwprintw(g->user, FIELD_X(x), FIELD_Y(y), "o");
            if(!g->user_field[x][y+size])
                mvwprintw(g->user, FIELD_X(x), FIELD_Y(y+size), " ");
            else
                mvwprintw(g->user, FIELD_X(x), FIELD_Y(y+size), "x");
        } 
    }
    // Каждую клетку вертикального корабля перемещаем влево, если можно
    else {
        if(y > 1){
            *y_gl -= 1; y--;
            for(int i = 0; i < size; i++){
                mvwprintw(g->user, FIELD_X(x+i), FIELD_Y(y), "o");
                if(!g->user_field[x+i][y+1])
                    mvwprintw(g->user, FIELD_X(x+i), FIELD_Y(y+1), " ");
                else
                    mvwprintw(g->user, FIELD_X(x+i), FIELD_Y(y+1), "x");
            }
        }
    }
}


// Перемещает корабль вправо на 1 клетку
static void ship_right(game *g, int *x_gl, int *y_gl, int orient, int size) {
    int x = *x_gl;
    int y = *y_gl;

    // У горизонтального корабля перемещаем вправо только левую клетку, если можно
    if(orient == horizontal) {
        if(y + size <= FIELD_SIZE){
            mvwprintw(g->user, FIELD_X(x), FIELD_Y(y+size), "o");
            if(!g->user_field[x][y])
                mvwprintw(g->user, FIELD_X(x), FIELD_Y(y), " ");
            else
                mvwprintw(g->user, FIELD_X(x), FIELD_Y(y), "x"); 
            *y_gl += 1; y++;
        }  
    }
    // Каждую клетку вертикального корабля перемещаем вправо, если можно
    else {
        if(y < FIELD_SIZE){
            *y_gl += 1; y++;
            for(int i = 0; i < size; i++){
                mvwprintw(g->user, FIELD_X(x+i), FIELD_Y(y), "o");
                if(!g->user_field[x+i][y-1])
                    mvwprintw(g->user, FIELD_X(x+i), FIELD_Y(y-1), " ");
                else
                    mvwprintw(g->user, FIELD_X(x+i), FIELD_Y(y-1), "x");
            }
        }
    }
}


// Поворачивает корабль
static void ship_rotate(game *g, int x, int y, int *orient_gl, int size) {
    // Если получается повернуть корабль вокруг верхней (левой) клетки - поворачиваем:
    //  x x x x
    //  x        - функция умеет только поворот такого типа
    //  x
    //  x
    if(*orient_gl == horizontal){
        if(x + size - 1 <= FIELD_SIZE){
            *orient_gl = !(*orient_gl);
            for(int i = 1; i < size; i++){
                mvwprintw(g->user, FIELD_X(x+i), FIELD_Y(y), "o");
                if(!g->user_field[x][y+i])
                    mvwprintw(g->user, FIELD_X(x), FIELD_Y(y+i), " ");
                else
                    mvwprintw(g->user, FIELD_X(x), FIELD_Y(y+i), "x");
            }
            return;
        }
    }
    else{
        if(y + size - 1 <= FIELD_SIZE){
            *orient_gl = !(*orient_gl);
            for(int i = 1; i < size; i++){
                mvwprintw(g->user, FIELD_X(x), FIELD_Y(y+i), "o");
                if(!g->user_field[x+i][y])
                    mvwprintw(g->user, FIELD_X(x+i), FIELD_Y(y), " ");
                else
                    mvwprintw(g->user, FIELD_X(x+i), FIELD_Y(y), "x");
            }
            return;
        }
    }

    // Иначе - печатаем сообщение о том, что корабль не повернуть
    wmove(g->win, LINES - 1, 0);
    wclrtoeol(g->win);
    wattron(g->win, A_REVERSE);
    mvwprintw(g->win, LINES - 1, 0, ROTATE_MSG);
    wattroff(g->win, A_REVERSE);
    wrefresh(g->win);
}


// Устанавливает корабль
// Возвращает 1, если корабль можно установить, 0 иначе
static int ship_place(game *g, int x, int y, int orient, int size, int current_ship) {
    // Проверяем, не граничит ли корабль с другими кораблями по сторонам или углам
    int x_max, y_max;

    if(orient == horizontal) {
        x_max = x + 1;
        y_max = y + size;
    }
    else {
        x_max = x + size;
        y_max = y + 1;
    }

    int flag = 1;
    for (int row = x-1; row <= x_max; row++)
        for (int col = y-1; col <= y_max; col++)
            if (g->user_field[row][col] != 0)
                flag = 0;

    // Если граничит, выводим сообщение, что нельзя поставить корабль и выходим
    if (flag == 0){
        wmove(g->win, LINES - 1, 0);
        wclrtoeol(g->win);
        wattron(g->win, A_REVERSE);
        mvwprintw(g->win, LINES - 1, 0, MOVE_MSG);
        wattroff(g->win, A_REVERSE);
        wrefresh(g->win);
        return 0;
    }

    // Иначе устанавливаем корабль и отображаем его
    if(orient == horizontal)
        for(int i = 0; i < size; i++)
            g->user_field[x][y+i] = current_ship + 1;
    else
        for(int i = 0; i < size; i++)
            g->user_field[x+i][y] = current_ship + 1;  
    print_ships(g);

    return 1;
}


// Печатает установленные корабли на поле пользователя
void print_ships(game *g) {
    for (int i = 1; i <= FIELD_SIZE; i++)
        for (int j = 1; j <= FIELD_SIZE; j++)
            if (g->user_field[i][j] != 0)
                mvwprintw(g->user, FIELD_X(i), FIELD_Y(j), "x");
            else
                mvwprintw(g->user, FIELD_X(i), FIELD_Y(j), " ");
}


// Печатает текущий устанавливаемый корабль
static void print_current_ship(game *g, int x, int y, int orient, int size) {
    if (orient == horizontal) {
        for(int i = 0; i < size; i++)
            mvwprintw(g->user, FIELD_X(x), FIELD_Y(y+i), "o");
    }
    else {
        for(int i = 0; i < size; i++)
            mvwprintw(g->user, FIELD_X(x+i), FIELD_Y(y), "o");
    }
}


// Расстановка кораблей пользователем
// Возвращает 1, если нужно выйти из приложения, 0 иначе
int place_ships(game *g) {
    keypad(g->user, 1);
    curs_set(0);

    int size[] = SHIPS;
    int current_ship = 0;
    int orientation = horizontal;

    for(int col = 0; col < FIELD_SIZE + 2; col++)
        for(int row = 0; row < FIELD_SIZE + 2; row++)
            g->user_field[col][row] = 0;

    int x = 1, y = 1;
    print_current_ship(g, x, y, orientation, size[current_ship]);
    wrefresh(g->user);

    int c;
    while(current_ship < NUMBER_OF_SHIPS) {
        c = getch();
        wmove(g->win, LINES - 1, 0);
        wclrtoeol(g->win);
        wattron(g->win, A_REVERSE);
        mvwprintw(g->win, LINES - 1, 0, "%s", MAIN_MSG);
        wattroff(g->win, A_REVERSE);
        wrefresh(g->win);

        switch(c) {
            case KEY_DOWN: // Опустить корабль на 1 клетку
                ship_down(g, &x, &y, orientation, size[current_ship]);
                break;

            case KEY_UP: // Поднять корабль на 1 клетку
                ship_up(g, &x, &y, orientation, size[current_ship]);
                break;

            case KEY_LEFT: // Переместить корабль влево на 1 клетку
                ship_left(g, &x, &y, orientation, size[current_ship]);
                break;
                
            case KEY_RIGHT: // Переместить корабль вправо на 1 клетку
                ship_right(g, &x, &y, orientation, size[current_ship]);
                break;

            case 32: // space - перевернуть корабль
                ship_rotate(g, x, y, &orientation, size[current_ship]);
                break;

            case 10: // enter - установить корабль
                if (!ship_place(g, x, y, orientation, size[current_ship], current_ship))
                    break;

                g->user_ships[current_ship].size = size[current_ship];
                g->user_ships[current_ship].hit_cells = 0;

                current_ship++;
                if(current_ship == NUMBER_OF_SHIPS)
                    break;

                orientation = horizontal; x = 1; y = 1;
                print_current_ship(g, x, y, orientation, size[current_ship]);
                break;

            case 'h': // Вызвать справку
                help_loop(g->h);
                top_panel(g->pan);
                update_panels();
                doupdate();
                print_grid(g);
                print_ships(g);
                print_current_ship(g, x, y, orientation, size[current_ship]);
                break;

            case 'q': // Выйти из приложения
                return 1;

            case KEY_RESIZE: // Изменение размера окна
                endwin();
                refresh();
                wclear(g->win);
                wrefresh(g->win);
                print_grid(g);
                print_ships(g);
                print_current_ship(g, x, y, orientation, size[current_ship]);
                break;
        }
        wrefresh(g->user);
    }

    return 0;
}
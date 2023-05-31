#include "user_shoot.h"


// Отображает текущее состояние клетки на поле бота
static void print_current_state(game *g, int x, int y) {
    mvwprintw(g->bot, FIELD_X(x), FIELD_Y(y)-1, " ");
    mvwprintw(g->bot, FIELD_X(x), FIELD_Y(y)+1, " ");
    if (g->bot_shot[x][y] == shot) {
        if (g->bot_field[x][y] > 0)
            mvwprintw(g->bot, FIELD_X(x), FIELD_Y(y), "x");
        else
            mvwprintw(g->bot, FIELD_X(x), FIELD_Y(y), ".");
    }
    else
        mvwprintw(g->bot, FIELD_X(x), FIELD_Y(y), " ");
}


// Отображает состояние клеток на полях пользователя и бота
static void print_shot(game *g) {
    for (int i = 1; i <= FIELD_SIZE; i++)
        for (int j = 1; j <= FIELD_SIZE; j++){
            print_current_state(g, i, j);
            if(g->user_shot[i][j] == shot || g->user_shot[i][j] == miss){
                mvwprintw(g->user, FIELD_X(i), FIELD_Y(j)-1, ">");
                mvwprintw(g->user, FIELD_X(i), FIELD_Y(j)+1, "<");
                wrefresh(g->user);
            }
        }
}


// Отображает текущую выбранную клетку
static void print_current_cell(game *g, int x, int y) {
    mvwprintw(g->bot, FIELD_X(x), FIELD_Y(y)-1, ">");
    mvwprintw(g->bot, FIELD_X(x), FIELD_Y(y)+1, "<");
}


// Ход пользователя
// Возвращает 1, если нужно выйти из приложения, 0 иначе
int user_shooting(game *g) {
    // Кто ходит следующим
    int next_player = user;
    // Координаты текущец выбранной клетки
    int x = 1, y = 1;
    // Текущее сообщение
    int current_msg = you;

    // Стреляем, пока не попадём мимо
    int c;
    while (next_player == user) {
        print_shot(g);
        print_current_cell(g, x, y);
        wrefresh(g->bot);

        if(g->cells_left == 0)
            return 0;

        // Печатаем текущее сообщение
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
            case KEY_DOWN: // Курсор вниз
                print_current_state(g, x, y);
                if (x < FIELD_SIZE)
                    x++;
                print_current_cell(g, x, y);
                break;

            case KEY_UP: // Курсор вверх
                print_current_state(g, x, y);
                if (x > 1)
                    x--;
                print_current_cell(g, x, y);
                break;

            case KEY_LEFT: // Курсор влево
                print_current_state(g, x, y);
                if (y > 1)
                    y--;
                print_current_cell(g, x, y);
                break;

            case KEY_RIGHT: // Курсор вправо
                print_current_state(g, x, y);
                if (y < FIELD_SIZE)
                    y++;
                print_current_cell(g, x, y);
                break;

            case 10: //enter - ударить
                // Попали в корабль и ещё не ударяли в эту клетку
                if (g->bot_field[x][y] > 0) {
                    mvwprintw(g->bot, FIELD_X(x), FIELD_Y(y), "x");
                    if (g->bot_shot[x][y] == not_shot){
                        int ship = g->bot_field[x][y] - 1;
                        g->bot_ships[ship].hit_cells++;
                        g->cells_left--;

                        if(g->bot_ships[ship].hit_cells == g->bot_ships[ship].size)
                            current_msg = destr;
                        else
                            current_msg = hit;
                    }
                }
                // Не попали в корабль
                else {
                    if(g->bot_shot[x][y] == not_shot){
                        mvwprintw(g->bot, FIELD_X(x), FIELD_Y(y), ".");
                        next_player = bot;
                    }
                }
                g->bot_shot[x][y] = shot;
                print_shot(g);

                break;

            case 'h': // Вызвать справку
                help_loop(g->h);
                top_panel(g->pan);
                update_panels();
                doupdate();
                print_grid(g);
                print_ships(g); wrefresh(g->user);
                print_shot(g);
                print_current_cell(g, x, y);
                break;

            case KEY_RESIZE: // Изменение размеров окна
                endwin();
                refresh();
                wclear(g->win);
                wrefresh(g->win);
                print_grid(g);
                print_ships(g); wrefresh(g->user);
                print_shot(g);
                print_current_cell(g, x, y);
                break;

            case 'q': // Выйти из приложения
                return 1;
        }
        wrefresh(g->bot);
    }

    return 0;
}

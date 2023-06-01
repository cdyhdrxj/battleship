#include "main_loop.h"


// Цикл игры
void start_game(game *g) {
    print_grid(g);
    init_help(g->h);

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


// Отображает справку в окне
void print_help(help *h) {
    wclear(h->win);
    mvwprintw(h->win, 0, 0, "%s", h->text);

    attron(A_REVERSE);
    mvprintw(LINES - 1, 0, "%s", HELP_MSG);
    attroff(A_REVERSE);
    refresh();
}


// Возвращает количество строк text при заданной ширине окна cols
static int get_rows(char *text, int cols) {
    size_t size = strlen(text);
    int rows = 1, cur_line = 0;

    for (size_t i = 0; i < size; i++) {
        if (text[i] == '\n'){
            cur_line = 0;
            rows++;
            continue;
        }

        cur_line++;
        if (cur_line == cols){
            rows++;
            cur_line = 0;
        }
    }

    return rows;
}


// Цикл обработки событий при просмотре справки
void help_loop(help *h) {
    // Сделать панель окна справки верхней
    top_panel(h->pan);
    update_panels();
    doupdate();

    // Получаем количество строк в справке (с учётом ширины окна)
    int rows = get_rows(h->text, COLS);
    
    // Изменяем размеры под количество строк в справке 
    wresize(h->win, rows, COLS);

    // Текущая первая строка
    int mypadpos = 0;
    
    print_help(h);
    prefresh(h->win, mypadpos, 0, 0, 0, LINES-2, COLS);

    keypad(h->win, TRUE); // Включить работу с функциональными клавишами (стрелки)
    curs_set(0);          // Отключаем курсор

    // Пока не вышли из справки (выход - нажатие q)
    int c;
    while((c = getch()) != 'q') {
        switch(c) {
            case KEY_UP: // Листать справку вверх
                if (mypadpos > 0)
                    mypadpos--;
                break;
            case KEY_DOWN: // Листать справку вниз
                if (mypadpos <= rows - LINES)
                    mypadpos++;
                break;
            case KEY_RESIZE: // Изменение размеров окна
                // Печатаем справку заново
                clear();
                rows = get_rows(h->text, COLS);
                wresize(h->win, rows, COLS);
                print_help(h);

                // Переходим к началу справки (TODO: лучше переходить к предыдущей последней)
                mypadpos = 0;
                break;
            default:
                break;
        }
        prefresh(h->win, mypadpos, 0, 0, 0, LINES-2, COLS);
    }
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
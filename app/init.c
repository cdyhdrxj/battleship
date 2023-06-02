#include "init.h"

// Инициализация игры
// Возвращает 0, если возникла ошибка, 1 иначе
int init_game(game *g) {
    keypad(stdscr, TRUE);
    noecho(); 

    g->h = (help *) malloc(sizeof(help));
    if (g->h == NULL)
        return 0;

    g->win = newwin(LINES, COLS, 0, 0);
    g->pan = new_panel(g->win);

    g->h->win = newwin(LINES, COLS, 0, 0);
    g->h->pan = new_panel(g->h->win);
    g->h->win = newpad(LINES, COLS);

    if(!init_help(g->h))
        return 0;

    top_panel(g->pan);
    update_panels();
    doupdate();

    return 1;
}


// Печатает сетку на полях игроков
void print_grid(game *g) {
    // Сетка
    char *sep   = "———————————————————————————————————————";
    char *cells = "   |   |   |   |   |   |   |   |   |   ";

    // Названия полей
    char *lbl1 = "Bot";
    char *lbl2 = "You";

    // Координаты окна поля бота в окне игры
    int bot_x = 1, bot_y = 1; 

    // Ширина и высота окон полей
    int field_wigth = strlen(cells) + 2; // + 2 границы 
    int field_heigth = 2*FIELD_SIZE + 1; // 10 клеток + 11 границ

    g->bot = newwin(field_heigth, field_wigth, bot_x, bot_y); 
    box(g->bot, 0, 0);

    for(int i = 1; i < field_heigth - 1; i++) {
        if(i % 2 == 0)
            mvwprintw(g->bot, i, 1, "%s", sep);
        else
            mvwprintw(g->bot, i, 1, "%s", cells);
    }


    g->user = newwin(field_heigth, field_wigth, bot_x, bot_y + field_wigth + 1);
    box(g->user, 0, 0);

    for(int i = 1; i < field_heigth - 1; i++) {
        if(i % 2 == 0)
            mvwprintw(g->user, i, 1, "%s", sep);
        else
            mvwprintw(g->user, i, 1, "%s", cells);
    }

    wrefresh(g->bot);
    wrefresh(g->user);

    // Печатаем названия полей
    mvwprintw(g->win, 0, (field_wigth - strlen(lbl1)) / 2, "%s", lbl1);
    mvwprintw(g->win, 0, bot_y + field_wigth + 1 + (field_wigth - strlen(lbl2)) / 2, "%s", lbl2);

    // Печатаем вспомогательное сообщение
    wattron(g->win, A_REVERSE);
    mvwprintw(g->win, LINES - 1, 0, "%s", MAIN_MSG);
    wattroff(g->win, A_REVERSE);

    wrefresh(g->win);
}


// Читает справку из файла, записывает в h->text
// Возвращает 0, если возникла ошибка, 1 иначе
int init_help(help *h) {
    FILE *f;
    f = fopen(HELP_FILE, "r");
    if (f == NULL)
        return 0;

    char s[LINE_MAX];
    int i = 0;

    if (fgets(s, LINE_MAX, f) == NULL){
        fclose(f);
        return 0;
    }

    size_t size = strlen(s);

    h->text = (char *)malloc((i + size) * sizeof(char));
    if (h->text == NULL){
        fclose(f);
        return 0;
    }

    strncpy(h->text + i, s, size);
    i += size;
    
    while(fgets(s, LINE_MAX, f) != NULL) {
        size = strlen(s);

        h->text = (char *)realloc(h->text, (i + size) * sizeof(char));
        if (h->text == NULL){
            fclose(f);
            return 0;
        }

        strncpy(h->text + i, s, size);
        i += size;
    }

    fclose(f);

    return 1;
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


// Отображает справку в окне
void print_help(help *h) {
    wclear(h->win);
    mvwprintw(h->win, 0, 0, "%s", h->text);

    attron(A_REVERSE);
    mvprintw(LINES - 1, 0, "%s", HELP_MSG);
    attroff(A_REVERSE);
    refresh();
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


// Освобождение памяти
void end_game(game *g) {
    del_panel(g->h->pan);
    delwin(g->h->win);

    del_panel(g->pan);
    delwin(g->bot);
    delwin(g->user);
    delwin(g->win);

    free(g->h->text);
    free(g->h);
    free(g);
}

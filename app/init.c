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
    f = fopen("help.txt", "r");
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
    if (h->text == NULL)
        return 0;

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

    if (fclose(f) != 0)
        return 0;

    return 1;
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

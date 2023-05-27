#include "init.h"


void print_grid(game *g) {
    char *sep   = "———————————————————————————————————————";
    char *cells = "   |   |   |   |   |   |   |   |   |   ";

    int field_wigth = strlen(cells) + 2; // + 2 границы 
    int field_heigth = 10 + 11; // 10 клеток + 11 границ

    g->bot = newwin(field_heigth, field_wigth, 2, 1); 
    box(g->bot, 0, 0);

    for(int i = 1; i < field_heigth - 1; i++) {
        if(i % 2 == 0)
            mvwprintw(g->bot, i, 1, "%s", sep);
        else
            mvwprintw(g->bot, i, 1, "%s", cells);
    }


    g->pl = newwin(field_heigth, field_wigth, 2, field_wigth + 2);
    box(g->pl, 0, 0);

    for(int i = 1; i < field_heigth - 1; i++) {
        if(i % 2 == 0)
            mvwprintw(g->pl, i, 1, "%s", sep);
        else
            mvwprintw(g->pl, i, 1, "%s", cells);
    }

    wrefresh(g->bot);
    wrefresh(g->pl);
}


int init_help(help *h) {
    FILE *f;
    f = fopen("help.txt", "r");
    if (f == NULL)
        return 0;

    char s[LINE_MAX];
    int i = 0;

    fgets(s, LINE_MAX, f);
    size_t size = strlen(s);

    h->text = (char *)malloc((i + size) * sizeof(char));
    if (h->text == NULL)
        return 0;

    strncpy(h->text + i, s, size);
    i += size;
    
    while(fgets(s, LINE_MAX, f)) {
        size = strlen(s);

        h->text = (char *)realloc(h->text, (i + size) * sizeof(char));
        if (h->text == NULL)
            return 0;

        strncpy(h->text + i, s, size);
        i += size;
    }

    if (fclose(f) != 0)
        return 0;

    return 1;
}

void print_help(help *h) {
    wclear(h->win);
    mvwprintw(h->win, 0, 0, "%s", h->text);
    attron(A_REVERSE);
    mvprintw(LINES - 1, 0, "Help (press q to quit, arrows to scroll)");
    attroff(A_REVERSE);
    refresh();
}

static int new_rows(char *text, int cols) {
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


void help_loop(help *h) {
    top_panel(h->pan);
    update_panels();
    doupdate();

    int rows = 1;
    size_t size = strlen(h->text);
    for(size_t i = 0; i < size; i++)
        if(h->text[i] == '\n')
            rows++;

    int mypadpos = 0;
    h->win = newpad(rows, COLS);
    
    print_help(h);
    prefresh(h->win, mypadpos, 0, 0, 0, LINES-2, COLS);

    keypad(h->win, TRUE);
    curs_set(0);

    int c;
    while((c = wgetch(h->win)) != 'q') {
        switch(c) {
            case KEY_UP:
                if (mypadpos >= 0)
                    mypadpos--;
                prefresh(h->win, mypadpos, 0, 0, 0, LINES-2, COLS);
                break;
            case KEY_DOWN:
                if (mypadpos <= rows - LINES)
                    mypadpos++;
                prefresh(h->win, mypadpos, 0, 0, 0, LINES-2, COLS);
                break;
            case KEY_RESIZE:
                clear();
                rows = new_rows(h->text, COLS);
                wresize(h->win, rows, COLS);        
                print_help(h);

                mypadpos = 0;
                prefresh(h->win, 0, 0, 0, 0, LINES-2, COLS);
                break;
        }
    }
}
#include "init.h"


void init_help(help *h) {
    FILE *f;
    f = fopen("help.txt", "r");

    if (f == NULL)
        return;

    h->text = NULL;
    char s[LINE_MAX];
    int i = 0;
    while(fgets(s, LINE_MAX, f)) {
        int size = strlen(s);

        h->text = (char *)realloc(h->text, (i + size) * sizeof(char)); // нет проверки выделения памяти нигде
        strncpy(h->text + i, s, size);
        i += size;
    }
    fclose(f);
}


// TODO: изменять rows, ибо количество строк при ресайзинге 
// меняется и под них нужно изменять размеры окна 
void print_help(help *h) {
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
    wprintw(h->win, "%s", h->text);
    prefresh(h->win, mypadpos, 0, 0, 0, LINES-2, COLS);
    
    attron(A_REVERSE);
    mvprintw(LINES - 1, 0, "Help (press q to quit, arrows to scroll)");
    attroff(A_REVERSE);

    refresh();
    
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
                wresize(h->win, rows, COLS);
                wclear(h->win);
                mvwprintw(h->win, 0, 0, "%s", h->text);
                attron(A_REVERSE);
                mvprintw(LINES - 1, 0, "Help (press q to quit, arrows to scroll)");
                attroff(A_REVERSE);
                refresh();
                mypadpos = 0;
                prefresh(h->win, 0, 0, 0, 0, LINES-2, COLS);
                break;
        }
    }
}
#include "init.h"
#include "main_loop.h"

int main(){
    // Инилизируем игру и ncurses
    setlocale(LC_ALL, "");
    initscr();

    game *g;
    g = (game *) malloc(sizeof(game));
    if (g == NULL)
        return 1;

    if(init_game(g))
        start_game(g); // Запускаем игру


    // Освобождаем память, заканчиваем работу с ncurses
    end_game(g);
    endwin();

    return 0;
}
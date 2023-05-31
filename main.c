#include "init.h"
#include "main_loop.h"

int main(){
    // Инилизируем игру и ncurses
    setlocale(LC_ALL, "");
    initscr();

    game *g;
    g = (game *) malloc(sizeof(game));
    if (g == NULL)
        return 0;

    init_game(g);

    // Запускаем игру
    start_game(g);

    // Освобождаем память, заканчиваем работу с ncurses
    end_game(g);
    endwin();

    return 0;
}
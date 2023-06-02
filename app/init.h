#ifndef INIT_H
#define INIT_H

#include "battleship.h"

// Инициализация игры
int init_game(game *g);

// Печатает сетку на полях игроков
void print_grid(game *g);

// Читает справку из файла, записывает в h->text
int init_help(help *h);

// Возвращает количество строк text при заданной ширине окна cols
int get_rows(char *text, int cols);

// Отображает справку в окне
void print_help(help *h);

// Цикл обработки событий при просмотре справки
void help_loop(help *h);

// Освобождение памяти
void end_game(game *g);

#endif /* INIT_H */
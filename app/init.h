#ifndef INIT_H
#define INIT_H

#include "battleship.h"

// Инициализация игры
int init_game(game *g);

// Печатает сетку на полях игроков
void print_grid(game *g);

// Читает справку из файла, записывает в h->text
int init_help(help *h);

// Освобождение памяти
void end_game(game *g);

#endif /* INIT_H */
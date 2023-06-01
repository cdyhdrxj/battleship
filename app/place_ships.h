#ifndef PLACE_SHIPS_H
#define PLACE_SHIPS_H

#include "battleship.h"
#include "init.h"
#include "main_loop.h"

// Расстановка кораблей пользователем
int place_ships(game *g);

// Печатает корабли на поле пользователя
void print_ships(game *g);

#endif /* PLACE_SHIPS_H */
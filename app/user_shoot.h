#ifndef USER_SHOOT_H
#define USER_SHOOT_H

#include "battleship.h"
#include "init.h"
#include "place_ships.h"

// Отображает текущее состояние клетки на поле бота
void print_current_state(game *g, int x, int y);

// Отображает состояние клеток на полях пользователя и бота
void print_shot(game *g);

// Отображает текущую выбранную клетку
void print_current_cell(game *g, int x, int y);

// Ход пользователя
int user_shooting(game *g);

#endif /* USER_SHOOT_H */
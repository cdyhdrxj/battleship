#ifndef PLACE_SHIPS_H
#define PLACE_SHIPS_H

#include "battleship.h"
#include "init.h"

// Опускает корабль на 1 клетку
void ship_down(game *g, int *x_gl, int *y_gl, int orient, int size);

// Поднимает корабль на 1 клетку
void ship_up(game *g, int *x_gl, int *y_gl, int orient, int size);

// Перемещает корабль влево на 1 клетку
void ship_left(game *g, int *x_gl, int *y_gl, int orient, int size);

// Перемещает корабль вправо на 1 клетку
void ship_right(game *g, int *x_gl, int *y_gl, int orient, int size);

// Поворачивает корабль
void ship_rotate(game *g, int x, int y, int *orient_gl, int size);

// Устанавливает корабль
// Возвращает 1, если корабль можно установить, 0 иначе
int ship_place(game *g, int x, int y, int orient, int size, int current_ship);

// Расстановка кораблей пользователем
int place_ships(game *g);

// Печатает корабли на поле пользователя
void print_ships(game *g);

// Печатает текущий устанавливаемый корабль
void print_current_ship(game *g, int x, int y, int orient, int size);

#endif /* PLACE_SHIPS_H */
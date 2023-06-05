#ifndef BOT_SHOOT_H
#define BOT_SHOOT_H

#include "battleship.h"

// Отмечает клетки вокруг убитых кораблей
void make_buffer_zone(game *g);

// Добивает корабль
// Возвращает следующего игрока
int finish_ship(game *g);

// Для впервые раненного корабля составляет массив соседних клеток, в которых он может находится
void hit_ship(game *g, int x, int y);

// Ход бота
__attribute((weak)) // для тестирования (наверное, не должно быть в исходном коде)
void bot_shooting(game *g);

#endif /* BOT_SHOOT_H */

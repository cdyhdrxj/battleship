#ifndef GENERATE_BOT_FIELD_H
#define GENERATE_BOT_FIELD_H

#include "battleship.h"
#include "init.h"

// Расстановка многопалубных кораблей "змейкой"
void snake(int field[][FIELD_SIZE + 2], int var1, int var2);

// Расстановка многопалубных кораблей двумя параллельными линиями
void line(int field[][FIELD_SIZE + 2], int var1, int var2, int var3);

// Вращает и зеркально отображает поле
void rotate_field(int field[][FIELD_SIZE + 2], int var1, int var2, int var3);

// Генерирует поле бота
void gener_field(int field[][FIELD_SIZE + 2]);

// По матрице поля бота формирует массив кораблей
void fill_bot_ships(game *g);

#endif /* GENERATE_BOT_FIELD_H */

#ifndef GENERATE_BOT_FIELD_H
#define GENERATE_BOT_FIELD_H

#include "battleship.h"
#include "init.h"

// Генерирует поле бота
void gener_field(int field[][FIELD_SIZE + 2]);

// По матрице поля бота формирует массив кораблей
void fill_bot_ships(game *g);

#endif /* GENERATE_BOT_FIELD_H */
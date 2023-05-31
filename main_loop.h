#ifndef MAIN_LOOP_H
#define MAIN_LOOP_H

#include "battleship.h"
#include "place_ships.h"
#include "generate_bot_field.h"
#include "bot_shoot.h"
#include "user_shoot.h"

// Цикл игры
void start_game(game *g);

// Цикл перестрелки
int shooting_loop(game *g);

// Отображает справку в окне
void print_help(help *h);

// Цикл обработки событий при просмотре справки
void help_loop(help *h);

#endif /* MAIN_LOOP_H */
#ifndef PLACE_SHIPS_H
#define PLACE_SHIPS_H

#include <ncursesw/ncurses.h>
#include <ncursesw/panel.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include "init.h"

int place_ships(game *g);
void print_ships(game *g);


#endif /* PLACE_SHIPS_H */
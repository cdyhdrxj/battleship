#ifndef SHOOT_H
#define SHOOT_H

#include <ncursesw/ncurses.h>
#include <ncursesw/panel.h>
#include <unistd.h>
#include "init.h"
#include "place_ships.h"
#include "bot_shoot.h"

int shooting_loop(game *g);

#endif /* SHOOT_H */
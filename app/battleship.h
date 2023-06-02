#ifndef BATTLESHIP_H
#define BATTLESHIP_H

#include <ncursesw/ncurses.h>
#include <ncursesw/panel.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#include <unistd.h>
#include <time.h>

#define HELP_FILE "help.txt"
#define LINE_MAX 200         // Максимальная длина строки при чтении из файла

#define FIELD_X(x) 2*(x)-1   // Переводят координаты точки на поле в
#define FIELD_Y(y) 4*(y)-2   // координаты точки в окне поля

// Сообщения для вывода на экран.
#define MAIN_MSG    "Press h for help, q to quit"
#define ROTATE_MSG  "Can't rotate (h for help, q to quit)"
#define MOVE_MSG    "Move this ship (h for help, q to quit)"
#define HELP_MSG    "Help (press q to quit, arrows to scroll)"
#define BOT_MSG     "It's bot's turn (h for help, q to quit)"
#define YOU_MSG     "It's your turn (h for help, q to quit)"
#define HIT_MSG     "Hit! It's your turn (h for help, q to quit)"
#define DESTROY_MSG "Destroyed! It's your turn (h for help, q to quit)"
#define WIN_MSG     "You win! (press any key to quit)"
#define LOSE_MSG    "You lose... (press any key to quit)"

// Информация о игре
#define FIELD_SIZE      10                   // Сторона поля
#define NUMBER_OF_SHIPS 10                   // Количество кораблей
#define SHIPS {4, 3, 3, 2, 2, 2, 1, 1, 1, 1} // Размеры кораблей
#define NUMBER_OF_CELLS 20                   // Общее количество клеток, занятых кораблями
#define NUMBER_OF_MULTICELLS 6               // Количество многопалубных кораблей

enum ORIENTATIONS {horizontal, vertical}; // Ориентации кораблей
enum PLAYERS      {user, bot};            // Игроки
enum CURRENT_MSG  {you, hit, destr};      // Текущее сообщение о ходе пользователя
                                          // (YOU_MSG, HIT_MSG, DESTROY_MSG)
// Состояние клетки (мимо, не было удара, попал, рядом с убитым кораблём)
enum CELL_STATE   {miss = -1, not_shot = 0, shot = 1, buffer = 2};

// Корабль
typedef struct __ship {
    int size;                // Размер корабля (в клетках)
    int hit_cells;           // Количество подбитых клеток
} ship;


// Данные для обстрела поля противника
typedef struct __shoot {
    int cells_left;          // Количество оставшихся клеток на поле
    int is_battleship_found; // Флаг - найден ли линкор
    int multicells_found;    // Количество найденных многопалубников (размер > 1)
    int is_destroyed;        // Флаг - есть ли раненый корабль
    int current_ship;        // Номер текущего раненого корабля
    int poss_cell[4][2];     // Массив клеток, в которых возможно располагается раненый корабль
} shoot;


// Справка
typedef struct _help {
    WINDOW *win;             // Окно справки
    PANEL *pan;              // Панель окна справки
    char *text;              // Текст справки
} help; 


// Игра
typedef struct _game {
    int user_field[FIELD_SIZE+2][FIELD_SIZE+2]; // Матрица поля пользователя (корабли) 
    int user_shot[FIELD_SIZE+2][FIELD_SIZE+2];  // Матрица поля пользователя (подбитые клетки)
    ship user_ships[NUMBER_OF_SHIPS];           // Массив кораблей пользователя
    int cells_left;                             // Количество неподбитых клеток пользователя

    int bot_field[FIELD_SIZE+2][FIELD_SIZE+2];  // Матрица поля бота (корабли)
    int bot_shot[FIELD_SIZE+2][FIELD_SIZE+2];   // Матрица поля бота (подбитые клетки)
    ship bot_ships[NUMBER_OF_SHIPS];            // Массив кораблей бота

    shoot bot_shoot;          // Данные о стрельбе бота

    WINDOW *win, *user, *bot; // Окно игры, окна полей пользователя и бота
    PANEL *pan;               // Панель окна игры
    help *h;                  // Справка
} game;

#endif /* BATTLESHIP_H */

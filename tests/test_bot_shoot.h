#ifndef TEST_BOT_SHOOT_H
#define TEST_BOT_SHOOT_H

#include <gtest/gtest.h>

extern "C" {
#include "init.h"
#include "bot_shoot.h"
}

TEST(make_buffer1, pos) {
    int field[12][12] =     {{0, 0,  0,  0, 0, 0,  0, 0, 0,  0,  0, 0},
                             {0, 0,  0,  0, 0, 0,  0, 0, 0,  0,  0, 0},
                             {0, 0,  0,  0, 0, 0, -1, 0, 0,  0,  0, 0},
                             {0, 0, -1,  0, 0, 0,  0, 0, 0,  0,  0, 0},
                             {0, 0,  0,  0, 0, 0,  0, 1, 0,  0,  0, 0},
                             {0, 0,  0, -1, 0, 0,  0, 1, 0,  0,  0, 0},
                             {0, 0,  1,  1, 1, 1,  0, 0, 0,  0,  0, 0},
                             {0, 0,  0,  0, 0, 0,  0, 0, 0,  0,  0, 0},
                             {0, 2,  2,  2, 0, 0,  0, 0, 0,  0,  0, 0},
                             {0, 2,  1,  2, 0, 0,  0, 0, 0, -1, -1, 0},
                             {0, 2,  1,  2, 0, 0,  0, 0, 0,  0,  0, 0},
                             {0, 2,  2,  2, 0, 0,  0, 0, 0,  0,  0, 0}};

    int field_res[12][12] = {{0, 0,  0,  0, 0, 0,  0, 0, 0,  0,  0, 0},
                             {0, 0,  0,  0, 0, 0,  0, 0, 0,  0,  0, 0},
                             {0, 0,  0,  0, 0, 0, -1, 0, 0,  0,  0, 0},
                             {0, 0, -1,  0, 0, 0,  2, 2, 2,  0,  0, 0},
                             {0, 0,  0,  0, 0, 0,  2, 1, 2,  0,  0, 0},
                             {0, 2,  2, -1, 2, 2,  2, 1, 2,  0,  0, 0},
                             {0, 2,  1,  1, 1, 1,  2, 2, 2,  0,  0, 0},
                             {0, 2,  2,  2, 2, 2,  2, 0, 0,  0,  0, 0},
                             {0, 2,  2,  2, 0, 0,  0, 0, 0,  0,  0, 0},
                             {0, 2,  1,  2, 0, 0,  0, 0, 0, -1, -1, 0},
                             {0, 2,  1,  2, 0, 0,  0, 0, 0,  0,  0, 0},
                             {0, 2,  2,  2, 0, 0,  0, 0, 0,  0,  0, 0}};

    game *g;
    g = (game *) malloc(sizeof(game));
    init_game(g);

    for(int i = 0; i < FIELD_SIZE + 2; i++)
        for(int j = 0; j < FIELD_SIZE + 2; j++)
            g->user_shot[i][j] = field[i][j];

    make_buffer_zone(g);

    for(int i = 0; i < FIELD_SIZE + 2; i++)
        for(int j = 0; j < FIELD_SIZE + 2; j++)
            EXPECT_EQ(field_res[i][j], g->user_shot[i][j]);
    end_game(g);
}

TEST(hit_ship1, pos) {
    int field[12][12] =     {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

    int res[4][2] = {{4, 5}, {5, 6}, {6, 5}, {5, 4}};

    game *g;
    g = (game *) malloc(sizeof(game));
    init_game(g);

    int x = 5, y = 5;

    g->user_field[x][y] = 1;
    g->user_ships[0].size = 3;
    g->user_ships[0].hit_cells = 0;
    g->bot_shoot.cells_left = NUMBER_OF_CELLS;
    g->bot_shoot.is_destroyed = 1;

    for(int i = 0; i < FIELD_SIZE + 2; i++)
        for(int j = 0; j < FIELD_SIZE + 2; j++)
            g->user_shot[i][j] = field[i][j];

    hit_ship(g, x, y);

    EXPECT_EQ(1, g->user_ships[0].hit_cells);
    EXPECT_EQ(NUMBER_OF_CELLS - 1, g->bot_shoot.cells_left);
    EXPECT_EQ(0, g->bot_shoot.is_destroyed);

    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 2; j++)
            EXPECT_EQ(res[i][j], g->bot_shoot.poss_cell[i][j]);

    end_game(g);
}

TEST(hit_ship2, pos) {
    int field[12][12] =     {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

    int res[4][2] = {{-1, -1}, {1, 2}, {2, 1}, {-1, -1}};

    game *g;
    g = (game *) malloc(sizeof(game));
    init_game(g);

    int x = 1, y = 1;

    g->user_field[x][y] = 1;
    g->user_ships[0].size = 3;
    g->user_ships[0].hit_cells = 0;
    g->bot_shoot.cells_left = NUMBER_OF_CELLS;
    g->bot_shoot.is_destroyed = 1;

    for(int i = 0; i < FIELD_SIZE + 2; i++)
        for(int j = 0; j < FIELD_SIZE + 2; j++)
            g->user_shot[i][j] = field[i][j];

    hit_ship(g, x, y);

    EXPECT_EQ(1, g->user_ships[0].hit_cells);
    EXPECT_EQ(NUMBER_OF_CELLS - 1, g->bot_shoot.cells_left);
    EXPECT_EQ(0, g->bot_shoot.is_destroyed);

    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 2; j++)
            EXPECT_EQ(res[i][j], g->bot_shoot.poss_cell[i][j]);

    end_game(g);
}

TEST(hit_ship3, pos) {
    int field[12][12] =     {{0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 1, -1, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 2, 2,  2, 2, 0, 0, 0, 0, 0},
                             {0, 0, 0, 2, 1,  1, 2, 0, 0, 0, 0, 0},
                             {0, 0, 0, 2, 2,  2, 2, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0}};

    int res[4][2] = {{5, 4}, {-1, -1}, {-1, -1}, {6, 3}};

    game *g;
    g = (game *) malloc(sizeof(game));
    init_game(g);

    int x = 6, y = 4;

    g->user_field[x][y] = 1;
    g->user_ships[0].size = 3;
    g->user_ships[0].hit_cells = 0;
    g->bot_shoot.cells_left = NUMBER_OF_CELLS - 2;
    g->bot_shoot.is_destroyed = 1;

    for(int i = 0; i < FIELD_SIZE + 2; i++)
        for(int j = 0; j < FIELD_SIZE + 2; j++)
            g->user_shot[i][j] = field[i][j];

    hit_ship(g, x, y);

    EXPECT_EQ(1, g->user_ships[0].hit_cells);
    EXPECT_EQ(NUMBER_OF_CELLS - 3, g->bot_shoot.cells_left);
    EXPECT_EQ(0, g->bot_shoot.is_destroyed);


    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 2; j++)
            EXPECT_EQ(res[i][j], g->bot_shoot.poss_cell[i][j]);

    end_game(g);
}

TEST(hit_ship4, pos) {
    int field[12][12] =     {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

    int res_field[12][12] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 2, 1, 2, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 2, 2, 2, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                             {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};

    game *g;
    g = (game *) malloc(sizeof(game));
    init_game(g);

    int x = 5, y = 5;

    g->user_field[x][y] = 1;
    g->user_ships[0].size = 1;
    g->user_ships[0].hit_cells = 0;
    g->bot_shoot.cells_left = NUMBER_OF_CELLS;
    g->bot_shoot.is_destroyed = 1;

    for(int i = 0; i < FIELD_SIZE + 2; i++)
        for(int j = 0; j < FIELD_SIZE + 2; j++)
            g->user_shot[i][j] = field[i][j];

    hit_ship(g, x, y);

    EXPECT_EQ(1, g->user_ships[0].hit_cells);
    EXPECT_EQ(NUMBER_OF_CELLS - 1, g->bot_shoot.cells_left);
    EXPECT_EQ(1, g->bot_shoot.is_destroyed);

    for(int i = 0; i < 12; i++)
        for(int j = 0; j < 12; j++)
            EXPECT_EQ(res_field[i][j], g->user_shot[i][j]);

    end_game(g);
}

TEST(finish_ship1, pos) {
    int res[4][2] = {{-1, -1}, {5, 6}, {6, 5}, {5, 4}};

    game *g;
    g = (game *) malloc(sizeof(game));
    init_game(g);

    g->bot_shoot.is_destroyed = 0;
    g->bot_shoot.cells_left = NUMBER_OF_CELLS - 1;

    g->bot_shoot.poss_cell[0][0] = 4;
    g->bot_shoot.poss_cell[0][1] = 5;
    g->bot_shoot.poss_cell[1][0] = 5;
    g->bot_shoot.poss_cell[1][1] = 6;
    g->bot_shoot.poss_cell[2][0] = 6;
    g->bot_shoot.poss_cell[2][1] = 5;
    g->bot_shoot.poss_cell[3][0] = 5;
    g->bot_shoot.poss_cell[3][1] = 4;

    g->user_field[4][5] = 0;

    g->user_shot[4][5] = not_shot;

    int next_player = finish_ship(g);

    EXPECT_EQ(next_player, user);
    EXPECT_EQ(g->user_shot[4][5], miss);
    EXPECT_EQ(0, g->bot_shoot.is_destroyed);
    EXPECT_EQ(NUMBER_OF_CELLS - 1, g->bot_shoot.cells_left);

    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 2; j++)
            EXPECT_EQ(res[i][j], g->bot_shoot.poss_cell[i][j]);

    end_game(g);
}

// ТУТ ЕЩЁ MAKE_BUFFER_ZONE
TEST(finish_ship2, pos) {
    game *g;
    g = (game *) malloc(sizeof(game));
    init_game(g);

    g->user_field[2][2] = 3;
    g->user_shot[2][2] = not_shot;

    g->user_ships[2].size = 4;
    g->user_ships[2].hit_cells = 3;

    g->bot_shoot.is_destroyed = 0;
    g->bot_shoot.is_battleship_found = 0;
    g->bot_shoot.multicells_found = 0;
    g->bot_shoot.cells_left = NUMBER_OF_CELLS - 3;
    g->bot_shoot.current_ship = 2;

    g->bot_shoot.poss_cell[0][0] = 2;
    g->bot_shoot.poss_cell[0][1] = 2;
    g->bot_shoot.poss_cell[1][0] = -1;
    g->bot_shoot.poss_cell[1][1] = -1;
    g->bot_shoot.poss_cell[2][0] = -1;
    g->bot_shoot.poss_cell[2][1] = -1;
    g->bot_shoot.poss_cell[3][0] = -1;
    g->bot_shoot.poss_cell[3][1] = -1;

    int next_player = finish_ship(g);

    EXPECT_EQ(bot, next_player);
    EXPECT_EQ(shot, g->user_shot[2][2]);
    EXPECT_EQ(1, g->bot_shoot.is_destroyed);
    EXPECT_EQ(1, g->bot_shoot.is_battleship_found);
    EXPECT_EQ(1, g->bot_shoot.multicells_found);
    EXPECT_EQ(NUMBER_OF_CELLS - 4, g->bot_shoot.cells_left);

    end_game(g);
}

TEST(finish_ship3, pos){
    int res[4][2] = {{3, 5}, {-1, -1}, {6, 5}, {-1, -1}};

    game *g;
    g = (game *) malloc(sizeof(game));
    init_game(g);

    g->user_field[4][5] = 3;
    g->user_shot[4][5] = not_shot;

    g->user_ships[2].size = 3;
    g->user_ships[2].hit_cells = 1;

    g->bot_shoot.is_destroyed = 0;
    g->bot_shoot.cells_left = NUMBER_OF_CELLS - 1;
    g->bot_shoot.current_ship = 2;

    g->bot_shoot.poss_cell[0][0] = 4;
    g->bot_shoot.poss_cell[0][1] = 5;
    g->bot_shoot.poss_cell[1][0] = 5;
    g->bot_shoot.poss_cell[1][1] = 6;
    g->bot_shoot.poss_cell[2][0] = 6;
    g->bot_shoot.poss_cell[2][1] = 5;
    g->bot_shoot.poss_cell[3][0] = 5;
    g->bot_shoot.poss_cell[3][1] = 4;

    int next_player = finish_ship(g);

    EXPECT_EQ(bot, next_player);
    EXPECT_EQ(shot, g->user_shot[4][5]);
    EXPECT_EQ(0, g->bot_shoot.is_destroyed);
    EXPECT_EQ(NUMBER_OF_CELLS - 2, g->bot_shoot.cells_left);

    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 2; j++)
            EXPECT_EQ(res[i][j], g->bot_shoot.poss_cell[i][j]);

    end_game(g);
}

TEST(finish_ship4, pos){
    int res[4][2] = {{-1, -1}, {5, 7}, {-1, -1}, {5, 4}};

    game *g;
    g = (game *) malloc(sizeof(game));
    init_game(g);

    g->user_field[5][6] = 3;
    g->user_shot[5][6] = not_shot;

    g->user_ships[2].size = 3;
    g->user_ships[2].hit_cells = 1;

    g->bot_shoot.is_destroyed = 0;
    g->bot_shoot.cells_left = NUMBER_OF_CELLS - 1;
    g->bot_shoot.current_ship = 2;

    g->bot_shoot.poss_cell[0][0] = -1;
    g->bot_shoot.poss_cell[0][1] = -1;
    g->bot_shoot.poss_cell[1][0] = 5;
    g->bot_shoot.poss_cell[1][1] = 6;
    g->bot_shoot.poss_cell[2][0] = 6;
    g->bot_shoot.poss_cell[2][1] = 5;
    g->bot_shoot.poss_cell[3][0] = 5;
    g->bot_shoot.poss_cell[3][1] = 4;

    int next_player = finish_ship(g);

    EXPECT_EQ(bot, next_player);
    EXPECT_EQ(shot, g->user_shot[5][6]);
    EXPECT_EQ(0, g->bot_shoot.is_destroyed);
    EXPECT_EQ(NUMBER_OF_CELLS - 2, g->bot_shoot.cells_left);

    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 2; j++)
            EXPECT_EQ(res[i][j], g->bot_shoot.poss_cell[i][j]);

    end_game(g);
}

TEST(finish_ship5, pos){
    int res[4][2] = {{-1, -1}, {-1, -1}, {7, 5}, {-1, -1}};

    game *g;
    g = (game *) malloc(sizeof(game));
    init_game(g);

    g->user_field[6][5] = 3;
    g->user_shot[6][5] = not_shot;

    g->user_ships[2].size = 3;
    g->user_ships[2].hit_cells = 1;

    g->bot_shoot.is_destroyed = 0;
    g->bot_shoot.cells_left = NUMBER_OF_CELLS - 1;
    g->bot_shoot.current_ship = 2;

    g->bot_shoot.poss_cell[0][0] = -1;
    g->bot_shoot.poss_cell[0][1] = -1;
    g->bot_shoot.poss_cell[1][0] = -1;
    g->bot_shoot.poss_cell[1][1] = -1;
    g->bot_shoot.poss_cell[2][0] = 6;
    g->bot_shoot.poss_cell[2][1] = 5;
    g->bot_shoot.poss_cell[3][0] = 5;
    g->bot_shoot.poss_cell[3][1] = 4;

    int next_player = finish_ship(g);

    EXPECT_EQ(bot, next_player);
    EXPECT_EQ(shot, g->user_shot[6][5]);
    EXPECT_EQ(0, g->bot_shoot.is_destroyed);
    EXPECT_EQ(NUMBER_OF_CELLS - 2, g->bot_shoot.cells_left);

    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 2; j++)
            EXPECT_EQ(res[i][j], g->bot_shoot.poss_cell[i][j]);

    end_game(g);
}

TEST(finish_ship6, pos){
    int res[4][2] = {{-1, -1}, {-1, -1}, {-1, -1}, {5, 3}};

    game *g;
    g = (game *) malloc(sizeof(game));
    init_game(g);

    g->user_field[5][4] = 3;
    g->user_shot[5][4] = not_shot;

    g->user_ships[2].size = 3;
    g->user_ships[2].hit_cells = 1;

    g->bot_shoot.is_destroyed = 0;
    g->bot_shoot.cells_left = NUMBER_OF_CELLS - 1;
    g->bot_shoot.current_ship = 2;

    g->bot_shoot.poss_cell[0][0] = -1;
    g->bot_shoot.poss_cell[0][1] = -1;
    g->bot_shoot.poss_cell[1][0] = -1;
    g->bot_shoot.poss_cell[1][1] = -1;
    g->bot_shoot.poss_cell[2][0] = -1;
    g->bot_shoot.poss_cell[2][1] = -1;
    g->bot_shoot.poss_cell[3][0] = 5;
    g->bot_shoot.poss_cell[3][1] = 4;

    int next_player = finish_ship(g);

    EXPECT_EQ(bot, next_player);
    EXPECT_EQ(shot, g->user_shot[5][4]);
    EXPECT_EQ(0, g->bot_shoot.is_destroyed);
    EXPECT_EQ(NUMBER_OF_CELLS - 2, g->bot_shoot.cells_left);

    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 2; j++)
            EXPECT_EQ(res[i][j], g->bot_shoot.poss_cell[i][j]);

    end_game(g);
}

#endif // TEST_BOT_SHOOT_H

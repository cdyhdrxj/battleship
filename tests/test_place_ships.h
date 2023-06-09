#ifndef TEST_PLACE_SHIPS_H
#define TEST_PLACE_SHIPS_H

#include <gtest/gtest.h>

extern "C" {
#include "init.h"
#include "place_ships.h"
}

TEST(ship_down1, horiz1) {
    game *g;
    g = (game *) malloc(sizeof(game));
    init_game(g);

    for(int i = 0; i < 10 + 2; i++)
        for(int j = 0; j < 10 + 2; j++)
            g->user_field[i][j] = 0;

    int x = 5, y = 8;
    ship_down(g, &x, &y, horizontal, 2);

    EXPECT_EQ(6, x);
    EXPECT_EQ(8, y);

    end_game(g);
}

TEST(ship_down2, horiz2) {
    game *g;
    g = (game *) malloc(sizeof(game));
    init_game(g);

    for(int i = 0; i < 10 + 2; i++)
        for(int j = 0; j < 10 + 2; j++)
            g->user_field[i][j] = 0;

    int x = 10, y = 3;
    ship_down(g, &x, &y, horizontal, 3);

    EXPECT_EQ(10, x);
    EXPECT_EQ(3, y);

    end_game(g);
}

TEST(ship_down3, vertic1) {
    game *g;
    g = (game *) malloc(sizeof(game));
    init_game(g);

    for(int i = 0; i < 10 + 2; i++)
        for(int j = 0; j < 10 + 2; j++)
            g->user_field[i][j] = 0;

    int x = 2, y = 10, size = 2;
    ship_down(g, &x, &y, vertical, size);

    EXPECT_EQ(3, x);
    EXPECT_EQ(10, y);

    end_game(g);
}

TEST(ship_down4, vertic2) {
    game *g;
    g = (game *) malloc(sizeof(game));
    init_game(g);

    for(int i = 0; i < 10 + 2; i++)
        for(int j = 0; j < 10 + 2; j++)
            g->user_field[i][j] = 0;

    int x = 7, y = 3;
    int size = 10 + 1 - x;
    ship_down(g, &x, &y, vertical, size);

    EXPECT_EQ(7, x);
    EXPECT_EQ(3, y);

    end_game(g);
}

TEST(ship_up1, horiz1) {
    game *g;
    g = (game *) malloc(sizeof(game));
    init_game(g);

    for(int i = 0; i < 10 + 2; i++)
        for(int j = 0; j < 10 + 2; j++)
            g->user_field[i][j] = 0;

    int x = 5, y = 8;
    ship_up(g, &x, &y, 2, horizontal);

    EXPECT_EQ(4, x);
    EXPECT_EQ(8, y);

    end_game(g);
}

TEST(ship_up2, horiz2) {
    game *g;
    g = (game *) malloc(sizeof(game));
    init_game(g);

    for(int i = 0; i < 10 + 2; i++)
        for(int j = 0; j < 10 + 2; j++)
            g->user_field[i][j] = 0;

    int x = 1, y = 3;
    ship_up(g, &x, &y, horizontal, 3);

    EXPECT_EQ(1, x);
    EXPECT_EQ(3, y);

    end_game(g);
}

TEST(ship_up3, vertic1) {
    game *g;
    g = (game *) malloc(sizeof(game));
    init_game(g);

    for(int i = 0; i < 10 + 2; i++)
        for(int j = 0; j < 10 + 2; j++)
            g->user_field[i][j] = 0;

    int x = 8, y = 10, size = 2;
    ship_up(g, &x, &y, vertical, size);

    EXPECT_EQ(7, x);
    EXPECT_EQ(10, y);

    end_game(g);
}

TEST(ship_up4, vertic2) {
    game *g;
    g = (game *) malloc(sizeof(game));
    init_game(g);

    for(int i = 0; i < 10 + 2; i++)
        for(int j = 0; j < 10 + 2; j++)
            g->user_field[i][j] = 0;

    int x = 1, y = 3;
    int size = 4;
    ship_up(g, &x, &y, vertical, size);

    EXPECT_EQ(1, x);
    EXPECT_EQ(3, y);

    end_game(g);
}

TEST(ship_left1, horiz1) {
    game *g;
    g = (game *) malloc(sizeof(game));
    init_game(g);

    for(int i = 0; i < 10 + 2; i++)
        for(int j = 0; j < 10 + 2; j++)
            g->user_field[i][j] = 0;

    int x = 5, y = 8;
    ship_left(g, &x, &y, 2, horizontal);

    EXPECT_EQ(5, x);
    EXPECT_EQ(7, y);

    end_game(g);
}

TEST(ship_left2, horiz2) {
    game *g;
    g = (game *) malloc(sizeof(game));
    init_game(g);

    for(int i = 0; i < 10 + 2; i++)
        for(int j = 0; j < 10 + 2; j++)
            g->user_field[i][j] = 0;

    int x = 1, y = 1;
    ship_left(g, &x, &y, horizontal, 3);

    EXPECT_EQ(1, x);
    EXPECT_EQ(1, y);

    end_game(g);
}

TEST(ship_left3, vertic1) {
    game *g;
    g = (game *) malloc(sizeof(game));
    init_game(g);

    for(int i = 0; i < 10 + 2; i++)
        for(int j = 0; j < 10 + 2; j++)
            g->user_field[i][j] = 0;

    int x = 8, y = 10, size = 2;
    ship_left(g, &x, &y, vertical, size);

    EXPECT_EQ(8, x);
    EXPECT_EQ(9, y);

    end_game(g);
}

TEST(ship_left4, vertic2) {
    game *g;
    g = (game *) malloc(sizeof(game));
    init_game(g);

    for(int i = 0; i < 10 + 2; i++)
        for(int j = 0; j < 10 + 2; j++)
            g->user_field[i][j] = 0;

    int x = 6, y = 1;
    int size = 4;
    ship_left(g, &x, &y, vertical, size);

    EXPECT_EQ(6, x);
    EXPECT_EQ(1, y);

    end_game(g);
}

TEST(ship_right1, horiz1) {
    game *g;
    g = (game *) malloc(sizeof(game));
    init_game(g);

    for(int i = 0; i < 10 + 2; i++)
        for(int j = 0; j < 10 + 2; j++)
            g->user_field[i][j] = 0;

    int x = 2, y = 5;
    ship_right(g, &x, &y, 2, horizontal);

    EXPECT_EQ(2, x);
    EXPECT_EQ(6, y);

    end_game(g);
}

TEST(ship_right2, horiz2) {
    game *g;
    g = (game *) malloc(sizeof(game));
    init_game(g);

    for(int i = 0; i < 10 + 2; i++)
        for(int j = 0; j < 10 + 2; j++)
            g->user_field[i][j] = 0;

    int x = 8, y = 8;
    int size = 10 + 1 - y;
    ship_right(g, &x, &y, horizontal, size);

    EXPECT_EQ(8, x);
    EXPECT_EQ(8, y);

    end_game(g);
}

TEST(ship_right3, vertic1) {
    game *g;
    g = (game *) malloc(sizeof(game));
    init_game(g);

    for(int i = 0; i < 10 + 2; i++)
        for(int j = 0; j < 10 + 2; j++)
            g->user_field[i][j] = 0;

    int x = 8, y = 5, size = 2;
    ship_right(g, &x, &y, vertical, size);

    EXPECT_EQ(8, x);
    EXPECT_EQ(6, y);

    end_game(g);
}

TEST(ship_right4, vertic2) {
    game *g;
    g = (game *) malloc(sizeof(game));
    init_game(g);

    for(int i = 0; i < 10 + 2; i++)
        for(int j = 0; j < 10 + 2; j++)
            g->user_field[i][j] = 0;

    int x = 5, y = 10;
    int size = 4;
    ship_right(g, &x, &y, vertical, size);

    EXPECT_EQ(5, x);
    EXPECT_EQ(10, y);

    end_game(g);
}

TEST(ship_rotate1, horiz1) {
    game *g;
    g = (game *) malloc(sizeof(game));
    init_game(g);

    for(int i = 0; i < 10 + 2; i++)
        for(int j = 0; j < 10 + 2; j++)
            g->user_field[i][j] = 0;

    int x = 1, y = 1;
    int size = 3;
    int orient = horizontal;
    ship_rotate(g, x, y, &orient, size);

    EXPECT_EQ(vertical, orient);

    end_game(g);
}

TEST(ship_rotate2, horiz2) {
    game *g;
    g = (game *) malloc(sizeof(game));
    init_game(g);

    for(int i = 0; i < 10 + 2; i++)
        for(int j = 0; j < 10 + 2; j++)
            g->user_field[i][j] = 0;

    int x = 9, y = 3;
    int size = 3;
    int orient = horizontal;
    ship_rotate(g, x, y, &orient, size);

    EXPECT_EQ(horizontal, orient);

    end_game(g);
}

TEST(ship_rotate3, vertic1) {
    game *g;
    g = (game *) malloc(sizeof(game));
    init_game(g);

    for(int i = 0; i < 10 + 2; i++)
        for(int j = 0; j < 10 + 2; j++)
            g->user_field[i][j] = 0;

    int x = 2, y = 5;
    int size = 4;
    int orient = vertical;
    ship_rotate(g, x, y, &orient, size);

    EXPECT_EQ(horizontal, orient);

    end_game(g);
}

TEST(ship_rotate4, vertic2) {
    game *g;
    g = (game *) malloc(sizeof(game));
    init_game(g);

    for(int i = 0; i < 10 + 2; i++)
        for(int j = 0; j < 10 + 2; j++)
            g->user_field[i][j] = 0;

    int x = 5, y = 8;
    int size = 4;
    int orient = vertical;
    ship_rotate(g, x, y, &orient, size);

    EXPECT_EQ(vertical, orient);

    end_game(g);
}

TEST(ship_place1, horiz1) {
    game *g;
    g = (game *) malloc(sizeof(game));
    init_game(g);

    for(int i = 0; i < 10 + 2; i++)
        for(int j = 0; j < 10 + 2; j++)
            g->user_field[i][j] = 0;

    int x = 5, y = 4;
    int size = 4;
    int orient = horizontal;
    int number = 1;
    EXPECT_EQ(1, ship_place(g, x, y, orient, size, number));

    for(int i = 0; i < 10 + 2; i++)
        for(int j = 0; j < 10 + 2; j++){
            if(i == x && j >= y && j < y + size)
                EXPECT_EQ(number+1, g->user_field[i][j]);
            else
                EXPECT_EQ(0, g->user_field[i][j]);
        }

    end_game(g);
}

TEST(ship_place2, horiz2) {
    game *g;
    g = (game *) malloc(sizeof(game));
    init_game(g);

    int field[12][12] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};


    for(int i = 0; i < 10 + 2; i++)
        for(int j = 0; j < 10 + 2; j++)
            g->user_field[i][j] = field[i][j];

    int x = 5, y = 4;
    int size = 4;
    int orient = horizontal;
    int number = 1;
    EXPECT_EQ(0, ship_place(g, x, y, orient, size, number));

    for(int i = 0; i < 10 + 2; i++)
        for(int j = 0; j < 10 + 2; j++)
                EXPECT_EQ(field[i][j], g->user_field[i][j]);

    end_game(g);
}

TEST(ship_place3, vertic1) {
    game *g;
    g = (game *) malloc(sizeof(game));
    init_game(g);

    for(int i = 0; i < 10 + 2; i++)
        for(int j = 0; j < 10 + 2; j++)
            g->user_field[i][j] = 0;

    int x = 5, y = 8;
    int size = 3;
    int orient = vertical;
    int number = 1;
    EXPECT_EQ(1, ship_place(g, x, y, orient, size, number));

    for(int i = 0; i < 10 + 2; i++)
        for(int j = 0; j < 10 + 2; j++){
            if(i >= x && i < x + size && j == y)
                EXPECT_EQ(number+1, g->user_field[i][j]);
            else
                EXPECT_EQ(0, g->user_field[i][j]);
        }

    end_game(g);
}

TEST(ship_place4, vertic2) {
    game *g;
    g = (game *) malloc(sizeof(game));
    init_game(g);

    int field[12][12] = {{0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 2, 0},
                         {0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 2, 0},
                         {0, 0, 3, 0, 0, 0, 0, 0, 0, 0, 2, 0},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                         {0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
                         {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}};


    for(int i = 0; i < 10 + 2; i++)
        for(int j = 0; j < 10 + 2; j++)
            g->user_field[i][j] = field[i][j];

    int x = 4, y = 2;
    int size = 2;
    int orient = vertical;
    int number = 3;
    EXPECT_EQ(0, ship_place(g, x, y, orient, size, number));

    for(int i = 0; i < 10 + 2; i++)
        for(int j = 0; j < 10 + 2; j++){
                EXPECT_EQ(field[i][j], g->user_field[i][j]);
        }

    end_game(g);
}

#endif // TEST_PLACE_SHIPS_H

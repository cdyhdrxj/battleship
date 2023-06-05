#ifndef TEST_MAIN_LOOP_H
#define TEST_MAIN_LOOP_H

#include <gtest/gtest.h>
#include "fff.h"

extern "C" {
#include "user_shoot.h"
#include "bot_shoot.h"
#include "main_loop.h"
}

DEFINE_FFF_GLOBALS;
FAKE_VOID_FUNC(bot_shooting, game *);
FAKE_VALUE_FUNC(int, user_shooting, game *);

int custom_user_shooting_fake(game *g)
{
    g->cells_left--;
    return 0;
}

void custom_bot_shooting_fake(game *g)
{
    g->bot_shoot.cells_left--;
}

TEST(shooting_loop1, pos) {
    RESET_FAKE(bot_shooting);
    RESET_FAKE(user_shooting);

    int user_return_vals[3] = {0, 0, -1};
    SET_RETURN_SEQ(user_shooting, user_return_vals, 3);

    game *g;
    g = (game *) malloc(sizeof(game));
    init_game(g);

    int winner = shooting_loop(g, user);

    EXPECT_EQ(-1, winner);
    EXPECT_EQ(user_shooting_fake.call_count, 3);
    EXPECT_EQ(bot_shooting_fake.call_count, 2);

    end_game(g);
}

TEST(shooting_loop2, pos) {
    RESET_FAKE(bot_shooting);
    RESET_FAKE(user_shooting);

    int user_return_vals[3] = {0, 0, -1};
    SET_RETURN_SEQ(user_shooting, user_return_vals, 3);

    game *g;
    g = (game *) malloc(sizeof(game));
    init_game(g);

    int winner = shooting_loop(g, bot);

    EXPECT_EQ(-1, winner);
    EXPECT_EQ(user_shooting_fake.call_count, 3);
    EXPECT_EQ(bot_shooting_fake.call_count, 3);

    end_game(g);
}

TEST(shooting_loop3, pos) {
    RESET_FAKE(bot_shooting);
    RESET_FAKE(user_shooting);

    user_shooting_fake.custom_fake = custom_user_shooting_fake;
    bot_shooting_fake.custom_fake = custom_bot_shooting_fake;

    game *g;
    g = (game *) malloc(sizeof(game));
    init_game(g);

    int winner = shooting_loop(g, user);

    EXPECT_EQ(user, winner);
    EXPECT_EQ(user_shooting_fake.call_count, 20);
    EXPECT_EQ(bot_shooting_fake.call_count, 19);

    end_game(g);
}

TEST(shooting_loop4, pos) {
    RESET_FAKE(bot_shooting);
    RESET_FAKE(user_shooting);

    user_shooting_fake.custom_fake = custom_user_shooting_fake;
    bot_shooting_fake.custom_fake = custom_bot_shooting_fake;

    game *g;
    g = (game *) malloc(sizeof(game));
    init_game(g);

    int winner = shooting_loop(g, bot);

    EXPECT_EQ(bot, winner);
    EXPECT_EQ(user_shooting_fake.call_count, 19);
    EXPECT_EQ(bot_shooting_fake.call_count, 20);

    end_game(g);
}

#endif // TEST_MAIN_LOOP_H


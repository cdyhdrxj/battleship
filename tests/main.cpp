#include <gtest/gtest.h>
#include "fff.h"

#include "test_bot_shoot.h"
#include "test_generate_bot_field.h"
#include "test_init.h"
#include "test_main_loop.h"
#include "test_place_ships.h"

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);

    return RUN_ALL_TESTS();
}

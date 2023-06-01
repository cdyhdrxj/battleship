#include <gtest/gtest.h>
#include <fff.h>
#include <stdio.h>
#include "test_place_ships.h"

int main(int argc, char *argv[])
{
    printf("%d", FIELD_SIZE);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

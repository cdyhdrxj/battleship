#ifndef TEST_INIT_H
#define TEST_INIT_H

#include <gtest/gtest.h>

extern "C" {
#include "init.h"
#include "init.c"
}

TEST(get_rows1, pos) {
    char str[] = "string\nanother string\nand another one!";
    int col = 100;

    EXPECT_EQ(3, get_rows(str, col));
}

TEST(get_rows2, pos) {
    char str[] = "string\nanother string\nand another one!";
    int col = 5;

    EXPECT_EQ(9, get_rows(str, col));
}

TEST(get_rows3, neg) {
    char str[] = "";
    int col = 5;

    EXPECT_EQ(1, get_rows(str, col));
}

TEST(get_rows4, neg) {
    char str[] = "hi, it's a string";
    int col = 0;

    EXPECT_EQ(1, get_rows(str, col));
}

TEST(init_help1, pos) {
    help *h;
    h = (help *) malloc(sizeof(help));

    int res = init_help(h);

    EXPECT_EQ(1, res);

    FILE *f;
    f = fopen(HELP_FILE, "r");

    int i = 0;
    int c;
    while((c = fgetc(f)) && h->text[i]){
        EXPECT_EQ(h->text[i], c);
        i++;
    }

    EXPECT_EQ(c, EOF);
    EXPECT_EQ(h->text[i], 0);

    fclose(f);

    free(h);
}

#endif // TEST_INIT_SHIPS_H

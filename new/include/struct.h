/**
 * @file struct.h
 * @author Laborde Quentin & Kies Remy
 * @brief
 * @date 01-08-2023
 *
 * @copyright Copyright (c) 2023
 *
 */

#ifndef __INIT_STRUCT__
#define __INIT_STRUCT__

#define NEIGHBOR(x, y)          \
    {                           \
        {(x) + 1, (y)},         \
            {(x) + 1, (y) + 1}, \
            {(x) + 1, (y)-1},   \
            {(x), (y) + 1},     \
            {(x), (y)-1},       \
            {(x)-1, (y)},       \
            {(x)-1, (y) + 1},   \
        { (x) - 1, (y)-1 }      \
    }

typedef enum {
    UNDISCOVERED,
    ONE,
    TWO,
    TREE,
    FOUR,
    FIVE,
    SIX,
    SEVEN,
    EIGHT,
    MINE,
    EXPLOSION,
    FLAG_MINE,
    FLAG,
    EMPTY
} Cell;

typedef struct {
    int seed;
    int width;
    int height;
    int cell_size;
    int mines;
    char* map;
    Cell** terrain;
    int finished;
} Game;

#endif
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
    FLAG,
    MINE,
    FLAG_MINE,
    EMPTY
} Cell;

typedef struct {
    int seed;
    int width;
    int height;
    int cell_w;
    int cell_h;
    int mines;
    Cell** terrain;
    int finished;
} Game;

#endif
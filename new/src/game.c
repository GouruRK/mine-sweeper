/**
 * @file game.c
 * @author Laborde Quentin & Kies Remy
 * @brief
 * @date 01-08-2023
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../include/game.h"

#include "../include/struct.h"

int is_in_board(int width, int height, int x, int y) {
    return ((x >= 0 && x < width) &&
            (y >= 0 && y < width));
}

int nb_mines(Game* g, int x, int y) {
    int coords[8][2] = {
        {x + 1, y},
        {x + 1, y + 1},
        {x + 1, y - 1},
        {x, y + 1},
        {x, y - 1},
        {x - 1, y},
        {x - 1, y + 1},
        {x - 1, y - 1}};
    int acc = 0;
    for (int i = 0; i < 8; i++) {
        acc += (is_in_board(g->width, g->height, coords[i][0], coords[i][1]) &&
                (g->terrain[y][x] == MINE || g->terrain[y][x] == FLAG_MINE));
    }
    return acc;
}

int brake_cell(Game* g, int x, int y) {
    if (g->terrain[y][x] == MINE) {
        g->terrain[y][x] = EXPLOSION;
        return 1;
    }
    if (g->terrain[y][x] == UNDISCOVERED) {
        int val = nb_mines(g, x, y);
        (val == 0) ? (g->terrain[y][x] = EMPTY) : (g->terrain[y][x] = val);
    }
    return 0;
}
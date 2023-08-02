/**
 * @file init.c
 * @author Laborde Quentin & Kies Remy
 * @brief
 * @date 01-08-2023
 *
 * @copyright Copyright (c) 2023
 *
 */

#include "../include/init.h"

#include <stdlib.h>

#include "../include/struct.h"

Game init_game(void) {
    Game g;
    g.cell_h = 0;
    g.cell_w = 0;

    g.width = 10;
    g.height = 10;

    g.finished = 0;
    g.mines = 10;
    g.terrain = NULL;
    return g;
}

Cell** init_board(int width, int height) {
    Cell** tab = calloc(height, sizeof(Cell*));
    if (!tab) {
        return NULL;
    }
    for (int i = 0; i < height; i++) {
        Cell* tmp = calloc(width, sizeof(Cell));
        if (!tmp) {
            free_board(tab, i);
            return NULL;
        }
        tab[i] = tmp;
    }
    return tab;
}

void free_board(Cell** tab, int line) {
    for (int i = 0; i < line; i++) {
        free(tab[i]);
    }
    free(tab);
}